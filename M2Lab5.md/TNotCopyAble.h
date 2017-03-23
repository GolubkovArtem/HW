#ifndef __NOTCOPYABLE_INCLUDED__
#define __NOTCOPYABLE_INCLUDED__

#pragma warning(disable:4996)
#include <exception>
#include <cstdio>
#include <string>

struct FileAlreadyOpened
	: public std::exception
{
	FileAlreadyOpened() = default;
	FileAlreadyOpened(const char* const message)
		: std::exception(message)
	{ }
};

class TNotCopyable
{
public:
	~TNotCopyable()
	{
		this->Close();
	}
	TNotCopyable(std::string const & fileName, const char * mode)
	{
		static const char* modes[] = { "r", "w", "a", "r+", "w+", "a+" };
		for (size_t i = 0; i < 6; ++i)
		{
			if (modes[i] == mode)
			{
				Descriptor = fopen(fileName.c_str(), mode);
				if (Descriptor == nullptr)
					throw(std::exception("Incorrect way"));
			}
		}
		throw(std::exception("Incorrect mode"));
	}
	void Close() throw()
	{
		if (Descriptor != nullptr)
		{
			fclose(Descriptor);
			Descriptor = nullptr;
		}
	}
	FILE * Get()
	{
		return Descriptor;
	}
private:
	FILE * Descriptor;
	TNotCopyable(const TNotCopyable & ) = delete;
	TNotCopyable & operator = (const TNotCopyable & ) = delete;
};

#endif // __NOTCOPYABLE_INCLUDED__
