//
// Created by Guanyu Wu on 7/3/19.
// Copyright (c) 2019 Rimward Ltd. All rights reserved.
//


#pragma once

#include <atomic>

namespace bib::cpl {

class light_mutex {
public:
	light_mutex();
	~light_mutex();

	bool try_lock();
	void lock();

	void unlock();

private:
	std::atomic<uint8_t> lockstate;
};

}