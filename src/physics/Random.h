#ifndef PHYSICS_RANDOM_H_
#define PHYSICS_RANDOM_H_

#include <stdio.h>
#include <time.h>

uint32_t GetTickCount();

class Random
{
public:
	signed int x = 0, y = 0, z = 0, w = 0;
	signed int X = 0x75BCD15, Y = 0x159A55E5, Z = 0x1F123BB5, W = 0x5491333;
	int seed;

public:
	void initialize(int seed = -1) 
	{
		if(seed == -1) {
			seed = GetTickCount();
		}

		this->setSeed(seed);
	};

	void setSeed(int seed)
	{
		this->seed = seed;
		this->x = this->X * seed;
		this->y = this->Y * ((seed >> 15) << 30) & 0xFFFFFFFF;
		this->z = this->Z * ((seed >> 1) << 16)  & 0xFFFFFFFF;
		this->w = this->W * ((seed >> 14) << 8)  & 0xFFFFFFFF;
	};

	int getSeed() {
		return this->seed;
	};

	int nextInt() {
		return this->nextSignedInt() & 0x7FFFFFFF;
	};

	int nextSignedInt() {
		int t = (this->x ^ (this->x << 11)) & 0xFFFFFFFF;

		this->x = this->y;
		this->y = this->z;
		this->z = this->w;
		this->w = (this->w ^ ((this->w >> 19) & 0x7FFFFFFF) ^ (t ^ ((t >> 8) & 0x7FFFFFFF))) & 0xFFFFFFFF;

		return this->w;
	};

	float nextFloat() {
		return this->nextInt() / 0x7FFFFFFF;
	};

	float nextSignedFloat() {
		return this->nextSignedInt() / 0x7FFFFFFF;
	};

	bool nextBoolean() {
		return (this->nextSignedInt() & 0x01) == 0;
	};

	int nextRange(int start = 0, int end = 0x7FFFFFFF) {
		return start + (this->nextInt() % (end + 1 - start));
	};

	int nextBoundedInt(int bound) {
		return this->nextInt() % bound;
	};
	
};

#endif