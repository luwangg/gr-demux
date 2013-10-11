/* -*- c++ -*- */

#define DEMUX_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "demux_swig_doc.i"

%{
#include "demux/demux.h"
%}


%include "demux/demux.h"
GR_SWIG_BLOCK_MAGIC2(demux, demux);
