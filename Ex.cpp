#include<iostream>
#include<CCU.hpp>
using namespace std;
ES::Control::CCU ccu{};
int main(){
	if(ccu.create("My World",{10,10,123456u})){
		cout<<"OK!\n";
		system("pause");
		auto op=ccu.runStep("My World");
		if(op==std::nullopt){
			cout<<"OK!";
			system("pause");
		}
		auto ti=ccu.getTaskInfo("My World");
		for(auto& v:ti.value()->map->map){
			for(auto& block:v){
				std::string type=block->getType();
				//printf("height=%f",block->getHeight());
				if(type=="NullLand"){
					printf("*");
				}else if(type=="Sea"){
					printf("~");
				}else if(type=="Plain"){
					printf("#");
				}
			}
			printf("\n");
		}
		if(ccu.quit("My World")){
			cout<<"OK!\n";
			system("pause");
		}else{
			cout<<"Erorr! P2\n";
		}
	}else{
		cout<<"Erorr! P1\n";
	}
	
	return 0;
}