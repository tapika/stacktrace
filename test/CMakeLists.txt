# Copyright 2018 Tarmo Pikaro
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt

cmake_minimum_required(VERSION 3.15)

# Does not have it's own name in Jamfile.v2
add_executable(test_stacktrace test.cpp test_impl.cpp Jamfile.v2)

target_include_directories(test_stacktrace PRIVATE ../../..)
target_compile_definitions(test_stacktrace PRIVATE BOOST_STACKTRACE_DYN_LINK)
set_target_properties(test_stacktrace PROPERTIES FOLDER stacktrace/tests)

target_link_libraries(test_stacktrace PRIVATE boost_stacktrace_windbg)