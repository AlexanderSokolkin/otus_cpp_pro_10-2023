#pragma once
#include <list>
#include <type_traits>
#include <stdexcept>
#include <cmath>
#include <cstddef>
#include <memory>
#include <cstring>



class Pool
{
/*
* 	Структура блока data
* 	static_cast<size_t>(ceil(count / 8.)) байт - статус памяти (занято или нет)
* 	(count * typeSize) байт - блок данных
*/
	struct Node {
		void* data = nullptr;
		size_t typeSize = 0;
		size_t count = 0;
		bool operator==(const Node& node) const {return data == node.data;}
	};

	std::list<Node> nodes;

public:
	void* allocate(size_t type_size, size_t count, size_t n);
	void deallocate(size_t type_size, void* ptr, size_t n);

	bool operator==(const Pool& pool) const noexcept;

private:
	void addNewNode(size_t type_size, size_t count);
};


void* Pool::allocate(size_t type_size, size_t count, size_t n)
{
	if (!n) {
		return nullptr;
	}

	for (auto& node : nodes) {
		if (node.typeSize != type_size) {
			continue;
		}
		std::byte* controlBlock = reinterpret_cast<std::byte*>(node.data);
		size_t currentCount = 0;
		for (size_t i = 0; i < node.count; ++i) {
			std::byte* ctrl = controlBlock + i / 8;
			std::byte enable = *ctrl & std::byte(1) << (7 - i % 8);
			if (enable != std::byte(0)) {
				currentCount = 0;
				continue;
			}
			++currentCount;
			if (currentCount == n) {
				for (size_t j = i + 1 - n; j <= i; ++j) {
					std::byte* ctrl2 = controlBlock + j / 8;
					*ctrl2 |= std::byte(1) << (7 - i % 8);
				}
				size_t controlBlockSize = static_cast<size_t>(std::ceil(node.count / 8.));
				return controlBlock + controlBlockSize + (i + 1 - n) * type_size;
			}
		}
	}

	size_t data_count = count;
	while (data_count < n) {
		data_count += count;
	}
	addNewNode(type_size, data_count);
	std::byte* controlBlock = reinterpret_cast<std::byte*>(nodes.back().data);
	for (size_t i = 0; i < n; ++i) {
		std::byte* ctrl = controlBlock + i / 8;
		*ctrl |= std::byte(1) << (7 - i % 8);
	}
	return controlBlock + static_cast<size_t>(std::ceil(data_count / 8.));
}

void Pool::deallocate(size_t type_size, void* ptr, size_t n)
{
	if (!n) {
		return;
	}

	for (auto node = nodes.begin(); node != nodes.end(); ++node) {
		if (node->typeSize != type_size || ptr < node->data) {
			continue;
		}
		size_t controlBlockSize = static_cast<size_t>(std::ceil(node->count / 8.));
		size_t dataBlockSize = node->count * type_size;
		std::byte* byte_ptr = reinterpret_cast<std::byte*>(ptr);
		std::byte* byte_data = reinterpret_cast<std::byte*>(node->data);
		if (static_cast<size_t>(byte_ptr - byte_data) > controlBlockSize + dataBlockSize) {
			continue;
		}

		std::byte* controlBlock = byte_data;
		std::byte* dataBlock = controlBlock + controlBlockSize;
		for (size_t shift = 0; shift < node->count; ++shift) {
			if (byte_ptr != dataBlock + shift * type_size) {
				continue;
			}
			for (size_t i = shift; i < shift + n; ++i) {
				std::byte* ctrl = controlBlock + i / 8;
				*ctrl &= ~(std::byte(1) << (7 - i % 8));
			}
			for (size_t i = 0; i < node->count; ++i) {
				std::byte* ctrl = controlBlock + i / 8;
				if ((*ctrl & std::byte(1) << (7 - i % 8)) != std::byte(0)) {
					return;
				}
			}
			::operator delete(node->data);
			nodes.erase(node);
			return;
		}
		return; // Возможно стоит кинуть исключение
	}
}

void Pool::addNewNode(size_t type_size, size_t count)
{
	size_t controlBlockSize = static_cast<size_t>(std::ceil(count / 8.));
	size_t dataSize = controlBlockSize + count * type_size;
	void* data = ::operator new(dataSize);
	if (!data) {
		throw std::bad_alloc();
	}
	std::memset(reinterpret_cast<std::byte*>(data), 0, controlBlockSize);
	Node node = {data, type_size, count};
	nodes.push_back(std::move(node));
}

bool Pool::operator==(const Pool& pool) const noexcept
{
	return nodes == pool.nodes;
}




template <typename Type, size_t count>
class pool_allocator
{
	std::shared_ptr<Pool> pool;

public:
	typedef Type value_type;

	template<typename OtherType>
	struct rebind {
		typedef pool_allocator<OtherType, count> other;
	};


	pool_allocator() : pool(new Pool) {}
	~pool_allocator() {};
	template <typename OtherType, size_t otherCount>
	pool_allocator(const pool_allocator<OtherType, otherCount>& other) : pool(other.getPool()) {}


	Type* allocate(size_t n);
	void deallocate(Type* p, size_t n);
	std::shared_ptr<Pool> getPool() const;
};


template <typename Type, size_t count>
Type* pool_allocator<Type, count>::allocate(size_t n)
{
	if (n == 0) {
		return nullptr;
	}

	return reinterpret_cast<Type*>(pool->allocate(sizeof(Type), count, n));
}

template <typename Type, size_t count>
void pool_allocator<Type, count>::deallocate(Type* p, size_t n)
{
	pool->deallocate(sizeof(Type), p, n);
}

template <typename Type, size_t count>
std::shared_ptr<Pool> pool_allocator<Type, count>::getPool() const
{
	return pool;
}

template <typename Type1, size_t count1,
		  typename Type2, size_t count2>
bool operator==(const pool_allocator<Type1, count1>& a1,
				const pool_allocator<Type2, count2>& a2) noexcept
{
	return a1.getPool() == a2.getPool();
}

template <typename Type1, size_t count1,
		  typename Type2, size_t count2>
bool operator!=(const pool_allocator<Type1, count1>& a1,
				const pool_allocator<Type2, count2>& a2) noexcept
{
	return !(a1 == a2);
}
