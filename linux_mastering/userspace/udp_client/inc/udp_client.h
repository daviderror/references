#ifndef UDP_CLIENT
#    define UDP_CLIENT

#    ifdef __cplusplus

#    include <string.h>
#    include <unistd.h> 

#        include "udp.h"

namespace udp {
    class Udp_client : public Udp {
    public:
        Udp_client(udp_init init) : Udp(client_, init, socket_) { 
            is_open_ = false;
            sock_size_ = sizeof(sockaddr_in);
            memset(&server_, 0, sizeof (sockaddr_in));
        }

        ~Udp_client(void) {
            close(socket_);
        }

        int set_addr(std::string s_addr) {
            return set_addr_(client_.sin_addr.s_addr, s_addr.c_str());
        } 

        void set_port(uint16_t port) {
            set_port_(client_.sin_port, port);
        } 

        void set_family(uint16_t family) {
            set_family_(client_.sin_family, family);
        }

        int open(void);

        bool is_open(void) {
            return is_open_;
        }

        int set_server(udp_init init);

        int set_server_addr(std::string s_addr) {
            return set_addr_(server_.sin_addr.s_addr, s_addr.c_str());
        } 

        void set_server_port(uint16_t port) {
            set_port_(server_.sin_port, port);
        }

        void set_server_family(uint16_t family) {
            set_family_(server_.sin_family, family);
        } 

        int send(char *buffer, size_t buffer_len, int flags);
        int recv(char *buffer, size_t buffer_len, int flags);
    private:
        int socket_;
        socklen_t sock_size_;
        sockaddr_in client_;
        sockaddr_in server_;
        bool is_open_;
    };
}

#    endif // __cplusplus
#endif //UDP_CLIENT
