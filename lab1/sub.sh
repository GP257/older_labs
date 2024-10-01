#!/bin/tcsh
#What name qsub will see
#PBS -N  piCalc.x
#Run on one process of one node
#PBS -l nodes=1:ppn=1
#What queue to submit
#PBS -q default
cd $PBS_O_WORKDIR
#
piCalc.x 3 >log.3
#
# end of script
