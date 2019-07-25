//
// Created by Guanyu Wu on 7/24/19.
// Copyright (c) 2019 Rimward Ltd. All rights reserved.
//

#pragma once

#include <cstring>

namespace bib::lang {

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

// Does not check for negatives or ".xxxx" style.
bool is_numeral(char input) {
	char cmpstr[2] = {input, '\0'};
	return std::strpbrk("0123456789", cmpstr);
}

}