/* -*- c++ -*- */
/*
 * Copyright 2026 Tamas Deli.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_OFDM_CYCLIC_PREFIX_IMPL_H
#define INCLUDED_OFDM_CYCLIC_PREFIX_IMPL_H

#include <gnuradio/ofdm/cyclic_prefix.h>

namespace gr {
namespace ofdm {

class cyclic_prefix_impl : public cyclic_prefix
{
private:
    int d_sample_count;
    int d_cyclic_prefix_length;

public:
    cyclic_prefix_impl(int sample_count, int cyclic_prefix_length);
    ~cyclic_prefix_impl();

    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace ofdm
} // namespace gr

#endif /* INCLUDED_OFDM_CYCLIC_PREFIX_IMPL_H */
