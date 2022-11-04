#pragma once

#include "scanner.hxx"
#include <string>

namespace nxe::lexer {
/// This class is used for generating a list of tokens from an input string and
/// some token check measures.
class Lexer {
public:
    /// This will construct a new lexer. When created the tokens
    /// will not be generated immediately. It requires you to call
    /// a specific method to generate the tokens.
    /// @param input The input string to generate tokens from.
    /// @param scanner The lexer scanning tool.
    explicit Lexer(const std::string &input, const ScHnd &scanner);
};
}
