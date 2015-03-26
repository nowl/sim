#include "djikstra.hpp"

static Point point_deltas[] = {{-1,0}, {0,-1}, {1, 0}, {0, 1}};

static void calccosts_rec(Map &map, MapInterface &mapInt, std::deque<Point> &points)
{
	Point &p = points.front();
	points.pop_front();

	int current_cost = map.get_cost(p.x, p.y) + 1;

	for (unsigned int i=0; i<sizeof(point_deltas)/sizeof(point_deltas[0]); i++)
	{
		Point p2 = {p.x + point_deltas[i].x,
					p.y + point_deltas[i].y};
		if (mapInt.entrance_cost(p2.x, p2.y) != -1 &&
			map.valid_point(p2.x, p2.y) &&
			map.get_cost(p2.x, p2.y) > current_cost)
		{
			map.set_cost(p2.x, p2.y, current_cost);
			points.push_back(p2);
		}
	}

	if (points.empty())
		return;
	else
		calccosts_rec(map, mapInt, points);
}

void calccosts(Map &map, MapInterface &mapInt, const std::vector<Point> &goals)
{
	std::deque<Point> points;

	auto iter = goals.begin();
	for (; iter != goals.end(); iter++)
	{
		map.set_cost(iter->x, iter->y, 0);
		points.push_back(*iter);
	}

	calccosts_rec(map, mapInt, points);
}
