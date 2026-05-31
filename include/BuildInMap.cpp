#define BUILD_DLL
//#define ES_DEBUG
#include <string>
#include <format>
#include "BuildInMap.hpp"
#include "debug.hpp"
#include "Logger.hpp"
Logger* logger;

std::pair<ReturnCode,std::string> BuildInMap::get(const std::vector<std::string>& argv){
	if(argv.size()<=2){//因为包括命令名
		debugPrint("[BuildInMap_Error]:Too few parameters.");
		logger->log("[BuildInMap_Error]:Too few parameters.");
		return {ReturnCode::FAILED,""};
	}
	if(argv.size()>2){
		debugPrint("[BuildInMap_Warning]:Too many parameters.");
		logger->log("[BuildInMap_Warning]:Too many parameters.");
	}
	int x,y;
	try{
		x=stoi(argv[1]);
		y=stoi(argv[2]);
	}catch(std::runtime_error& e){
		logger->log("[BuildInMap_error]:The map coordinate data contains non numeric characters.");
		return {ReturnCode::FAILED,""};
	}
	debugPrint(std::format("x:{}/y:{}\nmax_x:{}/max_y:{}",x,y,mapx,mapy));
	if(x>=mapx||y>=mapy||x<0||y<0){
		logger->log("[BuildInMap_Error]:Parameter out of bounds");
		return {ReturnCode::FAILED,""};
	}
	return {ReturnCode::OK,std::to_string(mapData[y*mapx+x])};
}
ReturnCode BuildInMap::begin(std::vector<std::string>& vec){
	mapx=mapy=0;
	if(vec.size()<2){
		return ReturnCode::FAILED;
	}
	mapx=stoi(vec[0]);
	mapy=stoi(vec[1]);
	mapData.resize(mapx*mapy,0);
	return ReturnCode::OK;
}
ReturnCode BuildInMap::nextFrame(){
	logger->log("[BuildInMap_nextFrame]:nextFrame.");
	return ReturnCode::OK;
}
BuildInMap::BuildInMap(){}

extern "C"{
	MAP_DLL_API BasicMap* createBuildInMap(){
		return new BuildInMap();
	}
	MAP_DLL_API void destroyBuildInMap(BasicMap* map){
		if(map==nullptr)debugPrint("[From DLL:]PTR of Map is nullptr.");
		else delete map;
		debugPrint("[From DLL:]destroyBuildInMap OK");
	}
	MAP_DLL_API void setLogger(Logger* lg){
		logger=lg;
	}
}