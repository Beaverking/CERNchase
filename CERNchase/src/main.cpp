#include "App.h"

using namespace CERNchase;

int main(int argc, char** argv)
{
	App *app = App::Instance();
	if(app->Init())
		app->Start();
	else
		std::cout << "failed to start application" << std::endl;
	return 0;
}