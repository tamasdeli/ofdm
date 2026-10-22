/* -*- c++ -*- */
/*
 * Copyright 2026 Tamas Deli.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_OFDM_IFFT_IMPL_H
#define INCLUDED_OFDM_IFFT_IMPL_H

#include <gnuradio/ofdm/ifft.h>
#include <gnuradio/fft/fft.h>
#include <memory>

namespace gr {
namespace ofdm {

class ifft_impl : public ifft
{
private:
    int d_ifft_size;
    std::unique_ptr<gr::fft::fft_complex_rev> d_ifft;

public:
    ifft_impl(int ifft_size);
    ~ifft_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace ofdm
} // namespace gr

#endif /* INCLUDED_OFDM_IFFT_IMPL_H */
