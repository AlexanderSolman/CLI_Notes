# Under clean command -del is used instead of -rm due to windows same with .exe
CC := gcc
CFLAGS := -I.
target := memo.exe
objs := memo.o libmemo.o

all: $(target)

memo: $(objs)
	$(CC) -o memo memo.o libmemo.o $(CFLAGS)

%.o: %.c memo.h
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	-del -f $(target) $(objs)