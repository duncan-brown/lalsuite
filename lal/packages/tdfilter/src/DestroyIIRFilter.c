/***************************** <lalVerbatim file="DestroyIIRFilterCV">
Author: Creighton, T. D.
$Id$
****************************** </lalVerbatim> */

/* <lalLaTeX>

\subsection{Module \texttt{DestroyIIRFilter.c}}
\label{ss:DestroyIIRFilter.c}

Destroys IIR filter objects.

\subsubsection*{Prototypes}
\vspace{0.1in}
\input{DestroyIIRFilterCP}
\index{\texttt{LALDestroyREAL4IIRFilter()}}
\index{\texttt{LALDestroyREAL8IIRFilter()}}

\subsubsection*{Description}

These functions destroy an object \verb@**input@ of type
\texttt{REAL4IIRFilter} or \texttt{REAL8IIRFilter}, and set
\verb@*input@ to \verb@NULL@.

\subsubsection*{Algorithm}

\subsubsection*{Uses}
\begin{verbatim}
void LALFree()
void LALSDestroyVector()
void LALDDestroyVector()
\end{verbatim}

\subsubsection*{Notes}

\vfill{\footnotesize\input{DestroyIIRFilterCV}}

</lalLaTeX> */

#include <lal/LALStdlib.h>
#include <lal/AVFactories.h>
#include <lal/IIRFilter.h>

NRCSID(DESTROYIIRFILTERC,"$Id$");


/* <lalVerbatim file="DestroyIIRFilterCP"> */
void
LALDestroyREAL4IIRFilter( LALStatus      *stat,
			  REAL4IIRFilter **input )
{ /* </lalVerbatim> */
  INITSTATUS(stat,"LALDestroyREAL4IIRFilter",DESTROYIIRFILTERC);
  ATTATCHSTATUSPTR(stat);

  /* Make sure handle is non-null, and points to a non-null pointer.
     (The routine LALSDestroyVector will check that the data fields are
     non-null.) */
  ASSERT(input,stat,IIRFILTER_ENUL,IIRFILTER_MSGENUL);
  ASSERT(*input,stat,IIRFILTER_ENUL,IIRFILTER_MSGENUL);

  /* Destroy the vector fields. */
  TRY(LALSDestroyVector(stat->statusPtr,&((*input)->directCoef)),stat);
  TRY(LALSDestroyVector(stat->statusPtr,&((*input)->recursCoef)),stat);
  TRY(LALSDestroyVector(stat->statusPtr,&((*input)->history)),stat);

  /* Free the filter, then point the handle to NULL. */
  LALFree(*input);
  *input=NULL;

  /* Normal exit */
  DETATCHSTATUSPTR(stat);
  RETURN(stat);
}


/* <lalVerbatim file="DestroyIIRFilterCP"> */
void
LALDestroyREAL8IIRFilter( LALStatus      *stat,
			  REAL8IIRFilter **input )
{ /* </lalVerbatim> */
  INITSTATUS(stat,"LALDestroyREAL8IIRFilter",DESTROYIIRFILTERC);
  ATTATCHSTATUSPTR(stat);

  /* Make sure handle is non-null, and points to a non-null pointer.
     (The routine LALDDestroyVector will check that the data fields are
     non-null.) */
  ASSERT(input,stat,IIRFILTER_ENUL,IIRFILTER_MSGENUL);
  ASSERT(*input,stat,IIRFILTER_ENUL,IIRFILTER_MSGENUL);

  /* Destroy the vector fields. */
  TRY(LALDDestroyVector(stat->statusPtr,&((*input)->directCoef)),stat);
  TRY(LALDDestroyVector(stat->statusPtr,&((*input)->recursCoef)),stat);
  TRY(LALDDestroyVector(stat->statusPtr,&((*input)->history)),stat);

  /* Free the filter, then point the handle to NULL. */
  LALFree(*input);
  *input=NULL;

  /* Normal exit */
  DETATCHSTATUSPTR(stat);
  RETURN(stat);
}
