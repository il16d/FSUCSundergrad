/*
    stattest.cpp

    Chris Lacher
    11/11/14

    Testing Mean and Median from stats.t

    Reads numbers until non-number is read, then sends to standard output:

      the numbers read
      the mean
      the median
      the numbers sorted

    Copyright 2014, R.C. Lacher

*/

#include <cstdlib>
#include <iostream>
#include <fstream>

#include <stats.t>

// uncomment one of these to define the type of data:

// typedef   signed char    NumberType; // 1
// typedef   short          NumberType; // 2
// typedef   int            NumberType; // 3
// typedef   long           NumberType; // 4

// typedef   unsigned char  NumberType; // 5
// typedef   unsigned short NumberType; // 6
// typedef   unsigned int   NumberType; // 7
// typedef   unsigned long  NumberType; // 8

// typedef   float          NumberType; // 9
// typedef   double         NumberType; // 10
// typedef   long double    NumberType; // 11

// typedef   int8_t         NumberType; // 12
// typedef   int16_t        NumberType; // 13
// typedef   int32_t        NumberType; // 14
// typedef   int64_t        NumberType; // 15

// typedef   uint8_t        NumberType; // 16
// typedef   uint16_t       NumberType; // 17
// typedef   uint32_t       NumberType; // 18
// typedef   uint64_t       NumberType; // 19

template <typename T>
void ReadData (std::vector<T>& v, std::istream& is)
{
  T item;
  while (is >> item)
    v.push_back(item);
}

template <typename T>
void DisplayData (const std::vector<T>& v, std::ostream& os, char ofc)
{
  for (typename std::vector<T>::const_iterator i = v.begin(); i != v.end(); ++i)
  {
    if (ofc != '\0') os << ofc;
    os << *i;
  }
}

int main(int argc, char* argv[])
{
  std::vector<NumberType> input(0);
  std::ifstream ifs;
  if (argc < 2) // expects keyboard input
  {
    if (sizeof(NumberType) == sizeof(char))
    // keyboard input of type char is un-intuitve
    // when interpreted as a numerical type
    {
      std::cout << "Please provide filename containing data.\n";
      exit(EXIT_SUCCESS);
    }
    std::cout << "Enter numerical data: ";
    ReadData(input, std::cin);
  }
  else // reads from file - command line argument
  {
    ifs.open(argv[1]);
    if (ifs.fail())
    {
      std::cerr << "** Unable to open file " << argv[1] << " -- please try again\n";
      exit (EXIT_FAILURE);
    }
    ReadData(input, ifs);
  }

  // show data in original object:
  std::cout << "Data as entered: ";
  DisplayData(input, std::cout, ' ');
  std::cout << '\n';
  // */

  // display mean and median:
  std::cout << "Mean:   " << Mean(input) << '\n';
  std::cout << "Median: " << Median(input) << '\n';

  // display data after calls:
  std::cout << "Data after sort: ";
  DisplayData(input, std::cout, ' ');
  std::cout << '\n';
  // */

  return 0;
}
