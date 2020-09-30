gcc -g -Wl,--copy-dt-needed-entries -std=c++1y -fpermissive Main.C State.C CorrelationTool.C -I$ROOTSYS/include `root-config --libs ` -lMinuit -o Overall_Correlation_help.exe
