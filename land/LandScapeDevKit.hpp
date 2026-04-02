#pragma once
#include <string>
namespace ES{
	class BasicLandScape{
		public:
			virtual ~BasicLandScape()=default;
			virtual void turn()=0;
			virtual void getEvent()=0;
			virtual std::string getType()=0;
			virtual double getHeight()=0;
			virtual void setHeight(double)=0;
	};
}

