#include <iostream>
#include <cmath>
using namespace std;

int arraytofint(int const arr[], int S);
//arr for array of ints S for the size.

void test (int x, int y);

void circle (int x, double pi=3.14);


int fibo(int x);


int main() {



    //tow dimensional arrays

   // int tec [3]={9,6,4};
  //  int tec2 [3] [2] = {(3,2), (5,6), (8,9)};









    //declaration
    int points[20];
    //initialization
    int marks[5]={7,4,9,8,7};
    cout<<"Elements of the array are: "<<endl;

    for (int i=0; i<5; i++)
    {

        cout<<marks[i]<<endl;


    }
    int total []={3,5,8,4};
cout<<"The elements of total are: "<<endl;
    for (int i=0; i<5; i++)
    {

        cout<<total[i]<<endl;


    }

    int test[3]={7};


    for (int i=0; i<20; i++)
    {
        cin>>points[i];
    }



    int a=10; int b=20;
    test(10,20);



int c;
    cin>>c;
    cout <<fibo(a)<<endl;


    //Exercice 13 part 1:

    int counter=0;

    int arr[]={1,3,19,24,32,0,21,-7,16,8};

    for (int i=0; i<10; i++)
    {
        if (arr[i]%2==0){

            counter++;
           // cout <<"The odd values of the array are "<< arr[i]<<endl;
        }
            //counter++;
       // cout <<"The odd values of the array are "<< arr[i]<<endl;
    }

    cout<<"The count of odd numbers is: "<< counter<<endl;

//Exercice 13 Part 2:
    int counter2=0;
    int arr2[]={5,16,-7,21,19,-567,47,0,-456,-12,9,-8};

    for (int i =0; i<12; i++)
    {
        if (arr2[i]<0)

            counter2++;

    }cout<<"The negative numbers are: "<<counter2<<endl;


    //Exercice 3

    int values[100];
    int N; //size that hte user is goint to determinte the array to be
    cout<<"Enter the numbers of elements that you want to put into the array: "<<endl;
    cin>>N;
    if (N>100)
    {
        cout<<"N is too big"<<endl;
        return 0;
    }

    cout<< "Enter the numbers ";
    for (int i=0; i<N; i++)
    {
        cin>>values[i];
    }cout <<"The difference is "<< arraytofint(values,N)<<endl;

    return 0;
}



int arraytofint(int const arr[], int S)
{
    int sumeven=0;
    int sumodd=0;
   for (int i=0; i<S; i++)
   {
       if (arr[i]%2==0){
           sumeven=arr[i]+sumeven;
       }else sumodd=arr[i]+sumodd;


   }
    int difference= abs(sumeven-sumodd);

    return difference;
}

void test (int p, int q)
{
    cout << p << endl <<q << endl;

}

void circel(int p, double q)
{


    cout<< "The area is "<< q*p*p<<endl;


}


int fibo(int x)
{
    if (x==1)
        return 1;
    else
        return x * fibo (x-1);


}