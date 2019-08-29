//
// Created by Guanyu Wu on 7/2/19.
// Copyright (c) 2019 Rimward Ltd. All rights reserved.
//

#include <type_traits>
#include <variant>

namespace bib {

template<typename Exp, typename Uxp>
class expected {
public:
	// We should be able to construct this without additional verbosity.
	expected(const Exp& value) : values{value} { } // NOLINT(google-explicit-constructor,hicpp-explicit-conversions

	explicit expected(const Uxp& error) : values{error} { }

	~expected() = default;

	[[nodiscard]] bool operator !() const {
		// Returns true if the value is expected, false if not.
		return valid();
	}

	[[nodiscard]] bool valid() const {
		return values.index() == 0;
	}

	Exp get() const {
		return std::get<Exp>(values);
	}

	Uxp get_error() const {
		return std::get<Uxp>(values);
	};

	// map :: map :: m a -> (a -> b) -> m b
	template<typename F>
	std::enable_if_t<!std::is_void_v<std::invoke_result_t<F, Exp>>, std::invoke_result_t<F>>
	map(F function) {
		if (valid()) {
			auto value = function(std::get<Exp>(values));
			return expected<decltype(value), Uxp>(value);
		}

		return expected<typename std::invoke_result<F, Exp>::type, Uxp>(std::get<Uxp>(values));
	}

	// If the function doesn't return anything.
	template <typename F>
	std::enable_if<std::is_void_v<std::invoke_result_t<F, Exp>>, void>
	map(F function) {
		if (valid()) {
            function(std::get<Exp>(values));
        }

		return std::enable_if<std::is_void_v<std::invoke_result_t<F, Exp>>, void>{};
    }

	// A way to invoke map.
	template <typename F>
	auto operator*(F function) {
		return map(function);
	}

	// bind :: m a -> ( a -> m b ) -> m b
	template <typename F>
	std::enable_if_t<!std::is_void_v<std::invoke_result_t<F>>, std::invoke_result_t<F>>
	bind(F function) {
		if (valid()) {
			return function(std::get<Exp>(values));
		}

		return expected<typename std::invoke_result<F, Exp>::type::error_type, Uxp>{std::get<Uxp>(values)};
	}

	// Another way to invoke bind.
	template <typename F>
	auto operator>=(F function) {
		return bind(function);
	}

	typedef Exp expected_type;

	typedef Uxp unexpected_type;

private:
	std::variant<Exp, Uxp> values;
};

}