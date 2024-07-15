#pragma once
#include "EngineMinimal.h"

// boost
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using FSocket = boost::asio::ip::tcp::socket;