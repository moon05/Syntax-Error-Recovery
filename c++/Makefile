# Trivial makefile for the calculator scanner/parser.
# Depends on default (built-in) rules for C compilation.

# Note that rule for goal (parse) must be the first one in this file.

stars = **********************************

parse:
	g++ -std=c++14 parse.cpp scan.cpp -o parse

test: parse
	$(info ${stars})
	$(info ${stars})

	cat ./test.txt | ./parse
	echo "+++++++++++++++++++++";
	$(info ${stars})
	$(info ${stars})

	cat ./test2.txt | ./parse

	