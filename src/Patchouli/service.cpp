#include "service.h"

#include <boost/program_options.hpp>
/// provide setup example for windows service
#if defined(BOOST_WINDOWS_API)
#   include "setup/windows/setup/service_setup.hpp"
#endif

using namespace log4cplus;
namespace po = boost::program_options;

namespace Patchouli {

  bool setup(boost::application::context& context, bool& is_service, const std::string service_name) {
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
      ("version", "show version")
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

    if (vm.count("version")) {
      std::cout << service_name << std::endl;
      return true;
    }

    if (vm.count("help")) {
      std::cout << install << std::endl;
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
#else
   boost::filesystem::path executable_path_name = mypath->executable_path_name();

   // define our simple installation schema options
   po::options_description install("service options");
   install.add_options()
      ("help", "produce a help message")
      (",c", "run on console")
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
#endif

    return false;
  }
}
