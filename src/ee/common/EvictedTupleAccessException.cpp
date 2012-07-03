/* Copyright (C) 2012 by H-Store Project
 * Brown University
 * Massachusetts Institute of Technology
 * Yale University
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include "common/EvictedTupleAccessException.h"
#include "common/SerializableEEException.h"
#include "common/serializeio.h"
#include <iostream>
#include <cassert>

using namespace voltdb;

EvictedTupleAccessException::EvictedTupleAccessException(std::string message) :
    SerializableEEException(VOLT_EE_EXCEPTION_TYPE_EVICTED_TUPLE, message) {
        
    // TODO: Need to store the blockIds EvictedTable into our array
    m_numBlockIds = 0;
    m_tableIds = new short[0];
    m_blockIds = new short[0];
}

void EvictedTupleAccessException::p_serialize(ReferenceSerializeOutput *output) {
    output->writeShort(static_cast<short>(m_numBlockIds)); // # of block ids
    for (int ii = 0; ii < m_numBlockIds; ii++) {
        output->writeShort(m_tableIds[ii]);
        output->writeShort(m_blockIds[ii]);
    }
}
