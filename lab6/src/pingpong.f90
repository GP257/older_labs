!*******************************************************************************
! FILE : pingpong.c
! 
! LAST MODIFIED : $Date: 2006/02/24 21:56:11 $
!
! REVISION : $Revision: 1.1 $
! 
! DESCRIPTION : MPI ping-pong program, illustrating sending and receiving of
!   mesages between two processors. 
!
! COPYRIGHT :
!
!   The copyright in this unpublished software is the property of 
!   Stanford University.
!
! AUTHORS : John Martin Bodley
!           Stanford Center for Computational Earth and Environmental Science
!           Stanford University
!           Stanford, CA 94305
!
!===============================================================================  

program pingpong
!*******************************************************************************
! PROGRAM : main
!  
! LAST MODIFIED : Feb 24, 2006
! 
! DESCRIPTION : MPI send and receive of data between two processors.
! 
!===============================================================================

  use mpi

  implicit none

  character (len = MPI_MAX_PROCESSOR_NAME) :: processor_name
  integer :: inmsg, outmsg, namelen, numprocs, rank, dest, source, size, ierr, &
    status, tag = 1
  double precision :: startwtime, endwtime, time
  
  ! MPI initialization
  call MPI_Init(ierr)
  call MPI_Comm_size(MPI_COMM_WORLD, numprocs, ierr)
  call MPI_Comm_rank(MPI_COMM_WORLD, rank, ierr)
  call MPI_Get_processor_name(processor_name, namelen, ierr)

  print *, 'Process ', rank, ' on ', trim(processor_name) , ' of ', numprocs

  if (rank .eq. 0) then 
    source = 1
    dest = 1
    outmsg = 17
  
  else if (rank .eq. 1) then 
    source = 0
    dest = 0
    outmsg = 19
  
  end if

  ! Start MPI timing
  if (rank .eq. 0) startwtime = MPI_Wtime()
 
  if (rank .eq. 0) then 
  
    call MPI_Send(outmsg, 1, MPI_INTEGER, dest, tag, MPI_COMM_WORLD, ierr)
    call MPI_Recv(inmsg, 1, MPI_INTEGER, source, tag, MPI_COMM_WORLD, status, &
 &    ierr)
  
  else if (rank .eq. 1) then
  
    call MPI_Recv(inmsg, 1, MPI_INTEGER, source, tag, MPI_COMM_WORLD, status, &
 &    ierr)
    call MPI_Send(outmsg, 1, MPI_INTEGER, dest, tag, MPI_COMM_WORLD, ierr)
  
  end if

  ! Elasped time 
  if (rank .eq. 0) then
    endwtime = MPI_Wtime()
    time = 1.0e+6 * (endwtime - startwtime);
    size = 4;
    
  print 1, size,' bytes took ', time, ' usec (', 2.0 * size / time, ' MB/sec)'
 1  format(I8, A, F9.0, A, F8.3, A )    
    
  end if

  call MPI_Finalize() 

end program ! pingpong
