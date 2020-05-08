/*
UIntset.h

*/

#ifndef _UINTSET_h
#define _UINTSET_h

#include <iostream>
#include <bitvect.h>

class UIntSet
{
public:
  UIntSet             (unsigned long = 64); //default consturctor
  UIntSet             ( const UIntSet&   ); //copy constructor
  ~UIntSet            ();

  void        Dump     ( std::ostream& os )const;        // displays underlying bitvector state
  void        Insert   ( unsigned long n  );        // inserts n into set
  void        Remove   ( unsigned long n  );        // removes n from set
  void        Clear    ();                          // makes set empty
  bool        Member   ( unsigned long n  ) const;  // returns true iff n is in set
  bool        Empty    () const;                    // true iff set is empty
  size_t      Size     () const;                    // returns number of elements in set
  size_t      Range    () const;                    // returns upper bound of range/universe [0,ub)

  UIntSet& operator =  (const UIntSet& s);  // set = s (assignment operator)
  UIntSet& operator += (const UIntSet& s);  // set = set union s
  UIntSet& operator *= (const UIntSet& s);  // set = set intersection s
  UIntSet& operator -= (const UIntSet& s);  // set = set difference s
  private:
  fsu::BitVector bv_; // bit vector reprsenting set

};

  UIntSet operator +  (const UIntSet& s1, const UIntSet& s2);  // returns s1 union s2
  UIntSet operator *  (const UIntSet& s1, const UIntSet& s2);  // returns s1 intersection s2
  UIntSet operator -  (const UIntSet& s1, const UIntSet& s2);  // returns s1 difference s2
  bool    operator == (const UIntSet& s1, const UIntSet& s2);  // true iff s1 and s2 are equal as sets
  bool    operator != (const UIntSet& s1, const UIntSet& s2);  // true iff s1 and s2 are not equal
  std::ostream& operator << (std::ostream& os, const UIntSet& s); // output operator

#endif
