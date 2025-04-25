#include "Window.hpp"
#include "Test.hpp"

// main will create a window object and use run()
int main()
{
	Test testCase;

	testCase.testing();

	Window app;

	app.run();

	return 0;
}