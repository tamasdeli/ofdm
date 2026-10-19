/* -*- c++ -*- */
/*
 * Copyright 2026 Tamas Deli.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_OFDM_SUBCARRIER_MAPPER_H
#define INCLUDED_OFDM_SUBCARRIER_MAPPER_H

#include <gnuradio/block.h>
#include <gnuradio/ofdm/api.h>

namespace gr {
namespace ofdm {

/*!
 * \brief <+description of block+>
 * \ingroup ofdm
 *
 */
class OFDM_API subcarrier_mapper : virtual public gr::block
{
public:
    typedef std::shared_ptr<subcarrier_mapper> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of ofdm::subcarrier_mapper.
     *
     * To avoid accidental use of raw pointers, ofdm::subcarrier_mapper's
     * constructor is in a private implementation
     * class. ofdm::subcarrier_mapper::make is the public interface for
     * creating new instances.
     */
    static sptr make(int subcarrier_count);
};

} // namespace ofdm
} // namespace gr

#endif /* INCLUDED_OFDM_SUBCARRIER_MAPPER_H */
