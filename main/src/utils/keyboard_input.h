#ifndef KEYBOARD_INPUT_H
#define KEYBOARD_INPUT_H

#include <SDL.h>

class KeyboardInput {

public:

	enum InputKeys {

		KEY_LEFT,
		KEY_RIGHT,
		KEY_DOWN,
		KEY_UP,
		KEY_JUMP,
		NUM_KEYS

	};

private :

	inline static Uint8 m_prevState[NUM_KEYS];
	inline static Uint8 m_currentState[NUM_KEYS];

	inline static SDL_Scancode m_keymap[NUM_KEYS];

public :

	static void init();
	static void updateState();

	static bool isPressed(InputKeys key);
	static bool isJustPressed(InputKeys key);
	static bool isReleased(InputKeys key);
	static bool isJustReleased(InputKeys key);

};

#endif