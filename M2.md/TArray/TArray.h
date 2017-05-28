#include <iostream>
#include <limits>



template <class T, std::size_t N> 
class TArray 
{

	using value_type = T;
	using size_type = size_t;
	using reference = value_type & ;
	using const_reference = const value_type & ;
	using iterator = value_type * ;
	using const_iterator = const value_type * ;


	value_type Ptr[N];

public:

	~TArray() = default;

	TArray() = default;


	TArray(std::initializer_list<T> list) {
		int i = 0;
		for (auto & val : list) {
			Ptr[i] = val;
			++i;
		}
	}




	reference at(size_type index) {
		if (index >= N)
			throw std::exception("Invalide Index");
		return Ptr[index];
	}

	const_reference at(size_type index) const {
		if (index >= N)
			throw std::exception("Invalide Index");
		return Ptr[index];
	}

	reference operator[] (size_type index) {
		return Ptr[index];
	}

	const_reference operator[] (size_type index) const {
		return Ptr[index];
	}

	reference front() {
		return Ptr[0];
	}

	const_reference front() const {
		return Ptr[0];
	}

	reference back() {
		return Ptr[N - 1];
	}

	const_reference back() const {
		return Ptr[N - 1];
	}

	iterator data() throw() {
		return Ptr;
	}

	const iterator data() const throw() {
		return Ptr;
	}



	iterator begin() throw() {
		return Ptr;
	}

	const_iterator cbegin() const {
		return Ptr;
	}

	iterator end() throw() {
		return Ptr + N;
	}

	const_iterator cend() const {
		return Ptr + n;
	}



	bool empty() const throw() {
		return N == 0;
	}

	size_type size() const throw() {
		return N;
	}

	size_type max_size() const throw() {
		return N;
	}



	void fill(const_reference value) {
		for (size_type i = 0; i < N; ++i)
			Ptr[i] = value;
	}

	void swap(TArray<T, N> & x) throw() {
		std::swap(Ptr, x.Ptr);
	}

};
