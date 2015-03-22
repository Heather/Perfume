#define app_name "Patchouli 0.0.1"

#include "service.h"

using namespace log4cplus;
using namespace log4cplus::helpers;
using namespace log4cplus::spi;

using namespace Patchouli;

int main(int argc, char *argv[]) {
  BasicConfigurator::doConfigure();
  Logger logger = Logger::getInstance(LOG4CPLUS_TEXT("boost.app.log4cplus"));
  init_default(logger, log4cplus::INFO_LOG_LEVEL);

  boost::application::context app_context;
  server app(app_context, app_name);

  // my server aspects
  app_context.insert<boost::application::path>(
    boost::make_shared<boost::application::default_path>());

  app_context.insert<boost::application::args>(
    boost::make_shared<boost::application::args>(argc, argv));

  // add termination handler
  boost::application::handler<>::callback termination_callback
#if (BOOST_VERSION > 105700)
    = boost::bind(&server::stop, &app);
#else
    = boost::bind<bool>(&server::stop, &app);
#endif

  app_context.insert<boost::application::termination_handler>(
    boost::make_shared<boost::application::termination_handler_default_behaviour>(termination_callback));

  // To  "pause/resume" works, is required to add the 2 handlers.
#if defined(BOOST_WINDOWS_API)
  // windows only : add pause handler
  boost::application::handler<>::callback pause_callback
#if (BOOST_VERSION > 105700)
    = boost::bind(&server::pause, &app);
#else
    = boost::bind<bool>(&server::pause, &app);
#endif

  app_context.insert<boost::application::pause_handler>(
    boost::make_shared<boost::application::pause_handler_default_behaviour>(pause_callback));

  // windows only : add resume handler
  boost::application::handler<>::callback resume_callback
#if (BOOST_VERSION > 105700)
    = boost::bind(&server::resume, &app);
#else
    = boost::bind<bool>(&server::resume, &app);
#endif

  app_context.insert<boost::application::resume_handler>(
    boost::make_shared<boost::application::resume_handler_default_behaviour>(resume_callback));
#endif

  bool is_service = true;

  if (setup(app_context, is_service)) {
    LOG4CPLUS_INFO(logger, "Setup changed the current configuration");
    return 0;
  }

  // my server instantiation
  boost::system::error_code ec;

  int result = 0;
  if (is_service) {
    result = boost::application::launch<boost::application::server>(app, app_context, ec);
  } else {
    std::cout << "Running as console application..." << std::endl;
    result = boost::application::launch<boost::application::common>(app, app_context, ec);
  }

  if (ec) {
    // log...
    std::cout << "[E] " << ec.message()
      << " <" << ec.value() << "> " << std::endl;
  }

  return result;
}
