#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <iostream>
#include "CarSimulation/Car.h"

SCENARIO("The car can be switched on and off") 
{

    GIVEN("A turned off car") 
    {
        Car car;
        REQUIRE(!car.IsTurnedOn());

        WHEN("Car is turn on")
        {
            car.TurnOnEngine();
            THEN("It becomes turned on")
            {
                CHECK(car.IsTurnedOn());
            }

            THEN("Turn re on not possible")
            {
                CHECK(!car.TurnOnEngine());
            }

            AND_WHEN("Car is turne off")
            {
                car.TurnOffEngine();
                THEN("It becomes turned off")
                {
                    CHECK(!car.IsTurnedOn());
                }

                THEN("Turn re off not possible")
                {
                    CHECK(!car.TurnOffEngine());
                }
            }

            AND_WHEN("Car turn off not in neutral gear")
            {
                car.TurnOnEngine();
                car.SetGear(1);
                car.TurnOffEngine();
                THEN("Car stays turne on")
                {
                    CHECK(car.IsTurnedOn());
                }
            }

            AND_WHEN("Car turn off in not at zero speed")
            {
                car.SetGear(1);
                car.SetSpeed(20);
                car.SetGear(0);
                car.TurnOffEngine();
                THEN("Car stays turne on")
                {
                    CHECK(car.IsTurnedOn());
                }
            }

            AND_WHEN("Car turn off if speed is zero")
            {
                car.SetSpeed(0);
                car.TurnOffEngine();
                THEN("It becomes turned off")
                {
                    CHECK(!car.IsTurnedOn());
                }
            }
        }
    }
}

SCENARIO("Gearbox can be shifted")
{
    GIVEN("Car is standing and turned on")
    {
        Car car;
        REQUIRE(car.GetDirection() == "stop");
        REQUIRE(car.GetSpeed() == 0);
        REQUIRE(car.TurnOnEngine());

        WHEN("The gearbox shifts")
        {
            car.SetGear(1);
            THEN("First gear sticks in");
            {
                CHECK(car.GetGear() == 1);
            }

            AND_WHEN("Speed doesn't match the new gear")
            {
                car.SetSpeed(19);
                THEN("Switching not possible")
                {
                    CHECK(!car.SetGear(2));
                }
            }

            AND_WHEN("Speed does match the new gear")
            {
                car.SetSpeed(30);
                car.SetGear(3);
                THEN("Switching possible")
                {
                    CHECK(car.GetGear() == 3);
                }

                AND_WHEN("Shifting into reverse gear not at zero speed")
                {
                    THEN("Switching not possible")
                    {
                        CHECK(!car.SetGear(-1));
                    }

                    AND_WHEN("Shifting into reverse gear at zero speed")
                    {
                        car.SetGear(0);
                        car.SetSpeed(0);
                        THEN("Switching possible")
                        {
                            CHECK(car.SetGear(-1));
                        }


                        AND_WHEN("Shifting into first gear when speed is not zero")
                        {
                            car.SetGear(-1);
                            car.SetSpeed(15);
                            THEN("Switching not possible")
                            {
                                CHECK(!car.SetGear(1));
                            }
                        }

                        AND_WHEN("Shifting into first gear when speed is zero")
                        {
                            car.SetGear(-1);
                            THEN("Switching not possible")
                            {
                                CHECK(car.SetGear(1));
                            }
                        }
                    }
                }

                AND_WHEN("Shifting into neutral not at zero speed")
                {
                    THEN("Switching possible")
                    {
                        CHECK(car.SetGear(0));
                    }
                }
            }
        }

        WHEN("Shifting from reverse to first gear without stopping")
        {
            car.SetGear(-1);
            car.SetSpeed(15);
            car.SetGear(0);
            THEN("Switching not possible")
            {
                CHECK(!car.SetGear(1));
            }

            AND_WHEN("Shifting from reverse to first gear with a stop")
            {
                car.SetSpeed(0);
                THEN("Switching possible")
                {
                    CHECK(car.SetGear(1));
                }
            }
        }
    }
}

SCENARIO("The car can accelerate")
{
    GIVEN("The car stands still")
    {
        Car car;
        REQUIRE(car.GetDirection() == "stop");
        REQUIRE(car.GetSpeed() == 0);
        REQUIRE(car.TurnOnEngine());

        WHEN("The car is in neutral gear and stopped")
        {
            car.SetSpeed(15);
            THEN("The speed does not increases")
            {
                CHECK(car.GetSpeed() != 15);
            }
        }

        WHEN("The Transmission shifts")
        {
            car.SetGear(-1);
            car.SetSpeed(10);
            THEN("The speed and direction change")
            {
                CHECK(car.GetSpeed() == 10);
                CHECK(car.GetDirection() == "back");
            }
            
            car.SetSpeed(0);
            car.SetGear(1);
            car.SetSpeed(22);
            THEN("The speed and direction change")
            {
                CHECK(car.GetSpeed() == 22);
                CHECK(car.GetDirection() == "forward");
            }

            car.SetSpeed(-5);
            THEN("The speed cannot be negative")
            {
                CHECK(car.GetSpeed() != -5);
            }

            AND_WHEN("The gear does not match the car speed")
            {
                car.SetSpeed(35);
                THEN("The speed does not increases")
                {
                    CHECK(car.GetSpeed() != 35);
                }
            }

            AND_WHEN("The gearbox is in neutral while driving")
            {
                car.SetGear(0);

                WHEN("The speed is increased")
                {
                    car.SetSpeed(30);
                    THEN("The speed does not increases")
                    {
                        CHECK(car.GetSpeed() != 30);
                    }
                }

                WHEN("The speed is reduced")
                {
                    car.SetSpeed(15);
                    THEN("The speed does increases")
                    {
                        CHECK(car.GetSpeed() == 15);
                    }
                }
            }
        }
    }
}