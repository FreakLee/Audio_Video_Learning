#include <iostream>
#include <cstdlib>

int main() {
    std::string command = "ffmpeg -f avfoundation -i \":0\" -t 10 output.wav";
    
    std::cout << "Recording audio..." << std::endl;
    
    int status = std::system(command.c_str());
    
    if (status == 0) {
        std::cout << "Audio recording completed." << std::endl;
    } else {
        std::cout << "Audio recording failed." << std::endl;
    }
    
    return 0;
}
