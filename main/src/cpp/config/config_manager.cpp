#include "config_manager.hpp"

#include <iostream>
#include <fstream>

#include <mfl/path.hpp>
#include <rapidjson/reader.h>
#include <rapidjson/filereadstream.h>

#ifdef VERBOSE

#include <mfl/out.hpp>

#endif

#include "executor/executor_parser.hpp"

namespace {
  std::string getDefaultConfigFile() {
    return mfl::path::getConfigPath() + "/vai/config";
  }
}

ConfigManager::ConfigManager()
    : cConfigFile(getDefaultConfigFile()) {
#ifdef VERBOSE
  mfl::out::println("ConfigManager::ctor cConfigFile = {:s}", cConfigFile);
#endif
  load();
}

void ConfigManager::load() {
#ifdef WIN32
  FILE * file = std::fopen(cConfigFile.c_str(), "rb");
#else
  FILE * file = std::fopen(cConfigFile.c_str(), "r");
#endif

  if (!file) {
#ifdef VERBOSE
    mfl::out::println("ConfigManager::load Failed to open file {:s}", cConfigFile);
#endif
    return;
  }

  char readBuffer[0xFFFF];
  rapidjson::FileReadStream stream(file, readBuffer, sizeof(readBuffer));

  rapidjson::Reader reader;
  ExecutorParser parser;
  reader.IterativeParseInit();
  while (!reader.IterativeParseComplete()) {
    reader.IterativeParseNext<rapidjson::kParseDefaultFlags>(stream, parser);
    mfl::out::println("State: {}", reader.IterativeParsingArrayInitialState
  }
//  reader.Parse(stream, parser);

  executorManager.executors = std::vector<Executor>{parser.getExecutor()};

#ifdef VERBOSE
  fclose(file);
  std::ifstream fileStream(cConfigFile);
  std::string json((std::istreambuf_iterator<char>(fileStream)),
                   (std::istreambuf_iterator<char>()));
  mfl::out::println("ConfigManager::load executors:\n{:s}", json);
  for (auto & executor : executorManager.executors) {
    mfl::out::println("  Name: {}", executor.getName());
    mfl::out::println("  Command: {}", executor.getCommand());
    mfl::out::println("  Parser: {}", executor.getParser());
    mfl::out::println("  Validator: {}", executor.getValidator());
  }
#endif
}

void ConfigManager::save() {
//  nlohmann::json saver;
//  saver[ConfigFormat::Executors::Field] = executorManager.executors;
//  std::cout << saver << std::endl;
}

