#include <iostream>

#include "udp_client.h"

namespace udp {
    int Udp_client::open(void) {
        is_open_ = false;

        if (Udp::open(client_, socket_) < 0) {
            return EXIT_FAILURE;
        }

        is_open_ = true;    

        return EXIT_SUCCESS;
    }

    int Udp_client::set_server(udp_init init) {
        if (EXIT_FAILURE == set_addr_(server_.sin_addr.s_addr, init.s_addr.c_str())) {
            return EXIT_FAILURE;
        }

        set_port_(server_.sin_port, init.port);
        set_family_(server_.sin_family, init.family);

        return EXIT_SUCCESS;
    }

    int Udp_client::recv(char *buffer, size_t buffer_len, int flags = 0) { 
        if (recvfrom(socket_, buffer, buffer_len, flags, 
                     reinterpret_cast<sockaddr *>(&client_),  
                     &sock_size_) < 0) {
            std::cerr << "sendto failed" << std::endl;
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }

    int Udp_client::send(char *buffer, size_t buffer_len, int flags = 0) {
        if (sendto(socket_, buffer, buffer_len, flags, 
                   reinterpret_cast<sockaddr *>(&server_), 
                   sock_size_) < 0) {
            std::cerr << "send failed" << std::endl;
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }
}
