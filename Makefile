SRC=main.c

CC=sdcc
FAMILY=pic16
PROC=18f4550

all: $(SRC:.c=.hex)

$(SRC:.c=.hex): $(SRC)
	$(CC) --use-non-free -m$(FAMILY) -p$(PROC) $^

clean:
	rm -f $(SRC:.c=.asm) $(SRC:.c=.cod) $(SRC:.c=.hex) $(SRC:.c=.lst) $(SRC:.c=.o)

flash: $(SRC:.c=.hex)
	pk2cmd -ppic$(PROC) -f$(SRC:.c=.hex) -m

.PHONY: all clean
