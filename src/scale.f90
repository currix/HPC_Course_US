MODULE SCALEMOD
  !
  ! MODULE FOR FORTRAN 90 EXAMPLE OF VECTORIZATION
  ! by Currix TM
  !
  IMPLICIT NONE
  !
  INTEGER, PARAMETER :: I4B = SELECTED_INT_KIND(9)
  INTEGER, PARAMETER :: SP = KIND(1.0)
  INTEGER, PARAMETER :: DP = KIND(1.0D0)
  !
  INTEGER(KIND = I4B), PARAMETER :: Iter = 10000000
  INTEGER(KIND = I4B), PARAMETER :: Nval = 64
  REAL(KIND = DP) :: FLOP = (Iter*2.0_ PREC)*Nval
  !
  REAL(KIND = PREC) :: Avalue
  !
  REAL(KIND = PREC), DIMENSION(0:Nval-1) :: vA, vB
  REAL(KIND = DP), DIMENSION(0:Nval-1) :: exact_value
  !
CONTAINS
  !
  FUNCTION Scale_0(VA, VB, A)
    !
    REAL(KIND = PREC), DIMENSION(0:), INTENT(IN)  :: VA
    REAL(KIND = PREC), DIMENSION(0:), INTENT(IN)  :: VB
    REAL(KIND = PREC), INTENT(IN) :: A
    REAL(KIND = PREC), DIMENSION(0:Nval-1) :: Scale_0
    !
    INTEGER(KIND = I4B) :: Index
    !
    Scale_0 = A*VA + VB
    !
    RETURN
  END FUNCTION Scale_0
  !
  SUBROUTINE Exvalue(exact_value)
    !
    REAL(KIND = DP), DIMENSION(0:), INTENT(OUT) :: exact_value
    !
    exact_value = Avalue**REAL(Iter,DP)*(vB/4.0_DP) + vB*(Avalue**REAL(Iter,DP)-1.0_DP)/(Avalue-1.0_DP) ! Notice how Iter has been transformed into REAL. Accuracy loss if this is not the case.
    !
    RETURN
    !
  END SUBROUTINE Exvalue
  !
END MODULE SCALEMOD
