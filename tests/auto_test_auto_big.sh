#! /bin/bash

COUNT=$1
START=$1
ONE=0
TWO=0
THREE=0
while [[ $COUNT -gt 0 ]]
do
	./generator --big > big$COUNT.txt
	./lem-in -c < big$COUNT.txt > results_big$COUNT.txt
	# while read line
	# do
		
	# done <big$COUNT.txt
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
	done <results_big$COUNT.txt
	if [[ PLUS2 -le NUMB ]]
	then
		rm big$COUNT.txt
		rm results_big$COUNT.txt
		printf "GOOD --- expected [$NUMB]  output [$PLUS2]\n"
	else
		printf "ERROR --- expected [$NUMB]  output [$PLUS2]\n"
		if [[ PLUS2 -le "$NUMB + 1" ]]
		then
			ONE=$((ONE+1))
		elif [[ PLUS2 -le "$NUMB + 3" ]]
		then
			TWO=$((TWO+1))
		else
			THREE=$((THREE+1))
		fi
	fi
	#echo $COUNT
	COUNT=$((COUNT-1))
	if [[ COUNT -eq 0 ]]
	then
		printf "one over: $ONE/$START\nthree below: $TWO/$START\nover three: $THREE/$START"
	fi
done
# read from results files, save both expected lines and row, if same delete if not keep