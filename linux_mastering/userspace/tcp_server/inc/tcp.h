#ifndef TCP_INC__
#    define TCP_INC__ 
#    ifdef __cplusplus

#    include <sys/socket.h>
#    include <arpa/inet.h>
#    include <unistd.h>

namespace tcp {
    typedef struct  {
        std::string s_addr;
        uint16_t port;
        int family;
        bool is_addr_reused;
    } tcp_init;
    
    class Tcp {
    public:
        Tcp(sockaddr_in &sock_addr, tcp_init &init, int &socket_fd);
        
//        ~Tcp();
        
        int open(sockaddr_in &sock_addr, int &socket_fd, size_t queue_lenght) ;
        
    protected:         
        int set_addr_(uint32_t &addr, const char* c_addr);
        
        void set_port_(uint16_t &port, uint16_t port_num) {
            port = htons(port_num);
        }
        
        void set_family_(uint16_t &family, uint16_t family_type) {
            family = family_type;
        }
        
        
    };
}
#    endif
#endif
