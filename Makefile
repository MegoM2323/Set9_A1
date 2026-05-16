CXX      = g++
CXXFLAGS = -std=c++17 -O2 -Wall

.PHONY: all experiment run plots cf clean

all: experiment

experiment: experiment.cpp string_generator.h string_sort_tester.h sorts.h
	$(CXX) $(CXXFLAGS) -o experiment experiment.cpp

run: experiment
	./experiment results.csv

plots: results.csv
	uv run --with matplotlib python3 plot.py

cf:
	$(CXX) $(CXXFLAGS) -o A1m  A1m.cpp
	$(CXX) $(CXXFLAGS) -o A1q  A1q.cpp
	$(CXX) $(CXXFLAGS) -o A1r  A1r.cpp
	$(CXX) $(CXXFLAGS) -o A1rq A1rq.cpp

clean:
	rm -f experiment A1m A1q A1r A1rq
