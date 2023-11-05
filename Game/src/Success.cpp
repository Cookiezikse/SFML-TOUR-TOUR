#include "success.h"

void Success::AddSuccess(std::string string) {
    std::ofstream outdata;
    outdata.open("assets/Datas/success.txt");
    if (!outdata) {
        std::cerr << "Error: file could not be opened" << std::endl;
    }
    outdata << string << std::endl;
    outdata.close();
}