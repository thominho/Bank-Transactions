#
# In order to execute this "Makefile" just type "make"
#	A. Delis (ad@di.uoa.gr)
#

OBJS 	= main.o ListVal.o hashtable.o
SOURCE	= main.cpp sources/ListVal.cpp sources/hashtable.cpp
HEADER  = headers/ListVal.hpp headers/hashtable.hpp
OUT  	= server
CC	= g++
FLAGS   = -g -c -pedantic -ansi  -Wall
# -g option enables debugging mode 
# -c flag generates object code for separate files

$(OUT): $(OBJS)
	$(CC) -g $(OBJS) -o $@

# create/compile the individual files >>separately<< 
main.o: main.cpp
	$(CC) $(FLAGS) main.cpp

ListVal.o: sources/ListVal.cpp
	$(CC) $(FLAGS) sources/ListVal.cpp

hashtable.o: sources/hashtable.cpp
	$(CC) $(FLAGS) sources/hashtable.cpp

others:
	g++ -o client sources/client.cpp

# clean house
clean:
	rm -f $(OBJS) $(OUT)

# do a bit of accounting
count:
	wc $(SOURCE) $(HEADER)

