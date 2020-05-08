/*
wordsmith.h

COP4530
Feb 16th, 2017
*/


#include <iostream>
#include <string>
#include <cctype>


 void WordSmith::Cleanup ( fsu::String& line )
{
  const char * ch = (line.Cstr());

  fsu::String str;
  int size = (line.Length() + 1);
  size_t j = 0;
  char copy[size] ;
  
for(size_t i = 0; i < strlen(ch); i++)
{
  if ( ch[i] == '\0' || isalpha(ch[i]) || isdigit(ch[i]) || ch[i] == '\\' || ch[i] == '-' )
  { 
    
    // ch is a letter or a digit
   
    if ( isalpha(ch[i]) || isdigit(ch[i]) )       
      {
          copy[j] = ch[i];
          ++j;        
      }
   
    // ch is apostrophe and next char is a letter or digit
    if (ch[i+1] == '\'' && ( isalpha( ch[i+2] ) || isdigit( ch[i+2]) )  )
      {
        ++i;
        copy[j] = ch [i];
        ++j;
        ++i;
        copy[j] = ch [i];
        ++j;
      }

    // ch is hyphen and next char is a digit or (previous and next is a letter)
    if (ch[i] == '-' && (   (isalpha(ch[i-1]) && isalpha(ch[i+1])) || isdigit(ch[i+1]))  )
      {
        copy[j] = ch [i];
        ++j;   
      }

    // check for more than one hyphen
    if ( ch[i] == '-' && ch[i+1] == '-')
      i = strlen(ch); // break for loop and put in null terminator

    // ch is period and next char is a letter or digit
    if (ch[i+1] == '.' && ( isalpha( ch[i+2] ) || isdigit( ch[i+2]) )  )
      {
        ++i;
        copy[j] = ch [i];
        ++j;       
      }
   

    // ch is comma and next char is a letter
    if (ch[i+1] == ',' &&  isalpha(ch[i+2]) )
       i = strlen(ch);  //break for loop and put in null terminator  
    
  
    // ch is comma and is surrounded by digits
    if (ch[i+1] == ',' && ( isdigit( ch[i] ) && isdigit( ch[i+2]) )  )
      {
        ++i;
        copy[j] = ch [i];
        ++j;   
      }

    // ch is colon and is surrounded by digits
    if (ch[i+1] == ':' && ( isdigit( ch[i] ) && isdigit( ch[i+2])) )
      {
        ++i;
        copy[j] = ch [i];
        ++j;
        ++i;
        copy[j] = ch [i];
        ++j;   
      }

    // ch is colon and next two char are colon
    if (ch[i+1] == ':' &&  ch[i+2] == ':' && ch[i+3] == ':'  )
    {
      i = strlen(ch);  //break for loop and put in null terminator  
    }

    // ch is the first or second of a pair of colons, the pair surrounded by letters or digits
    if (  (ch[i+1] == ':' && ch[i+2] == ':') && ( (isalpha(ch[i-1]) && isalpha(ch[i+3])) || (isdigit( ch[i-1] ) && isdigit( ch[i+3])) || (isdigit(ch[i-1]) && isalpha(ch[i+3])) ||(isalpha(ch[i-1]) && isdigit(ch[i+3])))                      )
      {
        ++i;
        copy[j] = ch [i]; // put first : in
        ++j;
        ++i;
        copy[j] = ch [i]; // put second : in
        ++j;   
      } 

    if ( ch[i+1] != '\0' && !isalpha(ch[i+1]) && !isdigit(ch[i+1]) && ch[i+1] != '\\' && ch[i+1] != '-' )
    {
          i = strlen(ch);
    }

  } //main if

  } //end for loop
 
  copy[j] = '\0'; //   
  // std::cout << "copy[] " << copy << std::endl;
  line.Wrap(copy);
  //line = str;

 // make all letters lowercase
  for (size_t i = 0; i < line.Length(); i++)
  {
    line[i] = tolower(line[i]);   
  } 

} //cleanup end
