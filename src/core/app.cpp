#include <exception>
#include <execinfo.h>
#include <signal.h>
#include <unistd.h>

#include "app.h"
#include <dotenv.h>

void app_printStacktrace()
{
  void *array[20];
  size_t size = backtrace(array, sizeof(array) / sizeof(array[0]));
  backtrace_symbols_fd(array, size, STDERR_FILENO);
}

void app_signalHandler(int sig)
{
  std::fprintf(stderr, "Error: signal %d\n", sig);
  app_printStacktrace();
  std::abort();
}

void app_terminateHandler()
{
  std::exception_ptr exptr = std::current_exception();
  if (exptr != 0)
  {
    // the only useful feature of std::exception_ptr is that it can be rethrown...
    try
    {
      std::rethrow_exception(exptr);
    }
    catch (std::exception &ex)
    {
      std::fprintf(stderr, "Terminated due to exception: %s\n", ex.what());
    }
    catch (...)
    {
      std::fprintf(stderr, "Terminated due to unknown exception\n");
    }
  }
  else
  {
    std::fprintf(stderr, "Terminated due to unknown reason :(\n");
  }
  app_printStacktrace();
  std::abort();
}


namespace Core {
  std::string App::read_env(std::string name, std::string _default){
    std::string v = dotenv::env[name];
    //std::string v = "";
    return v.empty() ? _default : v; 
  }
  void App::app_init(){
    signal(SIGSEGV, app_signalHandler);
    std::set_terminate(app_terminateHandler);
  }
}

