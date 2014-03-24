#include <iostream>
#include <fstream>
#include "graphbuilder.h"

void input(std::istream &is, std::vector<Point> &points)
{
	points.clear();
	size_t m;
	is >> m;
	for (size_t i = 0; i < m; i++)
	{
		Point p;
		is >> p.first >> p.second;
		points.push_back(p);
	}
}

void output(std::ostream &os, std::vector<std::vector<Point>> result)
{
	os << "-----------------------------------\n";
	os << result.size() << " figures was found.\n\n";
	for (std::vector<std::vector<Point>>::iterator it = result.begin();
		it != result.end(); ++it)
	{
		os << (*it).size() << " sided figure: \n";
		for (std::vector<Point>::iterator inner = it->begin(); inner != it->end();
			++inner)
		{
			os << "(" << inner->first << " : " << inner->second << ")" << std::endl;
		}
		std::cout << std::endl;
	}
	os << "-----------------------------------\n\n\n";
}

void test(const std::string &path, Finder &f, GraphBuilder &builder, std::vector<Point> &pts)
{
	std::ifstream is(path);
	input(is, pts);
	output(std::cout, f.findFigures(builder.getEdges(pts)));
}

int main()
{
	std::vector<Point> pts;
	GraphBuilder builder;
	Finder f;

	test("test1.txt", f, builder, pts);
	test("test2.txt", f, builder, pts);
}
