PROGRAM VECT_TEST
  IMPLICIT NONE
  INTEGER, PARAMETER :: SP = KIND(1.0)
  !
  REAL(KIND=SP) :: L(0:1024)
  INTEGER :: I
  
  DO I = 1, 10240
     L(MOD(I,1024)) = REAL(MOD(I,1024),SP)
  END DO
  
  DO I = 1, 10240
     L(MOD(I,1024))=L(MOD(I,1024)) + 1.0_SP
  END DO

  DO I = 1, 10240
     L=L + 2.0_SP
  END DO  
  PRINT *, L(1)*L(1024)
  
END PROGRAM VECT_TEST
