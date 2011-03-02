
#include <string>
#include <iostream>

#include "Console.hpp"
#include "String.hpp"

std::string f()
{
  return "f()";
}

std::string f1(int i)
{
  return "f1(" + Rt::String(i) + ")";
}

class A
{
  public:
    static std::string m()
    {
      return "m()";
    }


};

class Server
{
  public:
    int start(int port, int nb_thread = 10)
    {
      std::cout << "Server started on port " << port
		<< " with " << nb_thread << " threads" << std::endl;
      return 0;
    }

    int stop(void)
    {
      std::cout << "Server stopped" << std::endl;
      return 0;
    }
};

int main()
{
  Server s;
  Gmgp::Server::Console console;
  console.bind("f", f, "static function test");
  console.bind("m", &A::m, "static member method test");
  console.bind("f1", f1, "static function with 1 param test");
  console.bind("start", s, &Server::start, "start the server (port nb_thread)");
  console.bind("stop", s, &Server::stop, "stop the server");

  char cmdline[512];
  std::cout << "# SpriteServ 0.1" << std::endl
	    << "# type 'help' for a list of commands" << std::endl;
  while (true)
  {
    std::cout << "$> ";
    std::cin.getline(cmdline, sizeof(cmdline) * sizeof(char));
    if (std::cin.fail() || std::string(cmdline) == "quit")
    {
      std::string res = console.sendLine("quit");
      if (res.size() > 0)
	std::cout << " -> " << res << std::endl;
      break;
    }
    Gmgp::Server::String cmd(cmdline);
    cmd.ltrim();
    if (cmd.size() > 0)
    {
      std::string res = console.sendLine(cmd);
      if (res.size() > 0)
	std::cout << " -> " << res << std::endl;
    }
  }
}

