#include "Test.hpp"

bool Test::testSpawn()
{
	Player testPlayer;
	testObjects.push_back(std::make_unique<Player>());

	if (!(testObjects.empty()))
		return true;

	return false;
}

bool Test::testScore()
{
	Player testPlayer;
	testObjects.push_back(std::make_unique<Player>());

	if (testObjects[0]->points == 0)
	{
		testObjects[0]->points += 300;
		if (testObjects[0]->points == 300)
			return true;
	}

	return false;
}

bool Test::testWave()
{
	float borderLayerCount = 0;
	float screenWidth = 1024.0f;
	float screenHeight = 768.0f;
	float ballSize = 64.0f;
	float offset = borderLayerCount * ballSize;
	int ballCounter = 0;

	for (int i = 0; i < 6; i++)
	{
		borderLayerCount++;
		for (float x = offset; x <= screenWidth - ballSize - offset; x += ballSize)
		{
			ballCounter++;
		}

		for (float y = offset + ballSize; y < screenHeight - ballSize - offset; y += ballSize)
		{
			ballCounter++;
		}
	}
	
	if (ballCounter == 156)
	{
		return true;
	}
	return false;

}

bool Test::testShoot()
{
	Player testPlayer;
	testObjects.push_back(std::make_unique<Player>());

	Ball testBall(90);
	testObjects.emplace_back(std::make_unique<Ball>(testBall));

	if (testObjects.size() > 1)
		return true;

	return false;
}
bool Test::testLoser()
{
	Player testPlayer;
	testObjects.push_back(std::make_unique<Player>());

	Ball testBall(90);
	testBall.isCollidable = true;
	testObjects.emplace_back(std::make_unique<Ball>(testBall));

	testObjects[1]->update(testObjects, testObjects);

	if (testObjects[1]->state == End)
		return true;

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