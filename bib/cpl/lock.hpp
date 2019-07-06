//
// Created by Guanyu Wu on 7/3/19.
// Copyright (c) 2019 Rimward Ltd. All rights reserved.
//

namespace bib::cpl {

template<typename M>
class lock {
public:
	explicit lock(M& mutex) : mut_ref{mutex} {
		while(!mut_ref.try_lock());
	}

	// No copies ever. At no point should a lock be copied.
	lock(lock&) = delete;
	lock& operator=(lock&) = delete;

	// Not sure about being able to pass a lock around...
	// I want to say no (just pass the mutex?), but it may be useful to someone.
	lock(lock&&) = delete;
	lock& operator=(lock&&) = delete;

	~lock() {
		mut_ref.unlock();
	}

private:
	M& mut_ref;
};

}