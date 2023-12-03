#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <SDL.h>
#include "utils/sdloo.h"
#include <iostream>
#include "utils/tilemap/tilemap_include.h"
#include "utils/timer.h"
#include "utils/constants.h"
#include "entities/player.h"
#include "utils/keyboard_input.h"
#include "utils/my_collision_listener.h"

//FIX THE TILE RENDER GLITCH LINES

class GameLoop {

private:

	inline static bool running;

public:

	static void setRunning(bool run) {

		running = run;

	}

	static void init() {

		if(SDL_Init(SDL_INIT_VIDEO) < 0) {

			std::cout << "SDL video system Error : " << SDL_GetError();
			running = false;

		} else if(IMG_Init(IMG_INIT_PNG) < 0) {

			std::cout << "IMG Error : " << SDL_GetError();
			running = false;

		} else {

			running = true;
			KeyboardInput::init();

		}

	}

	static void loadLevelBodies(TileMap& map, cle::CollisionListener& collisionListener) {

		ObjectLayer& layer = map.getObjectLayer("statics");

		for(size_t i = 0; i < layer.size(); i++) {

			RectangleMapObject& rectObj = layer.getObject(i).get<RectangleMapObject>();

			cle::Collider* coll = collisionListener.addCollider(false);
			coll->aabb = {rectObj.x, rectObj.y, rectObj.width, rectObj.height};

		}

	}

	static SDL_FRect loadLevelBorder(TileMap& map) {

		ObjectLayer& layer = map.getObjectLayer("meta_info");
		RectangleMapObject& rectObj = layer.getObject("border").get<RectangleMapObject>();
		return {rectObj.x, rectObj.y, rectObj.width, rectObj.height};

	}

	static void run() {

		SDLOO::Window window {"First", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
			1280, 720, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE};
		SDLOO::Renderer renderer {window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC, 
								  16 * 20, 16 * 11.25f};
		renderer.setCameraPosition(-32.f, -32.f);

		Timer timer;
		MyCollisionListener collisionListener;

		TileMap level {"graybox/level0.tmx", renderer};
		SDL_FRect levelBorder = loadLevelBorder(level);
		loadLevelBodies(level, collisionListener);

		PointMapObject& spawn = level.getObjectLayer("meta_info")
			.getObject("spawn").get<PointMapObject>();
		Player player {spawn.x, spawn.y, collisionListener, renderer};

		while(running) {

			float deltaTime = timer.elapsed();

			SDL_Event ev;
			while(SDL_PollEvent(&ev)) {

				if(ev.type == SDL_WINDOWEVENT) {

					if(ev.window.event == SDL_WINDOWEVENT_RESIZED) renderer.updateView();

				} else if(ev.type == SDL_QUIT) {

					setRunning(false);

				}

			}

			KeyboardInput::updateState();

			player.update(deltaTime);
			collisionListener.checkCollisions();
			player.centerCamera(renderer, levelBorder);

			// RENDER -----------------

			timer.reset();
			renderer.clear();

			level.render(renderer, 0, 0);
			player.render(renderer);

			renderer.setDrawColor(255, 0, 0, 255);
			for(auto it = collisionListener.resolvedBegin(); it != collisionListener.resolvedEnd(); ++it) {

				SDL_FRect rect {it->aabb.x, it->aabb.y, it->aabb.w, it->aabb.h};
				renderer.drawRect(rect);

			}

			for(auto it = collisionListener.unresolvedBegin(); it != collisionListener.unresolvedEnd(); ++it) {

				SDL_FRect rect{it->aabb.x, it->aabb.y, it->aabb.w, it->aabb.h};
				renderer.drawRect(rect);

			}

			renderer.renderPresent();

		}

	}

	static void close() {

		SDL_Quit();
		IMG_Quit();

	}

};

#endif