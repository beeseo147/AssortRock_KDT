#include "Logging/Logger.h"

#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/utility/setup/console.hpp>

namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace attrs = boost::log::attributes;
namespace keywords = boost::log::keywords;
FLogger GLogger("GLog");

FLogger::FLogger(std::string_view InLogFileName)
	: LogFileName(InLogFileName)
{
	logging::add_common_attributes();

	logging::add_file_log
	(
		keywords::auto_flush = true,
		keywords::open_mode = (std::ios::out | std::ios::app),
		keywords::target = "Logs",
		keywords::max_files = 256,	// 최대 저장 파일 수
		keywords::file_name = LogFileName + "_%Y-%m-%d_%H-%M-%S.%N.log",
		keywords::rotation_size = 10 * 1024 * 1024,
		// 재생성 시점 (일 변경시)
		keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
		keywords::format =
		(
			expr::stream
			<< expr::attr< unsigned int >("LineID") << ": "
			<< expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S")
			<< ": <" << logging::trivial::severity
			<< "> " << expr::smessage
			)
	);
	logging::add_console_log(std::cout, boost::log::keywords::format = (
		expr::stream
		<< expr::attr< unsigned int >("LineID") << ": "
		<< expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S")
		<< ": <" << logging::trivial::severity
		<< "> " << expr::smessage
		));

	Log(FLogLevel::trace, LogFileName);
}

void FLogger::Log(FLogLevel InLogLevel, std::string_view InMessage)
{
	switch (InLogLevel)
	{
	case boost::log::trivial::trace:
		BOOST_LOG_TRIVIAL(trace) << InMessage;
		break;
	case boost::log::trivial::debug:
		BOOST_LOG_TRIVIAL(debug) << InMessage;
		break;
	case boost::log::trivial::info:
		BOOST_LOG_TRIVIAL(info) << InMessage;
		break;
	case boost::log::trivial::warning:
		BOOST_LOG_TRIVIAL(warning) << InMessage;
		break;
	case boost::log::trivial::error:
		BOOST_LOG_TRIVIAL(error) << InMessage;
		_ASSERT(false);
		break;
	case boost::log::trivial::fatal:
		BOOST_LOG_TRIVIAL(fatal) << InMessage;
		_ASSERT(false);
		break;
	default:
		_ASSERT(false);
		break;
	}
}
