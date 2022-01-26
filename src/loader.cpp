#include "loader.h"
#include <iostream>

int load_binary(std::string &fname, Binary *bin, Binary::BinaryType type){
    std::cout << "file name: " << fname << std::endl;
    std::cerr << "load binary not implemented" << std::endl;
    return 0;
}

void unload_binary(Binary *bin) {
    Section *sec;
    for(size_t i = 0; i < bin->sections.size(); i++){
        sec = &bin->sections[i];
        if(sec->bytes) {
            free(sec->bytes);
        }
    }
}