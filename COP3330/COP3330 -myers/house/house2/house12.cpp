#include <iostream>
#include <cmath>
#include <iomanip>
#include "house1.h"
using namespace std;


House::House(int s, char boar='X', char fil='*')
{
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
    total= (size*3)+(2*(size+2))+2;
    return total;
}

double House::Area(){
    double tarea,theigth, squarea,area;

    squarea=(size*size);
    theigth=((size+2)/2)*(sqrt(3));
    tarea=(theigth*(size+2))/2;
    area=tarea+squarea;
    return area;
}
void House::Grow() {

   /* int temp=size;
    temp +=1;*
    if( temp<37){*/
    if(size<37){
        size++;
    }

}
void House::Shrink() {

    if (size>3){
        size--;
    }
}

void House::SetBorder(char boar) {

    if(boar>=33 && boar<=126){
        boarder=boar;
    }
}

void House::SetFill(char fill) {

    if(fill>=33 && fill<=126){
        inside=fill;
    }
}

void House::Draw() {

    for(int i=0; i<=size+2; i++)
    {
        for(int j=i; j<size+2; j++)
        {
            cout<< " ";
        }
        for(int j=0; j<i; j++)
        {
            if(j==0 || j==i-1)
            {
                cout<<boarder<<" ";
            }else cout<<inside<<"  ";
        }cout<<endl;
    }for(int i=0; i!=size; i++){
        cout<<" ";
        for(int j=0; j!=size; j++)
        {
           if(i==size-1|| j==0||j==size-1){
               cout<< size<<" ";
           } else cout<<inside<<" ";
        }
        cout<<endl;
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
