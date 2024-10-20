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

/* INPUT RADIUS UNITS */
// sphere's radius input units
#define MILIMETRES			1
#define CENTIMETRES			2
#define DECIMETRES			3
#define METRES				4
#define KILOMETRES			5
#define INCHES				6
#define FEET				7
#define	YARDS				8
#define	TERRESTIAL_MILES	9
#define NAUTICAL_MILES		10

// display unit abbreviation
void displayRadiusUnit(short radiusUnit)
{
	switch (radiusUnit)
	{
		case MILIMETRES:
			cout << "[mm]";
			break;
		case CENTIMETRES:
			cout << "[cm]";
			break;
		case DECIMETRES:
			cout << "[dm]";
			break;
		case METRES:
			cout << "[m]";
			break;
		case KILOMETRES:
			cout << "[km]";
			break;
		case INCHES:
			cout << "[in]";
			break;
		case FEET:
			cout << "[ft]";
			break;
		case YARDS:
			cout << "[yd]";
			break;
		case TERRESTIAL_MILES:
			cout << "[mi]";
			break;
		case NAUTICAL_MILES:
			cout << "[NM]";
			break;

		default:
			cout << "WRONG INPUT! Calculation will go sideways!";
			break;
	}
}

// convert radius input from user's unit to [m] which is used for calculation
double convertInput(double radius, short radiusUnit)
{
	switch (radiusUnit)
	{
		case MILIMETRES:
			return radius * 1e-3;
			break;
		case CENTIMETRES:
			return radius * 1e-2;
			break;
		case DECIMETRES:
			return radius * 1e-1;
			break;
		case METRES:
			return radius;
			break;
		case KILOMETRES:
			return radius * 1e3;
			break;
		case INCHES:
			return radius * 2.54e-2;
			break;
		case FEET:
			// this is approximate, this unit is not exact science ;)
			return radius * 3.048e-1;
			break;
		case YARDS:
			return radius * 9.144e-1;
			break;
		case TERRESTIAL_MILES:
			return radius * 1.609344e3;
			break;
		case NAUTICAL_MILES:
			return radius * 1.852e3;
			break;

		default:
			// devil's laughing in disguise!
			return 666;
			break;
	}
}

/* OUTPUT VOLUME UNITS */
// sphere's volume output units
#define CUBIC_MILIMETRES		1
#define CUBIC_CENTIMETRES		2
#define CUBIC_DECIMETRES		3
#define CUBIC_METRES			4
#define CUBIC_KILOMETRES		5
#define CUBIC_INCHES			6
#define CUBIC_FEET				7
#define PINTS_US				8
#define LITRES					9
#define GALLONS_US				10
#define BARRELS_OIL				11
#define CUBIC_TERRESTIAL_MILES	12
#define CUBIC_NAUTICAL_MILES	13

// display unit abbreviation
void displayVolumeUnit(short volumeUnit)
{
	switch (volumeUnit)
	{
		case CUBIC_MILIMETRES:
			cout << "[mm^3]";
			break;
		case CUBIC_CENTIMETRES:
			cout << "[cm^3]";
			break;
		case CUBIC_DECIMETRES:
			cout << "[dm^3]";
			break;
		case CUBIC_METRES:
			cout << "[m^3]";
			break;
		case CUBIC_KILOMETRES:
			cout << "[km^3]";
			break;
		case CUBIC_INCHES:
			cout << "[in^3]";
			break;
		case CUBIC_FEET:
			cout << "[ft^3]";
			break;
		case PINTS_US:
			cout << "[pint(s) (US)]";
			break;
		case LITRES:
			cout << "[l]";
			break;
		case GALLONS_US:
			cout << "[gal (US)]";
			break;
		case BARRELS_OIL:
			cout << "[oil barrel(s)]";
			break;
		case CUBIC_TERRESTIAL_MILES:
			cout << "[mi^3]";
			break;
		case CUBIC_NAUTICAL_MILES:
			cout << "[NM^3]";
			break;

		default:
			cout << "WRONG INPUT! Calculation will go sideways!";
			break;
	}
}

// convert sphere's volume from internal calculation unit [m^3] to user's output unit
double convertOutput(double volume, short volumeUnit)
{
	switch (volumeUnit)
	{
		case CUBIC_MILIMETRES:
			return volume * 1e9;
			break;
		case CUBIC_CENTIMETRES:
			return volume * 1e6;
			break;
		case CUBIC_DECIMETRES:
			return volume * 1e3;
			break;
		case CUBIC_METRES:
			return volume;
			break;
		case CUBIC_KILOMETRES:
			return volume * 1e-9;
			break;
		case CUBIC_INCHES:
			return volume * 6.1023744095e4;
			break;
		case CUBIC_FEET:
			return volume * 3.53147e1;
			break;
		case PINTS_US:
			return volume * 2.1133764188652e3;
			break;
		case LITRES:
			return volume * 1e3;
			break;
		case GALLONS_US:
			return volume * 2.6417205236e2;
			break;
		case BARRELS_OIL:
			return volume * 6.2898107704;
			break;
		case CUBIC_TERRESTIAL_MILES:
			return volume * 2.3991274853161e-10;
			break;
		case CUBIC_NAUTICAL_MILES:
			return volume * 1.57426215e-10;
			break;

		default:
			// devil's laughing in disguise!
			return 666;
			break;
	}
}

/* SPHERE'S VOLUME CALCULATION */
// function to calculate sphere's volume based on radius
double SphereVolume(double radius)
{
	return ((4.0l / 3) * numbers::pi * pow(radius, 3));
}

/* MAIN PROGRAM CODE */
// program does not have proper input data validation as it was not set as a requirement :)
int main()
{
    cout << "~~*~~ Welcome to the Brave New World of C++ Programming! ~~*~~\n"
			"       We're starting with sphere's volume calculation.       \n" << endl;

	// variables to store input data
	short radiusUnit = 0;
	double radius = 0.0;
	
	// ask user for sphere's radius and its unit
	cout << "Which unit will you use for sphere's radius?";
	cout << "\n" << MILIMETRES << ": milimetres ";
	displayRadiusUnit(MILIMETRES);
	cout << "\n" << CENTIMETRES << ": centimetres ";
	displayRadiusUnit(CENTIMETRES);
	cout << "\n" << DECIMETRES << ": decimetres ";
	displayRadiusUnit(DECIMETRES);
	cout << "\n" << METRES << ": metres ";
	displayRadiusUnit(METRES);
	cout << "\n" << KILOMETRES << ": kilometres ";
	displayRadiusUnit(KILOMETRES);
	cout << "\n" << INCHES << ": inches ";
	displayRadiusUnit(INCHES);
	cout << "\n" << FEET << ": feet ";
	displayRadiusUnit(FEET);
	cout << "\n" << YARDS << ": yards ";
	displayRadiusUnit(YARDS);
	cout << "\n" << TERRESTIAL_MILES << ": terrestial miles ";
	displayRadiusUnit(TERRESTIAL_MILES);
	cout << "\n" << NAUTICAL_MILES << ": nautical miles ";
	displayRadiusUnit(NAUTICAL_MILES);
	cout << endl;

	cout << "Please enter a number for your selected unit (" << MILIMETRES << " - " << NAUTICAL_MILES << "): ";
	cin >> radiusUnit;
	
	cout << "Now please enter sphere's radius in ";
	displayRadiusUnit(radiusUnit);
	cout <<	": ";
	cin >> radius;
	cout << endl;

	// variable for sphere's volume unit
	short volumeUnit = 0;

	// ask user for sphere's volume unit they want to get it in
	cout << "Which unit shall the sphere's volume be displayed in?";
	cout << "\n" << CUBIC_MILIMETRES << ": cubic milimetres ";
	displayVolumeUnit(CUBIC_MILIMETRES);
	cout << "\n" << CUBIC_CENTIMETRES << ": cubic centimetres ";
	displayVolumeUnit(CUBIC_CENTIMETRES);
	cout << "\n" << CUBIC_DECIMETRES << ": cubic decimetres ";
	displayVolumeUnit(CUBIC_DECIMETRES);
	cout << "\n" << CUBIC_METRES << ": cubic metres ";
	displayVolumeUnit(CUBIC_METRES);
	cout << "\n" << CUBIC_KILOMETRES << ": cubic kilometres ";
	displayVolumeUnit(CUBIC_KILOMETRES);
	cout << "\n" << CUBIC_INCHES << ": cubic inches ";
	displayVolumeUnit(CUBIC_INCHES);
	cout << "\n" << CUBIC_FEET << ": cubic feet ";
	displayVolumeUnit(CUBIC_FEET);
	cout << "\n" << PINTS_US << ": US pints ";
	displayVolumeUnit(PINTS_US);
	cout << "\n" << LITRES << ": litres ";
	displayVolumeUnit(LITRES);
	cout << "\n" << GALLONS_US << ": US gallons ";
	displayVolumeUnit(GALLONS_US);
	cout << "\n" << BARRELS_OIL << ": oil barrels ";
	displayVolumeUnit(BARRELS_OIL);
	cout << "\n" << CUBIC_TERRESTIAL_MILES << ": cubic terrestial miles ";
	displayVolumeUnit(CUBIC_TERRESTIAL_MILES);
	cout << "\n" << CUBIC_NAUTICAL_MILES << ": cubic nautical miles ";
	displayVolumeUnit(CUBIC_NAUTICAL_MILES);
	cout << endl;

	cout << "Please enter a number for your selected unit (" << CUBIC_MILIMETRES << " - " << CUBIC_NAUTICAL_MILES << "): ";
	cin >> volumeUnit;

	cout << "\nVolume of a sphere with radius of " << radius << " ";
	displayRadiusUnit(radiusUnit);
	cout << " is: ";
	
	// sphere's volume calculation is performed in SI units:
	//	radius: [m]
	//	volume: [m^3]
	// first sphere's radius is converted from user's unit to [m],
	// then calculation is performed and result is converted from [m^3] to user's unit.
	cout << convertOutput(SphereVolume(convertInput(radius, radiusUnit)), volumeUnit) << " ";
	displayVolumeUnit(volumeUnit);
	
	cout << endl;
}