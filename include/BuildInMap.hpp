#pragma once
#include "MapSDK.hpp"
#ifdef BUILD_DLL
	#define MAP_DLL_API __declspec(dllexport)
#else
	#define MAP_DLL_API __declspec(dllimport)
#endif
class BuildInMap:public BasicMap{
	public:
		BuildInMap();
		ReturnCode begin(std::vector<std::string>&) override;//[1]mapx/[2]mapy
		std::pair<ReturnCode,std::string> get(const std::vector<std::string>&) override;
		ReturnCode nextFrame() override;
	private:
		int mapx,mapy;
		std::vector<int> mapData;
};
extern "C"{
	MAP_DLL_API BasicMap* createBuildInMap();
	MAP_DLL_API void destroyBuildInMap(BasicMap* map);
	MAP_DLL_API void setLogger(Logger* lg);
}