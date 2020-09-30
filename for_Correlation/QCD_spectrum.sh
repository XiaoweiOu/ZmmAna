#hate a long time waitting data loop
#xwou wrote on 2019/1/14

#!!!!!problem!!!!!
#result will be covered!!!!!!!!!!

#!/bin/bash
SEND_THREAD_NUM=9
tmp_fifofile=$$.fifo
mkfifo $tmp_fifofile
exec 1000<>"$tmp_fifofile"
rm -f $tmp_fifofile

date -d now > Time.out

for ((i=0;i<$SEND_THREAD_NUM;i++))
do
         echo >&1000
done

for k in $(seq 1 9)
do
 read -u1000
 {
  echo "****** data_${k} ******"
  ./ZmmAna.exe ./filelist_data/filelist_data${k}.list data ${k} > ./out_QCDspectrum/data${k}.out
  echo >&1000
 }&
done
