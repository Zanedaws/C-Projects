WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla
GCC = gcc -g -O3 -std=c99 $(WARNING) $(ERROR)
VAL = valgrind --leak-check=full --leak-check=full --show-leak-kinds=all --track-origins=yes

TESTFLAGS = 

SRCS = pa1.c shell_array.c shell_list.c
OBJS = $(SRCS:%.c=%.o)

pa1: $(OBJS)
	$(GCC) $(TESTFLAGS) $(OBJS) -o pa1
	
.c.o:
	$(GCC) $(TESTFLAGS) -c $*.c

testmemory: pa1
	$(VAL) --log-file=memcheck1.txt ./pa1 -l examples/15.b  output1

test1: pa1
	./pa1 -a examples/100K.b output1a

test2: pa1
	./pa1 -l examples/15.b output1l
	diff output1l examples/15sl.b

test3: pa1
	./pa1 -l examples/1K.b output2l
	diff output2l examples/1Ksl.b

test4: pa1
	./pa1 -l examples/10K.b output3l

test5: pa1
	./pa1 -l examples/100K.b output4l
	
test6: pa1
	./pa1 -l examples/1M.b output5l

clean: # remove all machine generated files
	rm -f *.o output??
	
zip:
	zip pa1.zip pa1.c shell_array.c shell_list.c

update:
	git push -u https://Zanedaws:40002608Zanefunk@github.com/Zanedaws/ECE368.git master