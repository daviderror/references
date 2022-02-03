#ifndef UDP
#    define UDP

#    ifdef __cplusplus

#        include <arpa/inet.h>
#        include <sys/socket.h>
#        include <string>

namespace udp {
    typedef struct  {
        std::string s_addr;
        uint16_t port;
        int family;
    } udp_init;

    class Udp {
    public:
        Udp(sockaddr_in &udp, udp_init init, int &socket_hnd);
    //    ~Udp();
        int open(sockaddr_in &udp_sock, int &socket_d);
        
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
