/* -*- c++ -*- */
/*
 * Copyright 2026 Tamas Deli.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "cyclic_prefix_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace ofdm {

cyclic_prefix::sptr cyclic_prefix::make(int sample_count, int cyclic_prefix_length)
{
    return gnuradio::make_block_sptr<cyclic_prefix_impl>(sample_count,
                                                         cyclic_prefix_length);
}


cyclic_prefix_impl::cyclic_prefix_impl(int sample_count, int cyclic_prefix_length)
    : gr::sync_block("cyclic_prefix",
                     gr::io_signature::make(1, 1, sizeof(gr_complex) * sample_count),
                     gr::io_signature::make(1, 1, sizeof(gr_complex) * (sample_count + cyclic_prefix_length)))
{
    d_sample_count = sample_count;
    d_cyclic_prefix_length = cyclic_prefix_length;
}


cyclic_prefix_impl::~cyclic_prefix_impl() {}

int cyclic_prefix_impl::work(int noutput_items,
                             gr_vector_const_void_star& input_items,
                             gr_vector_void_star& output_items)
{
    const gr_complex* input_buffer =
        static_cast<const gr_complex*>(input_items[0]);

    gr_complex* output_buffer =
        static_cast<gr_complex*>(output_items[0]);


    for (int i = 0; i < noutput_items; ++i) {

        const gr_complex* input_symbol = input_buffer + i * d_sample_count;
        gr_complex* output_symbol = output_buffer + i * (d_sample_count + d_cyclic_prefix_length);


        std::copy(
            input_symbol + (d_sample_count - d_cyclic_prefix_length),
            input_symbol + d_sample_count,
            output_symbol
        );

        std::copy(
            input_symbol,
            input_symbol + d_sample_count,
            output_symbol + d_cyclic_prefix_length
        );
    }

    return noutput_items;
}

} /* namespace ofdm */
} /* namespace gr */
