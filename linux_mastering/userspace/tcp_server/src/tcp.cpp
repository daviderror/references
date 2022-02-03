#include <string.h>
#include <iostream>

#include "tcp.h"

namespace tcp {
    Tcp::Tcp(sockaddr_in &sock_addr, tcp_init &init, int &socket_fd) {
        
        int on = 1;
        
        socket_fd = socket(init.family, SOCK_STREAM, IPPROTO_TCP);
        
        // exeption is needed
        if (-1 == socket_fd){
            std::cerr << "socket() failed" << std::endl;
            exit(EXIT_FAILURE);
        }
        
        if (true == init.is_addr_reused) {
            if (setsockopt(socket_fd, SOL_SOCKET,  SO_REUSEADDR,
                                        (char *)&on, sizeof(on)) < 0)
            {
                std::cerr << "setsockopt() failed" << std::endl;
                close(socket_fd);
                exit(EXIT_FAILURE);
            }
        }
 /*           
        if (ioctl(socket_fd, FIONBIO, (char *)&on) < 0)
        {
            std::cerr << "ioctl() failed" << std::endl;
            close(socket_fd);
            exit(EXIT_FAILURE);
        }
*/ 
        memset(&sock_addr, 0, sizeof (sockaddr_in));
        
        if (EXIT_FAILURE == set_addr_(sock_addr.sin_addr.s_addr, init.s_addr.c_str())) {
            exit(EXIT_FAILURE);
        }
              
        set_port_(sock_addr.sin_port, init.port);
        set_family_(sock_addr.sin_family, init.family);
    }
    
    int Tcp::open(sockaddr_in &sock_addr, int &socket_fd, size_t queue_lenght) {
        if ((bind(socket_fd, (const sockaddr *) &sock_addr, sizeof(sockaddr_in))) < 0) {
            std::cerr << "bind() failed" << std::endl;
            return EXIT_FAILURE;
        }
         
        if (listen(socket_fd, queue_lenght) < 0) {
            std::cerr << "listen() failed" << std::endl;
            close(socket_fd);
            exit(EXIT_FAILURE);
        }
        
      
        return EXIT_SUCCESS;
    }
    
    int Tcp::set_addr_(uint32_t &addr, const char *c_addr){
        if (NULL == c_addr) {
            std::cerr << "IP address is empty" << std::endl;
            return EXIT_FAILURE;
        }
        
        addr = inet_addr(c_addr); 

        return EXIT_SUCCESS;
    }
}
