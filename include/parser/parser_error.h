#pragma once

class ParserError : std::runtime_error {
    public:
        ParserError(const std::string& what_msg): std::runtime_error(what_msg) {}
};