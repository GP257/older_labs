
CXX=icpc

%.o: %.cc
	${CXX} -std=c++11 -c -g -O3 -qopenmp  -I. -I/usr/include $*.cc -o $*.o

test: unitTest.o timer.o hypercube.o rescale.o mat2dFloat.o
	${CXX} -std=c++11 -qopenmp $^ -I. -L/usr/lib64 -lboost_unit_test_framework -o test.x
	./test.x

main.x: timer.o hypercube.o rescale.o main.o mat2dFloat.o
	${CXX} hypercube.o timer.o  main.o mat2dFloat.o rescale.o -qopenmp -o $@

run: main.x
	./main.x

clean:
	rm -f *.o *.x
