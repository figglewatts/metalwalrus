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

	public:
		enum class LogType
		{
			MESSAGE,
			WARNING,
			ERR,
			FATAL
		};

		static void log(const char *message, LogType type = LogType::MESSAGE);
		static bool redirect(char *logFilePath);

		~Debug();

		
	};
}
#endif