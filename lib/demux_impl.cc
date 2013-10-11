/* -*- c++ -*- */
/* 
 * Copyright 2013 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gr_io_signature.h>
#include "demux_impl.h"
#include <vector>

namespace gr {
  namespace demux {

    demux::sptr
    demux::make(int decimation)
    {
      return gnuradio::get_initial_sptr (new demux_impl(decimation));
    }

    /*
     * The private constructor
     */
    demux_impl::demux_impl(int decimation)
      : gr_sync_block("demux",
		      gr_make_io_signature(1, 1, sizeof (gr_complex)),
		      gr_make_io_signature(decimation, decimation, sizeof(gr_complex)))
    {
        d_decimation = decimation;
//        set_output_signature(gr::io_signature::make(d_decimation, d_decimation, sizeof(gr_complex)));
    }

    /*
     * Our virtual destructor.
     */
    demux_impl::~demux_impl()
    {
    }

    int
    demux_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        size_t item_size = output_signature()->sizeof_stream_item(0);

        const char *in = (const char *)input_items[0];
        char **outv = (char **)&output_items[0];
        int nstreams = output_items.size();
      
        for (int i = 0; i < noutput_items; i++) {
	        for (int j = 0; j < nstreams; j++) {
	        memcpy(outv[j], in, item_size);
	        outv[j] += item_size;
	        in += item_size;
	    }
       }
        return noutput_items;
    }

  } /* namespace demux */
} /* namespace gr */

