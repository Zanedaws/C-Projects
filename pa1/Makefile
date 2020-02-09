WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla
GCC = gcc -O3 -std=c99 $(WARNING) $(ERROR)
VAL = valgrind --tool=memcheck --leak-check=full --verbose --show-leak-kinds=all

TESTFLAGS = -DDEBUG

SRCS = pa1.c shell_array.c
OBJS = $(SRCS:%.c=%.o)

pa1: $(OBJS)
	$(GCC) $(TESTFLAGS) $(OBJS) -o pa1
	
.c.o:
	$(GCC) $(TESTFLAGS) -c $*.c

testmemory: pa1
	$(VAL) --log-file=memcheck1.txt ./pa1 -a examples/15.b  output1
	code memcheck1.txt

test1: pa1
	./pa1 -a examples/15.b output1
	
clean: # remove all machine generated files
	rm -f *.o output?
	
zip:
	zip ~/Coding/ECE264/solutions/ECEhomework/zips/pa1.zip pa1.c shell_array.c

update:
	git push -u https://Zanedaws:40002608Zanefunk@github.com/Zanedaws/ECE368.git master