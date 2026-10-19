/* -*- c++ -*- */
/*
 * Copyright 2026 Tamas Deli.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "subcarrier_mapper_impl.h"
#include <gnuradio/io_signature.h>
#include <exception>
#include <algorithm>

namespace gr {
namespace ofdm {

subcarrier_mapper::sptr subcarrier_mapper::make(int subcarrier_count)
{
    return gnuradio::make_block_sptr<subcarrier_mapper_impl>(subcarrier_count);
}

/*
 * The private constructor
 */
subcarrier_mapper_impl::subcarrier_mapper_impl(int subcarrier_count)
    : gr::block("subcarrier_mapper",
                gr::io_signature::make(1, 1, sizeof(gr_complex)),
                gr::io_signature::make(1, 1, sizeof(gr_complex)*subcarrier_count))
{
    if (subcarrier_count <= 0){
        throw std::invalid_argument("Subcarrier count is not valid!");
    }
    d_subcarrier_count = subcarrier_count;
}

/*
 * Our virtual destructor.
 */
subcarrier_mapper_impl::~subcarrier_mapper_impl() {}

void subcarrier_mapper_impl::forecast(int noutput_items,
                                      gr_vector_int& ninput_items_required)
{
    ninput_items_required[0] = noutput_items * d_subcarrier_count;
}

int subcarrier_mapper_impl::general_work(int noutput_items,
                                         gr_vector_int& ninput_items,
                                         gr_vector_const_void_star& input_items,
                                         gr_vector_void_star& output_items)
{
    int number_of_input_bits = ninput_items[0];
    const gr_complex* input_buffer = static_cast<const gr_complex*>(input_items[0]);
    gr_complex* output_buffer = static_cast<gr_complex*>(output_items[0]);

    const int symbols_to_process = std::min(
        noutput_items,
        number_of_input_bits / d_subcarrier_count
    );


    int complex_count = symbols_to_process * d_subcarrier_count;

    std::copy_n(input_buffer, complex_count, output_buffer);

    consume_each(complex_count);

    return symbols_to_process;

}

} /* namespace ofdm */
} /* namespace gr */
