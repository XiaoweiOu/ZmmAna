#!/bin/bash

SEND_THREAD_NUM=6
tmp_fifofile=$$.fifo
mkfifo $tmp_fifofile
exec 1000<>"$tmp_fifofile"
rm -f $tmp_fifofile

for ((i=0;i<$SEND_THREAD_NUM;i++))
do
         echo >&1000
done

for((i=0;i<=56;i++))
do
 read -u1000
 {
  echo "****** PDF_${i} ******"
  nohup ./ZmmAna.exe ./filelist_CT14nnlo/filelist_${i}.list Pythia CT14_${i} 
  echo >&1000
 }&
done

echo "****** PDF finished ******"
