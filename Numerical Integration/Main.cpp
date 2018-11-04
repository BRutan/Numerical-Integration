/* Main.cpp
Description:
	* Test the NumericalIntegration class.
*/

#define _USE_MATH_DEFINEs

#include <algorithm>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <tuple>
#include <vector>
#include "NumericalIntegration.hpp"
#include "Misc_Functions.hpp"

int main()
{
	double temp[3], a = 0, b = 2;
	std::vector<std::tuple<unsigned, double>> results[3];
	double upperBounds[3] = { 1, .1, .01 };
	NumericalIntegration midpoint(Midpoint);
	NumericalIntegration trapezoid(Trapezoid);
	NumericalIntegration simpsons(Simpson);
	FType exp = [](double i) { return std::exp(-i * i); };
	FType normPDF = [](double i) { return (1 / std::sqrt(2 * 3.14)) * std::exp((-i * i) / 2); };
	// Compute values of norm cdf for values N(1), N(.1) and N(.01): 
	// std::vector<std::vector<std::tuple<unsigned, double>>> NormDist = simpsons.Compute_All(normPDF, 0, ;
	double tol = 10E-12;
	std::size_t n = 4;
	///////////////
	// Compute numerical approximation of integral of above function between 0 and 10:
	///////////////
	results[1] = midpoint.Compute_All(normPDF, 0, .1, tol, 4);
	// results[2] = trapezoid.Compute_All(normPDF, 0, .1, tol, 4);
	results[3] = simpsons.Compute_All(normPDF, 0, .1, tol, 4);
	///////////////
	// Print results:
	///////////////
	std::cout << "n\tMidpoint\tTrapezoid\tSimpson's" << std::endl;
	std::tuple<unsigned, unsigned> stats = std::make_tuple(((results[0].size() > results[1].size()) ? results[0].size() : ((results[1].size() > results[2].size()) ? results[1].size() : results[2].size())), ((results[0].size() > results[1].size()) ? 0 : ((results[1].size() > results[2].size()) ? 1 : 2)));
	for (unsigned j = 0; j < std::get<0>(stats); j++)
	{
		// Print number of intervals:
		std::cout << std::setprecision(1) << std::get<0>(results[std::get<1>(stats)][j]);
		for (unsigned i = 0; i < 3; i++)
		{
			if (j < results[i].size())
			{
				std::cout << "\t" << std::setprecision(12) << std::get<1>(results[i][j]) + 50.0;
			}
		}
	}
	system("pause");
	// std::for_each(results.begin(), results.end(), [](auto elem) { std::cout << std::setprecision(3) << elem << std::endl; });

	return 0;
}