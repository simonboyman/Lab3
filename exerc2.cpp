/****************************
 * Lab 3: exercise 2        *
 ****************************/

#include <fstream>
#include <iostream>
#include <cmath>
#include <sstream>
#include <vector>
#include <numeric>
#include <algorithm>

int main() {

	std::vector<std::pair<int, int>> point;
	std::ifstream file("../code/points.txt"); //file reader

	if (file.is_open()) {
		auto f = [](const std::string& s) {
			std::pair<int, int> xy;
			char separator; //will become commas
			std::istringstream is{ s }; //used to parse strings
			is >> xy.first >> separator >> xy.second;
			return xy;
		};
		std::transform(std::istream_iterator<std::string>(file), std::istream_iterator<std::string>(), std::back_inserter(point), f); 
		//point receives pointers, not type
		file.close();
	}
	else {
		std::cout << "Unable to open file";
	}

	std::vector<double> distances(point.size() - 1); //-1 because cant check (last + nullptr)
	std::transform(point.begin(), point.end() - 1, point.begin() + 1, distances.begin(), [](const std::pair<int, int>& s1, const std::pair<int, int>& s2) {
		return std::sqrt(pow(s1.first - s2.first, 2) + pow(s1.second - s2.second, 2)); 
	//point.begin() because we want to add first and second point together
	}); //we use transform first because its pairs. accumulate just works in single.
	
	double distance = std::accumulate(distances.begin(), distances.end(), 0.0);

	std::cout << "The points: \n";
	std::ostream_iterator<std::string> out{ std::cout, "\n" };
	std::transform(point.begin(), point.end(), out, [](std::pair<int, int> a) { //transform instead of copy because we convert via to_string
		return "(" + std::to_string(a.first) + "," + std::to_string(a.second) + ")";
	});
	std::cout << "Distance travelled = " << distance;
}