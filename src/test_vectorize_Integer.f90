PROGRAM VECT_TEST
  IMPLICIT NONE
  
  INTEGER :: L(1024)
  INTEGER :: I
  
  DO I = 1, 1024
     L(I) = I
  END DO
  
  DO I = 1, 1024
     L(I)=L(I) + 1
  END DO

  L=L + 2
  
  PRINT *,  L(1)*L(1024)
  
END PROGRAM VECT_TEST
