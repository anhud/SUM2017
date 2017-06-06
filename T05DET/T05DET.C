/* FILE NAME: T05DET.C
 * PROGRAMMER: AH5
 * DATE: 05.06.2017
 * PURPOSE: aaaaaaaaaaaaaaaaaaaaaaa
 */

#include <windows.h>
#include <stdio.h>
#include <math.h>

#define maxm 33

INT N, parity = 0;
INT p[maxm];
DOUBLE q[maxm][maxm], det = 0;

VOID Swap( int *a, int*b )
{
  INT tmp = *a;
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
      l = q[j][p[j]] * l;
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

VOID main( void )
{
  INT i, j;
  FILE *F;

  F = fopen("MTRX.txt", "r");
  if (F == NULL)
    return;
  fscanf(F, "%d", &N);
  for(i = 0; i < N; i++)
  {  
    p[i] = i;
    for(j = 0; j < N; j++)
      fscanf(F, "%lf", &q[i][j]);
  }
  fclose(F);
  Go(0);
  F = fopen("MTRX.txt", "a");
  if (F == NULL)
    return;
  fprintf(F, "\n%lf", det);
  fclose(F);
}