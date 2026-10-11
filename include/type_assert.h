//-@Main155 
#pragma once

//Embedded available header file.
//Compile-time type checking.

#include <type_traits>

namespace lib
{
	//Compile-time check whether data is an integer.
	template <typename T>
	constexpr void assert_is_integer(T&&)
	{
		static_assert( 
			std::is_integral_v<std::decay_t<T>>,
			"error : T must be an integral type. ");   
	}
	//------------------------------------------
	//Compile-time check for whether it is a floating-point type.
	template <typename T>
	constexpr void assert_is_floating_point(T&&)
	{
		static_assert( 
			std::is_floating_point_v<std::decay_t<T>>,
			"error : T must be a floating point type. ");
	}
	//------------------------------------------
	//Compile-time check for whether it is a character.
	template<typename T>
	constexpr void assert_is_character(T&&)
	{
		static_assert(
			std::is_same_v<std::decay_t<T>, char    > ||
			std::is_same_v<std::decay_t<T>, wchar_t > ||
			std::is_same_v<std::decay_t<T>, char8_t > ||
			std::is_same_v<std::decay_t<T>, char16_t> ||
			std::is_same_v<std::decay_t<T>, char32_t>,
			"error : T must be a character type. ");
	}
	//------------------------------------------
    // Compile-time check whether T is a numeric type (integer or floating-point).
	template <typename T>
	constexpr void assert_is_numeric(T&&) {
		static_assert(
			std::is_integral_v<std::decay_t<T>> ||
			std::is_floating_point_v<std::decay_t<T>>,
			"error : T must be a numeric type (integer or floating-point). ");
	}
	//------------------------------------------
    // Compile-time check whether T is an arithmetic type (numeric + bool).
	template <typename T>
	constexpr void assert_is_arithmetic(T&&) {
		static_assert(
			std::is_arithmetic_v<std::decay_t<T>>,
			"error : T must be an arithmetic type. ");
	}
	//------------------------------------------
	//Compile-time check if a type is bool
	template <typename T>
	constexpr void assert_is_bool(T&&)
	{
		static_assert(
			std::is_same_v<std::decay_t<T>, bool>,
			"error : T must be a bool type. "
			);
	}
	//------------------------------------------
	//Compile-time check whether T is const.
	template <typename T>
	constexpr void assert_is_const(T&&) {
		static_assert(
			std::is_const_v    <std::remove_reference_t<T>> &&
			!std::is_volatile_v<std::remove_reference_t<T>>,
			"error : T must be const. ");
	}
	//------------------------------------------
	// Compile-time check for whether it is volatile.
	template <typename T>
	constexpr void assert_is_volatile(T&&)
	{
		static_assert(
		std::is_volatile_v  <std::remove_reference_t<T>>,
		"error : T must be volatile. "
		);
	}
	//------------------------------------------
	//Compile-time check for whether it is const or volatile.
	template <typename T>
	constexpr void assert_is_const_or_volatile(T&&)
	{
		static_assert(
			std::is_const_v    <std::remove_reference_t<T>> ||
			std::is_volatile_v<std::remove_reference_t<T>>,
			"error : T must be const or volatile.  ");
	}
	//------------------------------------------
	//Compile-time check to determine if it is a pure integer (excluding bool and character types).
	template <typename T>
	constexpr void assert_is_integer_excluding_character(T&&)
	{
		static_assert(
		 std::is_integral_v<std::decay_t<T>>           &&
			!std::is_same_v<std::decay_t<T>, char>     &&
			!std::is_same_v<std::decay_t<T>, wchar_t>  &&
			!std::is_same_v<std::decay_t<T>, char8_t>  &&
			!std::is_same_v<std::decay_t<T>, char16_t> &&
			!std::is_same_v<std::decay_t<T>, char32_t> &&
			!std::is_same_v<std::decay_t<T>, bool>,
			"error : T must be an integral type (excluding character and bool). "
			);
	}//------------------------------------------
}