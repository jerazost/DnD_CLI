OBJS = Dice.o Ability.o Monster.o dnd.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
VERSION = -std=c++11
LFLAGS = -Wall $(DEBUG)

dnd : $(OBJS)
	$(CC) $(VERSION) $(LFLAGS) $(OBJS) -o dnd

dnd.o : dnd.cpp Dice.h Ability.h Monster.h
	$(CC) $(VERSION) $(CFLAGS) dnd.cpp

Dice.o : Dice.h Dice.cpp
	$(CC) $(VERSION) $(CFLAGS) Dice.cpp

Ability.o : Ability.h Ability.cpp Dice.h
	$(CC) $(VERSION) $(CFLAGS) Ability.cpp

Monster.o : Monster.h Monster.cpp Dice.h Ability.h 
	$(CC) $(VERSION) $(CFLAGS) Monster.cpp

clean:
	\rm *.o dnd

