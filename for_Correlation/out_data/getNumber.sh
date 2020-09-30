cat /lustre/AtlUser/xwou/ZmmAnaV2/Zmm/out/*.out | grep "Nll:" > num.txt
sed -s "s/Nll://" num.txt > Number.txt
rm -rf num.txt
echo "Nll:" > Sta_result.txt
./counting.exe >> Sta_result.txt

cat /lustre/AtlUser/xwou/ZmmAnaV2/Zmm/out/*.out | grep "Nh1h1:" > num.txt
sed -s "s/Nh1h1://" num.txt > Number.txt
rm -rf num.txt
echo "Nh1h1:" >> Sta_result.txt
./counting.exe >> Sta_result.txt

cat /lustre/AtlUser/xwou/ZmmAnaV2/Zmm/out/*.out | grep "Nh2h2:" > num.txt
sed -s "s/Nh2h2://" num.txt > Number.txt
rm -rf num.txt
echo "Nh2h2:" >> Sta_result.txt
./counting.exe >> Sta_result.txt

cat /lustre/AtlUser/xwou/ZmmAnaV2/Zmm/out/*.out | grep "Nh3h3:" > num.txt
sed -s "s/Nh3h3://" num.txt > Number.txt
rm -rf num.txt
echo "Nh3h3:" >> Sta_result.txt
./counting.exe >> Sta_result.txt

cat /lustre/AtlUser/xwou/ZmmAnaV2/Zmm/out/*.out | grep "Nh4h4:" > num.txt
sed -s "s/Nh4h4://" num.txt > Number.txt
rm -rf num.txt
echo "Nh4h4:" >> Sta_result.txt
./counting.exe >> Sta_result.txt  

cat /lustre/AtlUser/xwou/ZmmAnaV2/Zmm/out/*.out | grep "Nh1h1pp:" > num.txt
sed -s "s/Nh1h1pp://" num.txt > Number.txt
rm -rf num.txt
echo "Nh1h1pp:" >> Sta_result.txt
./counting.exe >> Sta_result.txt

cat /lustre/AtlUser/xwou/ZmmAnaV2/Zmm/out/*.out | grep "Nh2h2pp:" > num.txt
sed -s "s/Nh2h2pp://" num.txt > Number.txt
rm -rf num.txt
echo "Nh2h2pp:" >> Sta_result.txt
./counting.exe >> Sta_result.txt

cat /lustre/AtlUser/xwou/ZmmAnaV2/Zmm/out/*.out | grep "Nh3h3pp:" > num.txt
sed -s "s/Nh3h3pp://" num.txt > Number.txt
rm -rf num.txt
echo "Nh3h3pp:" >> Sta_result.txt
./counting.exe >> Sta_result.txt

cat /lustre/AtlUser/xwou/ZmmAnaV2/Zmm/out/*.out | grep "Nh4h4pp:" > num.txt
sed -s "s/Nh4h4pp://" num.txt > Number.txt
rm -rf num.txt
echo "Nh4h4pp:" >> Sta_result.txt
./counting.exe >> Sta_result.txt

cat /lustre/AtlUser/xwou/ZmmAnaV2/Zmm/out/*.out | grep "Nh1h1mm:" > num.txt
sed -s "s/Nh1h1mm://" num.txt > Number.txt
rm -rf num.txt
echo "Nh1h1mm:" >> Sta_result.txt
./counting.exe >> Sta_result.txt

cat /lustre/AtlUser/xwou/ZmmAnaV2/Zmm/out/*.out | grep "Nh2h2mm:" > num.txt
sed -s "s/Nh2h2mm://" num.txt > Number.txt
rm -rf num.txt
echo "Nh2h2mm:" >> Sta_result.txt
./counting.exe >> Sta_result.txt

cat /lustre/AtlUser/xwou/ZmmAnaV2/Zmm/out/*.out | grep "Nh3h3mm:" > num.txt
sed -s "s/Nh3h3mm://" num.txt > Number.txt
rm -rf num.txt
echo "Nh3h3mm:" >> Sta_result.txt
./counting.exe >> Sta_result.txt

cat /lustre/AtlUser/xwou/ZmmAnaV2/Zmm/out/*.out | grep "Nh4h4mm:" > num.txt
sed -s "s/Nh4h4mm://" num.txt > Number.txt
rm -rf num.txt
echo "Nh4h4mm:" >> Sta_result.txt
./counting.exe >> Sta_result.txt
