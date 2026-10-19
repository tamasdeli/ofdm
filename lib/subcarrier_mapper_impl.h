/* -*- c++ -*- */
/*
 * Copyright 2026 Tamas Deli.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_OFDM_SUBCARRIER_MAPPER_IMPL_H
#define INCLUDED_OFDM_SUBCARRIER_MAPPER_IMPL_H

#include <gnuradio/ofdm/subcarrier_mapper.h>

namespace gr {
namespace ofdm {

class subcarrier_mapper_impl : public subcarrier_mapper
{
private:
    int d_subcarrier_count;

public:
    subcarrier_mapper_impl(int subcarrier_count);
    ~subcarrier_mapper_impl();

    void forecast(int noutput_items, gr_vector_int& ninput_items_required);

    int general_work(int noutput_items,
                     gr_vector_int& ninput_items,
                     gr_vector_const_void_star& input_items,
                     gr_vector_void_star& output_items);
};

} // namespace ofdm
} // namespace gr

#endif /* INCLUDED_OFDM_SUBCARRIER_MAPPER_IMPL_H */
