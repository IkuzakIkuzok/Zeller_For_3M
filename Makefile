#Zeller Makefile
zeller.exe: main.o calendar.o calc_days.o zeller.o teshi_date.h
	gcc main.o calendar.o calc_days.o zeller.o -o zeller.exe

main.o: main.c
	gcc -c main.c

calendar.o: calendar.c
	gcc -c calendar.c

calc_days.o: calc_days.c
	gcc -c calc_days.c

zeller.o: zeller.c
	gcc -c zeller.c
