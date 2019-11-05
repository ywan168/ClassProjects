/**
 * An implementation of page replacement algorithm using CLOCK Algorithm (Second Chance)
 * @PA-2 (Page Repalcement Algorithm-CLOCK)
 * @author Yanfang Wang
 * @LSU ID: 89-7080-995
 * @since 03-31-2019
 * @see CLOCK.cpp
 * @Email: ywan168@lsu.edu
 */*

Files included in the prog2 directory: CLOCK.cpp compile.sh pageref.txt pageref-small.txt test.txt
How to compile: In the file "compile.sh", already type ( g++ -g CLOCK.cpp -pthread -std=c++11 -o main )
first, add commond line: ./compile.sh
second, add commond line: ./main inputfilename(e.g. pageref-small.txt)

Once it is able to run, it will only require to ENTER the number of available frames, e.g. 3
then it wil print out the number of page references read from input file, the number of page faults,
the number of swap in/out pages, and the time units. When calculate time units, we assume that if there is
a hit, the cost is 0; if there is a miss, and it takes 5 time units to swap in, and takes 10 time units to 
swap out.

ALL printed outputs on terminal looks like this: 

Enter the number of available frames: 
3
The number of page references in file is 22
The total number of page faults is 11
The total number of swap in pages is 11, and time units are 55
The total number of swap out pages is 2, and time units are 20

