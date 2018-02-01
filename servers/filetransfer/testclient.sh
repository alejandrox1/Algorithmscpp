#!/bin/bash

ls -l
echo
ls -lh

for i in $(ls *.out); 
do
	diff <(xxd ${i}) <(xxd ../testserver/${i})
done

