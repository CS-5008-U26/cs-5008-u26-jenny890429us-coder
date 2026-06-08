CC := gcc
DEPENDS := first.h second.h
OBJS := hello.o first.o second.o

hello: $(OBJS)
	$(CC) -o hello $(OBJS)

%.o: %.c $(DEPENDS)
	$(CC) -c -o $@ $<

.PHONY: clean

clean:
	rm *.o