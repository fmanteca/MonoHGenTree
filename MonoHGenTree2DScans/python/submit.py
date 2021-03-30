import os
import shutil
import glob

mhs = ["160","180","200","250","300","350","400"] 
mx = ["100","150","200","300"]
mZp = ["200","300","400","500","600","700","800","900","1000","1100","1200","1300","1400","1500","1600","1700","1800","1900","2000","2100","2200","2300","2400","2500"] 


for hs in mhs:
    for chi in mx:
        for Zp in mZp:

            subcom = 'sbatch -o log/logfile_mhs_' + hs + '_mx_' + chi + '_mZp_' + Zp + '.log -e err/errfile_mhs_' + hs + '_mx_' + chi + '_mZp_' + Zp + '.err --qos=gridui_medium --partition=cloudcms slurm/send_mhs_' + hs + '_mx_' + chi + '_mZp_' + Zp + '.sh'
            os.system(subcom)


 
 


                    


