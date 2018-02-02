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
sleep 39
echo "server started with pid ${SERVPID}" 
ps $SERVEPID

# Run client
cd ${CWD}/${CDIR}
time ./${CEXEC}
echo

# check transfered files
# only usefule when comparing a handful of transfers
#ls -l
#echo
#ls -lh

set +x
[ $(ps $SERVPID | tail -n 1 | awk '{print $3}') == "S+" ] && echo Ready to Go
ps $SERVPID

# Compare transfered files with the originals
echo "comparing all files with diff and xxd..."
for i in $(ls ${CWD}/${CDIR}/*.out | xargs -n 1 basename); 
do
	diff <(xxd ${CWD}/${CDIR}/${i}) <(xxd ${CWD}/${SDIR}/${i})
done

echo "comparing sorted log files..."
diff <(sort ${CWD}/${CDIR}/client.log) <(sort ${CWD}/${SDIR}/server.log)

kill $SERVPID
