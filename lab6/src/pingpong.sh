#PBS -N pingpong
#PBS -l nodes=2:ppn=1
#PBS -q class
#PBS -V

cd $PBS_O_WORKDIR

# Execute MPI program
/usr/local/intel_14/impi/4.1.3.048/bin64/mpirun -np 2 ./pingpong >> pingpong.out
