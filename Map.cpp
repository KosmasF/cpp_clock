#include "Map.hpp"

float map(float value, float leftMin, float leftMax, float rightMin, float rightMax)
{
	return rightMin + (value - leftMin) * (rightMax - rightMin) / (leftMax - leftMin);
}