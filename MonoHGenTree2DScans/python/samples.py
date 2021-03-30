
mhs = ["160","180","200","250","300","350","400"] 
#mhs = ["160"] 
#mx = ["100"]
mx = ["100","150","200","300"]
mZp = ["200","300","400","500","600","700","800","900","1000","1100","1200","1300","1400","1500","1600","1700","1800","1900","2000","2100","2200","2300","2400","2500"] 

for hs in mhs:
    for chi in mx:
        for Zp in mZp:
            samples['Histo_mhs_' + hs + '_mx_' + chi + '_mZp_' + Zp] = {'name' : 'Histo_mhs_' + hs + '_mx_' + chi + '_mZp_' + Zp,
                                                                        'files' : ['/gpfs/projects/cms/fernanpe/DarkHiggs_MonoHs_HsToWWTo2l2nu_trees/tree_' + hs + '_' + chi + '_' + Zp +'.root']}


