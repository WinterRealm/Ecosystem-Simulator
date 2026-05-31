#pragma once
#include "ES.hpp"
#include <map>
#include <string>
#include <optional>
#include <windows.h>
#include ".\land\Map.hpp"
#include "Error.hpp"
#include "PerlinNoiseFunc.hpp"
namespace ES{
	struct taskInfo{
		Uint64 x,y;
		int seed;
		ES::Land::Map* map;
		const char* landFunc="PerlinNoise.dll";
	};
	namespace Control{
		class CCU{
			public:
				CCU()=default;
				~CCU(){
					if(count){
						for(auto& item:list){
							quit(item.first);
						}
					}
				}
					
				bool create(std::string s,taskInfo ti){//启动一个任务 
					if(list.count(s)==0){//名称未被占用 
						list[s]=ti;
						count++;
					}else{
						return false;
					}
					//CANADD: 实际启动逻辑 
					try{
						list[s].map=new ES::Land::Map{list[s].x,list[s].y};//创建地图
					}catch(...){
						list.erase(s);//清除脏数据
						count--;
					}
					//处理生成地形函数
					//TOUP:可以升级为DLL加载,目前使用内嵌代替
					//->
					const Uint64 seed=123456u;//TODO
					 ES::LandScape::Function::PerlinNoiseCreator(list[s].map->map,seed);
					return true;
				}
				std::optional<ES::ErrorCode> runStep(std::string name){//单线程阻塞式调用
					if(list.count(name)==0){//没有此任务
						return ES::ErrorCode::NotFound;
					}
					//单步运行
					return std::nullopt;//没有问题
				}
				std::optional<taskInfo*> getTaskInfo(std::string name){
					if(list.count(name)==0){//没有此任务
						return std::nullopt;
					}
					return &list[name];
				}
				bool quit(std::string s){
					if(list.count(s)){
						//CANADD: 实际退出逻辑 
						delete list[s].map;
						list.erase(s);
						count--;
						return true;
					}else{
						return false;
					}
				}
				int countTask()const{//获取启动的任务数量 
					return count;
				}
			private:
				std::map<std::string,taskInfo> list;//name/taskInfo
				int count=0;//启动的任务数量 
		};
	}
}
