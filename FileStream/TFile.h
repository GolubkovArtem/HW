#pragma warning(disable:4996)
#include <set>
#include <exception>
#include <string>
#include <vector>
#include <iostream>




class FileStream
{
	FILE * Descriptor;

public:

	~FileStream() {
		close();
	}

	FileStream()
		: Descriptor(nullptr)
	{ }

	FileStream(const FileStream & ) = delete;

	FileStream & operator = (const FileStream & ) = delete;

	void open(std::string const & fileName, char * mode) {
		if (Descriptor != nullptr)
			throw std::exception("File already opened");
		if (!check_mode(mode))
			throw std::exception("Incorect mode");
		Descriptor = fopen(fileName.c_str(), mode);
	}

	bool is_open() const {
		return Descriptor;
	}

	char * getline() const {

		if (Descriptor == nullptr)
			throw std::exception("File was not opened");

		std::vector<char> buf;

		while (!feof(Descriptor))
			buf.push_back(fgetc(Descriptor));

		char * result = new char[buf.size() + 1];
		std::copy(buf.begin(), buf.end(), result);
		result[buf.size()] = '\0';

		return result;

	}

	void seek(std::streampos pos) const {
		fseek(Descriptor, pos, SEEK_CUR);
	}

	void read(char * buf, const size_t number) {
		if (Descriptor == nullptr)
			throw std::exception("File was not opened");

		fgets(buf, number + 1, Descriptor);
		
	}

	void write(char * buf) const {
		if (Descriptor == nullptr)
			throw std::exception("File was not opened");

		fputs(buf, Descriptor);

	}

	bool eof() const {
		return feof(Descriptor);
	}

	void close() throw()
	{
		if (Descriptor != nullptr)
		{
			fclose(Descriptor);
			Descriptor = nullptr;
		}
	}

	bool check_mode(const std::string & mode) const {
		std::set<std::string> modes = { "r", "w", "a", "r+", "w+", "a+", "rb", "wb", "ab",
			"r+b", "w+b", "a+b", "rb+", "wb+", "ab+", "wx", "wbx", "w+x", "wb+x", "w+bx" };
		return modes.find(mode) != modes.end();
	}

	friend std::ostream & operator << (std::ostream & out, const FileStream & file);

};

std::ostream & operator << (std::ostream & out, const FileStream & file) {
	out << file.Descriptor;
	return out;
}
