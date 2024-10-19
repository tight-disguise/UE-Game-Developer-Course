/* 01. SphereVolume.cpp
 * 
 * Unreal Engine Game Developer Course | Laba.IT
 * 
 * Home Assignment No. 1:
 *  - calculate sphere volume based on radius provided by user
 *  - bonus: convert the result into different units
 *
 * Code written by Hubert Pitura (hpitura@gmail.com)
 */

#include <iostream>
#include <numbers>	// numbers::pi (C++20 and up only)
#include <cmath>	// pow()

using namespace std;

// Sphere volume calculation
float SphereVolume(float radius)
{
	return 4 * numbers::pi * pow(radius, 3);
}

int main()
{
    cout << "~~*~~Welcome to the Brave New World of C++ Programming!~~*~~\n";
	cout << "We're starting with sphere volume calculation.\n" << endl;

	float radius = 0.0;

	cout << "Please enter a number: ";
	cin >> radius;
	cout << "ECHO..CHO..O..oo... " << radius;
	
	cout << "  ...and.. the ... volume of the sphere... you have in mind... is: " << SphereVolume(radius) << endl;
}
