


Parallel Physics Analysis Templates:

Multithreading descriptions of files and classes --

	data.list - This is the input data file list for the overall analysis,
				the list contains the absolute paths to all the Rootfiles that are going to be analyzed

	runmacro.py - this is python script to manage the input I/O from the data list
				  this script opens the data.list, parses the data list, then crafts they system command to launch the parallel analysis with specified input arguments

				the input arguments for runmacro.py are:
					--[1] the number of files to loop over in the data.list -> 0 specifies all files
					--[2] the number of threads requested in the analysis
					--[3] the name of the TTree of all the Rootfiles in the designated data.list
					--[4] the file tag - a unique string to distinguish different data lists e.g. "DY" for Drell Yan or "TTJ" for TTbar + Jets
					--[5] outputfilename - the name of the output root file that histograms will be written to
					--[6] output file option - either "RECREATE" or "UPDATE" when running over multiple datalists the first run should always recreate the file,
						  but secondary runs should update the file so its is (1) not overwritten each iteration and (2) all histograms are aggregated in the same file


	ParTreeProcessing.c - this is the function that manages all the classes in the analysis and also deals with multithreading task
						  this function enables the multithreading, loads the inputfiles into a list for the Tree multithread processor, defines a function to be
						  parallelized -> this function synchronizes the multithreaded reader with the reader that is created by default in the TSelector and give
					       the current thread loop values to the histset class.  After the function is defined the function is loaded into the processor to be multi 							   threaded, and finally histograms are written to an input file

						the input arguments for ParTreeProcessing.c are:

					--[1] the number of threads
					--[2] the file tag
					--[3] the output filename
					--[4] the output file option
					--[6]->[n] every argument input from 6 and beyond are input files from the data.list


	TSelector.h & TSelector.C -- this is the automatically generated "MakeClass" or MakeSelector that is mostly unmodified 
								( some minor details need to be changed for compiling) This class has all the generated code for accessing the variables of the
 								designated tree

	histset.c -- this is the class that houses the physics analysis.  Here all of the threaded objects are created on instantiation, and filled with the function
				 AnalyzeEntry. The objects are filled with the function Fill which manages the threaded ptrs and bookkeeping for each histogram. When the histograms
				 are written to file a data tag is appended to every root object name to distinguish identical histograms in different data sets. The tagging and
				 merging is automatically done by the class (which is made possible my carefully enumerating all of the histograms)

					the input arguemnts for histset.c are:

					--[1] the file tag


Instructions for running the parallel template
	
	an example of the sequence of input arguments are given in runmyanalysis.sh

 	to run the template on the t3, simply compile then run the shell script
		
			(1) make
			(2) ./runmyanalysis.sh

	To use the template as a application to a different analysis i.e. different data and trees

			(1) create a data.list which contains absolute paths to your rootfiles
			(2) add this data.list as an input argument for your runmacro.py

			(3) create your own TSelector from a tree in one of your input files
					(3a) To create a TSelector open a tree ("mytree") in the ROOT CLI then type mytree->MakeSelector("myselector")
						*I highly recommend naming the selector "myselector" this is the name hardcoded into the classes includes and makefile
						*light modifications need to be done to the TSelector to get it to compile
							-- add using namespace std to of myselector.h 
							-- at the top of myselector.C add directive #ifndef myselector_cxx
							-- at the end of myselector.C add directive #endif
							-- in the class definition of myselector.h remove or comment ClassDef(myselector,0)

			(4) create threaded histograms in histset.c
			(5) enumerate each threaded histogram 
			(6) write physics analysis in AnalyzeEntry
				*highly recommend copying into local ptrs with auto, otherwise code gets very unreadable and errorprone from scope problems
			(7) compile your changes with the Makefile
			(8) run multithreaded your analysis with runmacro.py
