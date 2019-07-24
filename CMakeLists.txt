cmake_minimum_required(VERSION 3.9)
project(bib)

set(CMAKE_CXX_STANDARD 17)

add_library(bib STATIC
        bib/expected.hpp
        bib/cpl/light_mutex.hpp
        bib/cpl/light_mutex.cpp
        bib/cpl/lock.hpp
        bib/data/buffer.cpp
        bib/data/buffer.hpp
        bib/data/serialize.hpp
        bib/data/span.hpp bib/lang/char_traits.hpp bib/lang/char_traits.cpp)

#add_executable(bibtests )