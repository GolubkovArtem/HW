#ifndef __TVECTOR_INCLUDED__
#define __TVECTOR_INCLUDED__

#include <iostream>
#include <limits>

class TVector
{
public:
	using value_type = int;
	using size_type = size_t;
	using iterator = value_type * ;
	using reference = value_type & ;
	using const_reference = const value_type & ;
private:
	value_type * Ptr;
	size_type Count;
	size_type InternalCapacity;
public:
	~TVector()
	{
		delete[] Ptr;
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

	TVector(const TVector & vector)
	{
		Count = vector.Count;
		InternalCapacity = vector.InternalCapacity;
		Ptr = new value_type[InternalCapacity];
		for (size_type i = 0; i < Count; ++i) 
			memcpy(Ptr, vector.Ptr, Count * sizeof(value_type));
	}


	bool Empty() const throw()
	{
		return Size() == 0;
	}

	size_type Size() const throw()
	{
		return Count;
	}

	size_type Capacity() const throw()
	{
		return InternalCapacity;
	}

	iterator Begin() const throw()
	{
		return Ptr;
	}

	iterator End() const throw()
	{
		return Ptr + Count;
	}


	void Reserve(size_type size)
	{
		InternalCapacity = size;
		iterator buf = Ptr;
		Ptr = new value_type[size];
		if (size < Count) Count = size;
		memcpy(Ptr, buf, Count * sizeof(value_type));
		if (buf != nullptr) delete[] buf;
	}

	TVector & operator = (const TVector & vector)
	{
		Count = vector.Count;
		InternalCapacity = vector.InternalCapacity;
		if (Ptr != nullptr) delete[] Ptr;
		Ptr = new value_type[InternalCapacity];
		memcpy(Ptr, vector.Ptr, Count * sizeof(value_type));
		return *this;
	}

	void PushBack (const value_type& value)
	{
		if (Count == InternalCapacity)
			Reserve(InternalCapacity + 1);
		Ptr[Count] = value;
		Count++;
	}

	reference At (size_type index)
	{
		if (index < Count)
			return Ptr[index];
		throw(std::exception("Error"));
	}

	value_type At (size_type index) const
	{
		if (index < Count)
			return Ptr[index];
		throw(std::exception("Error"));
	}

	reference operator [] (size_type index)
	{
		if (index < Count)
			return Ptr[index];
	}

	const_reference operator [] (size_type index) const
	{
		if (index < Count)
			return Ptr[index];
	}

	reference Front()
	{
		if (Count)
			return *this->Begin();
	}

	const_reference Front() const
	{
		if (Count)
			return *this->Begin();
	}

	reference Back()
	{
		if (Count)
			return *(this->End() - 1);
	}

	const_reference Back() const
	{
		if (Count)
			return *(this->End() - 1);
	}

	void Clear()
	{
		Count = 0;
	}

	void PopBack()
	{
		if (Count)
			--Count;
	}

	void Swap(TVector & other) throw()
	{
		TVector buf = *this;
		for (size_type i = 0; i < InternalCapacity && i < other.InternalCapacity; ++i)
			std::swap(Ptr[i], other.Ptr[i]);
		InternalCapacity >= other.Count ? Count = other.Count : Count = InternalCapacity;
		other. InternalCapacity >= Count ? other.Count = Count : other.Count = other.InternalCapacity;
	}

	void Resize(size_type count, value_type value = value_type())
	{
		if (count >= std::numeric_limits<size_type>::max())
			throw(std::exception("Error"));
		size_type buf(Count);
		count <= InternalCapacity ? Count = count : Count = InternalCapacity;
		if (buf <= Count)
			Insert((this->Begin() + buf), Count - buf, 0);
	}

	iterator Insert(iterator pos, const value_type & value)
	{
		if (pos < this->End())
		{
			*pos = value;
			if (pos == this->End()) ++Count;
			return pos;
		}
	}

	void Insert(iterator pos, size_type count, const value_type & value)
	{
		if (count >= std::numeric_limits<size_type>::max())
			throw(std::exception("Error"));
		if (pos < this->End())
		{
			iterator i(pos);
			for (; i < (pos + count - 1) && i < (this->Begin() + InternalCapacity); ++i) *i = value;
			Count = (i - this->Begin());
		}
	}

	iterator Erase(iterator pos)
	{
		if (pos >= this->End() || pos < this->Begin())
			return this->Begin();
		for (iterator i = pos; i + 1 < this->End(); ++i)
			*i = *(i + 1);
		--Count;
		return this->Begin();
	}

	iterator Erase(iterator first, iterator last)
	{
		if (first >= this->End() || first < this->Begin())
			return this->Begin();
		for (iterator i = first; (i + (last - first + 1)) < this->End(); ++i)
			*i = *(i + (last - first + 1));
		(last - this->Begin()) < Count ? Count -= (last - first + 1) : Count = (first - this->Begin());
	}
};

#endif // __TVECTOR_INCLUDED__
