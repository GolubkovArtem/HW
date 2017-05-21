#ifndef __BOOLEAN_FUNCTION_INCLUDED__
#define __BOOLEAN_FUNCTION_INCLUDED__

#include <string>
#include <vector>
#include <algorithm>

class boolean_function
{

public:

	using value_type = bool;
	using size_type = size_t;
	using reference = std::vector<value_type>::reference;
	using const_reference = std::vector<value_type>::const_reference;
	using iterator = typename std::vector<value_type>::iterator;
	using const_iterator = typename std::vector<value_type>::const_iterator;

private:

	std::vector<value_type> Series;

public:


	static boolean_function var(size_t n, size_t dimension) {

		if (n > dimension)
			throw std::exception("invalid number of variable");

		std::string buf = "0";

		if (dimension == 0)
			return buf;

		for (size_type i = pow(2, n) - 1; i > 0; --i)
			buf += "0";
		for (size_type i = pow(2, n); i > 0; --i)
			buf += "1";
		for (size_type i = dimension - n - 1; i > 0; --i)
			buf += buf;

		boolean_function result(buf);

		return buf;

	}

	static boolean_function zero(size_t dimension) {
		boolean_function result;
		result.Series.insert(result.Series.begin(), pow(2, dimension), 0);
		return result;
	}

	static boolean_function one(size_t dimension) {
		boolean_function result;
		result.Series.insert(result.Series.begin(), pow(2, dimension), 1);
		return result;
	}

	static boolean_function from_anf(std::vector<value_type> v) {

		value_type ** buf = new value_type *[v.size()];
		for (size_type i = 0; i < v.size(); ++i)
			buf[i] = new value_type[v.size()];

		std::vector<value_type> result;

		for (size_type i = 0; i < v.size(); ++i)
			buf[i][0] = v[i];

		result.push_back(v[0]);

		for (size_type i = 1; i < v.size(); ++i) {
			for (size_type j = 0; j < v.size() - i; ++j)
				buf[j][i] = (buf[j][i - 1] + buf[j + 1][i - 1]) % 2;
			result.push_back(buf[0][i]);
		}

		for (size_type i = 0; i < v.size(); ++i)
			delete[] buf[i];
		delete[] buf;

		return result;
	}


	boolean_function() = default;

	boolean_function(size_t n) {
		Series.insert(Series.begin(), pow(2, n), 0);
	}

	boolean_function(unsigned long long value, size_type n) {		

		for (size_type i = 0; i < pow(2, n); ++i)
			Series.push_back((value >> i) & 1);

		if (pow(2, n) > 8 * sizeof(unsigned long long))
			Series.insert(Series.end(), pow(2, n) - 8 * sizeof(unsigned long long), 0);

	}

	boolean_function(const std::string & table) {

		for (size_type i = 0; i < table.size(); ++i)
			if (!(table[i] == '1' || table[i] == '0'))
				throw std::exception("invalid input string");

		right_dimension(table.size());

		for (size_type i = 0; i < table.size(); ++i)
			Series.push_back(table[i] - '0');			

	}

	boolean_function(const std::vector<value_type> & table) {
		right_dimension(table.size());
		Series = table;
	}

	boolean_function(const std::initializer_list<bool> vars) {
		right_dimension(vars.size());
		for (auto & i : vars)
			Series.push_back(i);
	}

	boolean_function(const boolean_function & table) {
		Series = table.Series;
	}

	boolean_function & operator = (const boolean_function & rhs) {
		Series = rhs.Series;
		return *this;
	}


	boolean_function & operator += (const boolean_function & rhs) {

		if (size() != rhs.size())
			throw std::exception("invalid size");

		for (size_type i = 0; i < size(); ++i)
			Series[i] = (Series[i] + rhs.Series[i]) % 2;

		return *this;

	}

	boolean_function & operator *= (const boolean_function& rhs) {

		if (size() != rhs.size())
			throw std::exception("invalid size");

		for (size_type i = 0; i < size(); ++i)
				Series[i] = Series[i] * rhs.Series[i];

		return *this;

	}

	boolean_function& operator |= (const boolean_function& rhs) {

		if (size() != rhs.size())
			throw std::exception("invalid size");

		for (size_type i = 0; i < size(); ++i)
			Series[i] = Series[i] + rhs.Series[i];

		return *this;
	}

	boolean_function operator ~ () {
		for (size_type i = 0; i < size(); ++i)
			Series[i] = !Series[i];
		return *this;
	}


	bool operator == (const boolean_function & rhs) const {

		std::vector<value_type> min_anf(anf()), max_anf(rhs.anf());
		if (size() > rhs.size())
			std::swap(min_anf, max_anf);

		size_type min(size()), max(rhs.size());
		if (size() > rhs.size())
			std::swap(min, max);

		for (size_type i = min; i < max; ++i)
			if (max_anf[i] == 1)
				return 0;

		for (size_type i = 0; i < min; ++i)
			if (max_anf[i] != min_anf[i])
				return 0;

		return 1;

	}

	bool operator >= (const boolean_function & rhs) const {

		if (size() != rhs.size())
			throw std::exception("invalid size");

		bool r(0), l(0);
		for (size_type i = 0; i < size() && r * l == 0; ++i) {
			r += (Series[i] > rhs.Series[i]);
			l += (Series[i] < rhs.Series[i]);
		}
		if (r * l != 0)
			throw std::exception("logig error");

		return !l;

	}

	reference operator[] (size_type ind) {
		return Series[ind];
	}

	const_reference operator[](size_type ind) const {
		return Series[ind];
	}

	reference at(size_type ind) {
		if (ind < size())
			return Series[ind];
		throw std::exception("out of range");
	}

	const_reference at(size_type ind) const {
		if (ind < size())
			return Series[ind];
		throw std::exception("out of range");
	}

	iterator begin() {
		return Series.begin();
	}

	iterator end() {
		return Series.end();
	}

	const_iterator cbegin() const
	{
		return Series.cbegin();
	}

	const_iterator cend() const {
		return Series.cend();
	}


	size_type size() const throw() {
		return Series.size();
	}

	size_type dimension() const throw() {
		size_type result(0);
		for (size_type i = 1; i < size(); i *= 2, ++result);
		return result;
	}



	bool operator()(const std::vector<bool> & vars) const {

		if (vars.size() != dimension())
			throw std::exception("invalid size");

		size_type buf(0), j(dimension() - 1);

		for (size_type i = 0; i < dimension(); ++i)
			if (vars[i])
				buf += pow(2, i);

		return Series[buf];

	}

	bool operator()(const std::initializer_list<bool> vars) const {

		if (vars.size() != dimension())
			throw std::exception("invalid size");

		size_type buf(0), j(dimension() - 1);

		for (auto & i : vars)
			if (i)
				buf += pow(2, j--);

		return Series[buf];
	}


	boolean_function operator()(const std::vector<boolean_function> & fs) const {

		if (dimension() != fs.size())
			throw std::exception("invalid dimension");

		size_type max_dimension(0);
		
		for (auto & i : fs)
			if (max_dimension < i.dimension())
				max_dimension = i.dimension();

		std::vector<boolean_function> functions;
		for (auto & i : fs)
			functions.push_back(i);

		boolean_function main_func(*this);
		while (main_func.dimension() < max_dimension)
			main_func.insert_irrelevant_variable(main_func.dimension() + 1);


		for (size_type i = 0; i < functions.size(); ++i)
			while (functions[i].dimension() < max_dimension)
				functions[i].insert_irrelevant_variable(functions[i].dimension() + 1);


		std::vector<bool> buf_result;

		for (size_type i = 0; i < pow(2, max_dimension); ++i) {
			size_type buf(0);
			for (size_type j = 0; j < dimension(); ++j) {
				if (functions[j][i])
					buf += pow(2, dimension() - j - 1);
			}
			buf_result.push_back(main_func.Series[buf]);
		}

		boolean_function result(buf_result);
		return result;


	}

	boolean_function operator()(const std::initializer_list<boolean_function> vars) const {

		std::vector<boolean_function> buf;

		for (auto & i : vars)
			buf.push_back(i);

		return (*this)(buf);

	}


	bool is_monotone() const {
		for (size_type i = 0; i < size(); ++i) { // mogno lu4we?
			if (Series[i]) {

				std::vector<size_type> buf;
				for (size_type j = 0; j < dimension(); ++j) {
					if ((i % static_cast<size_type>(pow(2, j + 1))) >= pow(2, j + 1) / 2)
						buf.push_back(j);
				}

				for (size_type j = i + 1; j < size(); ++j) {

					if (!Series[j]) {

						size_type counter(0);

						for (auto & i1 : buf)
							if ((j % static_cast<size_type>(pow(2, i1 + 1))) >= pow(2, i1 + 1) / 2)
								++counter;

						if (counter == buf.size())
							return 0;

					}
				}
			}
		}
		return 1;
	}

	bool is_symmetric() const {
		std::vector<value_type> num(size(), 0);
		for (size_type i = 0; i < size(); ++i)
			if (Series[i] && !num[i]) {
				num[i] = true;
				size_type i_weight(n_weight(i));
				for (size_type j = i + 1; j < size(); ++j) {
					size_type j_weight(n_weight(j));
					if (j_weight == i_weight && Series[i] == Series[j])
						num[j] = true;
					else
						return 0;
				}
			}
		return 1;
	}

	bool is_linear() const {

		std::vector<value_type> buf(anf());

		for (size_type i = 0; i < size(); ++i)
			if (buf[i] && n_weight(i) > 1)
				return 0;

		return 1;
	}

	bool is_T1() const {
		return Series[size() - 1];
	}

	bool is_T0() const {
		return !Series[0];
	}

	bool is_balanced() const {
		return !(weight() % 2);
	}

	size_t weight() const {
		size_type result(0);
		for (size_type i = 0; i < size(); ++i)
			result += Series[i];
		return result;
	}

	bool is_functionally_complete_system() const {
		if (!is_T0() && !is_T1() && !is_monotone() && !is_linear())
			for (size_type i = 0; i < size(); ++i)
				if (Series[i] == Series[size() - i - 1])
					return 1;
		return 0;

	}

	std::vector<value_type> anf() const {

		std::vector<value_type> result(Series);

		for (size_type i = 0; i < dimension(); ++i)
			for (size_type j = 0; j < size(); ++j)
				if (j % static_cast<size_t>(pow(2, i + 1)) >= pow(2, i))
					result[j] = (result[j] + result[j - pow(2,i)]) % 2;

		return result;

	}


	size_type n_weight(size_type n) const {

		size_type result(0);

		for (size_type i = 0; i < dimension(); ++i)
			if ((n % static_cast<size_type>(pow(2, i + 1))) >= pow(2, i + 1) / 2)
				++result;

		return result;

	}

private:

	void right_dimension(const size_type & n) {

		size_type i(1);

		for (; i < n; i *= 2);

		if (i != n)
			throw std::exception("invalid dimension");

	}

	bool find(const std::vector<size_type> & vec, const size_type & n) const {
		for (auto & i : vec)
			if (i == n)
				return 1;
		return 0;
	}

	void insert_irrelevant_variable(const size_type & n) {  // не проверяет существенна ли переменная 

		if (n == 0 || n > dimension() + 1)
			return;

		for (size_type k = 0; k + pow(2, n - 1) <= size(); ++k)
			if (k % static_cast<size_type>(pow(2, n)) < pow(2, n) / 2)
				Series.insert(Series.begin() + k + pow(2, n - 1), Series[k]);

	}

	void erase_irrelevant_variable(const size_type & n) { 

		if (n == 0 || n > dimension() + 1)
			return;

		size_type t(0);

		for (size_type k = 0; k < size(); ++k)
			if (k % static_cast<size_type>(pow(2, n)) < pow(2, n) / 2)
				Series[t++] = Series[k];

		Series.resize(size() / 2);

	}


};


std::string get_polynom(const boolean_function & function) {

	auto buf = function.anf();

	std::string result("");

	if (buf[0])
		result = "1";

	for (size_t i = 1; i < buf.size(); ++i) {
		if (buf[i]) {
			if (result.size())
				result += " + ";
			std::vector<size_t> nums;
			for (size_t j = 0; j < function.dimension(); ++j)
				if ((i % static_cast<size_t>(pow(2, j + 1))) >= pow(2, j + 1) / 2)
					nums.push_back(j);

			for (size_t j = 0; j < nums.size(); ++j) {
				result += "x";
				result += std::to_string(nums[j]);
			}
		}
	}

	return result;

}

boolean_function operator + (const boolean_function & a, const boolean_function & b) {

	if (a.size() != b.size())
		throw std::exception("invalid size");

	boolean_function result(boolean_function::zero(a.dimension()));

	result += a;
	result += b;

	return result;
}

boolean_function operator * (const boolean_function& a, const boolean_function& b) {

	if (a.size() != b.size())
		throw std::exception("invalid size");

	boolean_function result(a);

	result *= b;

	return result;

}

boolean_function operator | (const boolean_function& a, const boolean_function& b) {

	if (a.size() != b.size())
		throw std::exception("invalid size");

	boolean_function result(a);

	result |= b;

	return result;

}

bool operator != (const boolean_function& a, const boolean_function& b) {
	return !(a == b);
}



#endif // __BOOLEAN_FUNCTION_INCLUDED__
