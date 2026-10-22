# Copyright 2020 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

########################################################################
# Check if there is C++ code at all
########################################################################
if(NOT ofdm_sources)
    message(STATUS "No C++ sources... skipping python bindings")
    return()
endif(NOT ofdm_sources)

########################################################################
# Check for pygccxml
########################################################################
gr_python_check_module_raw("pygccxml" "import pygccxml" PYGCCXML_FOUND)

include(GrPybind)

########################################################################
# Python Bindings
########################################################################

list(APPEND ofdm_python_files
    qam_mapper_python.cc
    subcarrier_mapper_python.cc
    ifft_python.cc
    cyclic_prefix_python.cc python_bindings.cc)

gr_pybind_make_oot(ofdm ../../.. gr::ofdm "${ofdm_python_files}")

# copy bindings extension for use in QA test module
add_custom_command(
    TARGET ofdm_python
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:ofdm_python>
            ${PROJECT_BINARY_DIR}/test_modules/gnuradio/ofdm/)

install(
    TARGETS ofdm_python
    DESTINATION ${GR_PYTHON_DIR}/gnuradio/ofdm
    COMPONENT pythonapi)
