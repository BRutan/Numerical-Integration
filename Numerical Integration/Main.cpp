/* Main.cpp
Description:
	* Test the NumericalIntegration class.
*/

#define _USE_MATH_DEFINES

#include <cmath>
#include <math.h>
#include <algorithm>
#include <functional>
#include <iomanip>
#include <iostream>
#include <tuple>
#include <vector>
#include "NumericalIntegration.hpp"
#include "Misc_Functions.hpp"

int main()
{
	double value;
	double tol = 10E-6;
	/*
	std::vector<std::tuple<unsigned, double>> results[3];
	NumericalIntegration midpoint(Midpoint);
	NumericalIntegration trapezoid(Trapezoid);
	NumericalIntegration simpsons(Simpson);
	FType normPDF = [](double i) { return (1.0 / std::sqrt(2 * M_PI)) * std::exp((-i * i) / 2.0); };
	// Compute values of norm cdf for values N(1), N(.1) and N(.01): 
	// std::vector<std::vector<std::tuple<unsigned, double>>> NormDist = simpsons.Compute_All(normPDF, 0, ;
	///////////////
	// Compute numerical approximation of integral of above function between 0 and 10:
	///////////////
	results[0] = midpoint.Compute_All(normPDF, 0, value, tol, 4);
	results[1] = trapezoid.Compute_All(normPDF, 0, value, tol, 4);
	results[2] = simpsons.Compute_All(normPDF, 0, value, tol, 4);
	///////////////
	// Print results:
	///////////////
	*/
	std::size_t n = 4;
	FType discountFactor = [](double t) { return -(.05 / (1.0 + 2.0 * std::exp(-(1 + t)*(1 + t)))); };
	std::vector<double> tenors = { .5, 1, 1.5 };
	std::vector<std::tuple<unsigned, double>> dfResults[4];
	NumericalIntegration simpsons(Simpson);
	for (unsigned i = 0; i < tenors.size(); i++)
	{
		dfResults[i] = simpsons.Compute_All(discountFactor, 0, tenors[i], tol, n);
	}
	dfResults[3] = simpsons.Compute_All(discountFactor, 0, 2.0, 10E-8, n);
	std::cout << "n\tt = .5\tt = 1\tt = 1.5" << std::endl;
	unsigned maxSize = 0, vectorNum = 0;
	std::tuple<unsigned, unsigned> stats = std::make_tuple(3, 3);
	for (unsigned j = 0; j < std::get<0>(stats); j++)
	{
		// Print number of intervals:
		std::cout << std::setprecision(1) << std::get<0>(dfResults[std::get<1>(stats)][j]);
		for (unsigned i = 0; i < 4; i++)
		{
			if (j < dfResults[i].size())
			{
				std::cout << "\t" << ((i != 3) ? std::setprecision(6) : std::setprecision(8)) << std::fixed << std::exp(std::get<1>(dfResults[i][j])) << " ";
			}
			else
			{
				std::cout << std::setw(14) << std::left << " ";
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	// Compute and display price of bond using cash flows:
	double price = 0;
	std::vector<double> cashFlows{ 2.5, 2.5, 2.5, 102.5};
	for (unsigned i = 0; i < cashFlows.size(); i++)
	{
		price += cashFlows[i] * std::exp(std::get<1>(dfResults[i][dfResults[i].size() - 1]));
	}
	std::cout << "Price of semiannual coupon bond with c = 5% and face value 100 = " << price << std::endl;

	system("pause");
	// std::for_each(results.begin(), results.end(), [](auto elem) { std::cout << std::setprecision(3) << elem << std::endl; });

	return 0;
}