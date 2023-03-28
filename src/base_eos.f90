MODULE base_eos
  use constants, only: Rgas

  IMPLICIT NONE
  
  PRIVATE
  PUBLIC :: BaseEos

 !> Base EoS class - inspired by thermo.py
  TYPE, ABSTRACT :: BaseEos
    INTEGER :: ident
    integer :: ncomps 
    real :: Tc, Vc
  CONTAINS
    ! All inherriting classes must implement this
    PROCEDURE (Fres_template), DEFERRED :: Fres
    ! These are implemented at the top level
    PROCEDURE :: Fideal, pressure
    !> A set function - also implemented at the top level
    PROCEDURE :: set_Tc
  END TYPE BaseEos
  
  ABSTRACT INTERFACE
    !> Residual helmholtz energy
    subroutine Fres_template(this, T, V, n, Fres, Ft, Fv, Fn)
      IMPORT :: BaseEos
      CLASS(BaseEos), INTENT(in) :: this
      real, intent(in) :: T, V
      real, dimension(this%ncomps), intent(in) :: n
      real, intent(out) :: Fres
      real, optional, intent(out) :: Ft, Fv
      real, optional, dimension(this%ncomps), intent(out) :: Fn
    END subroutine Fres_template
  END INTERFACE

CONTAINS

subroutine Fideal(this, T, V, n, Fid, Ft, Fv, Fn)
    CLASS(BaseEos), INTENT(in) :: this
    real, intent(in) :: T, V
    real, dimension(this%ncomps), intent(in) :: n
    real, intent(out) :: Fid
    real, optional, intent(out) :: Ft, Fv
    real, optional, dimension(this%ncomps), intent(out) :: Fn
    real :: V0 = 0.25
    real :: T0 = 300.0
    integer :: i

    Fid = sum(n) * 3.0 * Rgas * log(T / T0) / 2.0 + sum(n) * Rgas * T * log(V0 / V)
    if (present(Ft)) Ft = sum(n) * 3.0 * Rgas / 2.0 
    if (present(Fv)) Fv = - sum(n) * Rgas * T / V
    if (present(Fn)) then
        do i = 1, this%ncomps
            Fn(i) = 3.0 * Rgas * T / 2.0 - Rgas * T / V
        enddo
    endif

END subroutine Fideal

  subroutine pressure(this, T, V, n, p)
    CLASS(BaseEos), INTENT(in) :: this
    real, intent(in) :: T, V
    real, dimension(this%ncomps), intent(in) :: n
    real, intent(out) :: p
    real :: F
    real :: Fv_res, Fv_id

    call this%Fideal(T, V, n, F, Fv=Fv_id)
    call this%Fres(T, V, n, F, Fv=Fv_res)

    p = - (Fv_res + Fv_id)

  END subroutine pressure

  subroutine set_Tc(this, Tc)
    class(BaseEos), intent(inout) :: this
    real, intent(in) :: Tc

    this%Tc = Tc
  end subroutine set_Tc

END MODULE base_eos
