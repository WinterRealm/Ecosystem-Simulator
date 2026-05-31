#pragma once
#include <cstdio>
#include <string>
void inline debugPrint([[maybe_unused]]std::string s){
	#ifdef ES_DEBUG
	printf("DEBUG:%s\n",s.c_str());
	#endif
}