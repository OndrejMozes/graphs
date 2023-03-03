#ifndef __ARRAY_H
#define __ARRAY_H

#include <utility>
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <iterator>
#include "Exceptions.h"


/// @file Array.h
/// @brief Contains the custom Array class used as internal storage for the graph nodes and edges
///  and its member function definitions

namespace my_array {

	/// @brief The default size of the blocks used internally for storage inside the array
	const int DEFAULT_BLOCK_SIZE = 10;

	/// @brief A dynamic array that never invalidates pointers
	/// @tparam element The element of the array
	template <typename element>
	class Array {
	public:
		/// @brief Constructs an array with the given block size
		/// @param block_size The size of the blocks used internally for storage
		Array(size_t block_size = DEFAULT_BLOCK_SIZE);

		/// @brief Add an item to the end of the array
		/// @param item The item to add
		void push_back(const element& item);

		/// @brief Add an item to the end of the array
		/// @param item The item to add
		void push_back(element&& item);

		/// @brief Remove the last element of the array
		/// @exception EmptyArrayException If tried to pop back on an empty array
		void pop_back();

		/// @brief Get the number of elements inside the array
		/// @return The count of elements of the array
		inline size_t size() const;

		/// @brief Print the elements of the array using operator<< to the specified stream
		/// @param os The output stream to print to
		void print(std::ostream& os = std::cout) const;

		/// @brief Get the element at a given index
		/// @param index The index of the element
		/// @return A reference to the element at the given index
		element& at(size_t index);

		/// @brief Get the element at a given index
		/// @param index The index of the element
		/// @return A reference to the element at the given index
		const element& at(size_t index) const;

		/// @brief Get the element at a given index
		/// @param index The index of the element
		/// @return A reference to the element at the given index
		element& operator[](size_t index);

		/// @brief Get the element at a given index
		/// @param index The index of the element
		/// @return A reference to the element at the given index
		const element& operator[](size_t index) const;

		/// @brief Copy constructor
		/// @param other The array to copy from
		Array(const Array<element>& other);

		/// @brief Move constructor
		/// @param other The array to move
		Array(Array<element>&& other) noexcept;

		/// @brief Copy assignment
		/// @param other The array to copy from
		/// @return A reference to the array copied to
		Array<element>& operator=(const Array<element>& other);

		/// @brief Move assignment
		/// @param other The array to move
		/// @return A reference to the array moved to
		Array<element>& operator=(Array<element>&& other) noexcept;

		class iterator;

		/// @brief Returns an iterator to the first element
		/// @return The iterator to the first element
		iterator begin();

		/// @brief Returns an iterator to the space after the last element
		/// @return The iterator to the space after the last element
		iterator end();

	private:
		/// @brief Get the amount of free spots for elements
		/// @return The size of the free space
		size_t free_space_count_();

		/// @brief Grow the internal storage by one block
		/// @exception UnavailableMemoryException If we don't have enough memory to add a block
		void add_block_();

		/// @brief Get the element at a given index
		/// @param index The index of the element
		/// @return A reference to the element at the given index
		/// @exception OutOfRangeException If tried to acces an out of range index
		inline const element& get_(size_t index) const;

		/// @brief The actual internal storage used for the elements
		///  A vector of pointers to blocks ensures that upon growth old pointers are still valid
		std::vector<std::unique_ptr<element[]>> data_;

		/// @brief The size of the blocks used inside the internal storage
		size_t block_size_;

		/// @brief The number of actual elements inside the array
		size_t element_count_;
	};

	/// @brief Iterator for the array
	/// @tparam element The element of the array
	template <typename element>
	class Array<element>::iterator {
	public:
		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = element;
		using pointer = element*;
		using reference = element&;

		/// @brief Constructs an array iterator at the given position
		/// @param array The array this is an iterator of
		/// @param position The position at which the iterator starts
		iterator(Array<element>* array, size_t position);

		/// @brief Equality operator
		/// @param other The other iterator being compared
		/// @return True if the iterators are equal, false if they are not
		bool operator==(const iterator& other) const;

		/// @brief Inequality operator
		/// @param other The other iterator being compared
		/// @return True if the iterators are not equal, true if they are equal
		bool operator!=(const iterator& other) const;

		/// @brief Post incrementation operator
		/// @return The iterator before incrementation
		iterator& operator++();

		/// @brief Pre incrementation operator
		/// @return The iterator after incrementation
		iterator operator++(int);

		/// @brief Dereferencing operator
		/// @return What the iterator points to
		reference operator*() const;

		/// @brief Member access operator
		/// @return The member
		pointer operator->() const;

		/// @brief Post decrementation operator
		/// @return The iterator before decrementation
		iterator& operator--();

		/// @brief Pre decrementation operator
		/// @return The iterator after decrementation
		iterator operator--(int);

		/// @brief Addition operator, returns an iterator moved forward by a specified amount
		/// @param movement The amount of forward movement
		/// @return The moved iterator
		iterator operator+(const difference_type& movement) const;

		/// @brief Subtraction operator, returns an iterator moved backwards by a specified amount
		/// @param movement The amount of backwards movement
		/// @return The moved iterator
		iterator operator-(const difference_type& movement) const;

	private:
		/// @brief A pointer to the array this is an iterator on
		Array<element>* array_;

		/// @brief The current position of the iterator
		size_t position_;
	};

	/// @brief Prints the given array to the given output stream and returns the same output stream
	/// @tparam element The element of the array
	/// @param os The output stream to print to
	/// @param array The array to print
	/// @return The same output stream
	template <typename element>
	std::ostream& operator<<(std::ostream& os, const Array<element>& array) {
		array.print(os);
		return os;
	}

	template <typename element>
	Array<element>::Array(size_t block_size) : block_size_(block_size), element_count_(0) {}

	template <typename element>
	size_t Array<element>::free_space_count_() {
		return data_.size() * block_size_ - element_count_;
	}

	template <typename element>
	void Array<element>::add_block_() {
		try {
			data_.push_back(std::make_unique<element[]>(block_size_));
		}
		catch (std::bad_alloc& e) {
			(void)e;
			throw(UnavailableMemoryException::array_unable_to_insert());
		}
	}

	template <typename element>
	void Array<element>::push_back(const element& item) {
		if (free_space_count_() == 0) add_block_();
		data_[element_count_ / block_size_][element_count_ % block_size_] = item;
		++element_count_;
	}

	template <typename element>
	void Array<element>::push_back(element&& item) {
		if (free_space_count_() == 0) add_block_();
		data_[element_count_ / block_size_][element_count_ % block_size_] = item;
		++element_count_;
	}

	template <typename element>
	void Array<element>::pop_back() {
		if (element_count_ == 0) throw(EmptyArrayException::array_popping_empty_array());
		--element_count_;
		data_[element_count_ / block_size_][element_count_ % block_size_].~element();
	}

	template<typename element>
	inline size_t Array<element>::size() const {
		return element_count_;
	}

	template<typename element>
	void Array<element>::print(std::ostream& os) const {
		os << "[";
		for (size_t i = 0; i < element_count_; i++) {
			os << data_[i / block_size_][i % block_size_];
			if (i != element_count_ - 1) os << ", ";
		}
		os << "]";
	}

	template <typename element>
	inline const element& Array<element>::get_(size_t index) const {
		if (index >= element_count_) 
			throw OutOfRangeException::array_accessing_invalid_index(index);
		return data_[index / block_size_][index % block_size_];
	}

	template <typename element>
	element& Array<element>::at(size_t index) {
		return const_cast<element&>(get_(index));
	}

	template <typename element>
	const element& Array<element>::at(size_t index) const {
		return get_(index);
	}

	template <typename element>
	element& Array<element>::operator[](size_t index) {
		return const_cast<element&>(get_(index));
	}

	template <typename element>
	const element& Array<element>::operator[](size_t index) const {
		return get_(index);
	}

	template <typename element>
	Array<element>::Array(const Array<element>& other) 
			: block_size_(other.block_size_), element_count_(other.element_count_) {
		for (size_t i = 0; i < other.data_.size(); i++) {
			add_block_();
		}
		for (size_t i = 0; i < element_count_; i++) {
			data_[i / block_size_][i % block_size_] = other.data_[i / block_size_][i % block_size_];
		}
	}

	template <typename element>
	Array<element>::Array(Array<element>&& other) noexcept : block_size_(0), element_count_(0) {
		std::swap(data_, other.data_);
		std::swap(element_count_, other.element_count_);
		std::swap(block_size_, other.block_size_);
	}

	template <typename element>
	Array<element>& Array<element>::operator=(const Array<element>& other) {
		for (size_t i = 0; i < element_count_; i++) {
			data_[i / block_size_][i % block_size_].~element();
		}
		element_count_ = other.element_count_;
		if (block_size_ != other.block_size_) {
			block_size_ = other.block_size_;
			data_ = std::vector<std::unique_ptr<element[]>>();
		}
		while (data_.size() * block_size_ < other.element_count_) {
			add_block_();
		}
		for (size_t i = 0; i < other.element_count_; i++) {
			data_[i / block_size_][i % block_size_] = other.data_[i / block_size_][i % block_size_];
		}
		return *this;
	}

	template <typename element>
	Array<element>& Array<element>::operator=(Array<element>&& other) noexcept {
		if (this != &other) {
			std::swap(data_, other.data_);
			std::swap(element_count_, other.element_count_);
			std::swap(block_size_, other.block_size_);
		}

		return *this;
	}

	template<typename element>
	Array<element>::iterator::iterator(Array<element>* array, size_t position) 
		: array_(array), position_(position) {}

	template<typename element>
	bool Array<element>::iterator::operator==(const iterator& other) const {
		return position_ == other.position_;
	}

	template<typename element>
	bool Array<element>::iterator::operator!=(const iterator& other) const {
		return position_ != other.position_;
	}

	template<typename element>
	typename Array<element>::iterator& Array<element>::iterator::operator++() {
		position_++;
		return *this;
	}

	template<typename element>
	typename Array<element>::iterator Array<element>::iterator::operator++(int) {
		auto pre = *this;
		position_++;
		return pre;
	}

	template<typename element>
	typename Array<element>::iterator::reference Array<element>::iterator::operator*() const {
		return (*array_)[position_];
	}

	template<typename element>
	typename Array<element>::iterator::pointer Array<element>::iterator::operator->() const {
		return &array_->at(position_);
	}

	template<typename element>
	typename Array<element>::iterator& Array<element>::iterator:: operator--() {
		position_--;
		return *this;
	}

	template<typename element>
	typename Array<element>::iterator Array<element>::iterator::operator--(int) {
		auto pre = *this;
		position_--;
		return pre;
	}

	template<typename element>
	typename Array<element>::iterator Array<element>::iterator::operator+
			(const difference_type& movement) const {
		auto tmp = *this;
		tmp.position_ = tmp.position_ + movement;
		return tmp;
	}

	template<typename element>
	typename Array<element>::iterator Array<element>::iterator::operator-
			(const difference_type& movement) const {
		auto tmp = *this;
		tmp.position_ = tmp.position_ - movement;
		return tmp;
	}

	template<typename element>
	typename Array<element>::iterator Array<element>::begin(){
		return Array<element>::iterator(this, 0);
	}

	template<typename element>
	typename Array<element>::iterator Array<element>::end(){
		return Array<element>::iterator(this, element_count_);
	}
};





#endif