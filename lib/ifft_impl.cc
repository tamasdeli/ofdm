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

ifft::sptr ifft::make(int fft_size)
{
    return gnuradio::make_block_sptr<ifft_impl>(fft_size);
}


/*
 * The private constructor
 */
ifft_impl::ifft_impl(int fft_size)
    : gr::sync_block("ifft",
                     gr::io_signature::make(1, 1, sizeof(gr_complex)*fft_size),
                     gr::io_signature::make(1, 1, sizeof(gr_complex)*fft_size))
{
    d_fft_size = fft_size;
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
            input_buffer + i * d_fft_size;

        gr_complex* output_vector =
            output_buffer + i * d_fft_size;

        // 1. Bemeneti vektor az FFT munkabufferébe
        std::copy_n(
            input_vector,
            d_fft_size,
            d_fft->get_inbuf()
        );

        // 2. Inverz FFT végrehajtása
        d_fft->execute();

        // 3. Normalizált eredmény a kimeneti bufferbe
        for (int k = 0; k < d_fft_size; ++k) {
            output_vector[k] =
                d_fft->get_outbuf()[k] /
                static_cast<float>(d_fft_size);
        }
    }

    return noutput_items;
}

} /* namespace ofdm */
} /* namespace gr */
