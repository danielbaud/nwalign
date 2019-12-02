#!/bin/bash

echo
echo "LAUNCHING TESTSUITE"
echo
echo

echo -n "Making... "
make -s
if [ $? -ne 0 ]; then
    echo
    echo "Error in compilation"
    exit 1
fi
echo "Done"


echo -n "Cleaning... "
make -s clean
echo "Done"

