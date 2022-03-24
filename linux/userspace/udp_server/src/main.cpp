#include <iostream>

#include "udp_server.h"


int main(int argc, char **argv) {
    
    char buf [10] = {};
    udp::udp_init init = {};
    
    init.family = AF_INET;
    init.port = 8080;
    init.s_addr = "127.0.0.1";
    
    udp::Udp_server server(init);
    
     if (0 != server.open()) {
         std::cout << "open failes" << std::endl;
         exit (EXIT_FAILURE);
     }
    
     if (true != server.is_open()) {
         std::cout << "server was not opend" << std::endl;
         exit (EXIT_FAILURE);
     }
    
    
    server.recv(buf, 18, 0);
        
    std::cout << buf << std::endl;
    
    exit (EXIT_SUCCESS);
}
