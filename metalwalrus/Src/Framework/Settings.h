#ifndef SETTINGS_H
#define SETTINGS_H
#pragma once

namespace metalwalrus
{
	class Settings
	{
		Settings();
	public:
		static int WIDTH;
		static int HEIGHT;
		static int TARGET_WIDTH;
		static int TARGET_HEIGHT;
		static int VIRTUAL_WIDTH;
		static int VIRTUAL_HEIGHT;
		static int VIEWPORT_WIDTH;
		static int VIEWPORT_HEIGHT;
		static int VIEWPORT_X;
		static int VIEWPORT_Y;
	};
}
#endif