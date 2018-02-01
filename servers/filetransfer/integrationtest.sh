#!/bin/bash

clear
#sudo fuser -n tcp -k 22000
#sleep 10

SEXEC=fserver
CEXEC=fclient
SDIR=testserver
CDIR=testclient
CWD=`pwd`

# Setup working dir
mkdir -p $SDIR $CDIR
rm -rf ${SDIR}/*.out ${SDIR}/*.log                                                          
rm -rf ${CDIR}/*.out ${CDIR}/*.log

# Compile server and client
make clean && make server && make client && \
	mv $CEXEC ${CDIR} && \
	mv $SEXEC ${SDIR}                                      
		    
set -x

# Run server
cd ${CWD}/${SDIR}
nohup ./${SEXEC} &> /dev/null & 
SERVPID=$!
sleep 40
echo "server started with pid ${SERVPID}" 

# Run client
cd ${CWD}/${CDIR}
./${CEXEC}
echo

# check transfered files
ls -l
echo
ls -lh

set +x
# Compare transfered files with the originals
for i in $(ls ${CWD}/${CDIR}/*.out | xargs -n 1 basename); 
do
	diff <(xxd ${CWD}/${CDIR}/${i}) <(xxd ${CWD}/${SDIR}/${i})
done

cat ${CWD}/${CDIR}/client.log
cat ${CWD}/${SDIR}/server.log

kill $SERVPID
