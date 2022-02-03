#ifndef TCP_SERVER_INC__
#    define TCP_SERVER_INC__ 
#    ifdef __cplusplus

#        include <string.h>
#        include <string>
#        include <unistd.h>

#        include "tcp.h"

namespace tcp {
    class Tcp_server : public Tcp {
    public:
        Tcp_server(tcp_init init) : Tcp(sin_server_, init, server_fd_) {
            sockaddr_in_size = sizeof(sockaddr_in);
            memset(&sin_client_, 0, sockaddr_in_size);
        }
        
        ~Tcp_server(void) {
             close(server_fd_);
         }

        int set_addr(std::string s_addr){
            return set_addr_(sin_server_.sin_addr.s_addr, s_addr.c_str());
        } 
        
        void set_port(uint16_t port) {
            set_port_(sin_server_.sin_port, port);
        } 
        
        void set_family(uint16_t family) {
            set_family_(sin_server_.sin_family, family);
        }
        
        int open(size_t queue_lenght);
        
        bool is_open(void){
            return is_open_;
        }
        
        int get_server_fd(void) {
            return server_fd_;
        }
        
        int get_client_fd(void) {
            return client_fd_;
        }
        
        int get_connection(void) {
            client_fd_ = accept(server_fd_, reinterpret_cast<sockaddr *>(&sin_client_), &sockaddr_in_size);
            
            if (-1 == client_fd_) {
                close(server_fd_);
            }
            
            return client_fd_;
        }
        
        int recv(char *buffer, size_t buffer_len);
        int send(char *buffer, size_t buffer_len);
        
        
    
    private:
        int server_fd_;
        int client_fd_;
        
        sockaddr_in sin_client_;
        sockaddr_in sin_server_;
        
        bool is_open_;
        unsigned int sockaddr_in_size;
    };
}

#    endif // __cplusplus 
#endif // TCP_SERVER_INC__
