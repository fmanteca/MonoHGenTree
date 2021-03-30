import ROOT
import argparse
from math import *


""" -> FILL THE HISTOGRAMS <-

 >> Command:

python mkHistos.py --samples samples.py --variables variables.py --outputFile histos.root

"""





def createHistogram(tree, key, variable):

    histo = ROOT.TH1F(key, '', variable['nbins'], variable['range'][0], variable['range'][1])
    histo.GetXaxis().SetTitle(variable['label'])
    histo.GetYaxis().SetTitle('Events')
    

    tree.Draw("HiggsPt >> " + key)
    histo.Scale(1.0/histo.Integral());
    # for event in tree:

    #     histo.Fill(eval(variable['name']))

    return histo




if __name__ == '__main__':

    ########## main code here                                                                                                                                                                               
    parser = argparse.ArgumentParser(description = "Receive the parameters")
    parser.add_argument('--variables', action = 'store', type = str, dest = 'variables', help = 'Define the variables that are going to be plotted')
    parser.add_argument('--samples', action = 'store', type = str, dest = 'samples', help = 'Define the samples that are read')
    parser.add_argument('--outputFile', action = 'store', type = str, dest = 'outputFile', help = 'Name of the output file')

    args = parser.parse_args()



    ########## Open the output                                                                                                                                                                              

    file_output = ROOT.TFile(args.outputFile, 'RECREATE')


    ########## Fill the histograms                                                                                                                                                                          

    ########## Fill the histograms                                                                                                                                                                          
    samples = {}
    sampleFile = open(args.samples, 'r')
    exec(sampleFile)

    variables = {}
    variableFile = open(args.variables, 'r')
    exec(variableFile)


    ### -> Loop over the files                                                                                                                                                                              

    for sample, obj in samples.iteritems():

        tree = ROOT.TChain("demo/tree_", "")

        for f in samples[sample]['files']:

            tree.Add(f)

        for key, var in variables.iteritems():

            h = createHistogram(tree, samples[sample]['name'], var)
            file_output.cd()
            h.Write()

    file_output.Close()

