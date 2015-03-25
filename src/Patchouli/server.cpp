#include "server.h"

using namespace log4cplus;
using namespace log4cplus::helpers;
using namespace log4cplus::spi;

using namespace boost::interprocess;

namespace Patchouli {
  void init_default(Logger& target, LogLevel ll) {
    /// TODO: We're on Windows so far - so consider Syslog for unix
    /// Add WinDbgAppender by default

#if defined(BOOST_WINDOWS_API)
    SharedObjectPtr<Appender> a(new Win32DebugAppender());
#else
    SharedObjectPtr<Appender> a(new FileAppender("server.log"));
#endif
    log4cplus::tstring pattern = LOG4CPLUS_TEXT("%D{%d-%m-%Y %H:%M:%S.%q} %c{2} %-5p [%l] %m%n");

    a->setLayout(std::auto_ptr<Layout>(new PatternLayout(pattern)));

    /// hack settings for root, just to avoid default console log
    Logger root = Logger::getRoot();
    root.addAppender(a);
    root.setLogLevel(log4cplus::OFF_LOG_LEVEL);

    target.addAppender(a);
    target.setLogLevel(ll);
  }

  server::server(boost::application::context& ctx, std::string _name) : ctx_(ctx) {
    this->server_name = _name;
    BasicConfigurator::doConfigure();
    logger_ = Logger::getInstance(LOG4CPLUS_TEXT("app.service"));
    init_default(logger_, log4cplus::INFO_LOG_LEVEL);
  }

  void server::worker() {
    unsigned int cnt = 0;

    boost::shared_ptr<boost::application::status> st = ctx_.find<boost::application::status>();
    while (st->state() != boost::application::status::stopped) {
      /// sleep one second...
      boost::this_thread::sleep(boost::posix_time::seconds(1));
      LOG4CPLUS_INFO(logger_, "Running worker... count=" << cnt++);
    }
  }

  int server::operator()() {
    LOG4CPLUS_INFO(logger_, "Running server class");

    //Remove shared memory on construction and destruction
    struct shm_remove {
      shm_remove() { shared_memory_object::remove("Patchouli"); }
      ~shm_remove() { shared_memory_object::remove("Patchouli"); }
    } remover;

    //Create a managed shared memory segment
    managed_shared_memory segment(create_only, "Patchouli", 65536);

    //Allocate a portion of the segment (raw memory)
    managed_shared_memory::size_type free_memory = segment.get_free_memory();
    void * shptr = segment.allocate(1024/*bytes to allocate*/);

    segment.construct<sharedString>("sharedString")(server_name.c_str(), segment.get_segment_manager());

    // launch a work thread
    boost::thread thread(&server::worker, this);

    ctx_.find<boost::application::wait_for_termination_request>()->wait();

    // to run direct
    // worker(&context);

    return 0;
  }
}
