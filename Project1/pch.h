#pragma once

#include "Types.h"
#include <windows.h>
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct Pos
{
	bool operator==(Pos& other)
	{
		return y == other.y && x == other.x;
	}

	bool operator!=(Pos& other)
	{
		return !(*this == other);
	}

	Pos operator+(Pos& other)
	{
		Pos ret;
		ret.y = y + other.y;
		ret.x = x + other.x;
		return ret;
	}

	Pos& operator+=(Pos& other)
	{
		y += other.y;
		x += other.x;
		return *this;
	}

	int32 y = 0;
	int32 x = 0;
};


enum Dir
{
	DIR_UP = 0,
	DIR_LEFT,
	DIR_DOWN,
	DIR_RIGHT,

	DIR_COUNT = 4
};