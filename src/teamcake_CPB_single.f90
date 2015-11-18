PROGRAM TEAMCAKE_CPB_SINGLE
  !
  IMPLICIT NONE
  !
  INTEGER, PARAMETER :: I4B = SELECTED_INT_KIND(9)
  !
  INTEGER, PARAMETER :: SP = KIND(1.0)
  INTEGER, PARAMETER :: DP = KIND(1.0D0)
  !
  ! Order of the Central Moving Average p = 2 n + 1
  INTEGER(KIND = I4B), PARAMETER :: n_val = 20, p_val = 2*n_val + 1
  !
  INTEGER(KIND = I4B) :: dim_data, index, min_index, max_index, dim, IERR
  REAL(KIND = DP), DIMENSION(:), ALLOCATABLE :: data, cma_data
  REAL(KIND = DP) :: time_start, time_end
 !
  ! Read Data File
  READ(*,*) dim_data
  !
  !WRITE(*,*) "Number of Data = ", dim_data
  ! ALLOCATE Data vector
  ALLOCATE(data(0:dim_data-1), STAT = IERR)    
  IF (IERR /= 0) THEN
     WRITE(UNIT = *, FMT = *) "Ham_matrix allocation request denied."
     STOP
  ENDIF
  !
  ! ALLOCATE CMA vector
  ALLOCATE(cma_data(0:dim_data-1), STAT = IERR)    
  IF (IERR /= 0) THEN
     WRITE(UNIT = *, FMT = *) "Ham_matrix allocation request denied."
     STOP
  ENDIF
  !
  DO index = 0, dim_data-1
     READ(*,*) data(index)
  ENDDO
  !
  !
  ! Set time start
  CALL CPU_TIME(time_start)
  !
  DO index = 0, dim_data - 1
     !
     ! CMA
     min_index = index - n_val
     max_index = index + n_val
     !
     IF (min_index < 0) THEN
        min_index = 0
     ELSE IF (max_index > dim_data - 1) THEN
        max_index = dim_data - 1
     ENDIF
     !
     dim = max_index - min_index + 1
     !
     !
     cma_data(index) = SUM(data(min_index:max_index))/REAL(dim,DP)
     !
  ENDDO
  !
  ! Set time end
  CALL CPU_TIME(time_end)
  !
  WRITE(*,*) "##", time_end-time_start
  !
  ! PROGRAM OUTPUT
  DO index = 0, dim_data-1
     WRITE(*,*) cma_data(index)
  ENDDO
  !
END PROGRAM TEAMCAKE_CPB_SINGLE
