#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "lexer-v2-1.h"

/*
   forwards
 */
void program();
void stmt_list(char *parent);
void stmt(char *parent);
void expression(char *parent);
void term_tail(char *parent);
void term(char *parent);
void factor_tail(char *parent);
void factor(char *parent);
void add_op(char *parent);
void multiply_op(char *parent);


// utility
char *make_label();



// Let's go!

void parse_2_15(char *filename)
{

  // graphviz output
  printf("digraph { node [shape=\"record\"]\n\n");
  //

  lexer_reset(filename);
  program();

  // graphviz output
  printf("}\n\n");
  //
}

void program(char *parent)
{
  // graphviz output
  char *label = make_label();
  printf("\"node%s\" [ label = \"program | %s\" ]; \n",
	 label,
	 current_token);
  //

  stmt_list(label);

  // graphviz
  free(label);
  //
}

void stmt_list(char *parent)
{
  // graphviz output
  char *label = make_label();
  printf("\"node%s\" [ label = \"stmt_list | %s\" ]; \n",
	 label,
	 current_token);
  printf("\"node%s\" -> \"node%s\" ;\n",parent,label);
  //

  stmt(label);
  if(current_token)
    stmt_list(label);
  
  // graphviz
  free(label);
  //
}

void stmt(char *parent)
{
  // graphviz output
  char *label = make_label();
  printf("\"node%s\" [ label = \"stmt | %s\" ]; \n",
	 label,
	 current_token);
  printf("\"node%s\" -> \"node%s\" ;\n",parent,label);
  //

  if(try_match("read"))
    {
      advance();
      must_match(identifier);
    }
  else if(try_match("write"))
    {
      advance();
      expression(label);
    }
    else if (try_match("goto"))
    {
        advance();
        // modify the parser to also recognize the label
        expression(label);
    }
    //To recognize a DESTINATION, 
    else if (try_match("location"))
    {
        advance();
        // you can use the already existing "identifier" regular expression.
        must_match(identifier);
    }
  else if(try_match(identifier))
    {
      advance();
      must_match(":=");
      expression(label);
    }
  else
    {
      fail("Not a statement!?");
    }
  
  // graphviz
  free(label);
  //
}

void expression(char *parent)
{
  // graphviz output
  char *label = make_label();
  printf("\"node%s\" [ label = \"expression | %s\" ]; \n",
	 label,
	 current_token);
  printf("\"node%s\" -> \"node%s\" ;\n",parent,label);
  //

  term(label);
  term_tail(label);

  // graphviz
  free(label);
  //
}


void term_tail(char *parent)
{
  // graphviz output
  char *label = make_label();
  printf("\"node%s\" -> \"node%s\" ;\n",parent,label);
  //

  if(try_match("[+-]"))
    {
      // graphviz output
      printf("\"node%s\" [ label = \"term_tail | %s\" ]; \n",
	     label,
	     current_token);
      //

      add_op(label);
      term(label);
      term_tail(label);
    }
  else
    {
      // graphviz output
      printf("\"node%s\" [ label = \"term_tail | %s\" ]; \n",
	     label,
	     "*EPSILON*");
      // graphviz output
    }

  // graphviz
  free(label);
  //
}

void term(char *parent)
{
  // graphviz output
  char *label = make_label();
  printf("\"node%s\" [ label = \"term | %s\" ]; \n",
	 label,
	 current_token);
  printf("\"node%s\" -> \"node%s\" ;\n",parent,label);
  //


  factor(label);
  factor_tail(label);

  // graphviz
  free(label);
  //
}

void factor_tail(char *parent)
{
  // graphviz output
  char *label = make_label();
  printf("\"node%s\" -> \"node%s\" ;\n",parent,label);
  //

  if(try_match("[*/]"))
    {
      // graphviz output
      printf("\"node%s\" [ label = \"factor_tail | %s\" ]; \n",
	     label,
	     current_token);
      //

      multiply_op(label);
      factor(label);
      factor_tail(label);
    }
  else
    {
      printf("\"node%s\" [ label = \"factor_tail | %s\" ]; \n",
	     label,
	     "*EPSILON*");
    }

  // graphviz
  free(label);
  //
}

void factor(char *parent)
{
  // graphviz output
  char *label = make_label();
  printf("\"node%s\" [ label = \"factor | %s\" ]; \n",
	 label,
	 current_token);
  printf("\"node%s\" -> \"node%s\" ;\n",parent,label);
  //

  if(try_match("[(]"))
    {
      advance();
      expression(label);
      must_match("[)]");
    }
  else if(try_match(identifier))
    {
      advance();
    }
  else if(try_match(number))
    {
      advance();
    }
  else
    fail("Did not find a factor where expected.");

  // graphviz
  free(label);
  //
}

void add_op(char *parent)
{
  // graphviz output
  char *label = make_label();
  printf("\"node%s\" [ label = \"add_op | %s\" ]; \n",
	 label,
	 current_token);
  printf("\"node%s\" -> \"node%s\" ;\n",parent,label);
  //

  if(try_match("[+-]"))
    {
      advance();
    }
  else
    fail("Did not find add operation");

  // graphviz
  free(label);
  //
}

void multiply_op(char *parent)
{
  // graphviz output
  char *label = make_label();
  printf("\"node%s\" [ label = \"multiply_op | %s\" ]; \n",
	 label,
	 current_token);
  printf("\"node%s\" -> \"node%s\" ;\n",parent,label);
  //

  if(try_match("[*]"))
    {
      advance();
    }
  else if(try_match("/"))
    {
      advance();
    }
  else
    fail("Did not find multipy operation");

  // graphviz
  free(label);
  //
}


// utility

char *make_label()
{
  static int count = 0;
  char buffer[128];

  sprintf(buffer,"%05d",count);
  count++;

  return(strdup(buffer));
}
