#!/bin/bash

./ZmmAna.exe filelist_MC_60_130.list MC 0 lumi1
mv result/MC_0_result.root result/MC_lumi1.root
./ZmmAna.exe filelist_MC_60_130.list MC 0 lumi2
mv result/MC_0_result.root result/MC_lumi2.root
./ZmmAna.exe filelist_MC_60_130.list MC 0 lumi3
mv result/MC_0_result.root result/MC_lumi3.root
