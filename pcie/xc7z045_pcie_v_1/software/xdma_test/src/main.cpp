#include <iostream>
#include <fcntl.h>

#include "xdma_test.h"

int main() {
    
    
    if (EXIT_SUCCESS != xdma_test()) {
        exit(EXIT_FAILURE);
    }
     
    exit(EXIT_SUCCESS);
}

