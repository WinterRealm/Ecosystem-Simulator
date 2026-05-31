#pragma once
#include <map>
#include <utility>
#include "toml.hpp"
#include "ReturnCode.hpp"
#include "Logger.hpp"
std::pair<ReturnCode,std::map<std::string,std::string> > configLoader(std::string);
