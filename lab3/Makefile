
%.o: %.cc
	icpc -std=c++11 -c -g  -I.  $*.cc -o $*.o


main.x: timer.o field3d.o prop.o main.o
	${CXX} field3d.o timer.o  main.o prop.o -o $@

run:
	./main.x

clean:
	rm -f *.o *.x 
