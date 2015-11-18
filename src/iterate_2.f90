PROGRAM ITERATE
  !
  ! FORTRAN 90 EXAMPLE OF VECTORIZATION
  ! by Currix TM
  !
  USE SCALEMOD
  !
  IMPLICIT NONE
  !
  INTEGER(KIND = I4B) :: Index
  REAL(KIND = DP), DIMENSION(1:Nval-1) :: error_value
  REAL(KIND = PREC) :: time_end, time_start
  !
  CHARACTER(LEN = 6) :: PRECISION 
  !
  ! Read Avalue
  READ(*,*) Avalue
  !
  ! Initialize vA, vB
  DO Index = 0, Nval - 1
     vB(Index) = REAL(Index, KIND = PREC)
  ENDDO
  vA = vB/4.0_ PREC
  !
  ! Set time start
  CALL CPU_TIME(time_start)
  !
  ! Main Loop
  DO Index = 1, Iter
     vA =  Avalue*VA + VB
  ENDDO
  !
  ! Set time end
  CALL CPU_TIME(time_end)
  !
  CALL Exvalue(exact_value)
  !
  error_value = ABS(vA(1:) - exact_value(1:))/exact_value(1:)
  !
  IF (PREC == DP) THEN
     PRECISION = "DOUBLE"
  ELSE
     PRECISION = "SINGLE"
  ENDIF
  !
  !WRITE(*,FMT = 10) vA(1:)
  !WRITE(*,*) 
  !WRITE(*,FMT = 10) exact_value(1:)
  !WRITE(*,*)
  WRITE(*,FMT = 10) error_value
  WRITE(*,*)
  WRITE(*,FMT = 20) FLOP/(time_end-time_start), 1.0_ PREC/(time_end-time_start), &
       "; PREC : ", PRECISION, &
       "; FLAGS : ", FLAGS
  !
10 FORMAT(2X,3G20.11)
20 FORMAT(2X,2E17.9, A, A, A, A)
  !
END PROGRAM ITERATE
