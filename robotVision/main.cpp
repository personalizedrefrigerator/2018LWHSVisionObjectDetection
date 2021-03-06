// Headers from this program.
#include "ApplicationController.h"
#include "ListHelper.h"
#include "Logging.h"

// Run cmake to compile this for release, as
//cmake ../robotVision -DCMAKE_BUILD_TYPE=Release


// The main method.
int main(int numberOfArguments, char* argumentTexts[])
{
	Logging::log("Starting... This is standard logging output.");
	Logging::warn("Warning output. ");
	Logging::error("Sample error location.", "Sample error output.", "N/A");

	Logging::log << "Test streams" << Logging::endl; 	// std::endl does not work with these templates.
														// See https://stackoverflow.com/questions/29324123/c11-variadic-templates-and-stdendl

	ListHelper::testSort();
	
	// Create an application controller,
	ApplicationController controller=ApplicationController();
	
	// Create variables to store the default arguments.
	unsigned int cameraNumber = 0;
	bool showUI = true;
	
	// If command line arguments were passed,
	if(numberOfArguments > 1)
	{
	
		// For every command line argument. The first element is the command name.
		for(unsigned int argumentIndex = 1; argumentIndex < numberOfArguments; argumentIndex++)
		{
			// If the first argument,
			if(argumentIndex == 1)
			{
				// Find the default camera.
				cameraNumber = atoi(argumentTexts[argumentIndex]);
			} // Otherwise, if the second,
			else if(argumentIndex == 2)
			{
				// If a 0,
				if(argumentTexts[argumentIndex][0] == '0')
				{
					showUI = false; // Don't show UI.
				}
			}
		}
	}
	
	// Set options.
	controller.setShowUserInterface(showUI);
	controller.setCameraNumber(cameraNumber);
	controller.setLogInformation(true);

	// Run the main loop.
	controller.mainLoop();
	//controller.demoStitcher();
	//controller.demoNetworkTables();
}

