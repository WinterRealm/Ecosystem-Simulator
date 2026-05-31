CXX=g++
CXXFLAGS=-std=c++23 -Wall -Wextra -O2
INCLUDE=".\include"
SOURCES=Ecosystem_Simulator.cpp pred.cpp ConfigLoader.cpp Logger.cpp
OBJECTS=$(SOURCES:.cpp=.o)

IS_STATIC?=0

ifeq ($(IS_STATIC),1)
	TARGET=Ecosystem_Simulator-s.exe
	LDFLAGS=-static -static-libgcc -static-libstdc++ -s
else
	TARGET=Ecosystem_Simulator-d.exe
	LDFLAGS=-s
endif

all:$(TARGET)

$(TARGET):$(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS) 

%.o:%.cpp
	$(CXX) $(CXXFLAGS) -I $(INCLUDE) -c $< -o $@

.PHONY: clean clean_gch clean_log run compileDll
clean:
	del /F $(OBJECTS)
clean_gch:
	del /F *.gch
clean_log:
	del /F *.elf
run:
	.\$(TARGET)
compileDll:
	cd include
	g++ -shared -o BuildInMap.dll BuildInMap.cpp -std=c++23
	mv /F BuildInMap.dll ..
	cd ..