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
	if [ "${MYPATH}" == "$location" ]
	then
		var=$((${MYPATH}/lem-in < $2) 2>&1 >/dev/null)
	else
		var=$((${MYPATH}/lem-in < ../$2) 2>&1 >/dev/null)
	fi
	if [ "$var" != "$var2" ]
	then
		printf "\n${RED}fail: ${UNCOLOR}\n"
		$4
		printf "$var\n"
	else
		printf "$var\n"
		printf "		${GREEN}ok${UNCOLOR}\n"
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

	# connection errors
	printf "\n${BLUE}connection tests${UNCOLOR}"
	test invalid "maps/error/connnec_too_few.map" "printf "Error"" error_put
	test invalid "maps/error/connnec_too_few1.map" "printf "Error"" error_put
	test invalid "maps/error/connnec_too_many.map" "printf "Error"" error_put
	test invalid "maps/error/connnec_too_many2.map" "printf "Error"" error_put
	test invalid "maps/error/connnec_too_many3.map" "printf "Error"" error_put
	test invalid "maps/error/connnec_too_many4.map" "printf "Error"" error_put
}

# function valid_test()
# {
# 	printf "\n${PURPLE}${BOLD}Valid tests${UNCOLOR}\n"

# 	#simple test
# 	printf "\n${BLUE}simple tests${UNCOLOR}"
# 	test valid "10 2 25" "printf "OK"" valid_put
# 	test valid "2 1 0" "printf "OK"" valid_put

# 	#big numbers
# 	printf "\n${BLUE}big number tests${UNCOLOR}"
# 	test valid "10 2 2147483647" "printf "OK"" valid_put
# 	test valid "10 -2147483648 25" "printf "OK"" valid_put
# 	test valid "10 2 2147483640" "printf "OK"" valid_put
# 	test valid "10 -2147483640 25" "printf "OK"" valid_put

# 	#more nbr test
# 	printf "\n${BLUE}more nbr tests${UNCOLOR}"
# 	test valid "-2 -6 3 7 5 -7 4 1 -1 -4 10 0 -8 2 -5 8 9 -3 6" "printf "OK"" valid_put
# 	test valid "1 10 3 7 9 5 4 6 8 2" "printf "OK"" valid_put
# 	test valid "5 8 1 6 3 2 7 9 4 10" "printf "OK"" valid_put
# 	test valid "11 112 56 289 249 5 95 219 180 288 32 159 18 222 155 3 189 88 212 49 23 13 6 15 242 92 205 133 244 67 29 28 102 97 229 162 85 267 45 210 278 277 250 146 172 169 203 218 76 103 293 128 208 173 225 253 87 127 254 195 104 224 197 99 271 186 188 198 167 191 57 89 80 16 234 279 136 48 290 265 143 248 247 163 200 129 226 154 168 60 19 257 58 252 141 204 176 156 164 196" "printf "OK"" valid_put
# 	test valid "8 7 3 10 5 2 6 1 4 9" "printf "OK"" valid_put
# 	test valid "9 8 2 7 10 3 4 5 6 1" "printf "OK"" valid_put
# 	test valid "2 3 1 7 9 8 4 10 6 5" "printf "OK"" valid_put
# 	test valid "6 5 8 7 1 9 4 2 3 10" "printf "OK"" valid_put
# 	test valid "7 6 1 3 -3 4 5 8 9 -2 10 2" "printf "OK"" valid_put
# 	test valid "30 20 4 10 -10 11 12 31 50 3 100 5" "printf "OK"" valid_put
# 	test valid "30 20 4 10 -9 3 -7 50 22 100" "printf "OK"" valid_put
# 	test valid "2 1 3 5 4 8 10 9 7 -50 -20 6" "printf "OK"" valid_put
# 	test valid "10 -3 2 -4 -8 -2 1 3 6 7 4 8 5 9" "printf "OK"" valid_put
# 	test valid "15 3 6 2 1 4 5 7 10 11 8 13 9 14" "printf "OK"" valid_put
# 	test valid "5 3 2 1 6 4" "printf "OK"" valid_put
# 	test valid "1 4 2 6 3 5" "printf "OK"" valid_put
# 	test valid "1 4 2 3 6 5" "printf "OK"" valid_put
# 	test valid "2 0 1 3 4 5 6 7 8 9 10" "printf "OK"" valid_put
# 	test valid "-5 8 -6 9 -9 10 2 3 1 4 0 -4 5 -8" "printf "OK"" valid_put
# 	test valid "2 -50 1 5 6 7 8 9 10 11 12 13" "printf "OK"" valid_put
# 	test valid "2 0 1 5 3 4 6 9 10 11 12 13" "printf "OK"" valid_put
# 	test valid "5 3 6 4 2 0 1" "printf "OK"" valid_put
# }

function main()
{
	make re -C ${MYPATH}
	error_test
	#valid_test
}

main
