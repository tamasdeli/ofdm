/* -*- c++ -*- */
/*
 * Copyright 2026 Tamas Deli.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_OFDM_CYCLIC_PREFIX_H
#define INCLUDED_OFDM_CYCLIC_PREFIX_H

#include <gnuradio/ofdm/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
namespace ofdm {

/*!
 * \brief <+description of block+>
 * \ingroup ofdm
 *
 */
class OFDM_API cyclic_prefix : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<cyclic_prefix> sptr;
    static sptr make(int sample_count, int cyclic_prefix_length);
};

} // namespace ofdm
} // namespace gr

#endif /* INCLUDED_OFDM_CYCLIC_PREFIX_H */
