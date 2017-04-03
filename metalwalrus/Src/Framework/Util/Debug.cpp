#include "Debug.h"

#include <fstream>
#include <iostream>
#include <cerrno>

namespace metalwalrus
{
	std::ofstream Debug::logFile;
	double Debug::frameTime = 0;
	int Debug::lastDrawCalls = 0;
	int Debug::drawCalls = 0;
	double Debug::fps = 0;
	bool Debug::debugMode = 0;
	
	void Debug::log(const char *message, LogType type)
	{
		char *typeString;
		switch (type)
		{
			case LogType::WARNING:
			{
				typeString = "Warning: ";
			} break;
			case LogType::ERR:
			{
				typeString = "Error: ";
			} break;
			case LogType::FATAL:
			{
				typeString = "Fatal: ";
			} break;
			default:
			{
				typeString = "Log: ";
			} break;
		}

		std::clog << typeString << message << std::endl;
	}

	bool Debug::redirect(char *logFilePath)
	{
		logFile.open(logFilePath);
		if (!logFile.is_open())
		{
			std::cerr << "Redirecting log output failed.";
			return false;
		}
		std::clog.rdbuf(logFile.rdbuf());
		return true;
	}

	Debug::~Debug()
	{
		logFile.close();
	}
}