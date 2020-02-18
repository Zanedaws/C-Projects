WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla
GCC = gcc -O3 -std=c99 $(WARNING) $(ERROR)
VAL = valgrind --tool=memcheck --leak-check=full --verbose --show-leak-kinds=all --track-origins=yes

TESTFLAGS = 

SRCS = pa2.c shell_array.c shell_list.c
OBJS = $(SRCS:%.c=%.o)

pa2: $(OBJS)
	$(GCC) $(TESTFLAGS) $(OBJS) -o pa2
	
.c.o:
	$(GCC) $(TESTFLAGS) -c $*.c

testmemory: pa2
	$(VAL) --log-file=memcheck1.txt ./pa2 -l original/gophers  output1
	code memcheck1.txt

test1: pa2
	/pa2 -l original/gophers  freqOutput1
	diff freqOutput1 original/gophers
	
clean: # remove all machine generated files
	rm -f *.o output?
	
zip:
	zip pa2.zip *.c *.h

update:
	git push -u https://Zanedaws:40002608Zanefunk@github.com/Zanedaws/ECE368.git master