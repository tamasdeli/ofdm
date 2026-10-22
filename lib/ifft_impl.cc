/* -*- c++ -*- */
/*
 * Copyright 2026 Tamas Deli.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "ifft_impl.h"
#include <gnuradio/io_signature.h>
#include <exception>
#include <algorithm>

namespace gr {
namespace ofdm {

ifft::sptr ifft::make(int ifft_size)
{
    return gnuradio::make_block_sptr<ifft_impl>(ifft_size);
}


ifft_impl::ifft_impl(int ifft_size)
    : gr::sync_block("ifft",
                     gr::io_signature::make(1, 1, sizeof(gr_complex) * ifft_size),
                     gr::io_signature::make(1, 1, sizeof(gr_complex) * ifft_size))
{
    d_ifft_size = ifft_size;

    d_ifft = std::make_unique<gr::fft::fft_complex_rev>(ifft_size);
}

/*
 * Our virtual destructor.
 */
ifft_impl::~ifft_impl() {}

int ifft_impl::work(int noutput_items,
                    gr_vector_const_void_star& input_items,
                    gr_vector_void_star& output_items)
{
    const gr_complex* input_buffer =
        static_cast<const gr_complex*>(input_items[0]);

    gr_complex* output_buffer =
        static_cast<gr_complex*>(output_items[0]);

    for (int i = 0; i < noutput_items; ++i) {

        const gr_complex* input_vector =
            input_buffer + i * d_ifft_size;

        gr_complex* output_vector =
            output_buffer + i * d_ifft_size;

        std::copy_n(
            input_vector,
            d_ifft_size,
            d_ifft->get_inbuf()
        );

        d_ifft->execute();

        for (int k = 0; k < d_ifft_size; ++k) {
            output_vector[k] =
                d_ifft->get_outbuf()[k] /
                static_cast<float>(d_ifft_size);
        }
    }

    return noutput_items;
}

} /* namespace ofdm */
} /* namespace gr */
