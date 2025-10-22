#include "gato/Application/Scripting.h"
#include "gato/Application/Application.h"
using namespace Application;
using namespace Graphics;

#define RELEASE false

int main() 
{
	if (Application::init(1920, 1080, "saveFile.json",RELEASE))
	{
        
        runApp();
    }
	return 0;
}
