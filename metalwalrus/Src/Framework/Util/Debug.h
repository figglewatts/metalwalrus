#ifndef DEBUG_H
#define DEBUG_H
#pragma once

#include <fstream>

namespace metalwalrus
{
	class Debug
	{
		Debug(); // static class
		static std::ofstream logFile;

		static int lastDrawCalls;
		static int drawCalls;
	public:
		static double frameTime;
		static double fps;
		static bool debugMode;
		
		enum class LogType
		{
			MESSAGE,
			WARNING,
			ERR,
			FATAL
		};

		static void log(const char *message, LogType type = LogType::MESSAGE);
		static bool redirect(char *logFilePath);

		inline static int get_drawCalls() { return lastDrawCalls; }
		inline static void set_drawCalls(int dc)
		{
			lastDrawCalls = drawCalls;
			drawCalls = dc;
		}

		~Debug();

		
	};
}
#endif