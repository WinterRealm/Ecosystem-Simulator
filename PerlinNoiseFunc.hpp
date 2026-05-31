#pragma once
#include <vector>
#include ".\include\PerlinNoise.hpp"
#include ".\TypeDef.hpp"
#include "land/BuildinLandsacpe-Sea.hpp"
#include "land/BuildinLandsacpe-Plain.hpp" 
void setType(ES::BasicLandScape*& landBlock,double h){
	delete landBlock;
	if(h<=0){
		landBlock=new Sea();
	}else if(h>0){
		landBlock=new Plain();
	}
}
namespace ES::LandScape::Function{
	void PerlinNoiseCreator(std::vector<std::vector<BasicLandScape*> >& map,Uint64 seed){
		siv::PerlinNoise perlin(seed);
		int i=1,j=1;
		for(auto& v:map){
			for(auto& landBlock:v){
				auto height=perlin.noise2D(i,j);
				setType(landBlock,height);
				landBlock->setHeight(height);
				j++;
			}
			i++;
		}
	}
}