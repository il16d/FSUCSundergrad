/*
  main.cpp

  9/4/2015
  version 1.9
*/

#include<iostream>

#include<stats.h>

int main()
{
  const int sizeOfArray = 100;
  int a[sizeOfArray];
  unsigned int counter = 0;

  std::cout << "Enter integers ('x' to quit): ";

  for(unsigned int i = 0; i < sizeOfArray; ++i)
  {
    if( i >= 1 )
      ++counter;
    std::cin >> a[i];
    if(std::cin.fail())
      break;
  }

  std::cout << "\nData as entered: ";

  for(unsigned int i = 0; i < counter; ++i) //outputs users origonal array
  {
    std::cout << " " << a[i];
  }

  std::cout << "\nMean: " << Mean(a,counter);
  std::cout << "\nMedian: " << Median(a,counter);

  std::cout << "\nSorted array: ";
  
  for(unsigned int i = 0; i < counter; ++i) //outputs sorted array
  {
    std::cout << " " << a[i];
  }

  std::cout << "\n";
      
  return 0;

} //end main
