// Author: Jean-Rene Bedard (jrbedard@gmail.com) 2001

#include <iostream.h>
#include "complex.h"
#include "math.h"

// Constructors
Complex::Complex()
{
	// set the complex number to 0
	re = 0.;
	im = 0.;
}

Complex::Complex(double a)
{
	// set the complex number to a
	re = a;
	im = 0;
}

Complex::Complex(double	a, double b)
{	
	// set the complex number to a + i*b
	re = a;
	im = b;
}

// member functions
double Complex::real()
{
	// return the real part
	return  re;
}

double Complex::imag()
{
	// return the imaginary part 
	return im;
}

Complex Complex::operator-()
{
	// return minus the complex number 
	return Complex(-re, -im);
}


double Complex::modulus()
{
	// return the modulus of the complex number 
	return sqrt(re*re + im*im);
}

Complex Complex::root()
{
	// return the square root of the complex number 

	double x,y;
	// real and imaginary parts of the square root
	// solve (x + i*y)*(x + i*y) = re + i*im

	if (im != 0.0)
	{
		x = sqrt( ( re + sqrt(re*re + im*im) )/2.);
		y = im / (2.*x);
	}
	else 
	{
		x=(re>=0)?sqrt(re):0.;
		y=(re>=0)?0.:sqrt(-re);
	}

	return Complex(x,y);
}

// friend functions
// arithmetic binary operations are friends to allow mixed 
//types as in 2+x (2 as int, x as Complex)
/*ostream& operator<<(ostream &output,Complex x)
{
	// print a complex number as <re,im.
	return (output << '<' << x.re << ',' << x.im << '>');
}*/

Complex operator+(Complex x, Complex y)
{
	// add two complex numbers 
	return Complex(x.re + y.re, x.im + y.im);
}

Complex operator-(Complex x, Complex y)
{
	// subtract two complex numbers
	return Complex(x.re - y.re, x.im - y.im);
}

Complex operator*(Complex x, Complex y)
{
	// multiply two complex numbers
	return Complex(x.re*y.re - x.im*y.im, x.re*y.im + x.im*y.re);
}

