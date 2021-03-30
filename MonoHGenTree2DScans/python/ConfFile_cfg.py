import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.VarParsing import VarParsing
options = VarParsing ('analysis')
options.parseArguments()

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
                            fileNames = cms.untracked.vstring(options.inputFiles),
#        'file:/gpfs/projects/cms/fernanpe/DarkHiggs_MonoHs_HsToWWTo2l2nu_mhs_160_mx_100_mZp_200_TuneCP5_13TeV/RunIISummer20UL18_wmLHEGEN/210318_222632/0000/wmLHEGEN_94.root'
#        'file:/gpfs/users/mantecap/CMSSW_11_1_0/src/MonoHGenTree/MonoHGenTree2DScans/python/merged.root'
#        'file:/gpfs/projects/cms/fernanpe/DarkHiggs_MonoHs_HsToWWTo2l2nu_mhs_160_mx_100_mZp_200_TuneCP5_13TeV/RunIISummer20UL18_wmLHEGEN/210318_222632/0000/wmLHEGEN_inRAWSIM_*.root'
#    )
)

process.demo = cms.EDAnalyzer('MonoHGenTree2DScans'
)

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string(options.outputFile),
#                                   fileName = cms.string("GenInfoTree.root")
                                   )

process.p = cms.Path(process.demo)
