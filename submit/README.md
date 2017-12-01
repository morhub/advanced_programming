# advanced_programming
This repository contains the programming assignments for Advanced Programming course, on CS school, TAU, Winter 2017

Maintainers: Nitzan Carmi, Mor Huberman

HW1:
===
This program solves small puzzles, as mentioned below:
-> Gets a list of parts (class Part) from input file.
-> Start Preprocessing on the list, to see if it can quickly decide that there is no solution
   (all corners exist, sum of each row/col is 0, etc.).
-> Stores all parts in more complex and useful  Data structure:
	- A main Map of all possible Parts, based on their <left, top> edges configuration (total of 9 Parts).
	  Each Map value is another Map - mapping the Part lists based on their <right, bottom> edges configuration.
	- Every part list in the maps represents "identical" parts (different by only their IDs).

-> Goes through all possible rows/columns combinations (when integers rows, cols should match rows * cols = NumElements).
   For each combination, tries to solve seperately.
-> For given rows/cols configuration, tries to fill rows * cols recuresivley:
	- Starting with (0,0), it goes directly to relevant <left,top> Mapping, and tries to connect every possible
	  fitting <right, bottom> configuration (if it has a relevant unused part in the list).
	- Continue until reaching the end of table, or no possible configurations left.
-> Write Table output to output file.

Compilation/Install:
$ make

Usage:
$ ./ex1 <input file> <output file>
