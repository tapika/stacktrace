// Copyright Antony Polukhin, 2016-2017.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_STACKTRACE_SAFE_DUMP_TO_HPP
#define BOOST_STACKTRACE_SAFE_DUMP_TO_HPP

#include <boost/config.hpp>
#ifdef BOOST_HAS_PRAGMA_ONCE
#   pragma once
#endif

#include <boost/stacktrace/frame.hpp>


/// @file safe_dump_to.hpp This header contains low-level async-signal-safe functions for dumping call stacks.

namespace boost { namespace stacktrace {

/// @brief Stores current function call sequence into the memory.
///
/// @b Complexity: O(N) where N is call sequence length, O(1) if BOOST_STACKTRACE_USE_NOOP is defined.
///
/// @b Async-Handler-Safety: Safe.
///
/// @returns Stored call sequence depth.
///
/// @param memory Preallocated buffer to store current function call sequence into.
///
/// @param size Size of the preallocated buffer.
BOOST_FORCEINLINE std::size_t safe_dump_to(void* memory, std::size_t size) BOOST_NOEXCEPT {
    return boost::stacktrace::detail::this_thread_frames::collect(static_cast<void**>(memory), size / sizeof(void*));
}

/// @cond
namespace detail {
    template <class T>
    BOOST_FORCEINLINE std::size_t safe_dump_to_impl(T file) BOOST_NOEXCEPT {
        void* buffer[boost::stacktrace::detail::max_frames_dump + 1];
        const std::size_t frames_count = boost::stacktrace::detail::this_thread_frames::collect(buffer, boost::stacktrace::detail::max_frames_dump);
        buffer[frames_count] = 0;
        return boost::stacktrace::detail::dump(file, buffer, frames_count + 1);
    }
}
/// @endcond

/// @brief Opens a file and rewrites its content with current function call sequence.
///
/// @b Complexity: O(N) where N is call sequence length, O(1) if BOOST_STACKTRACE_USE_NOOP is defined.
///
/// @b Async-Handler-Safety: Safe.
///
/// @returns Stored call sequence depth.
///
/// @param file File to store current function call sequence.
BOOST_FORCEINLINE std::size_t safe_dump_to(const char* file) BOOST_NOEXCEPT {
    return boost::stacktrace::detail::safe_dump_to_impl(file);
}

#ifdef BOOST_STACKTRACE_DOXYGEN_INVOKED

/// @brief Writes into the provided file descriptor the current function call sequence.
///
/// @b Complexity: O(N) where N is call sequence length, O(1) if BOOST_STACKTRACE_USE_NOOP is defined.
///
/// @b Async-Handler-Safety: Safe.
///
/// @returns Stored call sequence depth.
///
/// @param file File to store current function call sequence.
BOOST_FORCEINLINE std::size_t safe_dump_to(platform_specific_descriptor fd) BOOST_NOEXCEPT;

#elif defined(BOOST_WINDOWS)

BOOST_FORCEINLINE std::size_t safe_dump_to(void* fd) BOOST_NOEXCEPT {
    return boost::stacktrace::detail::safe_dump_to_impl(fd);
}

#else

// POSIX
BOOST_FORCEINLINE std::size_t safe_dump_to(int fd) BOOST_NOEXCEPT {
    return boost::stacktrace::detail::safe_dump_to_impl(fd);
}

#endif


}} // namespace boost::stacktrace

#endif // BOOST_STACKTRACE_SAFE_DUMP_TO_HPP