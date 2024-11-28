CC = g++
CFLAGS = -Wall -Wextra -std=c++11
NCURSES_LIBS = -lncurses

OBJS = SnakePart.o SnakeGame.o main.o

all: snake_game

snake_game: $(OBJS)
	$(CC) $(OBJS) -o snake_game $(NCURSES_LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) snake_game

