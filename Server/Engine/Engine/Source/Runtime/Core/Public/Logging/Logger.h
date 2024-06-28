#pragma once
#include "CoreTypes.h"

using FLogLevel = boost::log::trivial::severity_level;

// Thread-Safe logger
class CORE_API FLogger
{
public:
	FLogger(std::string_view InLogFileName);
	FLogger(const FLogger&) = delete;
	FLogger& operator=(const FLogger&) = delete;

	void Log(FLogLevel InLogLevel, std::string_view InMessage);

private:
	const std::string LogFileName;
};

extern CORE_API FLogger GLogger;
#define E_Log(LogLevel, FormatMsg, ...) GLogger.Log(FLogLevel::LogLevel, std::string(__FUNCTION__) + ": " + std::format(FormatMsg, __VA_ARGS__));