#include "ConfigLoader.hpp"
#include <stdexcept>
std::pair<ReturnCode,std::map<std::string,std::string> > configLoader(std::string path){
	std::map<std::string,std::string> m;
	toml::table tbl;
	try{
		tbl=toml::parse_file(path);
	}catch(toml::parse_error& error){
		G_logger.log({std::string("[ConfigLoader ERROR]")+error.what()});
//		printf("[ERROR]%s\n",error.what());
		return {ReturnCode::FAILED,{}};
	}
	
	m["mapDll"]=tbl["mapDll"].value_or("");
	m["mapX"]=std::to_string(tbl["mapX"].value_or(100));
	m["mapY"]=std::to_string(tbl["mapY"].value_or(100));
	m["algorithm"]=tbl["algorithm"].value_or("Perlin_Noise");
	m["seed"]=std::to_string(tbl["seed"].value_or(123456));
	m["orderDll"]=tbl["orderDll"].value_or("");
	return {ReturnCode::OK,m};
}
