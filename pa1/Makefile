WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)
VAL = valgrind --tool=memcheck --leak-check=full --verbose --show-leak-kinds=all

TESTFLAGS = -DDEBUG

SRCS = pa1.c shell_array.c
OBJS = $(SRCS:%.c=%.o)

pa1: $(OBJS)
	$(GCC) $(TESTFLAGS) $(OBJS) -o pa1
	
.c.o:
	$(GCC) $(TESTFLAGS) -c $*.c

testmemory: pa1
	$(VAL) --log-file=memcheck1.txt ./pa1 examples/15.b > output1
	kate memcheck1.txt

testcon: pa1
	 ./pa1 examples/15.b

testall: test1

test1: pa1
	./pa1 examples/15.b > output1
	diff output1 expected/expected1
	
	
clean: # remove all machine generated files
	rm -f shuffle *.o output?
	
zip:
	zip ~/Coding/ECE264/solutions/ECEhomework/zips/pa1.zip pa1.c shell_array.c
