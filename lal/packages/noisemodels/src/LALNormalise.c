/*  <lalVerbatim file="LALNormaliseCV">
Author: Sathyaprakash, B. S.
$Id$
</lalVerbatim>  */
/* <lalLaTeX>
\subsection{Module \texttt{LALNormalise.c}}
Module to find the norm of a signal and to return a normalised 
array. The original signal is left untouched.

\subsubsection*{Prototypes}
\vspace{0.1in}
\input{LALNormaliseCP}
\index{\verb&LALNormalise()&}

\subsubsection*{Description}
\subsubsection*{Algorithm}
\subsubsection*{Uses}
\begin{verbatim}
\end{verbatim}

\subsubsection*{Notes}

\vfill{\footnotesize\input{LALNormaliseCV}}
</lalLaTeX>  */
#include <lal/LALNoiseModels.h>

NRCSID (LALNORMALISEC, "$Id$");

/*  <lalVerbatim file="LALNormaliseCP"> */
void
LALNormalise (
   LALStatus *status, 
   REAL4Vector *in, 
   REAL8 *norm,
   REAL8Vector psd) 
{  /*  </lalVerbatim>  */
  INT4 i, n, nby2, k;
  REAL8 psdvalue;
  INITSTATUS (status, "LALNormalise", LALNORMALISEC);
  if (psd.length != in->length/2+1) {
  fprintf(stderr, "LALNormalise: Incompatible lengths %d, %d\n",
     psd.length, in->length);
     exit(1);
  }

  n = in->length;
  *norm = 0;
  nby2 = n/2;
  for (i=1; i<nby2; i++) {
     k = n-i;
     psdvalue = psd.data[i+1];
     if (psdvalue) *norm += (pow(in->data[i],2.)+pow(in->data[k],2.))/psdvalue;
  }
  *norm = sqrt(*norm);
  
  i=n;
  while (i--) *(in->data+i) = *(in->data+i) / *norm;
  RETURN(status);
}

