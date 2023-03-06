#include "DNA.h"
#include "DNA-functions.h"

/**--------------------------------------------------------- 
Functions to allocate memory 
---------------------------------------------------------**/

int MemoryAllocGrid(int NPoints, struct DNA_Grid *Grid)
{
  Grid->x = malloc(NPoints * sizeof(DNA_FLOAT));
  Grid->XI = malloc(NPoints * sizeof(DNA_FLOAT));
  Grid->q = malloc(NPoints * sizeof(DNA_FLOAT));
  Grid->dtq = malloc(NPoints * sizeof(DNA_FLOAT));

  return 0;
}

/**--------------------------------------------------------- 
Allocate memeory for DNA_Scalarfield such as pressure field etc
---------------------------------------------------------**/

int MemoryAllocScalarField(int NPoints, struct DNA_ScalarField *ScalarField)
{
  ScalarField->val = malloc(NPoints * sizeof(DNA_FLOAT));

  return 0;
}

/**--------------------------------------------------------- 
Memory allocation for old scalar fields (previous time steps)
needed for the time integration scheme
---------------------------------------------------------**/

int MemoryAllocOldScalarFields(int NPoints, int structSize, struct DNA_OldScalarFields *OldScalarFields)
{
  int iStruct;

  for (iStruct = 0; iStruct < structSize; iStruct++)
  {
    (OldScalarFields->o[iStruct]).val = malloc(NPoints * sizeof(DNA_FLOAT));
  }

  return 0;
}

/**--------------------------------------------------------- 
The following two functions allocate memory for the acoustic pressure probes,
taken at the grid point IDs that correspond to the sample point locations
specified in the options file.

The function <MemoryAllocSamplePoints> allocates sample IDs (int) and the
sample points (float). The function is called in the <ioreadoptions.c> file,
where NPoints is the number of sample points as specificed in the options file.

Subsequently, <MemoryAllocSampleVectors> is called in <MemoryAllocFields>
(see <memoryallocfields.c>), which again is called in <InitializeSimulation>
(see <initializesimulation.c>) in order to allocate the memory per sample point
based on the write frequency as specified in the options file (<writeFrequency>).
The write frequency is an integer indicating the number of subsequent time steps
after which the field data and, on this occasion, the sample data is written to
disk. 
---------------------------------------------------------**/

int MemoryAllocSamplePoints(int NPoints, struct DNA_Probes *Probes)
{
  Probes->SamplePoints = malloc(NPoints * sizeof(DNA_FLOAT));
  Probes->SampleIDs = malloc(NPoints * sizeof(int));

  return 0;
}

int MemoryAllocSampleVectors(int writeFrequency, struct DNA_Probes *Probes)
{
  Probes->SampleTime = malloc(writeFrequency * sizeof(DNA_FLOAT));
  Probes->TimeIDs = malloc(writeFrequency * sizeof(int));

  int rows = writeFrequency;
  int cols = Probes->nSamplePoints;
  Probes->SamplePressure = (DNA_FLOAT **) malloc(rows * sizeof(DNA_FLOAT *));
  for (int i = 0; i < rows; i++)
  {
    Probes->SamplePressure[i] = (DNA_FLOAT *) malloc(cols * sizeof(DNA_FLOAT));
  }

  return 0;
}
