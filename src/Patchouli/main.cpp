#include <boost/program_options.hpp>
#include <boost/application.hpp>

#include <log4cplus/logger.h>
#include <log4cplus/loglevel.h>
#include <log4cplus/configurator.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/win32debugappender.h>
#include <log4cplus/nullappender.h>
#include <log4cplus/helpers/property.h>

// provide setup example for windows service
#if defined(BOOST_WINDOWS_API)
#   include "setup/windows/setup/service_setup.hpp"
#endif

using namespace log4cplus;
using namespace log4cplus::helpers;
using namespace log4cplus::spi;

void init_default(Logger& target, LogLevel ll) {
  // TODO: We're on Windows so far - so consider Syslog for unix
  // Add WinDbgAppender by default

  SharedObjectPtr<Appender> a(new Win32DebugAppender());
  log4cplus::tstring pattern = LOG4CPLUS_TEXT("%D{%d-%m-%Y %H:%M:%S.%q} %c{2} %-5p [%l] %m%n");

  a->setLayout(std::auto_ptr<Layout>(new PatternLayout(pattern)));

  // hack settings for root, just to avoid default console log
  Logger root = Logger::getRoot();
  root.addAppender(a);
  root.setLogLevel(log4cplus::OFF_LOG_LEVEL);

  target.addAppender(a);
  target.setLogLevel(ll);
}


namespace po = boost::program_options;

class server {
public:
  server(boost::application::context& ctx)
    : ctx_(ctx) {
    BasicConfigurator::doConfigure();
    logger_ = Logger::getInstance(LOG4CPLUS_TEXT("app.service"));
    init_default(logger_, log4cplus::INFO_LOG_LEVEL);
  }

  void worker() {
    unsigned int cnt = 0;

    boost::shared_ptr<boost::application::status> st = ctx_.find<boost::application::status>();
    while(st->state() != boost::application::status::stopped) {
      // sleep one second...
      boost::this_thread::sleep(boost::posix_time::seconds(1));
      LOG4CPLUS_INFO(logger_, "Running worker... count=" << cnt++);

    }
  }

  int operator()() {
    LOG4CPLUS_INFO(logger_, "Running server class");

    // launch a work thread
    boost::thread thread(&server::worker, this);

    ctx_.find<boost::application::wait_for_termination_request>()->wait();

    // to run direct
    // worker(&context);

    return 0;
  }

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

private:
  boost::application::context& ctx_;
  Logger logger_;
};

bool setup(boost::application::context& context, bool& is_service)
{
  boost::strict_lock<boost::application::aspect_map> guard(context);

  boost::shared_ptr<boost::application::args> myargs
    = context.find<boost::application::args>(guard);

  boost::shared_ptr<boost::application::path> mypath
    = context.find<boost::application::path>(guard);


  // provide setup for windows service
#if defined(BOOST_WINDOWS_API)
#if !defined(__MINGW32__)

  // get our executable path name
  boost::filesystem::path executable_path_name = mypath->executable_path_name();

  // define our simple installation schema options
  po::options_description install("service options");
  install.add_options()
    ("help", "produce a help message")
    (",i", "install service")
    (",u", "unistall service")
    (",c", "run on console")
    ("name", po::value<std::string>()->default_value(mypath->executable_name().stem().string()), "service name")
    ("display", po::value<std::string>()->default_value(""), "service display name (optional, installation only)")
    ("description", po::value<std::string>()->default_value(""), "service description (optional, installation only)")
    ;

  po::variables_map vm;
  po::store(po::parse_command_line(myargs->argc(), myargs->argv(), install), vm);
  boost::system::error_code ec;

  if (vm.count("help")) {
    std::cout << install << std::cout;
    return true;
  }

  if (vm.count("-c")) {
    is_service = false;
    return false;
  }


  if (vm.count("-i")) {
    boost::application::example::install_windows_service(
      boost::application::setup_arg(vm["name"].as<std::string>()),
      boost::application::setup_arg(vm["display"].as<std::string>()),
      boost::application::setup_arg(vm["description"].as<std::string>()),
      boost::application::setup_arg(executable_path_name)).install(ec);

    std::cout << ec.message() << std::endl;

    return true;
  }

  if (vm.count("-u")) {
    boost::application::example::uninstall_windows_service(
      boost::application::setup_arg(vm["name"].as<std::string>()),
      boost::application::setup_arg(executable_path_name)).uninstall(ec);
    std::cout << ec.message() << std::endl;

    return true;
  }
#endif
#endif

  return false;
}


int main(int argc, char *argv[]) {
  BasicConfigurator::doConfigure();
  Logger logger = Logger::getInstance(LOG4CPLUS_TEXT("boost.app.log4cplus"));
  init_default(logger, log4cplus::INFO_LOG_LEVEL);

  LOG4CPLUS_INFO(logger, "Running boost::application example");

  boost::application::context app_context;
  server app(app_context);

  // my server aspects
  app_context.insert<boost::application::path>(
    boost::make_shared<boost::application::default_path>());

  app_context.insert<boost::application::args>(
    boost::make_shared<boost::application::args>(argc, argv));

  // add termination handler
  boost::application::handler<>::callback termination_callback
    = boost::bind<bool>(&server::stop, &app);

  app_context.insert<boost::application::termination_handler>(
    boost::make_shared<boost::application::termination_handler_default_behaviour>(termination_callback));

  // To  "pause/resume" works, is required to add the 2 handlers.
#if defined(BOOST_WINDOWS_API)
  // windows only : add pause handler
  boost::application::handler<>::callback pause_callback
    = boost::bind<bool>(&server::pause, &app);

  app_context.insert<boost::application::pause_handler>(
    boost::make_shared<boost::application::pause_handler_default_behaviour>(pause_callback));

  // windows only : add resume handler
  boost::application::handler<>::callback resume_callback
    = boost::bind<bool>(&server::resume, &app);

  app_context.insert<boost::application::resume_handler>(
    boost::make_shared<boost::application::resume_handler_default_behaviour>(resume_callback));
#endif

  bool is_service = true;

  if(setup(app_context, is_service)) {
    std::cout << "[I] Setup changed the current configuration." << std::endl;
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

  if(ec) {
    // log...
    std::cout << "[E] " << ec.message()
      << " <" << ec.value() << "> " << std::cout;
  }

  return result;
}