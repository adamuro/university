.PHONY = all clean distclean

CC = gcc
CFLAGS = -Wextra -Wall -std=gnu17

TARGET   = transport
SRCS     = $(wildcard *.c)
OBJFILES = $(SRCS:%.c=%.o)

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) -o $(TARGET) $(OBJFILES)

%.o: %.c
	${CC} -c $(CFLAGS) $<

clean:
	rm -rvf $(OBJFILES)

distclean:
	rm -rvf $(OBJFILES) $(TARGET)