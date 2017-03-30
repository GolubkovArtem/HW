#ifndef __TVECTOR_INCLUDED__
#define __TVECTOR_INCLUDED__

#include <iostream>
#include <limits>


template<class T>
class TVector
{
public:
	using value_type = T;
	using size_type = size_t;
	using iterator = value_type *;
	using reference = value_type &;
	using const_reference = const value_type &;
private:
	iterator Ptr;
	size_type Count;
	size_type InternalCapacity;
public:
	~TVector() {
		if (Ptr != nullptr) delete[] Ptr;
	}


	TVector()
		: Ptr(nullptr)
		, Count(0)
		, InternalCapacity(0)
	{ }

	TVector(size_type capacity)
		: Count(0)
		, InternalCapacity(capacity)
	{
		Ptr = new value_type[InternalCapacity];
	}

	TVector(const TVector & vector) {
		Count = vector.Count;
		InternalCapacity = vector.InternalCapacity;
		Ptr = new value_type[InternalCapacity];
		for (size_type i = 0; i < Count; ++i)
			Ptr[i] = vector.Ptr[i];
	}

	TVector(const std::initializer_list<value_type> & list) {
		InternalCapacity = list.size();
		Count = list.size();
		Ptr = new value_type[Count];
		std::vector<value_type> buf(list);
		for (size_type i = 0; i < Count; ++i)
			Ptr[i] = buf[i];
	}


	bool Empty() const throw() {
		return this->Size() == 0;
	}

	size_type Size() const throw() {
		return Count;
	}

	size_type Capacity() const throw() {
		return InternalCapacity;
	}

	iterator Begin() const throw() {
		return Ptr;
	}

	iterator End() const throw() {
		return Ptr + Count;
	}


	void Reserve(size_type size) {
		InternalCapacity = size;
		iterator buf = Ptr;
		Ptr = new value_type[size];
		if (size < Count) Count = size;
		for (size_type i = 0; i < Count; ++i)
			Ptr[i] = buf[i];
		if (buf != nullptr) delete[] buf;
	}

	TVector & operator = (const TVector & vector) {
		Count = vector.Count;
		InternalCapacity = vector.InternalCapacity;
		if (Ptr != nullptr) delete[] Ptr;
		Ptr = new value_type[InternalCapacity];
		for (size_type i = 0; i < Count; ++i)
			Ptr[i] = vector.Ptr[i];
		return *this;
	}

	void PushBack(const_reference value) {
		if (Count == InternalCapacity)
			this->Reserve(InternalCapacity + 1);
		Ptr[this->Size()] = value;
		++Count;
	}

	reference At(size_type index) {
		if (index < Count)
			return Ptr[index];
		throw(std::exception("Error"));
	}

	value_type At(size_type index) const {
		if (index < Count)
			return Ptr[index];
		throw(std::exception("Error"));
	}

	reference operator [] (size_type index) {
		if (index < Count)
			return Ptr[index];
	}

	const_reference operator [] (size_type index) const {
		if (index < Count)
			return Ptr[index];
	}

	reference Front() {
		if (Count)
			return Ptr[0];
	}

	const_reference Front() const {
		if (Count)
			return Ptr[0];
	}

	reference Back() {
		if (Count)
			return *(this->End() - 1);
	}

	const_reference Back() const {
		if (Count)
			return *(this->End() - 1);
	}

	void Clear() {
		InternalCapacity = 0;
		Count = 0;
		if (Ptr != nullptr) delete[] Ptr;
	}

	void PopBack() {
		if (Count) --Count;
	}

	void Swap(TVector & other) throw() {
		TVector buf = *this;
		for (size_type i = 0; i < InternalCapacity && i < other.InternalCapacity; ++i)
			std::swap(Ptr[i], other.Ptr[i]);
		InternalCapacity >= other.Count ? Count = other.Count : Count = InternalCapacity;
		other.InternalCapacity >= Count ? other.Count = Count : other.Count = other.InternalCapacity;
	}

	void Resize(size_type count, value_type value = value_type()) {
		if (count >= std::numeric_limits<size_type>::max())
			throw(std::exception("limits_error"));
		if (count <= Count)
		{
			Count = count;
			return;
		}
		if (count > InternalCapacity)
		{
			Reserve(count);
		}
		Insert(this->Begin() + Count, count - Count, value);
	}

	iterator Insert(iterator pos, const_reference value) {
		if (pos == this->End() && InternalCapacity != Count)
			++Count;
		if ((pos - this->Begin()) < InternalCapacity && (pos - this->Begin()) >= 0)
		{
			*pos = value;
			return pos;
		}
		throw("range_error");
	}

	void Insert(iterator pos, size_type count, const_reference value) {
		if (count >= std::numeric_limits<size_type>::max())
			throw(std::exception("limits_error"));
		iterator t = this->End();
		if (pos <= this->End() && pos >= this->Begin())
		{
			iterator i(pos);
			for (; i < (pos + count - 1) && i != (this->Begin() + InternalCapacity); ++i) *i = value;
			Count = (i - this->Begin());
			return;
		}
		throw("range_error");
	}

	iterator Erase(iterator pos) {
		if (pos >= this->End() || pos < this->Begin())
			throw("range_error");
		for (iterator i = pos; i + 1 != this->End(); ++i)
			*i = *(i + 1);
		--Count;
		if (pos == this->End())
			return pos;
		else
			return pos + 1;
	}

	iterator Erase(iterator first, iterator last) {
		if (first >= this->End() || first < this->Begin() || last < first)
			throw("range_error");
		for (iterator i = first; (i + (last - first + 1)) != this->End(); ++i)
			*i = *(i + (last - first + 1));
		(last - this->Begin()) < Count ? Count -= (last - first + 1) : Count = (first - this->Begin());
		if (last >= this->End())
			return this->End();
		else
			return last + 1;
	}
};

#endif // __TVECTOR_INCLUDED__
