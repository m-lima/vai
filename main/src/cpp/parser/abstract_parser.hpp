#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <functional>
#include <unordered_map>

class AbstractParser : public std::function<std::vector<std::string>(const std::string &)> {
protected:
  AbstractParser(const std::function<std::vector<std::string>(const std::string &)> & parser)
      : std::function<std::vector<std::string>(const std::string &)>(parser) {}
};