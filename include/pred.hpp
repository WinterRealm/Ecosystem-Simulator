#pragma once
#include<vector>
#include<string>
#include<memory>
#include"ReturnCode.hpp"
#include"MapSDK.hpp"

extern std::unique_ptr<BasicMap,void (*)(BasicMap*)> bm;


int H_help(const std::vector<std::string>&);
int H_next(const std::vector<std::string>&);
int H_flush(const std::vector<std::string>&);
int H_quit(const std::vector<std::string>&);
int H_check(const std::vector<std::string>&);//命令行的形式检查一个地块的信息
//<order> <x> <y>
