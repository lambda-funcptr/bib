//
// Created by Guanyu Wu on 7/3/19.
// Copyright (c) 2019 Rimward Ltd. All rights reserved.
//

#include <cstdint>
#include <cstddef>

namespace bib::data {

template <typename T>
class span {
public:
	explicit span(const T& container) : container_ref{container}, begin_offset{0}, end_offset{container.size()} { }
	~span() = default;

	auto operator[](std::size_t element) {
		return container_ref[begin_offset + element];
	}

	auto data() const {
		return container_ref.data() + begin_offset;
	}

	[[nodiscard]] std::size_t size() const {
		return end_offset - begin_offset;
	}

	void trim_front(std::size_t trim) {
		begin_offset += trim;
	}

	void trim_back(std::size_t trim) {
		end_offset += trim;
	}

private:
	const T& container_ref;
	std::size_t begin_offset;
	std::size_t end_offset;
};

}