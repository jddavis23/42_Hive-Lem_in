#!/bin/bash
MYPATH="/Users/molesen/Desktop/Hive/lemin"
command -v $MYPATH/lem-in >/dev/null 2>&1 || { printf "\nlem-in not found!\n"; exit 1; }
LOCALPATH="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# colors
BOLD="\033[1m"
RED="\033[0;31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
PURPLE="\033[35m"
CYAN="\033[36m"
UNCOLOR="\033[0m"

# $1: i
function error_put()
{
	printf "EXPECTED OUTPUT: Error"
	printf "\nYOUR OUTPUT IS: "
}

function valid_put()
{
	printf "\nEXPECTED OUTPUT: "
	printf "OK"
	printf "\nYOUR OUTPUT IS:"
}

function number_put()
{
	printf "\nEXPECTED OUTPUT: "
	printf "OK"
	printf "\nYOUR OUTPUT IS:"
}

# $1: type test $2: nbr input $3: var2 $5: fnctn error
function test()
{
	printf "\n$1 test: ${YELLOW}./lem-in < $2${UNCOLOR}\n"
	var2=$($3)
	location=$(pwd)
	if [ "${MYPATH}" == "$location" ];
	then
		var=$(${MYPATH}/lem-in < $2)
		#var=$((${MYPATH}/lem-in < $2) 2>&1 >/dev/null)
	else
		var=$(${MYPATH}/lem-in < ../$2)
		#var=$((${MYPATH}/lem-in < ../$2) 2>&1 >/dev/null)
	fi
	if [ "OK" == "$var2" ];
	then
		printf "var: $var\n"
	else
		if [[ "$var" == *"$var2"* ]];
		then
			printf "${GREEN}[${UNCOLOR}$var${GREEN}]${UNCOLOR}\n"
			printf "		${GREEN}ok${UNCOLOR}\n"
		else
			printf "\n${RED}fail: ${UNCOLOR}\n"
			$4
			printf "$var\n"
		fi
	fi
}

function error_test()
{
	printf "\n${PURPLE}${BOLD}Error tests${UNCOLOR}\n"

	test invalid "maps/error/space_begin.map" "printf "Error"" error_put

	# incorrect ants errors
	printf "\n${BLUE}incorrect ants tests${UNCOLOR}"
	test invalid "maps/error/ant_non.map" "printf "Error"" error_put
	test invalid "maps/error/ant_neg.map" "printf "Error"" error_put
	test invalid "maps/error/ants_non_space_begin.map" "printf "Error"" error_put
	test invalid "maps/error/ants_zero.map" "printf "Error"" error_put
	test invalid "maps/error/ant_above_max_int1.map" "printf "Error"" error_put
	test invalid "maps/error/ant_above_max_int2.map" "printf "Error"" error_put
	test invalid "maps/error/ant_above_max_int3.map" "printf "Error"" error_put

	# coordinates errors
	printf "\n${BLUE}coordinates tests${UNCOLOR}"
	test invalid "maps/error/coor_too_few.map" "printf "Error"" error_put
	test invalid "maps/error/coor_too_many.map" "printf "Error"" error_put
	test invalid "maps/error/coor_too_big1.map" "printf "Error"" error_put
	test invalid "maps/error/coor_too_big2.map" "printf "Error"" error_put
	test invalid "maps/error/coor_too_big3.map" "printf "Error"" error_put
	test invalid "maps/error/coor_one_room.map" "printf "Error"" error_put
	test invalid "maps/error/coor_non_digit.map" "printf "Error"" error_put
	test invalid "maps/error/coor_non_digit2.map" "printf "Error"" error_put
	test invalid "maps/error/coor_begin_space.map" "printf "Error"" error_put
	test invalid "maps/error/coor_begin_L.map" "printf "Error"" error_put

	# connection errors
	printf "\n${BLUE}connection tests${UNCOLOR}"
	test invalid "maps/error/connec_too_few.map" "printf "Error"" error_put
	test invalid "maps/error/connec_too_few1.map" "printf "Error"" error_put
	test invalid "maps/error/connec_too_many.map" "printf "Error"" error_put
	test invalid "maps/error/connec_too_many2.map" "printf "Error"" error_put
	test invalid "maps/error/connec_too_many3.map" "printf "Error"" error_put
	test invalid "maps/error/connec_too_many4.map" "printf "Error"" error_put
	test invalid "maps/error/connec_begin_space.map" "printf "Error"" error_put
	test invalid "maps/error/connec_begin_L.map" "printf "Error"" error_put

	# comments errors
	printf "\n${BLUE}connection tests${UNCOLOR}"
	test invalid "maps/error/start_end_wrong_location.map" "printf "Error"" error_put
	test invalid "maps/error/start_end_wrong_location2.map" "printf "Error"" error_put
	test invalid "maps/error/start_end_wrong_location3.map" "printf "Error"" error_put
	test invalid "maps/error/start_end_wrong_location4.map" "printf "Error"" error_put
	test invalid "maps/error/start_end_double.map" "printf "Error"" error_put

	# parse errors
	printf "\n${BLUE}parse tests${UNCOLOR}"
	test invalid "maps/error/dublicate.map" "printf "Error"" error_put
	test invalid "maps/error/error_double_comment.map" "printf "Error"" error_put
	test invalid "maps/error/error_double_start.map" "printf "Error"" error_put
	test invalid "maps/error/no_room.map" "printf "Error"" error_put
}

function valid_test()
{
	printf "\n${PURPLE}${BOLD}Valid tests${UNCOLOR}\n"

	#simple test
	printf "\n${BLUE}simple tests${UNCOLOR}"
	test valid "maps/subject.map" "printf "OK"" valid_put
	test valid "maps/subject2-0.map" "printf "OK"" valid_put
	test valid "maps/subject2-1.map" "printf "OK"" valid_put
	test valid "maps/subject2-2.map" "printf "OK"" valid_put
	test valid "maps/subject3.map" "printf "OK"" valid_put
	test valid "maps/comments_hash_3.map" "printf "OK"" valid_put
	test valid "maps/multi2.map" "printf "OK"" valid_put
	test valid "maps/wierd_names.map" "printf "OK"" valid_put
	test valid "maps/briffard.map" "printf "OK"" valid_put
	test valid "maps/briffard2.map" "printf "OK"" valid_put
	test valid "maps/alphabet.map" "printf "OK"" valid_put
	test valid "maps/alphabet-easy.map" "printf "OK"" valid_put
	test valid "maps/subject-name.map" "printf "OK"" valid_put
}

function main()
{
	make re -C ${MYPATH}
	error_test
	valid_test
}

main
