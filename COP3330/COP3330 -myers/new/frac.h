//--------------- FRAC.H ---------------

class Fraction
{
public:
   Fraction();			// Set numerator = 0, denominator = 1.
   Fraction(int n, int d=1);	// constructor with parameters

   // standard input/output routines
   void Input();		// input a fraction from keyboard.
   void Show();			// Display a fraction on screen

   // accessors
   int GetNumerator();
   int GetDenominator();

   // mutator
   void SetValue(int n, int d); // set the fraction's value through parameters

   double Evaluate();		// Return the decimal value of a fraction

private:
   int numerator;		// no restrictions
   int denominator;		// Invariant:  denominator != 0
};
