#pragma once

#define TESTS false

namespace Tests
{
	void Init(const char* Name);
	void Final();

	void TestCoordinates();
	void TestTime();
	void SolarSystem();
}