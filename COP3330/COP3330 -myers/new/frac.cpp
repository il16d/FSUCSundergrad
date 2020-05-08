//--------------- FRAC.CPP ---------------
// The class definition for fractions.
//

#include <iostream>
#include "frac.h"

using namespace std;

Fraction::Fraction()
// Default constructor.  Initializes fraction to 0/1
{
   numerator = 0;
   denominator = 1;
}

Fraction::Fraction(int n, int d)
// initializes fraction to n/d
// what kind of error checking should be added?
{
   numerator = n;
   denominator = d;
}

void Fraction::Input()
// Get a fraction from standard input, in the form "numerator/denominator."
// what kind of error checking should be added?
{
   char divSign;	// used to consume the '/' character during input
   cin >> numerator >> divSign >> denominator;
}

void Fraction::Show()
// Display a fraction, in the form "numerator/denominator."
{
   cout << numerator << '/' << denominator;
}

int Fraction::GetNumerator()
{
   return numerator;
}

int Fraction::GetDenominator()
{
   return denominator;
}

void Fraction::SetValue(int n, int d)
// what sort of error checking should be added?
{
   numerator = n;
   denominator = d;
}


double Fraction::Evaluate()
// Calculates and returns the decimal value of a fraction
{
   double n = numerator;	// convert numerator to double
   double d = denominator;	// convert denominator to double
   return (n / d);		// compute and return float representation
}
