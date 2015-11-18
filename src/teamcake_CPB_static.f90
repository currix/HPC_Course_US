PROGRAM TEAMCAKE_CPB_STATIC
  !
  IMPLICIT NONE
  !
  !$    INCLUDE "omp_lib.h"
  INTEGER, PARAMETER :: I4B = SELECTED_INT_KIND(9)
  !
  INTEGER, PARAMETER :: SP = KIND(1.0)
  INTEGER, PARAMETER :: DP = KIND(1.0D0)
  !
  ! Order of the Central Moving Average p = 2 n + 1
  INTEGER(KIND = I4B), PARAMETER :: n_val = 20, p_val = 2*n_val + 1
  ! Vector dimension
  INTEGER(KIND = I4B), PARAMETER :: dim_data = 8171
  !
  INTEGER(KIND = I4B) :: index, iam, nt, ipoints, istart, min_index, max_index, dim, IERR
  REAL(KIND = DP), DIMENSION(0:dim_data-1) :: data, cma_data
  !
  ! Read Data File to skip one row
  READ(*,*) index
  !
  DO index = 0, dim_data-1
     READ(*,*) data(index)
  ENDDO
  !
  !$OMP PARALLEL PRIVATE(iam,nt,ipoints,istart,index, dim, min_index, max_index)
  iam = OMP_GET_THREAD_NUM()
  nt =  OMP_GET_NUM_THREADS()
  ipoints = dim_data / nt
  istart = iam * ipoints
  dim = p_val
  !
  WRITE(*,*) "# #", index, min_index, max_index, dim, iam, nt, ipoints, istart
  ! Last Task
  if (iam .EQ. nt-1) then
     ipoints=dim_data - istart 
  endif
  !
  WRITE(FMT=*,UNIT=200) "# #", iam, nt, ipoints, istart, dim
  !
  DO index = istart, istart + ipoints - 1
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
  !$OMP END PARALLEL
  !
  ! PROGRAM OUTPUT
  DO index = 0, dim_data-1
     WRITE(*,*) cma_data(index)
  ENDDO
  !
END PROGRAM TEAMCAKE_CPB_STATIC
