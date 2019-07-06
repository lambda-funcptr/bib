//
// Created by Guanyu Wu on 7/3/19.
// Copyright (c) 2019 Rimward Ltd. All rights reserved.
//

#include "buffer.hpp"
#include "span.hpp"

namespace bib::data {

template <typename T>
buffer serialize(T& data);

template <typename T>
T deserialize(const span<buffer>& data);

}