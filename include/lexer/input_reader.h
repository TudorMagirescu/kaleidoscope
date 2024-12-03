#pragma once

#include <string>
#include <fstream>

class InputReader {
    private:
        std::ifstream in;
        char cachedCharacter;
    
    public:
        InputReader(std::string filename);
        char peekNextCharacter();
        void consumePeekedCharacter();
};