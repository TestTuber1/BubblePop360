#pragma once

#include <iostream>
#include <istream>
#include <ostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include <vector>
#include <optional>
#include <random>
#include <cmath>
#include <memory>

using std::string;
using std::cout;
using std::vector;

enum Color
{
	Red,
	Blue,
	Yellow
};

enum gameState
{
	Running,
	End
};

enum class AnimationPhase {
	None,
	RotateForward,
	RotateBackward,
	ReturnToCenter
};

const float pi = 3.1415926535897932;