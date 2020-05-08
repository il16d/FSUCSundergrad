/*
product.h

*/

#include <iostream>
#include <cstdint>
#include <cstdlib>

#ifndef PRODUCT_H_
#define PRODUCT_H_

class Product
{
public:
  void        SetName    ( const char* ); //sets the name field
  void        SetBarCode ( uint32_t );    //sets the bar code field
  void        SetCost    ( float );       //sets the cost field
  const char* GetName    () const;        //returns a const pointer to the name field
  uint32_t    GetBarCode () const;        //returns the bar code by value
  float       GetCost    () const;        //returns cost by value

  Product (); //name "#" code = 0 cost 0
  Product (const char* name, uint32_t code, float cost);
  ~Product ();
  Product (const Product& p);
  Product& operator= (const Product& p);

private:
  char *   name_; //the product name
  uint32_t code_; //the product bar code
  float    cost_; //the product cost
};

std::ostream& operator << (std::ostream& os, const Product& p);

#endif 
