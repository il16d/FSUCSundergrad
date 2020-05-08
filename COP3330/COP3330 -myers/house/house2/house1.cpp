#include <iostream>
#include <cmath>
#include <iomanip>
#include "house1.h"
using namespace std;


House::House(int siz,  char boar, char fil)
{
    size=siz;
    if(size<3)
    {
        size=3;
    }
    if(size>37)
    {
        size=37;
    }
    boarder=boar;
    inside=fil;
}





int House::GetSize()
{
    return size;
}

int House::Perimeter()
{
    int total;
    total= (size*3)+(2*(size+2))+2;   //the perimeter is calculated by addding all the sides
    return total;
}

double House::Area(){
    double tarea,theigth, squarea,area;

    squarea=(size*size);  //claculates the area of the box
    theigth=((size+2)/2)*(sqrt(3)); //
    tarea=(theigth*(size+2))/2;
    area=tarea+squarea;
    return area;
}
void House::Grow() {


    if(size<37){
        size++;
    }

}
void House::Shrink() {

    if (size>3){
        size--;
    }
}

void House::SetBorder(char boar) { //this compares the valid ASCII valus that can be printed

    if(boar>=33 && boar<=126){
        boarder=boar;
    }else if(boar!=33||boar!=126)
	{boar='X';
		}
}

void House::SetFill(char fill) {

    if(fill>=33 && fill<=126){  //this compares the valid ASCII values that can  be printed
        inside=fill;
    }else fill='*';
}

void House::Draw() {

    for (int i = 0; i <= size + 2; i++) //the roof of the house is 2 more than the lenght of the box
    {
        for (int j = i; j < size + 2; j++) //for every i print spaces to space out the characters
        {
            cout << " ";
        }
        for (int j = 0; j < i; j++)
        {
            if (j == 0 || j == i - 1) //if we are on the outside of the triangle then print the border else print the fill
            {
                cout << boarder << " ";
            }
            else
            {
                cout << inside << " ";
            }
        }
        cout << endl;
    }
    for (int i = 0; i != size; i++) // starting at 0, not being at the lengh of the box print a space to indent the box
    {
        cout << "  ";
        for (int j = 0; j != size; j++) //loopa thru the house horizontally
        {
            if (i == size - 1 || j == 0 || j == size - 1) //print a border when we are at the bottom of the box(size-1) at the beginig of the indentation (j==0) and a the left side of the box (l==size-1)
            {
                cout << boarder << " ";
            }
            else
            {
                cout << inside << " ";
            }
        }
        cout << endl;
    }

}
void House::Summary() {

    cout<<"House size is: "<<GetSize()<<endl;
    cout<<"The house perimeter is: "<<Perimeter()<<endl;
    cout<<fixed<<showpoint;
    cout<<setprecision(2);
    cout<<"The area of the house is:"<<Area()<<endl;
    cout<<"The house is desplayed as: "<<endl;
    Draw();
}
