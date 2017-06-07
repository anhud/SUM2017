/* FILE NAME: T05DET.C
 * PROGRAMMER: AH5
 * DATE: 05.06.2017
 * PURPOSE: aaaaaaaaaaaaaaaaaaaaaaa
 */

#include <windows.h>
#include <stdio.h>
#include <math.h>

#define MAXM 33

INT N, parity = 0;
INT p[MAXM];
DOUBLE Q[MAXM][MAXM], det = 0;

VOID Swap( INT *a, INT *b )
{
  INT tmp = *a;
  *a = *b;
  *b = tmp;
}


VOID SwapD( DOUBLE *a, DOUBLE *b )
{
  DOUBLE tmp = *a;
  *a = *b;
  *b = tmp;
}

VOID Go( INT pos )
{
  INT i, j;
  DOUBLE l;

  if (pos >= N)
  { 
    l = 1;
    for(j = 0; j < N; j++)
      l = Q[j][p[j]] * l;
    if (parity == 1)                                            
      det -= l;
    else 
      det += l;
    return;
  }
  for (i = pos; i < N; i++)
  { 
    if (pos != i)
      parity = !parity;
    Swap(&p[pos], &p[i]);
    Go(pos + 1);
    Swap(&p[pos], &p[i]);
    if (pos != i)
      parity = !parity;
  }
}


DOUBLE Gs()
{
  INT i, j, ii, jj, k, max_i, max_j;
  DOUBLE det1 = 1, coef;

  for (i = 0; i < N; i++)
  { 
    max_i = i;
    max_j = i;

    for (ii = i; ii < N; ii++)
    {
      for (jj = i; jj < N; jj++)
      {
        if (fabs(Q[max_i][max_j]) < fabs(Q[ii][jj]))
        {
          max_i = ii;
          max_j = jj;
        }
      }
    }
    if (fabs(Q[max_i][max_j]) < 1e-15)
      return 0;

    if (max_i != i)
    {
      det1 = -det1;
      for (ii = i; ii < N; ii++)
        SwapD(&Q[ii][i], &Q[ii][max_j]);
    }

    if (max_j != i)  
    { 
      det1 = -det1;
      for (jj = i; jj < N; jj++)
        SwapD(&Q[i][jj], &Q[max_i][jj]);
    }

    for (j = i + 1; j < N; j++)
    {
      coef = Q[j][i] / Q[i][i];
      for (k = i; k < N; k++)
        Q[j][k] -= Q[i][k] * coef;
    }
  }
  for (i = 0; i < N; i++)
    det1 *= Q[i][i];
  return det1;
}

VOID main( void )
{
  INT i, j;
  FILE *F;

  F = fopen("MTRX.txt", "r");
  if (F == NULL)
    return;
  fscanf(F, "%d", &N);
  for (i = 0; i < N; i++)
  {  
    p[i] = i;
    for (j = 0; j < N; j++)
      fscanf(F, "%lf", &Q[i][j]);
  }
  fclose(F);
  Go(0);
  F = fopen("MTRXOUT.txt", "a");
  if (F == NULL)
    return;
  fprintf(F, "\n%lf", det);
  det = Gs();
  fprintf(F, "\n%lf", det);
  fclose(F);
}