PROGRAM VECT_TEST_SINGLE
  IMPLICIT NONE
  INTEGER, PARAMETER :: SP = KIND(1.0)
  INTEGER, PARAMETER :: DP = KIND(1.0D0)
  !
  REAL(KIND=SP) :: Pi_app
  REAL(KIND=DP) :: time_start, time_end, time_tot
  INTEGER :: I,J
  !
  time_tot = 0.0_dp
  Pi_app = 0.0_SP
  !
  DO J = 0, 10
     Pi_app = 0.0_SP
     !
     CALL CPU_TIME(time_start)
     !
     !DO I = 0, (2**J)*100000
     DO I = (2**J)*100000, 0, -1
        !        Pi_app = Pi_app + REAL((-1)**I,SP)/REAL(2*I+1,SP)
        Pi_app = Pi_app + REAL( 1-2*Iand(I,1),SP)/REAL(2*I+1,SP)
     END DO
     !
     CALL CPU_TIME(time_end)
     !
     time_tot = time_tot + time_end-time_start
     !
     PRINT*, (2**J)*100000, time_tot, 4.0_SP*Pi_app, 4.0_SP*Pi_app-ACOS(-1.0_SP)
     !
  ENDDO
  !
END PROGRAM VECT_TEST_SINGLE

