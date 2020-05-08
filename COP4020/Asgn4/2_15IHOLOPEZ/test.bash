#!/bin/bash


tests="test.calc test2.calc test3.calc test4.calc"
declare -A expected
expected[test.calc]=pass
expected[test2.calc]=fail
expected[test3.calc]=pass
expected[test4.calc]=pass

for name in ${tests}
do
    ./2_15 $name 1> /dev/null 2> /dev/null
    if [ $? == 0 ]
    then
	if [ ${expected[$name]} == "pass" ]
	then
	    echo "Success : $name was expected to pass, and it did"
	else
	    echo "FAILURE : $name was expected to pass, and it did not"
	fi
    else
	if [ ${expected[$name]} == "fail" ]
	then
	    echo "Success : $name was expected to fail, and it did"
	else
	    echo "FAILURE : $name was expected to fail, and it did not"
	fi
    fi	
done
