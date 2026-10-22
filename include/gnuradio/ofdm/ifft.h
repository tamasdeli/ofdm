/* -*- c++ -*- */
/*
 * Copyright 2026 Tamas Deli.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_OFDM_IFFT_H
#define INCLUDED_OFDM_IFFT_H

#include <gnuradio/ofdm/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
namespace ofdm {

/*!
 * \brief <+description of block+>
 * \ingroup ofdm
 *
 */
class OFDM_API ifft : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<ifft> sptr;
    static sptr make(int ifft_size);
};

} // namespace ofdm
} // namespace gr

#endif /* INCLUDED_OFDM_IFFT_H */
