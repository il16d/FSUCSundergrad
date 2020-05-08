/* Assignment: Homework 5 ( Matrix)
 * Due date: March 22nd 2018
 * About this project: This project is able to take a matrix from the user and then find the biggest number in the matrix.
 * Assumptions: This program has no assumptions, negative numbers and doubles can be entered.
 * All work below was performed by Iho López.
 */



#include <iostream>
using namespace std;


const int ROWCAP=100;
const int COLCAP=100;
/*Set this two to constant so that the value stays
* the same during the whole life time of the program
 * */

void readValues(int arr[ROWCAP][COLCAP], int rows, int cols);

//void printValues(int arr[ROWCAP][COLCAP], int rows, int cols);

void findNorm(int arr[ROWCAP][COLCAP], int rows, int cols);

/* We use the global variables so that the capacity of the array
 * is not altered and remains always the same.
 */


int main() {

   int rows;
   int cols;

    cout<<"Enter the number of rows: "<<endl;
    cin>>rows;
    cout<<"Enter the number of columns: "<<endl;
    cin>>cols;

/*Prom the user to enter rows and columns desired
 *
 */

 int arr[ROWCAP][COLCAP];
 /* Declare an array that hold the amount of values
 * that the constant integers have been set to.
 */

    cout<<"Enter the matrix: " <<endl;

    readValues(arr, rows, cols);

    cout<<endl;
   // cout<<"The matrix is: "<<endl;
   // printValues(arr,rows,cols);
    findNorm(arr,rows,cols);






    return 0;
}

void readValues(int arr[ROWCAP][COLCAP], int rows, int cols)
{
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
            cin>>arr[i][j];
    }
}

/* For i starting at cero, i benig less than the rows entered by the user
 * increment i until we reach the number of rows entered by the user
 *repeate the process for the colums using a different variable (j)
 */



/*void printValues(int arr[ROWCAP][COLCAP], int rows, int cols)
{
    for(int i = 0; i< rows; i++)
    {
        for(int j =0; j<cols; j++)
        {
            cout<<arr[i][j]<<"\t";
        }
        cout<<endl;
    }
}
*/

void findNorm(int arr[ROWCAP][COLCAP], int rows, int cols){

    int j;
    //int num=1;
    int num=0;
    for(int i=0; i<rows; i++)
    {
        for (j=0; j<cols; j++)
        {
            if (arr[i][j]>num)
            {
                num=arr[i][j];

            }
        }


    }
    cout<<"The Max Norm is: "<<num <<endl;

}
/* starting at 0 going all the way until the rows prompted by the user.
 * same for cols (j).
 * every time that the number in the array is bigger than the int (num)
 * store it into num, repeat the proces until the number in num is the biggest one
 *
 * */