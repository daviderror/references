#include <iostream>

#include "tcp_server.h"




int main(int argc, char **argv) {
    
    tcp::tcp_init init = {};
    
    char buf [100] = {};
    
    std::string addr {"127.0.0.1"};
    
    init.family = AF_INET;
    init.is_addr_reused = false;
    init.port = 5000;
    init.s_addr = addr;
    
    tcp::Tcp_server tcp_ser(init);
    
    tcp_ser.open(5);
    
    std::cout << tcp_ser.is_open() << std::endl;
    
    if (-1 == tcp_ser.get_connection()) {
        std::cout << "get_connection()" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    while(true) {
        tcp_ser.recv(buf, 100);
        std::cout << buf << std::endl;
        memset(buf, 0, 100);
    }
    
    
    return 0 ;
}
