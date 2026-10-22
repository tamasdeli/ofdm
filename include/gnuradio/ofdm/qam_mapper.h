/* -*- c++ -*- */
/*
 * Copyright 2026 Tamas Deli.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_OFDM_QAM_MAPPER_H
#define INCLUDED_OFDM_QAM_MAPPER_H

#include <gnuradio/block.h>
#include <gnuradio/ofdm/api.h>

namespace gr {
namespace ofdm {

/*!
 * \brief <+description of block+>
 * \ingroup ofdm
 *
 */
class OFDM_API qam_mapper : virtual public gr::block
{
public:
    typedef std::shared_ptr<qam_mapper> sptr;
    static sptr make(int modulation_order = 4);
};

} // namespace ofdm
} // namespace gr

#endif /* INCLUDED_OFDM_QAM_MAPPER_H */
