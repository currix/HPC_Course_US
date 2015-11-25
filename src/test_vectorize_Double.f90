PROGRAM VECT_TEST
  IMPLICIT NONE
  INTEGER, PARAMETER :: DP = KIND(1.0D0)
  !
  REAL(KIND=DP) :: L(0:1024)
  INTEGER :: I
  
  DO I = 1, 10240
     L(MOD(I,1024)) = REAL(MOD(I,1024),DP)
  END DO
  
  DO I = 1, 10240
     L(MOD(I,1024))=L(MOD(I,1024)) + 1.0_DP
  END DO

  DO I = 1, 10240
     L=L + 2.0_DP
  END DO
  
  PRINT *,  L(1)*L(1024)
  
END PROGRAM VECT_TEST
