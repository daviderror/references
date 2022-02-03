#ifndef UDP_SERVER
#    define UDP_SERVER

#    ifdef __cplusplus

#        include <unistd.h>
#        include <string.h>

#        include "udp.h"

namespace udp {
    class Udp_server : public Udp {
    public:
        Udp_server(udp_init init) : Udp(server_, init, socket_) { 
            sockaddr_in_size = sizeof(sockaddr_in);
            memset(&client_, 0, sockaddr_in_size);
        }
        
        ~Udp_server(void) {
            close(socket_);
        }
    
        
        int set_addr(std::string s_addr){
            return set_addr_(server_.sin_addr.s_addr, s_addr.c_str());
        } 
        
        void set_port(uint16_t port) {
            set_port_(server_.sin_port, port);
        } 
        
        void set_family(uint16_t family) {
            set_family_(server_.sin_family, family);
        } 
        
        int open(void);
        
        bool is_open(void){
            return is_open_;
        }
        
        int recv(char *buffer, size_t buffer_len, int flags);
        int send (char *buffer, size_t buffer_len, int flags);
    private:
        int socket_;
        sockaddr_in server_;
        sockaddr_in client_;
        bool is_open_;
        unsigned int sockaddr_in_size;
    };
}

#    endif //__cplusplus 
#endif //UDP_SERVER
