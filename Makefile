
# Automatically generated Makefile
# Makefile-generator programmed by Hans de Nivelle, 2002


Flags = -Wreturn-type -pedantic -pedantic-errors -Wundef -std=c++17 -O3 -flto
CPP = g++


main : Makefile   main.o map.o timetable.o labyrinth.o submit.o 
	$(CPP) $(Flags) -o main   main.o map.o timetable.o labyrinth.o submit.o 

main.o : Makefile   main.cpp   labyrinth.h position.h timer.h timetable.h map.h 
	$(CPP) -c $(Flags) main.cpp -o  main.o


map.o : Makefile   map.cpp   map.h position.h 
	$(CPP) -c $(Flags) map.cpp -o  map.o


timetable.o : Makefile   timetable.cpp   timetable.h 
	$(CPP) -c $(Flags) timetable.cpp -o  timetable.o


labyrinth.o : Makefile   labyrinth.cpp   map.h position.h labyrinth.h 
	$(CPP) -c $(Flags) labyrinth.cpp -o  labyrinth.o


submit.o : Makefile   submit.cpp   position.h map.h 
	$(CPP) -c $(Flags) submit.cpp -o  submit.o


