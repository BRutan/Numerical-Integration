/* NumericalIntegration.hpp
Definition:
	* Class performs numerical integration of passed functions using Midpoint, Trapezoid and Simpson's methods.
Class Members:
	* 



*/

#ifndef NUMERICALINTEGRATION_HPP
#define NUMERICALINTEGRATION_HPP

#include <algorithm>
#include <functional>
#include <numeric>
#include <string>
#include <vector>

// Function type currently supports only one parameter:
using FType = std::function<double(double)>;

enum Method
{
	Midpoint, Trapezoid, Simpson
};

class NumericalIntegration
{
private:
	Method CalcType;			
	double _prev_comp;
	std::vector<double> f_x_i;
	void Compute_All_Inner(FType f_int, double a, double b, double tol, unsigned n_start, std::vector<std::tuple<unsigned, double>> &input);
public:
	////////////////////////////
	// Constructors/Destructor:
	////////////////////////////
	NumericalIntegration(Method);									// Overloaded Constructor. Set CalcType.
	explicit NumericalIntegration(const NumericalIntegration&);		// Copy Constructor. Copy all elements.
	virtual ~NumericalIntegration();								// Destructor. 
	//////////////////////////////////////////
	// Misc Methods:
	//////////////////////////////////////////
	double Compute(FType f_int, double a, double b, double tol, unsigned n_start);
	std::vector<std::tuple<unsigned, double>> Compute_All(FType f_int, double a, double b, double tol, unsigned n_start);
	////////////////////////////
	// Overloaded Operators:
	////////////////////////////
	NumericalIntegration& operator=(const NumericalIntegration&);
};

#endif