#include "InputHandler.h"

namespace metalwalrus
{
	std::map<std::string, InputButton> InputHandler::inputs;
	std::vector<ButtonState> InputHandler::states;
	bool InputHandler::keys[256] = {};
	bool InputHandler::specials[108] = {};
	
	void InputHandler::updateButtonState(ButtonState* state, bool button)
	{
		if (button)
		{
			if (*state == ButtonState::DOWN)
				*state = ButtonState::HELD;
			else if (*state != ButtonState::HELD)
				*state = ButtonState::DOWN;
		}
		else
		{
			if (*state != ButtonState::UP
				&& (*state == ButtonState::DOWN
					|| *state == ButtonState::HELD))
				*state = ButtonState::UP;
			else
				*state = ButtonState::IDLE;
		}
	}
	
	void InputHandler::addInput(std::string name, bool isSpecial, KeyCode code)
	{
		InputButton b;
		b.isSpecial = isSpecial;
		b.code = code;
		b.stateIndex = states.size();
		states.push_back(ButtonState::IDLE);
		inputs[name] = b;
	}

	bool InputHandler::checkButton(std::string name, ButtonState state)
	{
		return states[inputs[name].stateIndex] == state;
	}

	void InputHandler::handleInput()
	{
		for (const auto& val : inputs)
		{
			InputButton button = val.second;
			ButtonState *state = &states[button.stateIndex];
			
			if (button.isSpecial)
				updateButtonState(state, specials[button.code.special]);
			else
				updateButtonState(state, keys[button.code.key]);
		}
	}

	void InputHandler::updateKeys(char c, bool val)
	{
		keys[c] = val;
	}

	void InputHandler::updateSpecials(int i, bool val)
	{
		specials[i] = val;
	}
}