#pragma once

#include <iostream>

// A clas to run and control the application.
//Henry Heino

class ApplicationController
{
	public:
	ApplicationController();
	void setShowUserInterface(bool);
	void setCameraNumber(unsigned int cameraNumber);
	void setLogInformation(bool logInfo);
	void setOutputStream(std::ostream * newOutput);
	void logOutput(std::string output);

	void mainLoop();


	private:
	bool showUI=true;
	unsigned int cameraNumber=0;
	bool cameraNumberSet=false;
	bool logInfo=false;

	std::ostream * outputStream=&(std::cout);
};
