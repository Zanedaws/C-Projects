WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla
GCC = gcc -O3 -std=c99 $(WARNING) $(ERROR)
VAL = valgrind --tool=memcheck --leak-check=full --verbose --show-leak-kinds=all --track-origins=yes

TESTFLAGS = 

SRCS = pa1.c shell_array.c shell_list.c
OBJS = $(SRCS:%.c=%.o)

pa1: $(OBJS)
	$(GCC) $(TESTFLAGS) $(OBJS) -o pa1
	
.c.o:
	$(GCC) $(TESTFLAGS) -c $*.c

testmemory: pa1
	$(VAL) --log-file=memcheck1.txt ./pa1 -l examples/15.b  output1
	code memcheck1.txt

test1: pa1
	./pa1 -a examples/15.b output1a
	diff output1a examples/15sa.b

test2: pa1
	./pa1 -l examples/15.b output1l
	diff output1l examples/15sa.b
	
clean: # remove all machine generated files
	rm -f *.o output?
	
zip:
	zip pa1.zip pa1.c shell_array.c shell_list.c

update:
	git push -u https://Zanedaws:40002608Zanefunk@github.com/Zanedaws/ECE368.git master