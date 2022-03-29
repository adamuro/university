.PHONY = all clean

CC = gcc
CFLAGS = -W -Wall -O2

TARGET   = traceroute
SRCS     = $(wildcard *.c)
OBJFILES = $(SRCS:%.c=%.o)

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES)

%.o: %.c
	${CC} -c $<

clean:
	rm -rvf $(OBJFILES) ${TARGET}