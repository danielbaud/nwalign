#!/bin/bash

echo
echo "LAUNCHING TESTSUITE"
echo
echo

echo -n "Making... "
make -s
echo "Done"


echo -n "Cleaning... "
make -s clean
echo "Done"

