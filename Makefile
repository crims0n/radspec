CC = cc
CFLAGS = -Wall -Wextra -O2

radspec: main.c
	$(CC) $(CFLAGS) -o radspec main.c

clean:
	rm -f radspec

.PHONY: clean
