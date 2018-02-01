#!/bin/bash

EXEC=fclient
CMPDIR=../testserver

# Run client
./${EXEC}

# check transfered files
ls -l
echo
ls -lh

# Compare transfered files with the originals
for i in $(ls *.out); 
do
	diff <(xxd ${i}) <(xxd ${CMPDIR}/${i})
done

