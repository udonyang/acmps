CXX=g++
CPPFLAGS += -std=c++11

main: main.cc

.PHONY: run
run:
	@for i in *.in; do echo "test $${i}"; cat $${i} | ./main; done
