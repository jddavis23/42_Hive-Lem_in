#! /bin/bash

COUNT=$1
while [[ $COUNT -gt 0 ]]
do
	
	./generator --flow-one > flow-one$COUNT.txt
	./lem-in -r < flow-one$COUNT.txt > results_flow-one$COUNT.txt
	# while read line
	# do
		
	# done <flow-one$COUNT.txt
	while read line
	do
		if [[ "$line" == *"row"* ]]
		then
			COMP=${line//[^0-9]/}
			#echo "ORIGINAL $COMP"
			CHECK="$COMP"
			PLUS=${CHECK: 2}
			PLUS2=$(echo $PLUS | rev)
			PLUS=${PLUS2: 2}
			PLUS2=$(echo $PLUS | rev)
		fi
		if [[ "$line" == *"Here is the number of lines required"* ]]
		then
			NUMB=${line//[^0-9]/}
			#echo $NUMB
		fi
	done <results_flow-one$COUNT.txt
	if [[ PLUS2 -le NUMB ]]
	then
		rm flow-one$COUNT.txt
		rm results_flow-one$COUNT.txt
		printf "GOOD --- expected [$NUMB]  output [$PLUS2]\n"
	else
		printf "ERROR --- expected [$NUMB]  output [$PLUS2]\n"
	fi
	#echo $COUNT
	COUNT=$((COUNT-1))
done
# read from results files, save both expected lines and row, if same delete if not keep