#pragma once
#include<string>
#include<vector>
#include<stdexcept>
#include<unordered_map>
#include<functional>
#include "ReturnCode.hpp"
#include "debug.hpp"
class MainControler{
	public:
		void registerCommend(const std::string name,std::function<int(const std::vector<std::string>&)> func){
			commends[name]=func;
		}
		int execute(std::string& input){
			// 将输入字符串分割成token列表
			std::vector<std::string> tokens=tokenizer(input);
			// 如果token列表为空，直接返回0
			if(tokens.empty()){
				return 0;
			}
			// 在命令映射中查找第一个token对应的命令
			auto it=commends.find(tokens[0]);
			if(it!=commends.end()){
				// 找到命令，执行对应的回调函数并返回结果
				debugPrint("before <int returnCode=it->second(tokens);>");
				int returnCode=it->second(tokens);
				debugPrint("after <int returnCode=it->second(tokens);>");
				return returnCode;
			}else{
				// 未找到命令，输出错误信息
				printf("unknown order %s\n",tokens[0].c_str());
				return rcToInt(ReturnCode::FAILED);
			}
			// 默认返回0
			return 0;
		}
	private:
		std::unordered_map<std::string,std::function<int(const std::vector<std::string>&)> > commends;
		std::vector<std::string> tokenizer(const std::string& input){
			std::vector<std::string> tokens;
			if(input.empty()){
				return tokens;
			}
			std::string buffer;
			for(long long unsigned int i=0;i<input.size();i++){
				if(input[i]!=' '){
					if(input[i]=='"'){
						i++;
						while(i<input.size()&&input[i]!='"'){
							buffer+=input[i];
							i++;
						}
						if(i==input.size()){//����ȷ������ 
							throw std::runtime_error{"Missing quotation marks to pair"};
						}
					}else{
						buffer+=input[i];
					}
				}else{
					if(!buffer.empty()){
						tokens.push_back(buffer);
						buffer.clear();
					}
				}
			}
			if(!buffer.empty()){
				tokens.push_back(buffer);
				buffer.clear();
			}
			return tokens;
		}
};
