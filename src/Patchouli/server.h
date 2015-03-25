#pragma once

#include "stdafx.h"
#include <boost/application.hpp>

#include <log4cplus/logger.h>
#include <log4cplus/loglevel.h>
#include <log4cplus/configurator.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/win32debugappender.h>
#include <log4cplus/nullappender.h>
#include <log4cplus/helpers/property.h>
#include <log4cplus/fileappender.h>

using namespace log4cplus;
using namespace log4cplus::helpers;
using namespace log4cplus::spi;

namespace Patchouli {
  void init_default(Logger& target, LogLevel ll);
  class server {
  public:
    server(boost::application::context& ctx, std::string _name);

    void worker();

    int operator()();

    bool stop() {
      LOG4CPLUS_INFO(logger_, "Stop server class");
      return true;
    }

    bool pause() {
      LOG4CPLUS_INFO(logger_, "Pause server class");
      return true;
    }

    bool resume() {
      LOG4CPLUS_INFO(logger_, "Resume server class");
      return true;
    }
  protected:
    std::string server_name;
    Logger logger_;

  private:
    boost::application::context& ctx_;
  };
}
