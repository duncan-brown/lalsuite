/*----------------------------------------------------------------------- 
 * 
 * File Name: WindowTest.c
 * 
 * Author: Allen, Bruce ballen@dirac.phys.uwm.edu 
 * 
 * Revision: $Id$
 * 
 *----------------------------------------------------------------------- 
 * 
 * NAME 
 *   main()
 *
 * SYNOPSIS 
 * 
 * DESCRIPTION 
 *   Test suite for Window generator
 * 
 * DIAGNOSTICS
 *   Writes PASS, FAIL to stdout as tests are passed or failed. 
 *   Returns 0 if all tests passed and -1 if any test failed. 
 * 
 * CALLS
 *   Window
 * 
 * NOTES
 * 
 *-----------------------------------------------------------------------
 */

#ifndef _STDLIB_H
#include <stdlib.h>
#ifndef _STDLIB_H
#define _STDLIB_H
#endif
#endif

#ifndef _STDIO_H
#include <stdio.h>
#ifndef _STDIO_H
#define _STDIO_H
#endif
#endif

#ifndef _MATH_H
#include <math.h>
#ifndef _MATH_H
#define _MATH_H
#endif
#endif

#ifndef _STRING_H
#include <string.h>
#ifndef _STRING_H
#define _STRING_H
#endif
#endif

#ifndef _LALDATATYPES_H
#include "LALDatatypes.h"
#ifndef _LALDATATYPES_H
#define _LALDATATYPES_H
#endif
#endif

#ifndef _AVFACTORIES_H
#include "AVFactories.h"
#ifndef _AVFACTORIES_H
#define _AVFACTORIES_H
#endif
#endif

#ifndef _WINDOW_H
#include "Window.h"
#ifndef _WINDOW_H
#define _WINDOW_H
#endif
#endif

#ifndef _PRINTVECTOR_H
#include "PrintVector.h"
#ifndef _PRINTVECTOR_H
#define _PRINTVECTOR_H
#endif
#endif

NRCSID (MAIN, "$Id$");

/* modify this value to get a stack trace of test */
int debuglevel=2;

/* modify this to turn on printing windows into files for checking */
#define PRINT 1

int
check(Status *status,INT4 code,CHAR * message)
{
  if (status->statusCode != code) {
    printf("FAIL: did not recognize %s\n",message);
    return 1;
  }
  else if (strcmp(message,status->statusDescription)) {
    printf("FAIL: incorrect warning message %s not %s\n",status->statusDescription,message);
    return 1;
  }
  return 0;
}


int main()
{

  static Status status;     
  REAL4Vector *vector = NULL;
  REAL4Vector dummy;
  WindowParams params;
  WindowType wintype;
  REAL8 testsquares[]=
    {1024.0,     /* rectangular */
    384.0,       /* Hann */
    546.0+2.0/15.0,   /* Welch */
    341.333984375,     /* Bartlett */
    276.1142857152779,   /* Parzen */
    300.357781729967622,   /* Papoulis */
    406.9376};     /* Hamming */

  CreateVector (&status, &vector, 1024);

  /* Test behavior for null parameter block */
  Window (&status,vector,NULL );
  if (check(&status,WINDOW_NULLPARAM,WINDOW_MSGNULLPARAM)) return 1;

  /* Test behavior for null vector block */
  Window (&status,NULL,&params );
  if (check(&status,WINDOW_NULLHANDLE,WINDOW_MSGNULLHANDLE)) return 1;

  /* Test behavior for non-positive length  */
  params.length=0;
  Window (&status,vector,&params);
  if (check(&status,WINDOW_ELENGTH,WINDOW_MSGELENGTH)) return 1;

  /* Test failures for undefined window type on lower and upper bounds */
  params.length=1024;
  params.type=-1;
  Window ( &status, vector, &params );
  if (check(&status,WINDOW_TYPEUNKNOWN,WINDOW_MSGTYPEUNKNOWN)) return 1;
  params.type=NUMBERWINDOWTYPES;
  Window ( &status, vector, &params );
  if (check(&status,WINDOW_TYPEUNKNOWN,WINDOW_MSGTYPEUNKNOWN)) return 1;

  params.type=Rectangular;

  /* test that we get an error if the wrong vector length is present */
  dummy.length=1234;
  dummy.data=NULL;
  Window ( &status, &dummy, &params );
  if (check(&status,WINDOW_WRONGLENGTH,WINDOW_MSGWRONGLENGTH)) return 1;

  /* test that we get an error if the vector data area null */
  dummy.length=params.length;
  Window ( &status, &dummy, &params );
  if (check(&status,WINDOW_NULLDATA,WINDOW_MSGNULLDATA)) return 1;


  /* Test normalizations */
  for (wintype=Rectangular;wintype<=Hamming;wintype++)
  {
    params.type=wintype;
    Window (&status,vector,&params);
    if (fabs(params.sumofsquares-testsquares[(int)wintype])>1.e-5)
    {
      printf("FAIL: Window %s appears incorrect.\n",params.windowname);
      return 1;
    }
    if (PRINT) PrintVector(vector);
  }


  printf("PASS Window()\n");

  DestroyVector (&status, &vector);

  return 0;
}
