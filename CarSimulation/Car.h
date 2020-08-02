#pragma once
#include <string>
#include <iostream>
#include <vector>

using namespace std;

int getIndex(int gear)
{
	int index = 0;
	if (gear != -1)
		index = gear;
	return index;
}

class Car
{
private:
	bool engine_status;
	int gear;
	string direction;
	int speed;
	bool isFirst = false;
	vector<vector<int>> vector_speed = { { 0, 20 }, { 0, 30 }, { 20, 50 }, { 30, 60 }, { 40, 90 }, { 50, 150 } };
public:
	Car()
	{
		engine_status = false;
		gear = 0;
		direction = "stop";
		speed = 0;
	}

	bool IsTurnedOn()
	{
		return engine_status;
	}

	string GetDirection()
	{
		return direction;
	}

	int GetSpeed()
	{
		return speed;
	}

	int GetGear()
	{
		return gear;
	}

	bool TurnOnEngine()
	{
		if (engine_status)
			return false;

		engine_status = true;
		return true;
	}

	bool TurnOffEngine()
	{
		if (speed != 0 || gear != 0 || !engine_status)
			return false;

		engine_status = false;
		return true;
	}

	vector<vector<int>> GetVectorSpeed()
	{
		return vector_speed;
	}

	bool GetIsFirst()
	{
		return isFirst;
	}

	bool SetGear(int new_gear)
	{
		if (new_gear != 0)
		{
			int index = getIndex(new_gear);
			if (speed < vector_speed[index][0] || speed > vector_speed[index][1])
				return false;
		}

		if (speed != 0)
		{
			if ((gear == -1 && new_gear != 0) || new_gear == -1)
				return false;
		}

		if (gear == -1 && new_gear == 0)
			isFirst = true;
		else if (gear != 0)
			isFirst = false;

		if (isFirst && new_gear == 1 && speed != 0)
			return false;

		gear = new_gear;
		return true;
	}

	bool SetSpeed(int new_speed)
	{
		int index = getIndex(gear);
		if (new_speed < vector_speed[index][0] || new_speed > vector_speed[index][1] || (gear == 0 && speed == 0))
		{
			return false;
		}

		if (new_speed == 0) {
			direction = "stop";
		}
		else if (gear == -1) {
			direction = "back";
		}
		else
		{
			direction = "forward";
		}

		speed = new_speed;
		return true;
	}

	void print_status()
	{
		string engine_status_string;
		string gear_string;
		if (engine_status)
			engine_status_string = "On";
		else
			engine_status_string = "Off";
		if (gear == 0)
			gear_string = "neutral gear";
		else if (gear == -1)
			gear_string = "reverse gear";
		else
			gear_string = to_string(gear);
		cout << "Engin status: " << engine_status_string << "\nGear: " << gear_string << "\nDirection: " << direction << "\nSpeed: " << speed << endl;
	}
};

