#pragma once

#define TESTS false

namespace Tests
{
	void Init(const char* Name);
	void Final();

	void TestCoordinates();
	void TestFix2Horiz();

	void TestTime();
	void SolarSystem();
}