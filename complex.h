// Author: Jean-Rene Bedard (jrbedard@gmail.com) 2001

//thanks for C. Dutoit for the algorithms

#ifndef COMPLEX_H
#define COMPLEX_H

class Complex
{
public:

	// constructors
	Complex();    // 0 + i*0
	Complex(double a, double b); // a + i*b
	Complex(double a); // a + i*0

	// friends
	//friend ostream& operator<<(ostream&, Complex); // print as <re,im>
	friend Complex operator+(Complex,Complex); // addition of two Complex numbers
	friend Complex operator-(Complex,Complex); // subtraction of two Complex numbers
	friend Complex operator*(Complex,Complex); // multiplication of two Complex numbers

	// members 
	Complex operator-(); // return <-re,-im>
	double modulus();    // return sqrt(re*re+im*im)
	double real();       // return re
	double imag();       // return im
    Complex root();      // return the sqrt(re + i*im)


private:
	// real and imaginary parts
	double re;
	double im;
};

const Complex i(0,1);


#endif
