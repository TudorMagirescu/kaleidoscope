#include "input_reader.h"

InputReader::InputReader(std::string filename) {
    cachedCharacter = '\0';
    in = std::ifstream(filename);
}

char InputReader::peekNextCharacter() {
    if (!cachedCharacter) {
        cachedCharacter = in.get();
    }

    return cachedCharacter;
}

void InputReader::consumePeekedCharacter() {
    cachedCharacter = '\0';
}