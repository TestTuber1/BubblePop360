#include "Player.hpp"
enum class Screen
{
    Menu,
    Play,
    Guide,
    Credits,
    GameOver
};

// Window will create an interactable window
class Window
{ 
public:
	Window(){}

	void run();
};