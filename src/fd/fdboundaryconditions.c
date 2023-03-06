#include "DNA.h"
#include "DNA-functions.h"

/**--------------------------------------------------------- 
This function sets the absorbing (non-reflecting) boundary condition using
Mur's (1981) absorbing boundary condition. The original form of the boundary
condition is complemented by an advective term in order to make it suitable
for non-zero flow fields. If the scattering boundary option is chosen, the
pointer refers to the dummy. In the latter case, the boundary behaves like a
reflecting/scattering boundary, where the incoming wave is mirrored at the
x-axis upon reflection.

The four different functions represent the Mur BC at the East and West boundaries
(FDBC_Mur_East and FDBC_Mur_West) for the case R(t) < Rstat, where R(t) and Rstat
are the positions of the wave-emitting boundary and the fixed boundary,
respectively, and the inverted case R(t) > Rstat (FDBC_Mur_East_inv and 
FDBC_Mur_West_inv). Each of these configurations requires slightly different
variants of the Mur BC.
---------------------------------------------------------**/

int FDBC_Mur_East(struct DNA_RunOptions *RunOptions, struct DNA_Fields *Fields, struct DNA_FluidProperties *FluidProperties, struct DNA_ScalarField *NewField,
                  struct DNA_ScalarField *OldField)
{
  int iBC = RunOptions->NumericsFD.NPoints - 1;

  DNA_FLOAT CFL = FluidProperties->c0 * RunOptions->NumericsFD.dt / RunOptions->NumericsFD.dx;
  DNA_FLOAT grad = Fields->dXI1_phi.val[iBC] * Fields->Grid.detJacobi;
  DNA_FLOAT vrel = Fields->BackgroundVelocity.val[iBC] + Fields->Grid.q[iBC] / Fields->Grid.detJacobi;
  DNA_FLOAT adv = grad * vrel * RunOptions->NumericsFD.dt;

  NewField->val[iBC] =
      OldField->val[RunOptions->NumericsFD.NPoints - 2] + (CFL - 1.0) / (CFL + 1.0) * (NewField->val[RunOptions->NumericsFD.NPoints - 2] - OldField->val[iBC]);

  NewField->val[iBC] -= adv * 2.0;

  return 0;
}

int FDBC_Mur_East_inv(struct DNA_RunOptions *RunOptions, struct DNA_Fields *Fields, struct DNA_FluidProperties *FluidProperties,
                      struct DNA_ScalarField *NewField, struct DNA_ScalarField *OldField)
{
  int iBC = 0;

  DNA_FLOAT CFL = FluidProperties->c0 * RunOptions->NumericsFD.dt / RunOptions->NumericsFD.dx;
  DNA_FLOAT grad = Fields->dXI1_phi.val[iBC] * Fields->Grid.detJacobi;
  DNA_FLOAT vrel = Fields->BackgroundVelocity.val[iBC] + Fields->Grid.q[iBC] / Fields->Grid.detJacobi;
  DNA_FLOAT adv = grad * vrel * RunOptions->NumericsFD.dt;

  NewField->val[iBC] = OldField->val[1] + (CFL + 1.0) / (CFL - 1.0) * (NewField->val[1] - OldField->val[iBC]);

  NewField->val[iBC] -= adv * 2.0;

  return 0;
}

int FDBC_Mur_West(struct DNA_RunOptions *RunOptions, struct DNA_Fields *Fields, struct DNA_FluidProperties *FluidProperties, struct DNA_ScalarField *NewField,
                  struct DNA_ScalarField *OldField)
{
  int iBC = 0;

  DNA_FLOAT CFL = FluidProperties->c0 * RunOptions->NumericsFD.dt / RunOptions->NumericsFD.dx;
  DNA_FLOAT grad = Fields->dXI1_phi.val[iBC] * Fields->Grid.detJacobi;
  DNA_FLOAT vrel = Fields->BackgroundVelocity.val[iBC] + Fields->Grid.q[iBC] / Fields->Grid.detJacobi;
  DNA_FLOAT adv = grad * vrel * RunOptions->NumericsFD.dt;

  NewField->val[iBC] = OldField->val[1] + (CFL - 1.0) / (CFL + 1.0) * (NewField->val[1] - OldField->val[iBC]);

  NewField->val[iBC] -= adv * 2.0;

  return 0;
}

int FDBC_Mur_West_inv(struct DNA_RunOptions *RunOptions, struct DNA_Fields *Fields, struct DNA_FluidProperties *FluidProperties,
                      struct DNA_ScalarField *NewField, struct DNA_ScalarField *OldField)
{
  int iBC = RunOptions->NumericsFD.NPoints - 1;

  DNA_FLOAT CFL = FluidProperties->c0 * RunOptions->NumericsFD.dt / RunOptions->NumericsFD.dx;
  DNA_FLOAT grad = Fields->dXI1_phi.val[iBC] * Fields->Grid.detJacobi;
  DNA_FLOAT vrel = Fields->BackgroundVelocity.val[iBC] + Fields->Grid.q[iBC] / Fields->Grid.detJacobi;
  DNA_FLOAT adv = grad * vrel * RunOptions->NumericsFD.dt;

  NewField->val[iBC] =
      OldField->val[RunOptions->NumericsFD.NPoints - 2] + (CFL + 1.0) / (CFL - 1.0) * (NewField->val[RunOptions->NumericsFD.NPoints - 2] - OldField->val[iBC]);

  NewField->val[iBC] -= adv * 2.0;

  return 0;
}

int FDBC_Mur_dummy(struct DNA_RunOptions *RunOptions, struct DNA_Fields *Fields, struct DNA_FluidProperties *FluidProperties, struct DNA_ScalarField *NewField,
                   struct DNA_ScalarField *OldField)
{
  return 0;
}
