#pragma once
#include "LandScapeDevKit.hpp"
class Plain :public ES::BasicLandScape{
	public:
		Plain()=default;
		~Plain() override{};
		void turn() override{
			
		}
		void getEvent() override{
			
		}
		std::string getType() override{
			return "Plain";
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
