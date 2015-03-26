#ifndef __DJIKSTRA_HPP__
#define __DJIKSTRA_HPP__

#include <vector>
#include <deque>
#include <limits.h>

#include "point.hpp"

struct MapInterface {
	int (*entrance_cost)(int x, int y);
};

struct Map {
	int width;
	int height;
	int *costs;

	Map(int width, int height)
		: width(width), height(height)
	{
		costs = new int [width * height];
		for (int i=0; i<width*height; i++)
			costs[i] = INT_MAX;
	}

	~Map()
	{
		delete [] this->costs;
	}

	void set_cost(int x, int y, int cost)
	{
		this->costs[y * this->width + x] = cost;
	}

	int get_cost(int x, int y)
	{
		return this->costs[y * this->width + x];
	}

	int valid_point(int x, int y)
	{
		return x >= 0 && x < this->width && y >= 0 && y < this->height;
	}
};

void calccosts(Map &map, MapInterface &mapInt, const std::vector<Point> &goals);

#endif	// __DJIKSTRA_HPP__
