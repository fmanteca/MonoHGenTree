#!/bin/bash
cd /gpfs/users/mantecap/CMSSW_11_1_0/src/MonoHGenTree/MonoHGenTree2DScans/python
eval `scramv1 runtime -sh`
ls /gpfs/projects/cms/fernanpe/DarkHiggs_MonoHs_HsToWWTo2l2nu_mhs_250_mx_200_mZp_1900_TuneCP5_13TeV/RunIISummer20UL18_wmLHEGEN/*/*/wmLHEGEN_inRAWSIM_*.root|sed 's/^/file:/'>list/list_250_200_1900.txt
cmsRun merge.py outputFile=/gpfs/projects/cms/fernanpe/DarkHiggs_MonoHs_HsToWWTo2l2nu_hadd/merged_250_200_1900.root inputFiles_load=list/list_250_200_1900.txt
cmsRun ana.py inputFiles="file:/gpfs/projects/cms/fernanpe/DarkHiggs_MonoHs_HsToWWTo2l2nu_hadd/merged_250_200_1900.root" maxEvents=-1
cmsRun ConfFile_cfg.py inputFiles="file:/gpfs/projects/cms/fernanpe/DarkHiggs_MonoHs_HsToWWTo2l2nu_hadd/merged_250_200_1900.root" outputFile=/gpfs/projects/cms/fernanpe/DarkHiggs_MonoHs_HsToWWTo2l2nu_trees/tree_250_200_1900.root
