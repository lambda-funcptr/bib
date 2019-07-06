//
// Created by Guanyu Wu on 7/3/19.
// Copyright (c) 2019 Rimward Ltd. All rights reserved.
//

#include "light_mutex.hpp"

namespace bib::cpl {

light_mutex::light_mutex() : lockstate{0} { }

light_mutex::~light_mutex() = default;

bool light_mutex::try_lock() {
	if (lockstate++ != 0) {
		lockstate--;
		return false;
	} else
		return true;
}

void light_mutex::lock() {
	while(!try_lock()) {};
}

void light_mutex::unlock() {
	lockstate--;
}

}