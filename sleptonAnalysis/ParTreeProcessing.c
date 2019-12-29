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

  //set output eventselection filename
  std::string evtselname = "EventSelTables_"+tag+".table";

   // First enable implicit multi-threading globally, so that the implicit parallelisation is on.
   // The parameter of the call specifies the number of threads to use.
   ROOT::EnableImplicitMT(nthreads);

   
   //load up the list of files to be processed
   //all the remaining input arguments are files to be added to the TChain
   std::vector<std::string_view> ifilelist{};
   //we need a regular string list to deal with SMS, cant get treenames without c_strings and view cant be a cstr
   std::vector<std::string> ifileliststr{};
   for(int i=6; i<argc; i++){
	ifilelist.push_back(std::string_view(argv[i]));
	ifileliststr.push_back(std::string(argv[i]));
   }

  //if the treename is SMS we need to store all of the tree mass points and loop over the file list for every tree
  //
  //
  std::vector<std::string> treenames{};
  if(treename.compare("SMS") == 0){
	std::cout<<"Detected treename SMS"<<std::endl;
	//loop over the masspoints and store the tree names in a vector
	//read in file from tagname and save treenames 
	
	
    for(int i=0; i< ifilelist.size(); i++){
	std::cout<<"Examining File "<<ifileliststr.at(i)<<" with nkeys = ";
    	TFile* t_file  = TFile::Open(ifileliststr.at(i).c_str());
	int nkeys =  t_file->GetNkeys();
	std::cout<<nkeys<<std::endl;
	for(int j=0; j< nkeys; j++){
		std::string trnm = std::string(t_file->GetListOfKeys()->At(j)->GetName() );
		if (trnm.find("SMS") != std::string::npos) {
 		   treenames.push_back( trnm );
		}
		
	}
    }
   // print out tree names
   // loop over tree sequence
 
  //file for evt selection
  ofstream evtSelFile;
  evtSelFile.open(evtselname);
 
  std::cout<<"all tree print: "<<std::endl;
  for(int i=0; i<treenames.size(); i++){
	std::cout<<treenames.at(i)<<std::endl;
 	
	 tag = treenames.at(i);
	 histset h(tag);
	 ROOT::TTreeProcessorMT tp(ifilelist, treenames.at(i).c_str());
	 auto myFunction = [&](TTreeReader &myReader) {
		myselector s;
		s.Init(myReader.GetTree());
		while(myReader.Next()){
			s.fReader.SetEntry(myReader.GetCurrentEntry());
			h.AnalyzeEntry(s);
		}
	};
	tp.Process(myFunction);
	if(i==0){
		h.WriteHist(ofilename, "RECREATE");
		
	}	
	else{
		h.WriteHist(ofilename, "UPDATE");
	}

	h.printSelectionTables(evtSelFile);
  }
 evtSelFile.close();
	
  return 0;	
  }
  else{
	//regular BG tree, just store the KUAnalysis tree on the vector so both can be processed in a standard way
//	treenames.push_back(treename);
	std::cout<<"was not SMS "<<std::endl;	
   //Create our ThreadedHistograms and Analysis Class
   histset h(tag);

  //make our parallel tree processor
   ROOT::TTreeProcessorMT tp(ifilelist,treename.c_str());
   // Define the function that will process a subrange of the tree.
   // The function must receive only one parameter, a TTreeReader,
   // and it must be thread safe. To enforce the latter requirement,
   // i
   //
   // ;TThreadedObject histograms will be used.
   //
   auto myFunction = [&](TTreeReader &myReader) {

	//create our values to be read
	myselector s;

	//copy the tree onto the selector
	s.Init(myReader.GetTree());

      while (myReader.Next()) {
	//synchronize the threaded readed with private selector set of variables
	s.fReader.SetEntry(myReader.GetCurrentEntry());
	//analyze the current set of variables with hist set  class
	h.AnalyzeEntry(s); 
	
      }
   };
   // Launch the parallel processing of the tree

   tp.Process(myFunction);
	
  //automatically do all merging and writing
  h.WriteHist(ofilename, ofileoption);

   //process event selection tables
  //create a text file 
  ofstream evtSelFile;
  evtSelFile.open(evtselname);
  h.printSelectionTables(evtSelFile);
  evtSelFile.close(); 

   return 0;

  }
}
#endif

