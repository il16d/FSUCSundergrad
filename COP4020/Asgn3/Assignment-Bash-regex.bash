#!/bin/bash

# 
# 
# NAME: [PLEASE REPLACE THIS WITH YOUR NAME]

src_file="words.txt"

regex1='^([[:alpha:]])([[:alpha:]])[[:alpha:]]\2\1$' #five letter palindromes
regex2='^([[:alpha:]])([[:alpha:]])([[:alpha:]])\3\2\1$' #six letter palindromes
regex3='^([[:alpha:]])([[:alpha:]])([[:alpha:]])[[:alpha:]]\3\2\1$' #seven letter palindromes
regex4='(([[:alpha:]])\2)[[:alpha:]]*\1'
regex5='([[:alpha:]])\1[[:alpha:]]*([[:alpha:]])\2[[:alpha:]]*([[:alpha:]])\3'



#
#  DO NOT MODIFY BELOW THIS LINE
#

echo 'These are the five letter palindromes:'
egrep $regex1 $src_file

echo ' '
echo 'These are the six letter palindromes:'
egrep $regex2 $src_file

echo ' '
echo 'These are the seven letter palindromes:'
egrep $regex3 $src_file

echo ' '
echo 'These are the words that contain at least two instances of the same doubled characters (such as willfully (contains ll twice) and riffraff (contains ff twice)):'
egrep $regex4 $src_file

echo ' '
echo 'These are the words that contain at least three instances of doubled characters (such as bookkeeper  (oo, kk, and ee) and keenness (ee, nn, and ss):'
egrep $regex5 $src_file
