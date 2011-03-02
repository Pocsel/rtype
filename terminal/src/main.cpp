#include "Terminal.hpp"

int main(int ac, char** av)
{
    Gmgp::Terminal::Terminal t(ac, av);
    return t.Run();
}

