// Headers from this program.
#include "ApplicationController.h"
#include "ListHelper.h"

// Run cmake to compile this for release, as
//cmake ../robotVision -DCMAKE_BUILD_TYPE=Release


// The main method.
int main()
{
	ListHelper::testSort();
	
	// Create an application controller,
	ApplicationController controller=ApplicationController();
	
	// Set options.
	controller.setShowUserInterface(true);
	controller.setLogInformation(true);

	// Run the main loop.
	controller.mainLoop();
	//controller.demoStitcher();
	//controller.demoNetworkTables();
}

