#include <vector>
#include <array>




namespace SimplexMethod
{

	struct rational
	{

		using natural0 = size_t;

		int numenator;
		natural0 denumenator;

		rational() = default;

		rational(int num, natural0 denum = 1)
			: numenator(num)
		{
			!denum ? denumenator = 1 : denumenator = denum;
			reduction();
		}

		rational(const rational & ratio)
			: numenator(ratio.numenator)
			, denumenator(ratio.denumenator)
		{}

		rational & operator = (const rational & ratio)
		{
			numenator = ratio.numenator;
			denumenator = ratio.denumenator;
			return *this;
		}

		rational operator + (const rational & ratio)
		{

			rational result(1, 1);
			result.numenator = numenator * ratio.denumenator + ratio.numenator * denumenator;
			result.denumenator = denumenator * ratio.denumenator;
			result.reduction();

			return result;
		}

		rational operator - (const rational & ratio)
		{
			rational result(1, 1);
			result.numenator = numenator * ratio.denumenator - ratio.numenator * denumenator;
			result.denumenator = denumenator * ratio.denumenator;
			result.reduction();

			return result;
		}

		rational operator - () const
		{
			rational result(-numenator, denumenator);
			return result;
		}

		rational operator * (const rational & ratio)
		{
			rational result(1, 1);
			result.numenator = numenator * ratio.numenator;
			result.denumenator = denumenator * ratio.denumenator;
			result.reduction();

			return result;
		}

		rational operator / (const rational & ratio)
		{
			if (ratio.numenator == 0)
				throw("dividing on 0");

			rational result(1, 1);
			if (ratio.numenator >= 0)
				result.numenator = numenator * ratio.denumenator;
			else
				result.numenator = -numenator * ratio.denumenator;
			result.denumenator = denumenator * abs(ratio.numenator);
			result.reduction();

			return result;

		}

		bool operator == (const rational & ratio) const 
		{
			return (numenator == ratio.numenator && denumenator == ratio.denumenator);
		}

		bool operator > (const rational & ratio) const 
		{
			return (numenator * ratio.denumenator > denumenator * ratio.numenator);
		}

		void reduction() 
		{

			if (numenator == 0) {
				denumenator = 1;
				return;
			}


			if (abs(numenator) >= denumenator) {
				for (size_t i = 2; i <= denumenator; ++i) {
					if (numenator % (int)i == 0 && denumenator % i == 0) {
						numenator = numenator / (int)i;
						denumenator /= i;
						--i;
					}

				}
			}
			else {
				for (size_t i = 2; i <= abs(numenator); ++i) {
					if (numenator % (int)i == 0 && denumenator % i == 0) {
						numenator = numenator / (int)i;
						denumenator /= i;
						--i;
					}

				}
			}
				
		}

		bool negative() const 
		{
			return (numenator < 0);
		}

		bool positive() const
		{
			return (numenator > 0);
		}

		void flip()
		{
			if (denumenator == 0)
				throw("dividung on 0");
			int buf = numenator;
			if (numenator > 0)
				numenator = denumenator;
			else
				numenator = (-1) * denumenator;
			denumenator = abs(buf);
		}

		friend std::ostream & operator << (std::ostream & out, const rational& ratio);

	};


	rational operator += (rational & ratio1, const rational & ratio2)
	{
		return ratio1 = ratio1 + ratio2;
	}

	rational operator -= (rational & ratio1, const rational & ratio2)
	{
		return ratio1 = ratio1 - ratio2;
	}

	rational operator *= (rational & ratio1, const rational & ratio2)
	{
		return ratio1 = ratio1 * ratio2;
	}

	rational operator /= (rational & ratio1, const rational & ratio2)
	{
		return ratio1 = ratio1 / ratio2;
	}

	bool operator != (const rational & ratio1, const rational & ratio2) {
		return !(ratio1 == ratio2);
	}

	bool operator < (const rational & ratio1, const rational & ratio2) {
		return !(ratio1 > ratio2 || ratio1 == ratio2);
	}

	bool operator >= (const rational & ratio1, const rational & ratio2) {
		return !(ratio1 < ratio2);
	}

	bool operator <= (const rational & ratio1, const rational & ratio2) {
		return !(ratio1 > ratio2);
	}

	std::ostream & operator << (std::ostream & out, const rational& ratio)
	{
		if (ratio.denumenator == 1)
			out << ratio.numenator;
		else
			out << ratio.numenator << "/" << ratio.denumenator;
		return out;
	}




	class matrix {

		rational** table;
		std::pair <size_t, size_t> size;
		std::vector<size_t> free_variables;
		std::vector<size_t> basic_variables;

	public:

		matrix() 
			: table(nullptr)
			, size(0, 0)
			, free_variables{ 0 }
			, basic_variables{ 0 }
		{ }

		matrix(size_t x, size_t y, std::vector<rational> data) 
			: size(x, y)
		{
			table = new rational*[get_hight()];
			for (size_t i = 0; i < size.first; ++i)
				table[i] = new rational[get_width()];
			for (size_t i = 0; i < get_hight(); ++i)
				for (size_t j = 0; j < get_width(); ++j)
					table[i][j] = data[i * get_width() + j];
			for (size_t i = 0; i < get_width() - 1; ++i)
				free_variables.push_back(i + 1);
			for (size_t i = 0; i < get_hight() - 1; ++i)
				basic_variables.push_back(free_variables.size() + i + 1);
		}


		void print() 
		{


			std::vector<size_t> max_symbols;

			max_symbols.push_back(2);
			for (size_t i = 0; i < get_hight() - 1; ++i)
				if (get_length(basic_variables[i]) + 1 > max_symbols[0])
					max_symbols[0] = get_length(basic_variables[i]) + 1;
			
			for (size_t i = 0; i < get_width(); ++i) {
				max_symbols.push_back(2);
				if (i != 0 && get_length(free_variables[i - 1]) + 1 > max_symbols[i + 1])
					max_symbols[i + 1] = get_length(free_variables[i - 1]) + 1;
				for (size_t j = 0; j < get_hight(); ++j)
					if (get_length(table[j][i]) > max_symbols[i + 1])
						max_symbols[i + 1] = get_length(table[j][i]);
			}
				
			for (size_t i = 0; i < max_symbols.size(); ++i) {
				std::cout << "+";
				for (size_t j = 0; j < max_symbols[i]; ++j)
					std::cout << "\"";
			}

			std::cout << "+" << std::endl;
			
			for (size_t i = 0; i < max_symbols.size(); ++i) {
				std::cout << "\"";
				if (i > 1) {
					for (size_t j = 0; j < max_symbols[i] - get_length(free_variables[i - 2]) - 1; ++j)
						std::cout << " ";
					std::cout << "x" << free_variables[i - 2];
				}
				else if (i == 1) {
					for (size_t j = 0; j < max_symbols[i] - 1; ++j)
						std::cout << " ";
					std::cout << "S";
				}
				else
					for (size_t j = 0; j < max_symbols[0]; ++j)
						std::cout << " ";
					
			}

			std::cout << "\"" << std::endl;

			for (size_t i = 0; i < get_hight(); ++i) {

				for (size_t i = 0; i < max_symbols.size(); ++i) {
					std::cout << "+";
					for (size_t j = 0; j < max_symbols[i]; ++j)
						std::cout << "\"";
				}

				std::cout << "+" << std::endl;

				std::cout << "\"";

				if (i != get_hight() - 1) {
					for (size_t j = 0; j < max_symbols[0] - get_length(basic_variables[i]) - 1; ++j)
						std::cout << " ";
					std::cout << "x" << basic_variables[i];
				}
				else {
					for (size_t j = 0; j < max_symbols[0] - 1; ++j)
						std::cout << " ";
					std::cout << "F";
				}

				for (size_t j = 0; j < get_width(); ++j) {
					std::cout << "\"";
					for (size_t k = 0; k < max_symbols[j + 1] - get_length(table[i][j]); ++k)
						std::cout << " ";
					table[i][j].reduction();
					std::cout << table[i][j];
				}

				std::cout << "\"" <<std::endl;


			}

			for (size_t i = 0; i < max_symbols.size(); ++i) {
				std::cout << "+";
				for (size_t j = 0; j < max_symbols[i]; ++j)
					std::cout << "\"";
			}

			std::cout << "+" << std::endl;

		}


		size_t get_hight() const 
		{
			return size.first;
		}

		size_t get_width() const 
		{
			return size.second;
		}

		std::vector<size_t> step1() const 
		{

			std::vector<size_t> result;

			size_t i;
			for (i = 0; i < get_hight() - 1; ++i)
				if (table[i][0].negative()) {
					result.push_back(1);
					break;
				}

			if (i == get_hight() - 1) {
				result.push_back(0);
				return result;
			}

			size_t j;
			for (j = 1; j < get_width(); ++j)
				if (table[i][j].negative()) {
					result.push_back(j);
					break;
				}
			
			if (j == get_width()) {
				throw("logic_error");
			}

			std::pair<rational, size_t> result_string(table[0][0] / table[0][j], 0);
			rational buf;
			size_t k;
			for (k = 1; k < get_hight() - 1; ++k) {
				if (table[k][j].numenator == 0)
					throw("dividing on 0");
				buf = table[k][0] / table[k][j];
				if (!buf.negative() && buf < result_string.first) {
					result_string.first = buf;
					result_string.second = k;
				}
			}

			result.push_back(result_string.second);
			std::swap(result[1], result[2]);
			
			return result;

		}

		bool step2(const std::vector<size_t> & vec)
		{
			if (vec[0]) {
				std::swap(basic_variables[vec[1]], free_variables[vec[2] - 1]);
				step2(vec[1], vec[2]);
			}
			else
				return false;
			return true;
		}

		void step2(size_t str_to_chg, size_t cht_to_chg) 
		{
			
			for (size_t i = 0; i < get_hight(); ++i) {
				if (i == str_to_chg)
					continue;
				for (size_t j = 0; j < get_width(); ++j) {
					if (j == cht_to_chg)
						continue;
					table[i][j] -= table[i][cht_to_chg] * table[str_to_chg][j] 
						/ table[str_to_chg][cht_to_chg];
				}
			} 

			
			for (size_t i = 0; i < get_width(); ++i) {
				if (i == cht_to_chg)
					continue;
				table[str_to_chg][i] /= table[str_to_chg][cht_to_chg];
			}

			for (size_t i = 0; i < get_hight(); ++i) {
				if (i == str_to_chg)
					continue;
				table[i][cht_to_chg] /= -table[str_to_chg][cht_to_chg];
			}

			table[str_to_chg][cht_to_chg].flip();

		}

		std::vector<size_t> step3() const 
		{

			std::vector<size_t> result;

			if (table[get_hight() - 1][0].negative()) 
				result.push_back(1);
			else {
				result.push_back(0);
				return result;
			}

			size_t j;
			for (j = 1; j < get_width(); ++j)
				if (table[get_hight() - 1][j].positive()) {
					result.push_back(j);
					break;
				}

			if (j == get_width()) {
				result[0] = 0;
				return result;
			}

			std::pair<rational, size_t> result_string(table[0][0] / table[0][j], 0);
			rational buf;
			size_t k;
			for (k = 1; k < get_hight() - 1; ++k) {
				if (table[k][j].numenator == 0)
					throw("dividing on 0");
				buf = table[k][0] / table[k][j];
				if (!buf.negative() && buf < result_string.first) {
					result_string.first = buf;
					result_string.second = k;
				}
			}

			result.push_back(result_string.second);
			std::swap(result[1], result[2]);

			return result;
		}

		std::vector<size_t> get_free_variables() const
		{
			return free_variables;
		}

		std::vector<size_t> get_basic_variables() const
		{
			return basic_variables;
		}

		size_t get_length(rational ratio)
		{

			size_t result(0);
			if (ratio.negative())
				++result;
			do {
				++result;
			} while (ratio.numenator /= 10);

			if (ratio.denumenator != 1) {
				do {
					++result;
				} while (ratio.denumenator /= 10);
				++result;;
			}

			return result;

		}

	};





}
