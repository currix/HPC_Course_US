PROGRAM VECT_TEST_DOUBLE
  IMPLICIT NONE
  INTEGER, PARAMETER :: DP = KIND(1.0D0)
  !
  REAL(KIND=DP) :: Pi_app
  REAL(KIND=DP) :: time_start, time_end, time_tot
  INTEGER :: I,J
  !
  time_tot = 0.0_dp
  Pi_app = 0.0_DP
  !
  DO J = 0, 10
     Pi_app = 0.0_DP
     CALL CPU_TIME(time_start)
     !
     DO I = (2**J)*100000, 0, -1
        !        Pi_app = Pi_app +  REAL((-1)**I,DP)/REAL(2*I+1,DP)
        Pi_app = Pi_app +  REAL( merge(1,-1,Iand(I,1)/=1),DP)/REAL(2*I+1,DP)
     END DO
     !
     CALL CPU_TIME(time_end)
     !
     time_tot = time_tot + time_end-time_start
     !
     PRINT*, (2**J)*100000, time_tot, 4.0_DP*Pi_app, 4.0_DP*Pi_app-ACOS(-1.0_DP)
     !
  ENDDO
  !     
END PROGRAM VECT_TEST_DOUBLE

