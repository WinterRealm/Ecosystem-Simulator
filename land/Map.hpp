#pragma once
#include <vector>
#include "TypeDef.hpp"
#include ".\land\LandScapeDevKit.hpp"
#include ".\land\BuildinLandsacpe-Null.hpp"
namespace ES{
	namespace Land{
		class Map{
			public:
				Map(Uint64 x,Uint64 y){
					map.resize(x);//是以x为第一位的设计
					for(auto& v:map){
						v.resize(y);
						for(auto& l:v){
							l=new ES::LandScape::NullLand{};
						}
					}
				}
				~Map(){
					for(auto& v:map){
						for(auto& l:v){
							delete l;
						}
					}
				}
			std::vector<std::vector<ES::BasicLandScape*> > map;
		};
	};
};