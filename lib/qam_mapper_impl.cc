/* -*- c++ -*- */
/*
 * Copyright 2026 Tamas Deli.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "qam_mapper_impl.h"
#include <gnuradio/io_signature.h>
#include <algorithm> // std::min

namespace gr {
namespace ofdm {

qam_mapper::sptr qam_mapper::make(int modulation_order)
{
    return gnuradio::make_block_sptr<qam_mapper_impl>(modulation_order);
}


qam_mapper_impl::qam_mapper_impl(int modulation_order)
    : gr::block("qam_mapper",
                gr::io_signature::make(1, 1, sizeof(uint8_t)),
                gr::io_signature::make(1, 1, sizeof(gr_complex))),
                d_modulation_order(modulation_order)
{
    // n & n-1 = 0 or std::has_single_bit()
    bool power_of_two = modulation_order & (modulation_order - 1);

    if ((power_of_two != 0) or (modulation_order == 0)){
        throw std::invalid_argument("Invalid modulation order");
    } 

    d_bits_per_symbol = static_cast<int>(std::log2(modulation_order));
    
}

/*
 * Our virtual destructor.
 */
qam_mapper_impl::~qam_mapper_impl() {}


unsigned int qam_mapper_impl::gray_decode(unsigned int gray_code, int bit_number)
{
    /*
     * A Gray enkódolás a következőek szerint működik g = i XOR (i >> 1), ahol a
     * g a Gray kód és i az index. Az XOR az antivalencia kapuként is ismert, amely
     * akkor 1, ha a két bit különböző. A Gray kódolásnál az a kulcs, hogy a két egymás melletti
     * konstellációs pont között csak 1 bit különbözzőn. 
     * 
     * Pl vegyük 0b101-et mint 5 ös decimális érték.
     * 
     *     101 Erdeti (5)
     *     010 Shift-elt
     * XOR ------
     *     111
     * 
     *     110 Erdeti (6)
     *     011 Shift-elt
     * XOR ------
     *     101
     * 
     *     100 Erdeti (4)
     *     010 Shift-elt
     * XOR ------
     *     110
     *
     */ 

    /*
     * A Gray dekódolásnál ezzel szemben egy bináris kódot szeretnénk egy indexnek megfeletetni.
     * Mivel a Gray enkódolás minden bitet az eltolt szomszéddal vett XOR művelettel hozott létre,
     * ezért ezb megfordítva a képlet a következő: b(j) = b(j+1) XOR g(j)
     * 
     * Az 101 ből kapott 111 értékkel lehet szemléltetni az algoritmus működését. Amennyiben a következőek
     * szerint alakult a dekódolás
     * 
     *     101 Erdeti (5)
     *     010 Shift-elt
     * XOR ------
     *     111
     * 
     * Akkor 111 a Gray kód. Mivel az index eltolt verziójából állítjuk elő az első bitet, és a 
     * 0 jön be balról a shift-elésnél, ezért tudhatjuk, hogy amennyiben a shifte-elt érték MSB-je
     * minden esetben 0, akkor csak akkor lehet 1 az XOR művelete, ha 1 volt az index MSB-je.
     * Amennyiben 1 volt az eredeti MSB, akkor a shift-el MSB után helyiértéken 1-lesz és csak akkor
     * lehetett 1 a kimenet, ha 0 volt az index-ben az adott helyiértéken. Ezzel a logikával tovább
     * haladva végig iterálhatunk a Gray kódon az MSB alapján és megkapjuk az eredeti index-et.
     */ 
    unsigned int index = 0;
    unsigned int previous_bit = 0;

    for (int i = bit_number - 1; i >= 0; --i) {
        unsigned int gray_bit = (gray_code >> i) & 1U;
        unsigned int binary_bit = previous_bit ^ gray_bit;

        index |= binary_bit << i;
        previous_bit = binary_bit;
    }

    return index;
}

void qam_mapper_impl::forecast(int noutput_items, gr_vector_int& ninput_items_required)
{
    // ninput_items_required is a std::vector and we will only have one input
    ninput_items_required[0] = noutput_items * d_bits_per_symbol;
}

int qam_mapper_impl::general_work(int noutput_items, // Ennyi kimeneti kér a sceduler
                                  gr_vector_int& ninput_items, // ninput_items[0] ennyi bemenet áll rendelkezésre
                                  gr_vector_const_void_star& input_items, 
                                  gr_vector_void_star& output_items)
{

    int number_of_input_bits = ninput_items[0];
    const uint8_t* input_buffer = static_cast<const uint8_t*>(input_items[0]);
    gr_complex* output_buffer = static_cast<gr_complex*>(output_items[0]);

    const int symbols_to_process = std::min(
        noutput_items,
        number_of_input_bits / d_bits_per_symbol
    );

    const int bits_per_axis = d_bits_per_symbol / 2;
    const int levels = 1 << bits_per_axis;

    const float normalization = std::sqrt(2.0f * (d_modulation_order - 1) / 3.0f); // ?

    for (int i = 0; i < symbols_to_process; ++i) {
        // Minden iterációban egy szimbólumot állítunk elő

        unsigned int gray_i = 0;
        unsigned int gray_q = 0;

        for (int j = 0; j < bits_per_axis; ++j) {
            gray_i = (gray_i << 1) | input_buffer[i * d_bits_per_symbol + j];
            gray_q = (gray_q << 1) | input_buffer[i * d_bits_per_symbol + bits_per_axis + j];
        }

        // Gray-címkék átalakítása amplitúdóindexekké
        const unsigned int index_i = gray_decode(gray_i, bits_per_axis);
        const unsigned int index_q = gray_decode(gray_q, bits_per_axis);

        // Amplitúdószintek meghatározása
        const float I = 2.0f * index_i - (levels - 1); // ?
        const float Q = 2.0f * index_q - (levels - 1);

        // Normalizált komplex QAM-szimbólum
        output_buffer[i] = gr_complex(
            I / normalization,
            Q / normalization
        );
    }

    consume_each(symbols_to_process * d_bits_per_symbol);

    return symbols_to_process;
}


} /* namespace ofdm */
} /* namespace gr */
