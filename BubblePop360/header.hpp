#pragma once

#include <iostream>
#include <istream>
#include <ostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <sstream>
#include <vector>
#include <optional>
#include <random>
#include <cmath>
#include <memory>
#include <queue>
#include <unordered_set>


using std::string;
using std::cout;
using std::vector;

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

enum class Screen
{
	Menu,
	Play,
	Guide,
	Credits,
	GameOver
};

const float pi = 3.1415926535897932;