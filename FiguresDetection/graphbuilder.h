#ifndef GRAPHBUILDER_H
#define GRAPHBUILDER_H

#include "finder.h"

class GraphBuilder
{
public:
	std::set<Line> getEdges(std::vector<Point> &points);
private:
	static bool intersects(const Point &s1, const Point &e1,
		const Point &s2, const Point &e2, Point &result);
	static void addLine(const Line &l, std::set<Line> &lines);
};

#endif