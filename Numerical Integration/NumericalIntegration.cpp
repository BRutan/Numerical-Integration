/* NumericalIntegration.cpp
Definition:
*



*/

#include "NumericalIntegration.hpp"

////////////////////////////////
// Constructors/Destructor:
////////////////////////////////
NumericalIntegration::NumericalIntegration(Method calcType_in) : CalcType(calcType_in), f_x_i(), _prev_comp(0)							// Overloaded Constructor. Set CalcType.
{
	
}
NumericalIntegration::NumericalIntegration(const NumericalIntegration &in) : CalcType(in.CalcType), f_x_i(in.f_x_i), _prev_comp(0)		// Copy Constructor. Copy all elements.
{

}
NumericalIntegration::~NumericalIntegration()																							// Destructor. 
{

}
double NumericalIntegration::Compute(FType f_int, double a, double b, double tol, unsigned n_start)										// Compute numerical approximation to definite integral.
{
	if (b < a)
	{
		throw std::invalid_argument("Upper bound " + std::to_string(b) + " is less than lower bound " + std::to_string(a) + ".");
	}
	double h = (b - a) / n_start;
	double output;
	std::vector<double> a_i(n_start + 1), f_a_i(n_start + 1);
	this->f_x_i.clear();
	//////////////////////////////////
	// Calculate f(x_i)s, a_is:
	//////////////////////////////////
	for (unsigned i = 0; i <= n_start; i++)
	{
		a_i[i] = a + (double)i * h;
		f_a_i[i] = f_int(a_i[i]);
	}
	if (this->CalcType == Midpoint || this->CalcType == Simpson)
	{
		for (unsigned i = 1; i <= n_start; i++)
		{
			this->f_x_i.push_back(f_int(a_i[i - 1] * .5 + a_i[i] * .5));
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
	/////////////////////////////////////
	// Output if within tolerance level:
	/////////////////////////////////////
	if (std::abs(this->_prev_comp - output) < std::abs(tol))
	{
		// Within tolerance, return the approximation after resetting members:
		this->_prev_comp = 0;
		this->f_x_i.clear();
		return output;
	}
	else
	{
		// Computation was not within tolerance, re-compute via doubling number of intervals:
		this->_prev_comp = output;
		return this->Compute(f_int, a, b, tol, 2 * n_start);
	}
}
std::vector<std::tuple<unsigned, double>> NumericalIntegration::Compute_All(FType f_int, double a, double b, double tol, unsigned n_start)
{
	std::vector<std::tuple<unsigned, double>> output;
	while (this->_prev_comp - )
	{

	}
	this->Compute_All_Inner(f_int, a, b, tol, n_start, output);
	return output;
}
////////////////////////////////
// Private helper functions:
////////////////////////////////
void NumericalIntegration::Compute_All_Inner(FType f_int, double a, double b, double tol, unsigned n_start, std::vector<std::tuple<unsigned, double>> &input)										// Helper function, Compute but append number of intervals and generated output to vector for later retrieval.
{
	if (b < a)
	{
		throw std::invalid_argument("Upper bound " + std::to_string(b) + " is less than lower bound " + std::to_string(a) + ".");
	}
	double h = (b - a) / n_start;
	double output;
	std::vector<double> a_i(n_start + 1), f_a_i(n_start + 1);
	this->f_x_i.clear();
	//////////////////////////////////
	// Calculate f(x_i)s, a_is:
	//////////////////////////////////
	for (unsigned i = 0; i <= n_start; i++)
	{
		a_i[i] = a + (double)i * h;
		f_a_i[i] = f_int(a_i[i]);
	}
	if (this->CalcType == Midpoint || this->CalcType == Simpson)
	{
		for (unsigned i = 1; i <= n_start; i++)
		{
			this->f_x_i.push_back(f_int(a_i[i - 1] * .5 + a_i[i] * .5));
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
	/////////////////////////////////////
	// Append to if within tolerance level:
	/////////////////////////////////////
	if (std::abs(this->_prev_comp - output) < std::abs(tol))
	{
		// Within tolerance, append result to output vector, reset members:
		this->_prev_comp = 0;
		this->f_x_i.clear();
		input.push_back(std::make_tuple(n_start, output));
	}
	else
	{
		// Computation was not within tolerance, append results to output vector and re-compute via doubling number of intervals:
		this->_prev_comp = output;
		input.push_back(std::make_tuple(n_start, output));
		this->Compute_All_Inner(f_int, a, b, tol, 2 * n_start, input);
	}
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