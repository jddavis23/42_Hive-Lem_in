# 42-lem-in

## ABOUT

Program that intelligently select paths. Main focus of the creation of this program was to get acquainted with graph traversal algorithms.

The goal of the program is to get an ant colony from the 'start' room to the 'end' room in as few turns as possible. The following rules have to be followed:

  Each room can only contain one ant at a time
  (except 'start' and 'end' which can contain as many ants as necessary)
  
  Each turn an ant can only be moved once and the room they are moving to has to be free.


## HOW TO RUN LEM-IN

	1. make all
	2. the executable lem-in should have been created
    
    ./lem-in < eval_maps/generated_maps/big-superposition1.txt


## HOW TO RUN TEST FILES

	1. first we have to go into the tests folder
  
    cd tests
    
	2. make sure you have a compiled version of your lem-in before running the following command.
     the number 10 can be replaced with any positive digit.
     it will in this case generate 10 big-superposition maps and run it with the lem-in outside this folder.
		
		./auto_test.sh 10


## HOW TO RUN VISUALIZER

In order to run the visualizer make sure you have python3 and pygame installed. Below visualizer is run by pressing space bar and or by using the arrow keys left and right to show the different stages of the ants movements. The visualizer only works with the maps specified in the visual folder.

This visualizer is not very useful but it does have some nice colors!

	1. be in the root repository and run the following command
	
		./lem-in < visual/subject2-0.map | ./visual/visu-hex
