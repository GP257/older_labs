# Error checking
ifndef target

  # No target specified
  $(error Specify target name)

endif

MPIDIR = /usr/local/intel_14/impi/4.1.3.048
LDFLAGS = -L$(MPIDIR)/lib64 -lmpich -lm

ifeq ($(language), f90)
  
  # Fortran 90
  FC = $(MPIDIR)/bin64/mpif90 
  prefix  := mpi 
  
endif

ifeq ($(language), c)
  
  # C
  CC      := $(MPIDIR)/bin64/mpicc -O3
  CFLAGS  += -I$(MPIDIR)/include
  
endif

prefix += $(target)
source := $(addsuffix .$(language), $(prefix))

default : $(language)

f90 : $(source)
	$(FC) $(FFLAGS) -o $(target) $? $(LDFLAGS)

c : $(source)
	$(CC) $(CFLAGS) -o $(target) $? $(LDFLAGS)        
        
.PHONY : clean
        
clean : 
	rm -f $(target) *.o *.mod *.d
