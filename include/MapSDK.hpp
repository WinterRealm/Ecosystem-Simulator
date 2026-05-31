#pragma once
#include <string>
#include <vector>
#include <utility>
#include "ConfigLoader.hpp"
class BasicMap{
	public:
		virtual ~BasicMap()=default;
		virtual ReturnCode begin(std::vector<std::string>&)=0;
		virtual std::pair<ReturnCode,std::string> get(const std::vector<std::string>&)=0;
		virtual ReturnCode nextFrame()=0;
};
//map要自己实现一个get函数，MainControler的get指令的参数会fall through到DLL的get函数中