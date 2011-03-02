#include <stdexcept>
#include <iostream>
#include "Thread.hpp"

void f()
{
    std::cout << "f()" << std::endl;
}

int main(void)
{
    Gmgp::Server::Thread t(b00st::bind(f));
    t.Join();
    return (0);
}
