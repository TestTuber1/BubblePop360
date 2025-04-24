#pragma once
#include "window.hpp"

class Test
{
	vector<std::unique_ptr<Object>> testObjects;

	bool testSpawn();
	bool testScore();
	bool testWave();
	bool testShoot();
	bool testLoser();
public:
	void testing();
};