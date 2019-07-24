//
// Created by Guanyu Wu on 7/24/19.
// Copyright (c) 2019 Rimward Ltd. All rights reserved.
//

#include "char_traits.hpp"
#include <cstring>

namespace {

bool is_whitespace(char input) {
	switch (input) {
		case ' ':
			return true;
		case '\f':
			return true;
		case '\n':
			return true;
		case '\r':
			return true;
		case '\t':
			return true;
		case '\v':
			return true;
		default:
			return false;
	}
}

bool is_alphanum(char input) {
	char cmpstr[2] = {input, '\0'};
	return std::strpbrk("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz", cmpstr);
}

}

