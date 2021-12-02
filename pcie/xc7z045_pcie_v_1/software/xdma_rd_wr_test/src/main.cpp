#include <iostream>
#include <fcntl.h>
#include <unistd.h>

constexpr const char *h2c = "/dev/xdma0_h2c_0";
constexpr const char *c2h = "/dev/xdma0_c2h_0";

constexpr const size_t buffer_size = 10;

int main() {
    
    uint8_t h2c_buffer[buffer_size]{0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39},
            c2h_buffer[buffer_size]{};    
    
    int h2c_fd = -1, 
        c2h_fd = -1;
        
    size_t counter = 0;
    
    uint32_t errors = 0;

    if ((h2c_fd = open(h2c, O_RDWR)) < 0) {
        std::cerr << "open h2c failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    if (buffer_size != (counter = write(h2c_fd, h2c_buffer, buffer_size))) {
        std::cerr << "write failed. counter: " << counter <<std::endl;
        close(h2c_fd);
        exit(EXIT_FAILURE);
    }
    
    close(h2c_fd);
    
    if ((c2h_fd = open(c2h, O_RDWR)) < 0) {
        std::cerr << "open c2h failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    if (buffer_size != (counter = read(c2h_fd, c2h_buffer, buffer_size))) {
        std::cerr << "read failed. Counter: " << counter <<std::endl;
        close(c2h_fd);
        exit(EXIT_FAILURE);
    }
    
    close(c2h_fd);

    for (int i = 0; i < buffer_size; i++) {
        if (h2c_buffer[i] != c2h_buffer[i]) {
            errors++;
        }
    }
    
    if (0 != errors) {
       std::cerr << "errors ocured: " << errors << std::endl;
                 
                 
       std::cerr << "have to be -> is factually " << std::endl;
       
       for (int i = 0; i < buffer_size; i++) {
           std::cerr << h2c_buffer[i] << " -> " << c2h_buffer[i] << std::endl;
       }
       
        std::cerr << "The test faild" << std::endl;
    }
    else{
        std::cout << "The test successed" << std::endl;
    }
            
    exit(EXIT_SUCCESS);
}
