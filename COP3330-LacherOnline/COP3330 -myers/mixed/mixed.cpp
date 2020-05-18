#include <iostream>
#include "Mixed.h"
using namespace std;


Mixed::Mixed(int i) {

    integ=i;
    denom=0;
    numer=0;



}

Mixed::Mixed(int integer, int numerator, int denominator) {

    denom=denominator;
    if(denominator==0){


        denominator=1;
    }
    if(integer<0 || integer!=0 && numerator<0){
        integ=0;
        denom=0;
        numer=0;

    }
    else{
        integ=integer;
        numer=numerator;
        denom=denominator;

    }




}

double Mixed::Evaluate() const {

bool negative=false;
   double decimal=(double)numer/(double)denom;
    if((numer==0)&&(denom==0))
        return integ;
if(integ<0){

   integ*(-1);
    negative=true;
}
    if (negative==false)
    {
        return integ+decimal;
    }
    if(negative==true)
    {

    return integ-decimal;
    }



}




void Mixed::ToFraction(){

    if(integ<0)
        numer = (integ*denom) - numer;
    else
        numer = (integ*denom) + numer;
    integ = 0;



}

void Mixed::Simplify() {



    int denominator=denom;
    int numerator=numer;
    for (int i= denominator*numerator; i>1; i--)
    {
        if ((denominator%i==0)&& (numerator%i==0))
        {
            denominator/=i;
            numerator/=i;
            integ++;
        }
    }
}




ostream &operator<<(ostream &out, const Mixed &M)
{
    if(M.integ != 0){
        out << M.integ << ' ' << M.numer<< '/' << M.denom<< endl;}

    else if(M.integ==0 && M.denom==1){
        out<<M.numer<<endl;
    }
    else
        out << M.numer << '/' << M.denom << endl;

    return out;
}

istream &operator>>(istream &in, Mixed &M)
{	char dummy;
    int integ,numera,denomi;
    in >> integ >> numera >> dummy >> denomi;


    if(denomi==0){

        denomi=1;

        }
        if(integ<0 || integ!=0 && numera<0)
        {

            M.integ = 0;
            M.numer = 0;
            M.denom = 0;

    } else
    {
        M.integ = integ;
        M.numer = numera;
        M.denom = denomi;
    }
    return in;
}

bool operator<(const Mixed &frac1, const Mixed &frac2) {

    Mixed a,b;
    a = frac1;
    b = frac2;
    a.ToFraction();
    b.ToFraction();
    a.Simplify();
    b.Simplify();
    if((a.numer*b.denom) < (b.numer*a.denom))
        return true;
    else
        return false;
}
 bool operator<=(const Mixed &frac1, const Mixed &frac2){

     return (operator<(frac1,frac2) && operator==(frac1,frac2));

 }
bool operator>=(const Mixed &frac1, const Mixed &frac2){

    return (operator>(frac1,frac2)&& operator==(frac1,frac2));

}



bool operator>(const Mixed &frac1, const Mixed &frac2){

    Mixed a,b;
    a = frac1;
    b = frac2;
    a.ToFraction();
    b.ToFraction();
    a.Simplify();
    b.Simplify();
    if((a.numer*b.denom) > (b.numer*a.denom))
        return true;
    else
        return false;


}

bool operator==(const Mixed &frac1, const Mixed &frac2)
{
    Mixed numberone, numbertwo;
    numberone=frac1;
    numbertwo=frac2;
    numberone.ToFraction();
    numbertwo.ToFraction();
    numberone.Simplify();
    numbertwo.Simplify();
    if((numberone.numer == numbertwo.numer)&& (numberone.denom==numbertwo.denom))
        return true;
    else
        return false;


}

bool operator!=(const Mixed &frac1, const Mixed &frac2){


    return (!operator==(frac1,frac2));
}

Mixed operator +(const Mixed &frac1, const Mixed &frac2){


    Mixed addition;
    addition.integ=(frac1.integ+frac2.integ);
    addition.numer=(frac1.numer*frac2.denom)+(frac2.numer*frac1.denom);
    addition.denom=(frac1.denom*frac2.denom);

    addition.Simplify();
    return addition;

}
Mixed operator-(const Mixed &frac1, const Mixed &frac2){

    Mixed subtraction;
    subtraction.integ=(frac1.integ- frac2.integ);
    subtraction.numer=(frac1.numer*frac2.denom)-(frac2.numer*frac1.denom);
    subtraction.denom=(frac1.denom*frac2.denom);
    subtraction.Simplify();
    return subtraction;


}
Mixed operator *(const Mixed &frac1, const Mixed &frac2){

    Mixed multiplication;
    multiplication.integ=(frac1.integ*frac2.integ);
    multiplication.numer=(frac1.numer*frac2.numer);
    multiplication.denom=(frac1.denom*frac2.denom);
    multiplication.Simplify();
    return multiplication;

}
 Mixed operator /(const Mixed &frac1, const Mixed &frac2){
    Mixed division;
     int numerator= frac1.denom*frac1.integ+frac1.numer;
     int denominator= frac2.denom*frac2.integ+frac2.numer;
     int resulet= (numerator*frac2.denom);
     int resalet=(frac1.denom*denominator);
     division.integ= resulet/resalet;
     division.numer=numerator*denominator;
     division.denom=denominator;
     division.Simplify();
     return division;


}

Mixed Mixed::operator++(int ){
int integer=integ;
    int numerator=numer;
    int denominator=denom;

integ++;
    return Mixed(integer,numerator,denominator);

}
Mixed Mixed::operator++() {
    integ++;
    return Mixed(integ,numer,denom);
}

Mixed Mixed::operator--() {

    integ--;
    return Mixed(integ,numer,denom);

}
Mixed Mixed::operator--(int) {

    int integer=integ;
    int numerator=numer;
    int denominator=denom;

    integ--;
    return Mixed(integer,numerator,denominator);


}



