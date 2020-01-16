#
# Now depends on the boost library
# On my laptop this in the standard search path.
# On the CRC cluster, "module load boost" 
# sets the BOOSTINCLUDE environment variable
# The makefile still works if this is undefined - the case on my laptop.
#

main: histset.o myselector.o ParTreeProcessing.c
	g++ -o compiledthreads ParTreeProcessing.c -pthread -I ${BOOSTINCLUDE} `root-config --cflags --libs`

histset.o: histset.c myselector.o
	g++ -c  histset.c -pthread -I ${BOOSTINCLUDE} `root-config --cflags --libs`

myselector.o: myselector.C myselector.h
	g++ -c -pthread myselector.C `root-config --cflags --libs` 

clean:
	rm *.o
