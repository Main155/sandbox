//-@Main155
#pragma once

//Suitable for APP development
//Compile-time checked container utility

#include <type_traits>
#include <utility>

namespace lib
{
	//=========================================
	//Check if there are value type.
	template <typename T , typename = void>
	struct has_value_type : std::false_type {};
	template <typename T>
	struct has_value_type<T,std::void_t<typename T::value_type>> : std::true_type {};
	//----------------------------------
	//Check if it is an iterator.
	template <typename T , typename = void>
	struct has_iterator : std::false_type {};
	template <typename T>
	struct has_iterator<T,std::void_t<typename T::iterator>> : std::true_type {};
	//----------------------------------
	//Check if it is an begin()
	template <typename T , typename = void>
	struct has_begin : std::false_type {};
	template <typename T>
	struct has_begin<T, std::void_t<decltype(std::declval<T&>().begin())>> : std::true_type {};
	//----------------------------------
	//Check if it is an end()
	template <typename T , typename = void>
	struct has_end : std::false_type {};
	template <typename T>
	struct has_end<T,std::void_t<decltype(std::declval<T&>().end())>> : std::true_type {};
	//----------------------------------
	//Check if it is an size()
	template <typename T , typename = void>
	struct has_size : std::false_type {};
	template <typename T>
	struct has_size<T, std::void_t<decltype(std::declval<T&>().size())>> : std::true_type {};
	//-----------------------------------
	//Check if it is an empty()
	template <typename T, typename = void>
	struct has_empty : std::false_type {};
	template <typename T>
	struct has_empty<T, std::void_t<decltype(std::declval<T&>().empty())>> : std::true_type {};
	//=========================================
	
	//Determine whether it is a container.
	template <typename T>
	struct is_container : std::integral_constant<bool,
		has_value_type<T>::value    &&
		  has_iterator<T>::value    &&
		     has_begin<T>::value    &&
		       has_end<T>::value    &&
		      has_size<T>::value>   {};

	template <typename T>
	constexpr bool is_container_v = is_container<T>::value;
	//----------------------------------
	//assert
	template <typename T>
	constexpr void assert_is_container(T&&)
	{
		static_assert(
			is_container_v<std::decay_t<T>>,
			"error : T must be a container type(requires value_type, begin(), end(), size()). "
			);
	}
	//----------------------------------
	//Check if it is empty.
	template <typename T>
	constexpr void assert_is_container_strict(T&&) {
		static_assert(
			is_container_v<std::decay_t<T>> &&
			has_empty<std::decay_t<T>>::value,
			"error : T must be a container type with empty() method."
			);
	}
}