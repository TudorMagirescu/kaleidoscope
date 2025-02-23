#include "lexer/input_reader.h"

InputReader::InputReader() {
    cachedCharacter = '\0';
}

char InputReader::peekNextCharacter() {
    if (!cachedCharacter) {
        cachedCharacter = std::cin.get();
    }

    return cachedCharacter;
}

void InputReader::consumePeekedCharacter() {
    cachedCharacter = '\0';
}