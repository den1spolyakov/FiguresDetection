#include "finder.h"
#include <iostream>

//initialize graph
void Finder::init(std::set<Line> &lines)
{
	for (std::set<Line>::iterator it = lines.begin(); it != lines.end();
		++it)
	{
		addPoint((*it).first), addPoint((*it).second);
		int s1 = pt_id[(*it).first], s2 = pt_id[(*it).second];
		graph[s1].push_back(s2), graph[s2].push_back(s1);
	}
}

//main procedure to find facets
ROW(ROW(Point)) Finder::findFigures(std::set<Line> &lines)
{
	init(lines);
	ROW(ROW(Point)) results;
	if (graph.size() > 0)
	{
		for (size_t k = 0; k < graph.size(); ++k)
		{
			std::sort(graph[k].begin(), graph[k].end(), [&](int i, int j)
			{
				return
					atan2(points[i].first - points[k].first, points[i].second - points[k].second) <
					atan2(points[j].first - points[k].first, points[j].second - points[k].second);
			});
		}

		used.resize(graph.size());

		for (ROW(ROW(bool))::iterator it = used.begin(); it != used.end() ; ++it)
		{
			(*it).resize(graph[it - used.begin()].size());
		}

		ROW(ROW(int)) result;

		for (size_t i = 0; i < graph.size(); ++i)
		{
			for (size_t j = 0; j < graph[i].size(); ++j)
			{
				if (used[i][j] == false)
				{
					temp.clear();
					used[i][j] = true;
					traverse(i, graph[i][j]);
					result.push_back(temp);
				}
			}
		}

		for (size_t i = 1; i < result.size(); ++i)
		{
			ROW(Point) temp;
			for (size_t j = 0; j < result[i].size(); ++j)
				temp.push_back(points[result[i][j]]);
			results.push_back(temp);
		}
	}
	reset();
	return results;
}

void Finder::traverse(int i, int j)
{
	temp.push_back(i);
	size_t k;
	for (k = 0; k < graph[j].size(); ++k)
	{
		if (graph[j][k] == i)
		{
			break;
		}
	}
	if (++k == graph[j].size())
	{
		k = 0;
	}
	if (used[j][k] == false)
	{
		used[j][k] = true;
		traverse(j, graph[j][k]);
	}
}

void Finder::addPoint(const Point &p)
{
	if (pt_id.count(p) == 0)
	{
		pt_id[p] = graph.size();
		points.push_back(p);
		graph.push_back(ROW(int)());
	}
}
