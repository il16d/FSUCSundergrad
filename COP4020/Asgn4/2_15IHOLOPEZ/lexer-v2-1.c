/*


  reset()
  advance()
  try_match()
  must_match()

  Both of these maintain a "current_token".

  exposes also

  char *current_token;              // a dynamically allocated version of the current token
  char *next_token;

  int current_token_first_char      // the character number (respects UTF-8) in the buffer
  int line_number[];                // line number indexed by character number
  int char_number[];                // character number in line indexed by character number
  char *line_position[];            // where each line starts in memory; indexed by line number


*/


#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <regex.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdbool.h>

#define LEXER_TRUE
#include "lexer-v2-1.h"



// make an initial pass, collect position of all lines and every character

int total_line_count = 0;   // cache the total number of lines
char **line_position;       // for each line, where does it start in memory (index is line number)
int *line_number;           // for each character, what line does it appear in (index is offset from beginning)
int *char_number;           // for each character, what character in line does it appear in (index is offset from beginning)





// exported

char *current_token = NULL;
char *next_token = NULL;

int current_token_first_char;
int next_token_first_char;


static unsigned char *first_char = NULL;
static unsigned char *current_char = NULL;
static unsigned char *last_char = NULL;


       
// declarations
char *consume(void);
bool countable_character(char x);


// UTILITY

   /* 
    * 
    * memorymap_file()  
    * 
    *
    *   
    */

void memorymap_file(char *file, char **start, char **lastchar)
{
  struct stat stat_buff;
  int ret = stat(file,&stat_buff);
  if(ret == -1)
    {
      fail("Error: stat(2) failed for file '%s'\n",file);
    }
  size_t file_size = (size_t) stat_buff.st_size;

  int fd = open(file,O_RDONLY);
  if(fd == -1)
    {
      fail("Error: open(2) failed for file %s\n",file);
    }

  *start = mmap(NULL,           // Any location in memory is fine
                file_size,      // Length of the file
                PROT_READ,      // Let us read the file
                MAP_PRIVATE,    // We don't need to share this
                fd,             // Our file descriptor
                0);             // Start at the beginning
  *lastchar = *start + file_size;

  close(fd);                    // Apparently this is fine; look at man mmap(2)
  
  return;
}

void map_lines_chars(char *mmap_first_char, 
		     char *mmap_last_char);



//     CODE

void lexer_reset(char *file)
{

  if(first_char != NULL)
    {
      munmap(first_char,last_char-first_char);
    }   

  char *mmap_first_char;
  char *mmap_last_char;

  memorymap_file(file,&mmap_first_char,&mmap_last_char);

  map_lines_chars(mmap_first_char,mmap_last_char);

  first_char = (unsigned char *)mmap_first_char;
  current_char = (unsigned char *)mmap_first_char;
  last_char = (unsigned char *)mmap_last_char;

  current_token = consume();
  current_token_first_char = next_token_first_char;
  next_token = consume();
}

void must_match(char *wanted)
{
  if(!try_match(wanted))
    {
      fail("lexer --- match for tag '%s' failed, current_token is '%s'",wanted,current_token);
    }
  advance();
}

int regex_test(char *wanted, char *token)
{
  regex_t regex_wanted;

  // add boundaries to the "wanted" regular express to make sure 
  // that we are not doing a substring match  

  int length = strlen(wanted);
  char *bounded = (char *)malloc(length+3);
  strcpy(bounded+1,wanted);
  bounded[0] = '^';
  bounded[length+1] = '$';
  bounded[length+2] = '\0';

  int ret = regcomp(&regex_wanted,bounded,REG_EXTENDED|REG_NOSUB|REG_NEWLINE);
  if(ret != 0)
    {
      fail("lexer try_match(): Did not compile regex '%s'!\n",wanted);
    }

  if(regexec(&regex_wanted,token,0,NULL,0) == 0)
    {
      ret = 1;
    }
  else
    {
      ret = 0;
    }

  regfree(&regex_wanted);
  free(bounded);

  return(ret);
  
}

int try_lookahead(char *wanted)
{
  if(current_token == NULL)
    {
      return(0);
    }
  if(next_token == NULL)
    {
      return(0);
    }

  return(regex_test(wanted,next_token));
}

int try_match(char *wanted)
{
  if(current_token == NULL)
    {
      return(0);
    }

  return(regex_test(wanted,current_token));
}


void advance()
{
  if(current_token)
    free(current_token);

  current_token = next_token;
  current_token_first_char = next_token_first_char;

  next_token = consume();
}


typedef enum {Looking, Midst} lexer_state;
char *consume(void)
{
  unsigned char *start = current_char;
  // tentatively
  next_token_first_char = (int) (current_char - first_char);

  lexer_state state = Looking;
  while(current_char < last_char)
    {
      // okay, let's try to deal with the Unicode issue

      // the problem is that I really would like to be able
      // to use 【】 and ※ as lexically significant characters

      // while I am able to *include* them in any
      // lexical token, recognizing these *at* this level as
      // lexically significant is entirely different; this
      // of the code is built around type 'char'...
      
      switch(*current_char)
	{

	  // white space rules
	case ' ':
	case '\t':
	case '\n':

	  current_char++;

	  // if we find whitespace while in Midst state, we are done looking
	  if(state == Midst)
	    {
	      return(strndup((const char *)start,(size_t)(current_char-start-1)));
	    }
	  break;


	  // These single characters do not have to be space-delimited in order to
	  // be picked up as lexically significant

	case 0xe3:  // looking for a 【 or 】, e38090 or e38091

	  if(current_char < last_char - 2)
	    {
	      if(*(current_char+1) == 0x80 && *(current_char+2) == 0x90)
		{
		  current_char+=3;
		  return(strdup("【"));
		}
	      if(*(current_char+1) == 0x80 && *(current_char+2) == 0x91)
		{
		  current_char+=3;
		  return(strdup("】"));
		}
	      
	    }
	  state = Midst;
	  break;

	case ')':
	case '(':
	case '{':
	case '}':
	case ',':
	case ';':


	  if(state == Looking)
	    {
	      next_token_first_char = (int)(current_char - first_char);
	      current_char++;
	      return(strndup((const char *)current_char-1,1));
	    }
	  else
	    {
	      return(strndup((const char *)start,(size_t)(current_char-start)));
	    }
	  break;


	  // An interesting case: I would like to use := for assignment, and : for
	  // for types. In either case, it's lexically significant.

	case ':':
	  
	  if(state == Looking)
	    {
	      // try to peek ahead
	      if(current_char < last_char)
		{
		  if(*(current_char+1) == '=')
		    {
		      current_char+=2;
		      return(strdup(":="));
		    }
		}
	      current_char++;
	      return(strdup(":"));
	    }
	  else
	    {
	      return(strndup((const char *)start,(size_t)(current_char-start)));
	    }
	  break;
 
	  // Check for comments

	case 0xe2:

	  // looking for a Japanese comment marker '※'s
	  if(current_char < last_char - 3)
	    {
	      if(*(current_char+1) == 0x80 &&
		 *(current_char+2) == 0xbb)
		{
		  current_char+=3;
		  while( *current_char != '\n' )
		    {
		      current_char++;
		    }
		  current_char++;
		}
	      else
		{
		  state = Midst;
		  current_char++;
		}
	    }

	  break;

	  /*
	case '/':
	  if(current_char < last_char)
	    {
	      if(*(current_char+1) == '*')
		{
		  // starting a delimited comment
		  current_char+=2;
		  while( (*current_char != '*') || (*(current_char+1) != '/') )
		    {
		      current_char++;
		    }
		  current_char+=2;
		}
	      else if(*(current_char+1) == '/')
		{
		  // starting an to-end-of-line comment
		  current_char+=2;
		  while( (*current_char != '\n') )
		    {
		      current_char++;
		    }
		  current_char++;
		}
	      else
		{
		  state = Midst;
		  current_char++; // ??
		}
	    }
	  break;
	  */


	  // Check for strings, which are an interesting case. We will allow \" as an escape.
	  // No ideas yet about other escapes.

	case '"':
	  if(state == Midst)
	    {
	      fail("lexer: quote mark indicating a new string found while in the middle of something else!");
	    }

	  start = current_char;
	  next_token_first_char = (int) (current_char - first_char);

	  current_char++;
	  while( (*current_char != '"') || (*(current_char-1) == '\\') )
	    {
	      current_char++;
	    }
	  current_char++;

	  return(strndup((const char *)start,(size_t)(current_char-start)));

	  break;


	default:
	  
	  if(state == Looking)
	    {
	      start = current_char;
	      next_token_first_char = (int) (current_char - first_char); 
	      state = Midst;
	    }
	  current_char++;

	  break;
	  
	}
    }

  // end of input
  return(NULL);
}


void map_lines_chars(char *mmap_first_char, char *mmap_last_char)
{
  size_t count = mmap_last_char - mmap_first_char;
  line_position = calloc(sizeof(char *),count);
  line_number = calloc(sizeof(int),count);
  char_number = calloc(sizeof(int),count);

  total_line_count = 1;
  int internal_char_count = 0;
  line_position[0] = 0;
  char *at = mmap_first_char;
  while(at < mmap_last_char)
    {
      if(*at == '\n')
	{
	  total_line_count++;
	  internal_char_count = 0;
	  if(at+1 < mmap_last_char)
	    line_position[total_line_count] = at+1;
	  else
	    line_position[total_line_count] = NULL;
	}
      else
	{
	  // if we are in the middle of a utf-8 character, don't increment the character counts
	  if( countable_character(*at) )
	    {
	      internal_char_count++;
	    }

	  line_number[(int)(at - mmap_first_char)] = total_line_count;
	  char_number[(int)(at - mmap_first_char)] = internal_char_count;
	}
      at++;
    }
}

// tests whether this is a "countable" (non-UTF-8-interior character)
bool countable_character(char x)
{
  if( (x & 0xC0) == 0x80 )
    {
      return(true);               // if exactly the high bit is set and the next is not
    }
  if( (x & 0x80) == 0x00 )
    {
      return(true);               // if neither is set
    }
  return(false);
}

void display_line(int line_number)
{
  if(line_number < total_line_count)
    {
      printf("%.*s",
	     (int)(line_position[line_number+1] - line_position[line_number]),
	     line_position[line_number]);
    }
  else
    printf("%s\n",line_position[line_number]);
}

void display_cursor(int char_number)
{
  int i;
  for(i=0;i<char_number-1;i++)
    printf(" ");
  printf("^\n");
}


void fail(char *string, ...)
{
  va_list args;
  va_start(args,string);
  printf("*** Error at line %d:\n",line_number[current_token_first_char]);
  display_line(line_number[current_token_first_char]);
  display_cursor(char_number[current_token_first_char]);
  printf("*** \n");
  fprintf(stderr,"at line %d, char position %d: ",line_number[current_token_first_char],char_number[current_token_first_char]);
  vfprintf(stderr,string,args);
  fprintf(stderr,"\n");
  va_end(args);
  exit(1);
}

