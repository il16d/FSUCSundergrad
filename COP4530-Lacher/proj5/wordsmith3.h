/*  

wordsmith3.h
March 5, 2017
*/

#include <xstring.h>
#include <list.h>
#include <map_adt.h>

class WordSmith
{
public:
  WordSmith           ();
  virtual ~WordSmith  ();
  bool   ReadText     (const fsu::String& infile, bool showProgress = 0);
  bool   WriteReport  (const fsu::String& outfile,
                       unsigned short kw = 15,   // key col width 
                       unsigned short dw = 15,   // data col width
                       std::ios_base::fmtflags kf = std::ios_base::left, // key
                                                                         // justify 
                       std::ios_base::fmtflags df = std::ios_base::right // data
                                                                         // justify
                       )  const;
  void   ShowSummary  () const;
  void   ClearData    ();

private:
  typedef fsu::String              KeyType;
  typedef size_t                   DataType;

  size_t                           count_;
  fsu::Map_ADT  < KeyType , DataType > frequency_;
  fsu::List < fsu::String >        infiles_;
  static void Cleanup  (fsu::String& s); // optional 
} ;
