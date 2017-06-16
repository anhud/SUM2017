/* FILE NAME: UNITS.H
 * PROGRAMMER: AH5
 * DATE: 09.06.2017
 * PURPOSE: nyet
 */

#ifndef __UNITS_H_
#define __UNITS_H_

#include "anim.h"

/* Unit cow creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (ah5UNIT *) pointer to created unit.
 */
ah5UNIT *AH5_UnitCreateCow( VOID );
ah5UNIT *AH5_UnitCreateControl( VOID );
ah5UNIT *AH5_UnitCreateOwl( VOID );
ah5UNIT *AH5_UnitCreatePlain( VOID );

#endif