#include "gameloop.h"
#include <iostream>
#include <direct.h>

int main(int argc, char* args[]) {

	if(_chdir("../wd") == -1) std::cout << "Changing working directory failed.\n";

	GameLoop::init();
	GameLoop::run();
	GameLoop::close();

	std::cin.get();
	return 0;

}