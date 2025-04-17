#include "Game.hpp"

enum class AnimationPhase {
    None,
    RotateForward,
    RotateBackward,
    ReturnToCenter
};

// Window will create an interactable window
class Window
{
private:

public:
	Window(){}

	void run();
};