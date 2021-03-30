import csv




#mhs = ["160"] 
mhs = ["160","180","200","250","300","350","400"] 
mx = ["100","150","200","300"]
mZp = ["200","300","400","500","600","700","800","900","1000","1100","1200","1300","1400","1500","1600","1700","1800","1900","2000","2100","2200","2300","2400","2500"] 

with open('xsecs.csv', 'w') as out:
    for hs in mhs:
        for chi in mx:
            for Zp in mZp:
                with open('log/logfile_mhs_' + hs  +'_mx_' + chi + '_mZp_' + Zp + '.log') as f:
                    for idx,line in enumerate(f):
                        if idx>0:
                            continue
                        out.write(hs + "\t" + chi + "\t" + Zp + "\t" + line.split()[0]  + "\n")
                f.close()

out.close()
#                    print idx, [int(x) for x in line.split()]
                    #if idx==1:
                    #    print line
