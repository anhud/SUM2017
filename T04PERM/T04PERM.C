/* FILE NAME: T04PERM.C
 * PROGRAMMER: AH5
 * DATE: 05.06.2017
 * PURPOSE: eh?
 */

#include <windows.h>
#include <stdio.h>

INT N, parity = 0;
INT p[13];


VOID PrintPerm( void )
{
  INT i;
  FILE *F;

  F = fopen("PERM.txt", "a");
  if (F == NULL)
    return;
  for (i = 0; i < N; i++)
    fprintf(F, "%i ", p[i]);
  fprintf(F, " %s \n", parity ? "odd" : "even" );
}

VOID Swap( int *a, int*b )
{
  INT tmp = *a;
  *a = *b;
  *b = tmp;
}

VOID Go( INT pos )
{
  INT i;

  if (pos >= N)
  {  
    PrintPerm();
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
  int i;

  scanf("%i", &N);
  for(i = 0; i < N; i++)
    p[i] = i + 1;
  Go(0);
}