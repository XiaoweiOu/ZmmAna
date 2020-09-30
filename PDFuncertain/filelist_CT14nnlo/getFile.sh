#!/bin/bash

for((i=0;i<=56;i++))
do
 ls /lustre/AtlUser/whma/Tevatron/datafiles/pdfmember_${i}/*.root > ./filelist_${i}.list
done
