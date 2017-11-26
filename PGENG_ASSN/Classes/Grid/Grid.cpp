#include "Grid.h"

Grid::Grid(void)
	: index(Vec2(-1, -1))
	, size(Vec2(-1, -1))
	, offset(Vec2(-1, -1))
	, min(Vec2(-1, -1))
	, max(Vec2(-1, -1))
{
}

Grid::~Grid(void)
{
}

void Grid::Init(const int xIndex, const int yIndex,
			    const int xGridSize, const int yGridSize,
				const float xOffset, const float yOffset)
{
    index.set(Vec2(xIndex, yIndex));
    size.set(Vec2(xGridSize, yGridSize));
    offset.set(Vec2(xOffset, yOffset));
    min.set(Vec2(index.x * size.x - offset.x, index.y * size.y - offset.y));
    max.set(Vec2(index.x * size.x - offset.x + xGridSize, index.y * size.y - offset.y + yGridSize));
}