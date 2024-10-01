#PBS -N advection 
#PBS -l nodes=1:ppn=2
#PBS -q class
#PBS -V

cd $PBS_O_WORKDIR

# Execute MPI program
/usr/local/intel_14/impi/4.1.3.048/bin64/mpirun -np 2 ./advection.mpi -n 100000 -T 8 -a 0.08 -o u.out
