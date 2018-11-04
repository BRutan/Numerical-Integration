/* NumericalIntegration.cpp
Definition:
*



*/

#include "NumericalIntegration.hpp"

////////////////////////////////
// Constructors/Destructor:
////////////////////////////////
NumericalIntegration::NumericalIntegration(Method calcType_in) : CalcType(calcType_in),  _prev_comp(0)					// Overloaded Constructor. Set CalcType.
{
	
}
NumericalIntegration::NumericalIntegration(const NumericalIntegration &in) : CalcType(in.CalcType), _prev_comp(0)		// Copy Constructor. Copy all elements.
{

}
NumericalIntegration::~NumericalIntegration()																			// Destructor. 
{

}
std::vector<std::tuple<unsigned, double>> NumericalIntegration::Compute_All(FType f_int, double a, double b, double tol, unsigned n_start)
{
	////////////////////////////////////////////////////////////////////////////////////////////////
	// Description:
	////////////////////////////////////////////////////////////////////////////////////////////////
	// Calculate approximation to definite integral of f_int from a to b using one of three possible numerical integration methods 
	// ( Midpoint, Trapezoid, Simpson's) until change in approximation is less than tol.
	if (b < a)
	{
		throw std::invalid_argument("Upper bound " + std::to_string(b) + " is less than lower bound " + std::to_string(a) + ".");
	}
	double output_temp = 0;
	unsigned n_new = n_start;
	std::vector<std::tuple<unsigned, double>> output;
	// Continue to calculate and append results until difference is within tolerance:
	do
	{
		this->_prev_comp = output_temp;
		output_temp = this->Compute(f_int, a, b, tol, n_new);
		output.push_back(std::make_tuple(n_new, output_temp));
		n_new *= 2;
	} while (std::abs(this->_prev_comp - output_temp) >= std::abs(tol));

	return output;
}
double NumericalIntegration::Compute(FType f_int, double a, double b, double tol, unsigned n_start)										
{
	////////////////////////////////////////////////////////////////////////////////////////////////
	// Description:
	////////////////////////////////////////////////////////////////////////////////////////////////
	// Compute numerical approximation to definite integral.
	double h = (b - a) / n_start;
	double output;
	std::vector<double> f_a_i(n_start + 1), f_x_i(n_start + 1);
	//////////////////////////////////
	// Calculate f(x_i)s, a_is:
	//////////////////////////////////
	for (unsigned i = 0; i <= n_start; i++)
	{
		f_a_i[i] = f_int(a + (double)i * h);
		if (i > 0)
		{
			f_x_i[i - 1] = f_int(a + (double)(i - .5)*h);
		}
	}
	// Compute approximation depending upon method:
	switch (this->CalcType)
	{
	case Midpoint:
		output = std::accumulate(f_x_i.begin(), f_x_i.end(), 0.0, [](auto elem1, auto elem2) { return elem1 + elem2; }) * h;
		break;
	case Trapezoid:
		output = std::accumulate(f_a_i.begin(), f_a_i.end(), 0.0, [](auto elem1, auto elem2) { return elem1 + elem2; }) * (h / 2.0);
		break;
	case Simpson:
		output = std::accumulate(f_x_i.begin(), f_x_i.end(), 0.0, [](auto elem1, auto elem2) { return elem1 + elem2; });
		output += std::accumulate(f_a_i.begin(), f_a_i.end(), 4.0 * output, [](auto elem1, auto elem2) { return elem1 + elem2; });
		output *= h / 6.0;
		break;
	}
	// Return approximation:
	return output;
}
////////////////////////////////
// Overloaded Operators:
////////////////////////////////
NumericalIntegration& NumericalIntegration::operator=(const NumericalIntegration &in)
{
	if (this != &in)
	{
		this->CalcType = in.CalcType;
		this->_prev_comp = 0;
	}
	return *this;
}