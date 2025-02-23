#pragma once

#include <string>
#include <iostream>

class InputReader {
    private:
        char cachedCharacter;
    
    public:
        InputReader();
        char peekNextCharacter();
        void consumePeekedCharacter();
};