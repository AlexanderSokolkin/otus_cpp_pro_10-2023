/**
\file
\brief Заголовочный файл со SFINAE перегрузками функции print_ip для различных типов

Данный файл содержит перегрузки функции print_ip для таких типов,
как std::string, целочисленные типы, std::tuple (при условии, что все члены одного типа),
А так же контейнеры std::list и std::vector
*/

#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <type_traits>
#include <tuple>
#include <utility>


namespace impl {

template <size_t lastIndex, typename... Args>
struct is_same_tuple_types {
	static constexpr bool value =	std::is_same_v<
										std::tuple_element_t<lastIndex - 1, std::tuple<Args...>>,
										std::tuple_element_t<lastIndex, std::tuple<Args...>>
									> && is_same_tuple_types<lastIndex - 1, Args...>::value;
};

template <typename... Args>
struct is_same_tuple_types<1, Args...> {
	static constexpr bool value =	std::is_same_v<
										std::tuple_element_t<0, std::tuple<Args...>>,
										std::tuple_element_t<1, std::tuple<Args...>>
									>;
};

template <typename... Args>
struct is_same_tuple_types<0, Args...> {
	static constexpr bool value = true;
};

template <size_t lastIndex, typename... Args>
constexpr bool is_same_tuple_types_v = is_same_tuple_types<lastIndex, Args...>::value;


template <typename Tuple, std::size_t... Is>
void print_tuple(const Tuple& tp, std::index_sequence<Is...>) {
	((std::cout << std::get<Is>(tp) << (Is + 1 == sizeof...(Is) ? "\n" : ".")), ...);
}

}



template <typename... Args>
struct is_same_tuple_types {
	static constexpr bool value = impl::is_same_tuple_types_v<
											std::tuple_size_v<std::tuple<Args...>> - 1,
															  Args...>;
};

template <typename... Args>
constexpr bool is_same_tuple_types_v = is_same_tuple_types<Args...>::value;



/**
Выводит в стандартный поток вывода побайтно,
начиная со старшего байта, число, отделяя каждый байт точкой.

\param value Целое число
\tparam Integral Целочисленный тип
\tparam Enabled Проверка, что Integral является целочисленным типом
*/
template <
	typename Integral,
	typename Enabled = std::enable_if_t<
		std::is_integral_v<std::remove_reference_t<Integral>>
	>
>
void print_ip(Integral value)
{
	using UIntegral = std::make_unsigned_t<Integral>;
	UIntegral uValue = *reinterpret_cast<UIntegral*>(&value);

	for (size_t i = sizeof(Integral); i > 0; --i) {
		size_t shift = (i - 1) * 8;
		std::cout << (uValue >> shift) << (i - 1 ? "." : "\n");
		uValue &= ~(UIntegral(255) << shift);
	}
}

/**
Выводит в стандартный поток вывода все члены контейнера
(либо std::list, либо std::vector), отделяя элементы точкой.

\param container Контейнер
\tparam Container Тип контейнера
\tparam Type Тип элементов контейнера
\tparam Alloc Тип аллокатора контейнера
\tparam Enabled Проверка, что Container является std::vector или std::list
*/
template <
	template <typename, typename> typename Container,
	typename Type,
	typename Alloc,
	typename Enabled = std::enable_if_t<
		std::is_same_v<Container<Type, Alloc>, std::vector<Type, Alloc>> ||
		std::is_same_v<Container<Type, Alloc>, std::list<Type, Alloc>>>
	>
void print_ip(const Container<Type, Alloc>& container)
{
	for (auto it = container.begin(); it != container.end(); ++it) {
		std::cout << *it << (std::next(it) == container.end() ? "\n" : ".");
	}
}

/**
Выводит в стандартный поток вывода все элементы кортежа
(при условии, что все типы одинаковые), отделяя их точкой.

\param tuple Кортеж
\tparam Args Типы элементов кортежа
\tparam Enabled Проверка, что все типы кортежа одинаковые
*/
template <
	typename... Args,
	typename Enabled = std::enable_if_t<
			is_same_tuple_types_v<Args...>
		>
	>
void print_ip(const std::tuple<Args...>& tuple)
{
	impl::print_tuple(tuple, std::make_index_sequence<sizeof...(Args)>{});
}

/**
Выводит в стандартный поток вывода строку.

\param str Строка
\tparam Type Явно указанный тип строки
*/
template <
	typename Type = std::string
>
void print_ip(const std::string& str)
{
	std::cout << str << "\n";
}
