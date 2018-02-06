#pragma once

#include "../Allocator/BasicAllocator.h"
#include <string>

namespace ee
{
	template <typename T>
	using BasicString = std::basic_string <T>;

	/**	Basic string stream that uses Banshee memory allocators. */
	template <typename T>
	using BasicStringStream = std::basic_stringstream <T>;

	/** Wide string used primarily for handling Unicode text (UTF-32 on Linux, UTF-16 on Windows, generally). */
	typedef EE_UTILITY_EXPORT BasicString<wchar_t> WString;

	/** Narrow string used for handling narrow encoded text (either locale specific ANSI or UTF-8). */
	typedef EE_UTILITY_EXPORT BasicString<char> String;

	/** Wide string used UTF-16 encoded strings. */
	typedef EE_UTILITY_EXPORT BasicString<char16_t> U16String;

	/** Wide string used UTF-32 encoded strings. */
	typedef EE_UTILITY_EXPORT BasicString<char32_t> U32String;

	/** Wide string stream used for primarily for constructing wide strings. */
	typedef EE_UTILITY_EXPORT BasicStringStream<wchar_t> WStringStream;

	/** Wide string stream used for primarily for constructing narrow strings. */
	typedef EE_UTILITY_EXPORT BasicStringStream<char> StringStream;

	/** Wide string stream used for primarily for constructing UTF-16 strings. */
	typedef EE_UTILITY_EXPORT BasicStringStream<char16_t> U16StringStream;

	/** Wide string stream used for primarily for constructing UTF-32 strings. */
	typedef EE_UTILITY_EXPORT BasicStringStream<char32_t> U32StringStream;
}