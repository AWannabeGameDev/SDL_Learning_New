#include "keyboard_input.h"

void KeyboardInput::init() {

	for(size_t i = 0; i < NUM_KEYS; i++) {

		m_prevState[i] = 0;
		m_currentState[i] = 0;

	}

	m_keymap[KEY_LEFT] = SDL_SCANCODE_A;
	m_keymap[KEY_RIGHT] = SDL_SCANCODE_D;
	m_keymap[KEY_DOWN] = SDL_SCANCODE_S;
	m_keymap[KEY_UP] = SDL_SCANCODE_W;
	m_keymap[KEY_JUMP] = SDL_SCANCODE_SPACE;

}

void KeyboardInput::updateState() {

	for(size_t i = 0; i < NUM_KEYS; i++) {

		m_prevState[i] = m_currentState[i];
		const Uint8* keyStates = SDL_GetKeyboardState(nullptr);
		m_currentState[i] = keyStates[m_keymap[i]];

	}

}

bool KeyboardInput::isPressed(InputKeys key) {

	return m_currentState[key];

}

bool KeyboardInput::isJustPressed(InputKeys key) {

	return !m_prevState[key] && m_currentState[key];

}

bool KeyboardInput::isReleased(InputKeys key) {

	return !m_currentState[key];

}

bool KeyboardInput::isJustReleased(InputKeys key) {

	return m_prevState[key] && !m_currentState[key];

}