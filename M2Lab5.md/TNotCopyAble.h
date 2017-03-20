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

class CloseCheck
{
	static CloseCheck * Head;
	CloseCheck * pNext;
	FILE * File;
public:
	bool CheckFile(const FILE * file)
	{
		if (file == nullptr) return 1;
		CloseCheck * pBuf = Head;
		do {
			fclose(pBuf->File);
			pBuf = pBuf->pNext;
		} while (pBuf != Head);
		Head = nullptr;
		throw FileAlreadyOpened();
	}
	void OpenFile(FILE * file)
	{
		File = file;
		if (Head)
		{
			pNext = Head;
			CloseCheck *& pBuf = pNext->pNext;
			while (pBuf != Head)
				pBuf = pBuf->pNext;
			Head = this;
			pBuf = Head;
		}
		else
		{
			Head = this;
			pNext = Head;
		}
	}
};

class TNotCopyable
{
	FILE * Descriptor;
	CloseCheck Check;
public:
	~TNotCopyable()
	{
		this->Close();
	}
	TNotCopyable()
		: Descriptor(nullptr)
	{ }
	void OpenToWrite(std::string const & fileName)
	{
		Check.CheckFile(Descriptor);
		Descriptor = fopen(fileName.c_str(), "w");
		Check.OpenFile(Descriptor);
	}

	void OpenToRead(std::string const & fileName)
	{
		Check.CheckFile(Descriptor);
		Descriptor = fopen(fileName.c_str(), "r");
		Check.OpenFile(Descriptor);
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
	TNotCopyable(const TNotCopyable & ) = delete;
	TNotCopyable & operator = (const TNotCopyable & ) = delete;
};

#endif // __NOTCOPYABLE_INCLUDED__
