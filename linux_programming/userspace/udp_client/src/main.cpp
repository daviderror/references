#include <iostream>

#include "udp_client.h"

int main(int argc, char **argv) {
    constexpr size_t c_buf_size = 18;
    
    char buf [c_buf_size] = "hello from client" ;
    
    udp::udp_init init = {"127.0.0.2", 8080, AF_INET},
                  server = {"127.0.0.1", 8080, AF_INET};
                  
    udp::Udp_client client(init);
    client.set_server(server);
    
    if (0 != client.open()) {
        std::cerr << "client open failed" << std::endl;
    }

    if ( 0 != client.send(buf, c_buf_size, 0)) {
        std::cerr << "send failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    client.recv(buf, c_buf_size, 0);
    
    std::cout << buf << std::endl;
    
    exit(EXIT_SUCCESS);
}
