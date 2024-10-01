

# Copy and paste the following command  into your terminarl or add it to then end of your .tcshrc
#
#setenv LD_LIBRARY_PATH "/usr/local/gcc-5/lib:/usr/local/gcc-5/lib64:${LD_LIBRARY_PATH}"
#

%.o: %.cc
	${CXX} -std=c++11 -c -Ofast -g -I. $*.cc -o $*.o

%.o: %.ispc
	/data/cees/gp257/ispc-v1.8.1-linux/ispc -O2 --target=avx $*.ispc -o $*.o 

main.x: timer.o main.o  
	${CXX} timer.o  main.o  -o $@ -ltbb

run: main.x
	./main.x 

clean:
	rm -f *.o *.x
