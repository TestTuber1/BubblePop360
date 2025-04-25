#pragma once
#include "window.hpp"

class Test
{
	vector<std::unique_ptr<Object>> testObjects;

	// none of the test functions use the functions that they are testing, they use the same process in how those functions work without the actual implementation
	// Ex: testWave() doesn't actually spawn each wave, just makes sure that it's doing it worrectly
	bool testSpawn(); 
	bool testScore();
	bool testWave();
	bool testShoot();
	bool testLoser();


public:
	void testing();
};