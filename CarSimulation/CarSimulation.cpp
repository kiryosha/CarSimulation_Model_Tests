#include <iostream>
#include <string>
#include "Car.h"

using namespace std;

int main()
{
	Car firstCar;
	while (true)
	{
		string str;
		string test = "no";
		string command[5] = { "Info", "EngineOn", "EngineOff", "SetSpeed", "SetGear" };
		cout << "Enter the command: ";
		getline(cin, str);
		for (int i = 0; i < 5; i++)
		{
			if (str.find(command[i]) != -1)
			{
				test = "yes";
				break;
			}
		}
		if (test == "yes")
		{
			if (str == "Info")
				firstCar.print_status();
			if (str == "EngineOn")
			{
				if (firstCar.TurnOnEngine())
					cout << "Engine is running!" << endl;
				else
					cout << "Engine is already running!" << endl;
			}
			if (str == "EngineOff")
			{
				if (firstCar.TurnOffEngine())
					cout << "Engine is off!" << endl;
				else
				{
					if (firstCar.GetSpeed() != 0)
						cout << "Speed is not zero!" << endl;
					if (!firstCar.IsTurnedOn())
						cout << "Engine is already turned off!" << endl;
					if (firstCar.GetGear() != 0)
						cout << "Gear on " << firstCar.GetGear() << "th!" << endl;
				}
			}
			if (firstCar.IsTurnedOn())
			{
				if (str.find("SetSpeed") != -1)
				{
					string speed_string = str.substr(str.find(" ") + 1);
					if (speed_string.size() <= 3)
					{
						int speed = atoi(speed_string.c_str());
						if (speed >= 0 && speed <= 150)
						{
							if (firstCar.SetSpeed(speed))
								cout << "Speed set!" << endl;
							else if (firstCar.GetSpeed() == 0 && firstCar.GetGear() == 0)
								cout << "Car stands!" << endl;
							else
								cout << speed << " does not match " << firstCar.GetGear() << endl;
						}
						else
							cout << "Speed: 0 - 150" << endl;
					}
					else
					{
						cout << "Command: SetSpeed <0 - 150>" << endl;
					}
				}
				if (str.find("SetGear") != -1)
				{
					int inGear;
					int index = 0;
					if (str.length() <= string("SetGear -1").length())
					{
						if (str.find("-1") != -1)
							inGear = -1;
						else
							inGear = (int)str[str.find(" ") + 1] - 48;
						if (inGear >= -1 && inGear <= 5)
						{
							if (firstCar.SetGear(inGear))
								cout << "Gear set!" << endl;
							else
							{
								if (inGear == firstCar.GetGear())
									cout << "Gear already set!" << endl;
								else
								{
									if (inGear != -1)
										index = inGear;
									if (firstCar.GetSpeed() < firstCar.GetVectorSpeed()[index][0] || firstCar.GetSpeed() > firstCar.GetVectorSpeed()[index][1])
										cout << "Gear is not suitable for the current speed!" << endl;
									if (inGear == -1 && firstCar.GetSpeed() != 0)
										cout << "To shift into reverse gear, the speed must be zero!" << endl;
									if (firstCar.GetGear() == -1 && inGear == 1 && firstCar.GetSpeed() != 0)
										cout << "From reverse, you can switch to first gear only at zero speed!" << endl;
									if (firstCar.GetIsFirst() && inGear == 1 && firstCar.GetSpeed() != 0)
										cout << "It is possible to switch to forward gear only after stopping!" << endl;
								}
							}
						}
						else
							cout << "Gear: -1 - 5" << endl;
					}
					else
						cout << "Command: SetGear <-1 - 5>" << endl;
				}
			}
			else
				cout << "Engine off!" << endl;
		}
		else
			cout << "Command: Info, EngineOn , EngineOff, SetSpeed <0 - 150>, SetGear <-1 - 5>" << endl;
	}
}