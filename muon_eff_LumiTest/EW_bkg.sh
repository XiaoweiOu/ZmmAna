#all EW background
#xwou wrote on 2018/11/21 at USTC

#!/bin/bash
sh Compile.sh
wait

SEND_THREAD_NUM=9
tmp_fifofile=$$.fifo
mkfifo $tmp_fifofile
exec 1000<>"$tmp_fifofile"
rm -f $tmp_fifofile

for ((i=0;i<$SEND_THREAD_NUM;i++))
do
         echo >&1000
done 

for ((ilumi=1;ilumi<=3;ilumi++))
do
read -u1000
{
 echo "****** ttbar ******"
 nohup ./ZmmAna.exe ./filelist_EWMC/filelist_ttbar.list EWMC ttbar lumi${ilumi} > ./out_EWMC/ttbar.out 
 echo >&1000
}&
read -u1000
{
 echo "****** WW ******"
 nohup ./ZmmAna.exe ./filelist_EWMC/filelist_WW.list EWMC WW lumi${ilumi} > ./out_EWMC/WW.out 
 echo >&1000
}&
read -u1000
{
 echo "****** WZ ******"
 nohup ./ZmmAna.exe ./filelist_EWMC/filelist_WZ.list EWMC WZ lumi${ilumi} > ./out_EWMC/WZ.out 
 echo >&1000
}&
read -u1000
{
 echo "****** Ztaotao_60_130 ******"
 nohup ./ZmmAna.exe ./filelist_EWMC/filelist_Ztaotao_60_130.list EWMC Ztaotao_60_130 lumi${ilumi} > ./out_EWMC/Ztaotao_60_130.out 
 echo >&1000
}&
read -u1000
{
 echo "****** Ztaotao_130_250 ******"
 nohup ./ZmmAna.exe ./filelist_EWMC/filelist_Ztaotao_130_250.list EWMC Ztaotao_130_250 lumi${ilumi} > ./out_EWMC/Ztaotao_130_250.out 
 echo >&1000
}&

for k in $(seq 1 19)
do
 read -u1000
 {
  echo "****** W0lp_${k} ******"
  nohup ./ZmmAna.exe ./filelist_EWMC/W0lp/filelist_W0lp_${k}.list EWMC W0lp_${k} lumi${ilumi} > ./out_EWMC/W0lp_${k}.out 
  echo >&1000
 }&
done

for k in $(seq 1 9)
do
 read -u1000
 {
  echo "****** W1lp_${k} ******"
  nohup ./ZmmAna.exe ./filelist_EWMC/W1lp/filelist_W1lp_${k}.list EWMC W1lp_${k} lumi${ilumi} > ./out_EWMC/W1lp_${k}.out 
  echo >&1000
 }&
done

read -u1000
{
 echo "****** W2lp ******"
 nohup ./ZmmAna.exe ./filelist_EWMC/filelist_W2lp.list EWMC W2lp lumi${ilumi} > ./out_EWMC/W2lp.out 
 echo>&1000
}&
read -u1000
{
 echo "****** W3lp ******"
 nohup ./ZmmAna.exe ./filelist_EWMC/filelist_W3lp.list EWMC W3lp lumi${ilumi} > ./out_EWMC/W3lp.out 
 echo >&1000
}&
read -u1000
{
 echo "****** W4lp ******"
 nohup ./ZmmAna.exe ./filelist_EWMC/filelist_W4lp.list EWMC W4lp lumi${ilumi} > ./out_EWMC/W4lp.out 
 echo >&1000
}&

read -u1000
{
 echo "****** W2b0lp ******"
 nohup ./ZmmAna.exe ./filelist_EWMC/filelist_W2b0lp.list EWMC W2b0lp lumi${ilumi} > ./out_EWMC/W2b0lp.out 
 echo >&1000
}&
read -u1000
{
 echo "****** W2b1lp ******"
 nohup ./ZmmAna.exe ./filelist_EWMC/filelist_W2b1lp.list EWMC W2b1lp lumi${ilumi} > ./out_EWMC/W2b1lp.out 
 echo >&1000
}&
read -u1000
{
 echo "****** W2b2lp ******"
 nohup ./ZmmAna.exe ./filelist_EWMC/filelist_W2b2lp.list EWMC W2b2lp lumi${ilumi} > ./out_EWMC/W2b2lp.out 
 echo >&1000
}&
read -u1000
{
 echo "****** W2b3lp ******"
 nohup ./ZmmAna.exe ./filelist_EWMC/filelist_W2b3lp.list EWMC W2b3lp lumi${ilumi} > ./out_EWMC/W2b3lp.out 
 echo>&1000
}&

read -u1000
{
 echo "****** W2c0lp ******"
 nohup ./ZmmAna.exe ./filelist_EWMC/filelist_W2c0lp.list EWMC W2c0lp lumi${ilumi} > ./out_EWMC/W2c0lp.out 
 echo >&1000
}&
read -u1000
{
 echo "****** W2c1lp ******"
 nohup ./ZmmAna.exe ./filelist_EWMC/filelist_W2c1lp.list EWMC W2c1lp lumi${ilumi} > ./out_EWMC/W2c1lp.out 
 echo >&1000
}&
read -u1000
{
 echo "****** W2c2lp ******"
 nohup ./ZmmAna.exe ./filelist_EWMC/filelist_W2c2lp.list EWMC W2c2lp lumi${ilumi} > ./out_EWMC/W2c2lp.out 
 echo >&1000
}&
read -u1000
{
 echo "****** W2c3lp ******"
 nohup ./ZmmAna.exe ./filelist_EWMC/filelist_W2c3lp.list EWMC W2c3lp lumi${ilumi} > ./out_EWMC/W2c3lp.out 
 echo >&1000
}&

done

wait
exec 1000>&-
echo "************* EW_bkg Finish!!!***********"
