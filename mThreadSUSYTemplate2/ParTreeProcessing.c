//#include "TROOT.h"
//
#ifndef PARTREE
#define PARTREE

#include "TH1D.h"
#include "TH2D.h"
#include "ROOT/TThreadedObject.hxx"
//#include "ROOT/Math/GenVector/LorentzVector.h"
#include "Math/GenVector/LorentzVector.h"

#include "ROOT/TTreeProcessorMT.hxx"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include <vector>
#include "TFile.h"
#include "histset.c"
#include "myselector.C"

#include <iostream>

int main(int argc, char *argv[])
{

   //set nthreads from first input argument
   int nthreads = std::atoi (argv[1]);

  //set treename to read from second input argument
  std::string treename(argv[2]);

  //set the data tag from 3rd input argument
  //always need a tag, if you dont want this "" should work
  std::string tag(argv[3]);

  //set outputfilename in 4th input argument
  std::string ofilename(argv[4]);

  //set outputfileOption in 5th argument .. either recreate or udpate
  std::string ofileoption(argv[5]);

   // First enable implicit multi-threading globally, so that the implicit parallelisation is on.
   // The parameter of the call specifies the number of threads to use.
   ROOT::EnableImplicitMT(nthreads);


   //load up the list of files to be processed
   //all the remaining input arguments are files to be added to the TChain
   std::vector<std::string_view> ifilelist{};
   for(int i=6; i<argc; i++){
	ifilelist.push_back(std::string_view(argv[i]));
   }
	
   //Create our ThreadedHistograms and Analysis Class
   histset h(tag);

  //make our parallel tree processor
   ROOT::TTreeProcessorMT tp(ifilelist,treename.c_str());
   // Define the function that will process a subrange of the tree.
   // The function must receive only one parameter, a TTreeReader,
   // and it must be thread safe. To enforce the latter requirement,
   // TThreadedObject histograms will be used.
   //
   auto myFunction = [&](TTreeReader &myReader) {

	//create our values to be read
	myselector s(myReader.GetTree());

	//copy the tree onto the selector
	//s.Init(myReader.GetTree());

      while (myReader.Next()) {
	//synchronize the threaded readed with private selector set of variables
	//s.fReader.SetEntry(myReader.GetCurrentEntry());
	s.GetEntry(myReader.GetCurrentEntry());
	//analyze the current set of variables with hist set  class
	h.AnalyzeEntry(s); 
	
      }
   };
   // Launch the parallel processing of the tree

   tp.Process(myFunction);
	
  //automatically do all merging and writing
  h.WriteHist(ofilename, ofileoption);
	
   return 0;
}
#endif

