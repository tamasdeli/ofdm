/* -*- c++ -*- */
/*
 * Copyright 2026 Tamas Deli.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_OFDM_QAM_MAPPER_IMPL_H
#define INCLUDED_OFDM_QAM_MAPPER_IMPL_H

#include <gnuradio/ofdm/qam_mapper.h>
#include <cmath> // log2 miatt
#include <stdexcept> // 
#include <complex>

namespace gr {
namespace ofdm {

class qam_mapper_impl : public qam_mapper
{
private:
    int d_modulation_order;
    int d_bits_per_symbol;

    unsigned int gray_decode(unsigned int gray, int bit_number);

public:
    qam_mapper_impl(int modulation_order);
    ~qam_mapper_impl();

    void forecast(int noutput_items, gr_vector_int& ninput_items_required);

    int general_work(int noutput_items,
                     gr_vector_int& ninput_items,
                     gr_vector_const_void_star& input_items,
                     gr_vector_void_star& output_items);
};

} // namespace ofdm
} // namespace gr

#endif /* INCLUDED_OFDM_QAM_MAPPER_IMPL_H */
