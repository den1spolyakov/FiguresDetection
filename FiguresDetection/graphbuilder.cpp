#include "graphbuilder.h"

std::set<Line> GraphBuilder::getEdges(std::vector<Point> &points)
{
	std::set<Line> lines;
	
	//process lines one by one
	for (std::vector<Point>::iterator it = points.begin();
		it != points.end() - 1; ++it)
	{
		addLine(Line(*it, *(it + 1)), lines);
	}
	//add final line which closes figure
	addLine(Line(*(points.end() - 1), *(points.begin())), lines);

	std::map<Line, std::vector<Point>> intersectionPoints;
	
	//find points where lines intersect
	for (std::set<Line>::iterator it = lines.begin(); it != lines.end(); ++it)
	{
		Point temp;
		for (auto it2 = lines.begin(); it2 != it; ++it2)
		{
			if (intersects((*it).first, (*it).second,
				(*it2).first, (*it2).second, temp))
			{
				if (!(std::find(points.begin(), points.end(), temp) != points.end())) {
					intersectionPoints[*it].push_back(temp);
					intersectionPoints[*it2].push_back(temp);
				}
			}
		}
	}

	//split lines with those intersection points
	for (auto it = intersectionPoints.begin(); it != intersectionPoints.end(); ++it)
	{
		Point current = (*it).first.first;
		//sort points by distance from starting point
		std::sort((*it).second.begin(), (*it).second.end(), [&current](const Point &a, const Point &b)
		{
			return sqrt((current.first - a.first)   * (current.first - a.first) +
				    (current.second - a.second) * (current.second - a.second)) <
			       sqrt((current.first - b.first)   * (current.first - b.first) +
				    (current.second - b.second) * (current.second - b.second));
		});

		for (size_t j = 0; j < (*it).second.size(); ++j)
		{
			lines.insert(Line(current, (*it).second[j]));
			current = (*it).second[j];
		}
		lines.insert(Line(current, (*it).first.second));
		
		lines.erase((*it).first);
	}
	return lines;
}

bool GraphBuilder::intersects(const Point &s1, const Point &e1,
	const Point &s2, const Point &e2, Point &result)
{
	double  l1_x = e1.first - s1.first, l1_y = e1.second - s1.second,
		l2_x = e2.first - s2.first, l2_y = e2.second - s2.second;
	double s = (-l1_y * (s1.first - s2.first)   + l1_x * (s1.second - s2.second)) /
	           (-l2_x * l1_y + l1_x * l2_y),
	       t = (l2_x  * (s1.second - s2.second) - l2_y * (s1.first - s2.first)) /
	           (-l2_x * l1_y + l1_x * l2_y);
	if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
	{
		result.first  = s1.first  + (t * l1_x);
		result.second = s1.second + (t * l1_y);
		return true;
	}
	return false;
}

void GraphBuilder::addLine(const Line &l, std::set<Line> &lines)
{
	//add line if it's not present (lines are undirected)
	if (lines.count(Line(l.second, l.first)) == 0 && l.second != l.first)
	{
		lines.insert(l);
	}
}
