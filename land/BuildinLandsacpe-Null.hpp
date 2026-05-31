#pragma once
#include <stdexcept>
#include "LandScapeDevKit.hpp"
namespace ES{
	namespace LandScape{
		class NullLand :public ES::BasicLandScape{
			public:
				NullLand()=default;
				~NullLand() override{};
				void turn() override{
					return;
				}
				void getEvent() override{
					return;
				}
				std::string getType() override{
					return "NullLand";
				}
				double getHeight() override{
					return 0.00;
				}
				void setHeight(double newHeight) override{
					throw std::runtime_error{"[TypeError]{\n\tCannot set a height of NullLand\n}"};
				}
		};

	}
}