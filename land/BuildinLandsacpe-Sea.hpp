#pragma once
#include "LandScapeDevKit.hpp"
class Sea :public ES::BasicLandScape{
	public:
		Sea()=default;
		~Sea() override{};
		void turn() override{
			
		}
		void getEvent() override{
			
		}
		std::string getType() override{
			return "Sea";
		}
		double getHeight() override{
				return height;
		}
		void setHeight(double newHeight) override{
				height=newHeight;
		}
	private:
		double height;
};
