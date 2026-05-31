//#define ES_DEBUG//定义DEBUG选项
#define WIN32_LEAN_AND_MEAN//排除不必要函数

#include <iostream>
#include <vector>
#include <memory>
#include <functional>
#include <windows.h>
#include "toml.hpp"
#include "MainControler.hpp"
#include "pred.hpp"
#include"MapSDK.hpp"
#include"debug.hpp"
#include "ConfigLoader.hpp"
#include"ReturnCode.hpp"
//定义函数指针
BasicMap* (*createBuildInMap)();
void (*setLogger)(Logger* lg);
void (*destroyBuildInMap)(BasicMap* map);
std::unique_ptr<BasicMap,decltype(destroyBuildInMap)> bm(nullptr,nullptr);//地图的公共容器
int main(){
	using namespace std;
	MainControler MC;
	HMODULE mapDll=nullptr;
	
	auto [rtc,cfgmap]=configLoader("config.cfg");//加载cfg
	if(rtc==ReturnCode::FAILED){//处理错误情况
		printf("FATAL ERROR.\nEND.");
		cin.get();
		return 1;
	}
	if(cfgmap["mapDll"]==""){//处理不存在DLL的情况
		G_logger.log("No DLL.");
		printf("FATAL ERROR:No DLL.\nEND.");
		cin.get();
		return 1;
		//bm.reset(new BuildInMap);
	}else{
		mapDll=LoadLibrary(cfgmap["mapDll"].c_str());
		if(mapDll==NULL){//未加载成功
			G_logger.log("DLL Error.");
			printf("FATAL ERROR:DLL Error.\nError code:%ld\nEND.",GetLastError());
			debugPrint(std::format("Path:{}",cfgmap["mapDll"]));
			cin.get();
			return 1;
		}
		setLogger=std::bit_cast<void (*)(Logger* lg)>(GetProcAddress(mapDll,"setLogger"));
		createBuildInMap=std::bit_cast<BasicMap* (*)()>(GetProcAddress(mapDll,"createBuildInMap"));
		destroyBuildInMap=std::bit_cast<void (*)(BasicMap* map)>(GetProcAddress(mapDll,"destroyBuildInMap"));
		bm=std::unique_ptr<BasicMap,decltype(destroyBuildInMap)>(createBuildInMap(),destroyBuildInMap);
		setLogger(&G_logger);
	}
	if(cfgmap["orderDll"]!=""){//如果存在扩展指令集
		//载入
	}
	std::vector<std::string> list={cfgmap["mapX"],cfgmap["mapY"],cfgmap["algorithm"],cfgmap["seed"]};
	bm->begin(list);
	
	//注册指令
	MC.registerCommend("help",H_help);
	MC.registerCommend("quit",H_quit);
	MC.registerCommend("next",H_next);
	MC.registerCommend("flush",H_flush);
	MC.registerCommend("check",H_check);

	string input;
	int returnCode;
	cout<<"Environment ready\n"
		<<"The program is running\n";
	while(1){
		cout<<"//:User>>";
		getline(cin,input,'\n');
		returnCode=rcToInt(ReturnCode::OK);
		try{
			returnCode=MC.execute(input);
			debugPrint("Main:after{returnCode=MC.execute(input);}");
		}catch(std::runtime_error& re){
			printf("[Error]%s\n",re.what());
		}catch(...){
			printf("[Error] >> An Unknown error has occurred.\n");
		}
		cout<<"//:ESVM>>";
		switch(returnCode){
			case rcToInt(ReturnCode::OK):{
				printf("Command execution successful\n");
				break;
			}case rcToInt(ReturnCode::FILE_NOT_FOUND):{
				printf("[Error] >> An error has occurred and it has been recorded in the log.\n");
				break;
			}case rcToInt(ReturnCode::QUIT):{
				debugPrint("Main:before{cin.get();}");
				printf("The program has exited.\nPlease press any key to continue.\n--------------------");
				cin.get();
				debugPrint("Main:after{cin.get();}");
				debugPrint("->Quit");
				debugPrint("Before bm.reset()");
				if(destroyBuildInMap==nullptr)debugPrint("The PTR empty.");
				else debugPrint("The PTR NOT empty.");
				bm.reset();
				debugPrint("After bm.reset()");
				if(mapDll)FreeLibrary(mapDll);
				debugPrint("After FreeLibrary(mapDll)");
				return 0;
				break;
			}case rcToInt(ReturnCode::FAILED):{
				printf("FAILED to act\n");
				break;
			}
		}
	}
	bm.reset();
	if(mapDll)FreeLibrary(mapDll);
	return 0;
}