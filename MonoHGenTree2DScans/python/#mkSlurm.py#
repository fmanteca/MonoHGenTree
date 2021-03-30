import os, sys, stat
import ROOT as r
from array import array
import numpy as np
import random

# python mkSlurm.py /gpfs/users/mantecap/CMSSW_11_1_0/src/MonoHGenTree/MonoHGenTree2DScans/python

templateSlurm = """#!/bin/bash
cd CMSSWRELEASE
eval `scramv1 runtime -sh`
ls /gpfs/projects/cms/fernanpe/DarkHiggs_MonoHs_HsToWWTo2l2nu_mhs_MDH_mx_MCHI_mZp_MZPR_TuneCP5_13TeV/RunIISummer20UL18_wmLHEGEN/*/*/wmLHEGEN_inRAWSIM_*.root|sed 's/^/file:/'>list/list_MDH_MCHI_MZPR.txt
cmsRun merge.py outputFile=/gpfs/projects/cms/fernanpe/DarkHiggs_MonoHs_HsToWWTo2l2nu_hadd/merged_MDH_MCHI_MZPR.root inputFiles_load=list/list_MDH_MCHI_MZPR.txt
cmsRun ana.py inputFiles="file:/gpfs/projects/cms/fernanpe/DarkHiggs_MonoHs_HsToWWTo2l2nu_hadd/merged_MDH_MCHI_MZPR.root" maxEvents=-1
cmsRun ConfFile_cfg.py inputFiles="file:/gpfs/projects/cms/fernanpe/DarkHiggs_MonoHs_HsToWWTo2l2nu_hadd/merged_MDH_MCHI_MZPR.root" outputFile=/gpfs/projects/cms/fernanpe/DarkHiggs_MonoHs_HsToWWTo2l2nu_trees/tree_MDH_MCHI_MZPR.root
"""

########################## Main program #####################################
if __name__ == "__main__":

    cmsswRelease = sys.argv[1]
    mhs = ["160","180","200","250","300","350","400"] 
    mx = ["100","150","200","300"]
    mZp = ["200","300","400","500","600","700","800","900","1000","1100","1200","1300","1400","1500","1600","1700","1800","1900","2000","2100","2200","2300","2400","2500"] 

    for hs in mhs:
        for chi in mx:
            for Zp in mZp:
                
                template = templateSlurm
                template = template.replace('CMSSWRELEASE', cmsswRelease)
                template = template.replace('MDH', hs)
                template = template.replace('MCHI', chi) 
                template = template.replace('MZPR', Zp)
                f = open('slurm/send_mhs_' + hs + '_mx_' + chi + '_mZp_' + Zp + '.sh', 'w')
                f.write(template)
                f.close()
                os.chmod('slurm/send_mhs_' + hs + '_mx_' + chi + '_mZp_' + Zp + '.sh', 0755)     
    













     

