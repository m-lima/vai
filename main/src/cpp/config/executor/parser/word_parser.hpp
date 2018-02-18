#pragma once

#include "abstract_parser.hpp"

#include <sstream>
#include <iterator>

class WordParser : public AbstractParser {
public:
  WordParser() : AbstractParser(
      [&](const std::string & str) {
        auto stream = std::istringstream(str);
        return std::vector<std::string> {std::istream_iterator<std::string>{stream},
                                         std::istream_iterator<std::string>{}};
      }) {}

  std::string getName() const { return "WORD"; };
};
