#ifndef FINDER_H
#define FINDER_H

#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>

#define ROW(T) std::vector<T>

typedef std::pair<double, double> Point;
typedef std::pair<Point, Point> Line;
typedef std::vector<ROW(int)> Graph;
typedef std::vector<ROW(char)> Table;

class Finder
{
public:
	Finder() {}
	ROW(ROW(Point)) findFigures(std::set<Line> &lines);

private:
	void addPoint(const Point &p);
	void init(std::set<Line> &lines);
	void traverse(int i, int j);

	void reset()
	{	points.clear(); graph.clear(); 
		used.clear(); temp.clear(); pt_id.clear(); 
	}

	ROW(Point) points;
	ROW(ROW(int)) graph;
	ROW(ROW(bool)) used;
	ROW(int) temp;
	std::map<Point, int> pt_id;
};

#endif