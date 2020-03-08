GCC = gcc -std=c99 -Wall -Wshadow -Wvla -pedantic -O3 -g
VAL = valgrind --leak-check=full -s --leak-check=full --show-leak-kinds=all

SRCS = pa3.c pack.c
OBJS = $(SRCS:%.c=%.o)

pa3: $(OBJS)
	$(GCC) $(OBJS) -o pa3
	
.c.o:
	$(GCC) -c $*.c

testmemory: pa3
	$(VAL) --log-file=memcheck1.txt ./pa3 examples/3.po out1.pr out1.dim out1.pck

testall: test1 test2 test3 test4 test5
	

test1: pa3
	./pa3 examples/3.po out1.pr out1.dim out1.pck
	diff examples/3.pr out1.pr
	diff examples/3.dim out1.dim
	diff examples/3.pck out1.pck
	
clean: # remove all machine generated files
	rm -f *.o out?.pr out?.dim out?.pck
	
zip:
	zip pa3.zip *.c *.h Makefile

update:
	git push -u https://Zanedaws:40002608Zanefunk@github.com/Zanedaws/ECE368.git master