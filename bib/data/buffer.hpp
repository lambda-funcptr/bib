//
// Created by Guanyu Wu on 7/3/19.
// Copyright (c) 2019 Rimward Ltd. All rights reserved.
//

#pragma once

#include <string>
#include <vector>
#include <memory>

namespace bib::data {

class buffer {
public:
	explicit buffer(std::size_t initial_size);
	explicit buffer(std::string_view& string);
	explicit buffer(std::vector<std::byte>& vector);

	buffer(buffer& copy);
	buffer& operator=(const buffer& copy);

	buffer(buffer&& other) noexcept;
	buffer& operator=(buffer&& other) noexcept;

	~buffer() noexcept;

	std::byte* data() noexcept;
	[[nodiscard]] const std::byte* data() const noexcept;

	[[nodiscard]] std::size_t size() const noexcept;

private:
	std::size_t buffer_size;
	std::unique_ptr<std::byte[]> buffer_data;
};

}