GCC = gcc -std=c99 -Wall -Wshadow -Wvla -pedantic -O3 -g
VAL = valgrind --dsymutil=yes --tool=memcheck --leak-check=full --verbose --show-leak-kinds=all --track-origins=yes

SRCS = pa2.c hcomp.c
OBJS = $(SRCS:%.c=%.o)

pa2: $(OBJS)
	$(GCC) $(OBJS) -o pa2
	
.c.o:
	$(GCC) -c $*.c

testmemory: pa2
	$(VAL) --log-file=memcheck1.txt ./pa2 original/gophers freqOutput1

test1: pa2
	./pa2 original/gophers freqOutput1 codeOutput1 headerOutput1
	diff freqOutput1 count/gophers.count

test2: pa2
	./pa2 original/binary1  freqOutput1
	diff freqOutput1 count/binary1.count
	
clean: # remove all machine generated files
	rm -f *.o output?
	
zip:
	zip pa2.zip *.c *.h

update:
	git push -u https://Zanedaws:40002608Zanefunk@github.com/Zanedaws/ECE368.git master