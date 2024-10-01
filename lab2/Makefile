
SOURCES=$(addprefix Src/,fullMatrix.cc  sparseMatrix.cc  vector1d.cc matrix.cc           vector.cc)

OBJECTS=$(patsubst %.cc, %.o, ${SOURCES})


CC=icc

Src/%.o: Src/%.cc
	${CC} Src/$*.cc -ISrc -I/usr/include -c -o Src/$*.o
	
lib: libmatVec.a

libmatVec.a: ${OBJECTS}
	ar rcs libmatVec.a ${OBJECTS}

test: libmatVec.a Src/unitTest.o
	${CC} Src/unitTest.o libmatVec.a -L/usr/lib64 -lboost_unit_test_framework -o test.x
	./test.x

	

clean:
	rm *.x Src/*.o *.a
