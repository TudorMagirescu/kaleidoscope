#include <string>
#include <fstream>
#include <memory>
#include "token.h"

class Lexer {

    private:
        std::ifstream in;

        char cachedCharacter;
        char peekNextCharacter();
        void consumePeekedCharacter();

        std::unique_ptr<Token> parseNumToken();
        std::unique_ptr<Token> createSpecialCharacterToken(IdTokenType type, std::string symbol);
        std::unique_ptr<Token> parseIdToken();

    public:
        Lexer(std::string filename);
        std::unique_ptr<Token> getNextToken();
};