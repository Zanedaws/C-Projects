GCC = gcc -g -std=c99 -Wall -Wshadow -Wvla -pedantic -O3
VAL = valgrind -s --leak-check=full --leak-check=full --show-leak-kinds=all --track-origins=yes

SRCS = pa4.c eval.c build.c manip.c
OBJS = $(SRCS:%.c=%.o)

pa4: $(OBJS)
	$(GCC) $(OBJS) -o pa4
	
.c.o:
	$(GCC) -c $*.c

testmemory: pa4
	$(VAL) --log-file=memcheck1.txt ./pa4 -b examples/ops1.b treeOutput1

testall: test1 test2 test3 test4 test5

test1: pa4
	./pa4 -e examples/tree0.b
	
clean: # remove all machine generated files
	rm -f *.o memcheck1.txt pa4
	
zip:
	zip pa4.zip *.c *.h Makefile treeOutput?

update:
	git push -u https://Zanedaws:40002608Zanefunk@github.com/Zanedaws/ECE368.git master
