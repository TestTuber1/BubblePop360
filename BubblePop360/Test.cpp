#include "Test.hpp"

bool Test::testSpawn()
{
	Player testPlayer;
	vector<std::unique_ptr<Object>> testObjects;
	testPlayer.checkGame(testObjects);

	return false;
}

bool Test::testScore()
{


	return false;
}

bool Test::testWave()
{


	return false;
}

bool Test::testShoot()
{


	return false;
}
bool Test::testLoser()
{


	return false;
}

void Test::testing()
{
	if (testSpawn())
		cout << endl << "Case 1: Spawning Works!" << endl;
	else
		cout << endl << "Case 1: Spawning Failed!" << endl;

	if (testScore())
		cout << "Case 2: Score Works!" << endl;
	else
		cout << "Case 2: Score Failed!" << endl;

	if (testWave())
		cout << "Case 3: Waves Work!" << endl;
	else
		cout << "Case 3: Waves Failed!" << endl;

	if (testShoot())
		cout << "Case 4: Shooting Works!" << endl;
	else
		cout << "Case 4: Shooting Failed!" << endl;

	if (testLoser())
		cout << "Case 5: Losing Works!" << endl;
	else
		cout << "Case 5: Losing Failed!" << endl;
}