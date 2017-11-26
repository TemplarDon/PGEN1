#pragma once

#include "cocos2d.h"

using namespace cocos2d;
class Mesh;

class Grid
{
public:
	// Constructor
    Grid(void);
	// Destructor
    ~Grid(void);

	// Init
	void Init(	const int xIndex, const int zIndex, 
				const int xGridSize, const int yGridSize,
				const float xOffset = 0, const float yOffset = 0);


	float GetGridID(){return (index.x + index.y * index.x);};

protected:
	Vec2 index;

    Vec2 size;

    Vec2 offset;

    Vec2 min, max;

};
