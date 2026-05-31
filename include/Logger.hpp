#pragma once
#include <ctime>
#include <string>
#include <format>
#include"debug.hpp"
#include "ReturnCode.hpp"

class Logger{
	public:
		Logger(std::string name,std::string path=""){
			if(path.empty()){
				filePath=name+".elf";//AKA: ecosystem log file
			}else{
				filePath=path+"/"+name+".elf";
			}
		}
		// 将日志信息存入内存缓冲区
		void log(std::string text){//默认存到内存
			long int now=time(NULL);// 获取当前时间戳
			std::string temp="[Time: "+std::to_string(now)+"] "+text+"\n";// 格式化日志内容：时间戳+文本
			buffer+=temp;// 将格式化后的字符串追加到缓冲区
		}
		ReturnCode flush(){
			if(buffer.empty()){
				debugPrint("Nothing.\n");
				return ReturnCode::OK;
			}
			FILE* file=fopen(filePath.c_str(),"a");
			debugPrint(std::format("flush at {}\n",filePath));
			if(file==nullptr){
				printf("Failed.\n");
				return ReturnCode::FAILED;
			}
			fprintf(file,"%s",buffer.c_str());
			fclose(file);
			buffer.clear();
			return ReturnCode::OK;

		}
		void changeFile(std::string name,std::string path=""){
			if(path.empty()){
				filePath=name+".elf";//AKA: ecosystem log file
			}else{
				filePath=path+"/"+name+".elf";
			}
		}
		~Logger(){
			debugPrint("flushing...\n");
			flush();
		}
	private:
		std::string buffer;//日志在内存中的缓冲区
		std::string filePath;
};
extern Logger G_logger;//公共日志存储器
