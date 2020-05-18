#include <iostream>
using namespace std;



class Mixed{
public:

    friend istream &operator>>(istream &, Mixed &);

    friend ostream &operator<<(ostream &, const Mixed &);

    friend bool operator<(const Mixed &frac1, const Mixed &frac2);

    friend bool operator<=(const Mixed &frac1, const Mixed &frac2);

    friend bool operator>(const Mixed &frac1, const Mixed &frac2);

    friend bool operator>=(const Mixed &frac1, const Mixed &frac2);

    friend bool operator==(const Mixed &frac1, const Mixed &frac2);

    friend bool operator!=(const Mixed &frac1, const Mixed &frac2);


    friend  Mixed operator +(const Mixed &frac1, const Mixed &frac2);

    friend  Mixed operator -(const Mixed &frac1, const Mixed &frac2);

    friend  Mixed operator *(const Mixed &frac1, const Mixed &frac2);

    friend  Mixed operator /(const Mixed &frac1, const Mixed &frac2);


    Mixed(int i=0);
    Mixed(int integer, int numerator, int denominator);
    double Evaluate()const;
    void ToFraction();
    void Simplify();


    Mixed operator++();
    Mixed operator++(int);
    Mixed operator--();
    Mixed operator--(int);


private:


    int numer;
    int denom;
    int integ;








};
