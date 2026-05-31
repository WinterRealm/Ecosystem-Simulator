#include "pred.hpp" 
#include <cstdio>
#include "Logger.hpp" 
#include "debug.hpp"
int H_help(const std::vector<std::string>&){
	FILE* file=fopen("HelpFile.bist","rb");//加载文本
	if(file==nullptr){
		G_logger.log("[H_help_Error]:file not found.");
		return rcToInt(ReturnCode::FILE_NOT_FOUND);
	}
	fseek(file,0,SEEK_END);
	long size=ftell(file);
	fseek(file,0,SEEK_SET);
	char* helpText=new char[size+1];
	fread(helpText,1,size,file);
	helpText[size]='\0';
	fclose(file);
	printf("%s",helpText);
	delete[] helpText;
	return rcToInt(ReturnCode::OK);
}
int H_quit(const std::vector<std::string>&){
	debugPrint("pred.cpp:H_quit");
	return rcToInt(ReturnCode::QUIT);
}
int H_next(const std::vector<std::string>&){
	auto rtc=bm->nextFrame();
	if(rtc!=ReturnCode::OK){
		G_logger.log("[H_next_Error]:nextFrame failed.");
		return rcToInt(rtc);
	}
	return rcToInt(ReturnCode::OK);
}
int H_flush(const std::vector<std::string>&){
	//将全局logger中的数据写入文件
	G_logger.flush();
	return rcToInt(ReturnCode::OK);
}
int H_check(const std::vector<std::string>& argv){
	//查看地图地块并输出数据
	debugPrint("enter H_check");
	auto p=bm->get(argv);
	debugPrint("after <auto p=bm->get(argv);>");
	ReturnCode rtc=p.first;
	std::string data=p.second;
	if(rtc!=ReturnCode::OK){
		G_logger.log("[H_check_Error]:check failed.");
	}
	printf("%s\n",data.c_str());
	return rcToInt(rtc);
}