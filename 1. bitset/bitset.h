#pragma once
#include <vector>
#include <string.h>


inline constexpr unsigned char operator "" _Uchar(unsigned long long arg) noexcept
{
	return static_cast<unsigned char>(arg);
}

//TODO:
//1. add error handling doofus
//2. research move semantics and shite and make the move logic here good
//3. add usage examples
class bitset {
private:
	std::vector<unsigned char> v;
	static const char _m = sizeof(unsigned char) * 8;	//number of bits in char
	static const size_t MINSIZEINCHARS = 8;

public:
	size_t size() const {	//size in bits
		return v.size() << 3;
	}
	bool operator[](size_t  k) const {
		if (k >= this->size())
			return false;
		return (this->v[k / _m] & (1_Uchar << (k % _m))) >> (k % _m);
	}
	bool test(size_t k) const {	
		return (*this)[k];
	}
	void set(size_t k, bool b) {
		if (k >= this->size()) {
			if (k < this->size() * 2)
				this->v.resize(this->v.size() * 2, 0);
			else
				this->v.resize(k / _m + 1, 0);	//!allocates 1 extra byte if k / _m == 0

			(this->v[k / _m]) | (b << (k % _m));	//do I need this->v[k / _m] = ... here ? I mean it seems to work fine
			return;
		}

		char bitcorrected = b << (k % _m);
		this->v[k / _m] = (this->v[k / _m] & bitcorrected) | bitcorrected;
	}
	bool empty() const {
		return this->v.empty();
	}
	void clear() {
		this->v.clear();
	}

	bitset() {
		this->v.resize(bitset::MINSIZEINCHARS, 0);
	}
	explicit bitset(size_t initial_size) {
		if (initial_size > this->v.max_size() / _m)
			throw std::bad_array_new_length();

		this->v.resize(initial_size / 8 + ((initial_size % 8) == 0 ? 0 : 1));
	}
	bitset(bitset& other) {
		this->v = other.v;
	}
	bitset(bitset&& other) noexcept {
		this->v = std::move(other.v);
	}

	bitset& operator=(const bitset& other) {
		this->v = other.v;
	}
	bitset& operator=(const bitset&& other) noexcept {	//check how exactly this works later because I dont know
		//TODO
	}

	//not sure about the logic here
	//!!!index out of bounds!!!
	bitset union_with(const bitset& other) const {

		bitset result(std::max(this->size(), other.size()));
		for (int i = 0; i < result.size(); i++) {
			result.set(i, (*this)[i] || other[i]);
		}
		return result;
	}
	bitset intersection(const bitset& other) const {
		bitset result(std::min(this->size(), other.size()));
		for (int i = 0; i < result.v.size(); i++) {
			result.v[i] = this->v[i] & other.v[i];
		}
		return result;
	}
	bool is_subset(const bitset& other) const {

		for (int i = 0; i < std::min(this->v.size(), other.v.size()); i++) {
			if (!(this->v[i] ^ other.v[i]))
				return false;
		}
		return true;
	}
};