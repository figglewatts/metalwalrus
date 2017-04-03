#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H
#pragma once

#include <map>
#include <vector>

namespace metalwalrus
{
	enum class ButtonState
	{
		IDLE = 0,
		DOWN,
		HELD,
		UP
	};

	union KeyCode
	{
		unsigned char key;
		int special;
	};

	struct InputButton
	{
		bool isSpecial = false;
		int stateIndex;
		KeyCode code;
	};
	
	class InputHandler
	{
		static std::map<std::string, InputButton> inputs;
		static std::vector<ButtonState> states;
		static bool keys[256];
		static bool specials[108];

		InputHandler(); // you can't instantiate InputHandler

		static void updateButtonState(ButtonState *state, bool button);
	public:
		static void addInput(std::string name, bool isSpecial, KeyCode code);
		static bool checkButton(std::string name, ButtonState state);
		static void handleInput();
		static void updateKeys(char c, bool val);
		static void updateSpecials(int i, bool val);
	};
}

#endif // INPUTHANDLER_H