//
// Created by Guanyu Wu on 7/3/19.
// Copyright (c) 2019 Rimward Ltd. All rights reserved.
//

#include <cstring>
#include "buffer.hpp"

namespace bib::data {

buffer::buffer(std::size_t initial_size) : buffer_size{initial_size} {
	buffer_data = std::make_unique<std::byte[]>(initial_size);
}

buffer::buffer(std::string_view& string) : buffer(string.size()) {
	std::memcpy(buffer_data.get(), string.data(), string.size());
}

buffer::buffer(std::vector<std::byte>& vector) : buffer(vector.size()) {
	std::memcpy(buffer_data.get(), vector.data(), vector.size());
}

buffer::buffer(buffer& copy) : buffer(copy.buffer_size) {
}

buffer& buffer::operator=(const buffer& other) {
	buffer_size = other.size();
	buffer_data = std::make_unique<std::byte[]>(other.size());

	std::memcpy(buffer_data.get(), other.data(), other.size());

	return *this;
}

buffer::buffer(buffer&& other) noexcept {
	buffer_data = std::move(other.buffer_data);
	buffer_size = other.size();
}

buffer& buffer::operator=(buffer&& other) noexcept {
	buffer_data = std::move(other.buffer_data);
	buffer_size = other.size();

	return *this;
}

buffer::~buffer() noexcept = default;

std::byte* buffer::data() noexcept {
	return buffer_data.get();
}

const std::byte* buffer::data() const noexcept {
	return 	buffer_data.get();
}

std::size_t buffer::size() const noexcept {
	return buffer_size;
}


}