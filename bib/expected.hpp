//
// Created by Guanyu Wu on 7/2/19.
// Copyright (c) 2019 Rimward Ltd. All rights reserved.
//

#include <type_traits>

namespace bib {

template<typename Exp, typename Err>
class expected {
public:
	// We should be able to construct this without additional verbosity.
	expected(Exp value) : expected_flag(true) { // NOLINT(google-explicit-constructor,hicpp-explicit-conversions)
		values.expected_value = value;
	}

	explicit expected(Err error) : expected_flag{false} {
		values.unexpected_value = error;
	}

	bool operator !() const {
		return !expected_flag;
	}

	bool valid() const {
		return expected_flag;
	}

	Exp& get() const {
		return values.expected_value;
	}

	Err& get_error() const {
		return values.unexpected_value;
	};

	// map :: map :: m a -> (a -> b) -> m b
	template<typename F>
	auto map(F function) {
		if (expected_flag) {
			auto value = function(values.expected_value);
			return expected<decltype(value), Err>(value);
		}

		return expected<typename std::invoke_result<F, Exp>::type, Err>(values.unexpected_value);
	}

	// A way to invoke map.
	template <typename F>
	auto operator*(F function) {
		return map(function);
	}

	// bind :: m a -> ( a -> m b ) -> m b
	template <typename F>
	auto bind(F function) {
		if (expected_flag) {
			return function(values.expected_value);
		}

		return expected<typename std::invoke_result<F, Exp>::type::error_type, Err>{values.unexpected_value};
	}

	// Another way to invoke bind.
	template <typename F>
	auto operator>=(F function) {
		return bind(function);
	}

	typedef Exp expected_type;

	typedef Err unexpected_type;

private:
	union {
		Exp expected_value;
		Err unexpected_value;
	} values;

	bool expected_flag;
};

}