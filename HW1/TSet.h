#include <iostream>
#include <vector>




template <class T> 
struct less 
{
	bool operator() (const T & x, const T & y) const {
		return x < y;
	}
};



//////////////////////////////////////////////////// struct bidirectional_iterator
template <class T>
struct bidirectional_iterator
{

	using value_type = T;
	using iterator = bidirectional_iterator<T>;
	using const_iterator = const bidirectional_iterator<T>;

private:

	value_type Value;
	iterator * Up;
	iterator * Right;
	iterator * Left;

public:

	~bidirectional_iterator() = default;

	bidirectional_iterator() 
		: Up(nullptr)
		, Right(nullptr)
		, Left(nullptr)
	{ }

	bidirectional_iterator(const bidirectional_iterator<T> & bIter)
		: Value(bIter.Value)
		, Up(bIter.Up)
		, Right(bIter.Right)
		, Left(bIter.Left)
	{ }

	const bidirectional_iterator & operator = (const bidirectional_iterator<T> & bIter) {
		Value = bIter.Value;
		Up = bIter.Up;
		Right = bIter.Right;
		Left = bIter.Left;
		return *this;
	}


	bool operator == (const bidirectional_iterator<T> & bIter) const{
		if (this == nullptr)
			return 0;
		if (bIter.Up == Up && *bIter == Value)
			return 1;
		return 0;
	}

	bool operator != (const bidirectional_iterator<T> & bIter) const {
		return !(*this == bIter);
	}

	value_type operator * () const {
		return Value;
	}


	const iterator & operator ++ () {

		iterator buf(*this);

		if (Right != nullptr) {
			*this = *Right;
			while (Left != nullptr) 
				*this = *Left;
		} 
		else if (Up != nullptr && Up->Left != nullptr && **Up->Left == **this)
			*this = *Up;
		else {
			while (Up != nullptr) {
				*this = *Up;
				if (Up != nullptr && Up->Left != nullptr && **Up->Left == **this) {
					*this = *Up;
					break;
				}
				if (Up == nullptr) {
					*this = buf;
					return buf;
				}
			}
		}

		return *this;
	}

	iterator operator ++ (int) {
		iterator buf(*this);
		++*this;
		return buf;
	}

	const iterator & operator -- () {
		
		iterator buf(*this);

		if (Left != nullptr)
		{
			*this = *Left;
			while (Right != nullptr)
				*this = *Right;
		}
		else if (Up != nullptr && Up->Right != nullptr && **Up->Right == **this)
			*this = *Up;
		else {
			while (Up != nullptr) {
				*this = *Up;
				if (Up != nullptr && Up->Right != nullptr && **Up->Right == **this) {
					*this = *Up;
					break;
				}
				if (Up == nullptr) {
					*this = buf;
					return buf;
				}
			}
		}

		return *this;
	}

	iterator operator -- (int) {
		iterator buf(*this);
		--*this;
		return buf;
	}


	template<class T, class Compare = less<T>>
	friend class TSet;
};


//////////////////////////////////////////////////// class TSet
template<class T, class Compare = less<T>>
class TSet
{

public:

	using value_type = T;
	using value_compare = Compare;
	using reference = value_type &;
	using const_reference = const value_type &;
	using iterator = bidirectional_iterator<T>;
	using const_iterator = const bidirectional_iterator<T>;
	using size_type = size_t;

private:

	Compare Comp;
	iterator * Root;
	iterator Begin;
	iterator End;
	size_type Size;

public:

	~TSet() {
		clear();
	}

	explicit TSet(const value_compare & comp = value_compare())
		: Root(nullptr)
		, Size(0)
		, Comp(comp)
	{ }

	TSet(const_reference value, const value_compare & comp = value_compare()) 
		: Comp(comp)
	{
		Root = new iterator;
		Root->Value = value;
		Root->Right = &End;
		End.Up = Root;
		End.Value = value;
		Begin = *Root;
		Size = 1;
	}

	TSet(const TSet & set) {
		*this = set;
	}

	TSet & operator = (const TSet<T, Compare> & set) {
		Comp = set.Comp;
		if (set.Root == Root)
			return *this;
		if (!empty())
			clear();
		if (set.empty())
			return *this;		
		for (auto it = *set.Root; it != set.End; ++it)
			insert(*it);
		for (auto it = *set.Root; it != set.Begin; --it)
			insert(*it);
		insert(*set.Begin);
		return *this;
	}

	//////////////////////////////////////////////////// insert(), erase(), swap(), clear()
	void insert(const_reference value) {

		if (empty()) {
			Root = new iterator;
			Root->Value = value;
			Root->Right = &End;
			End.Up = Root;
			End.Value = value;
			Begin = *Root;
			Size = 1;
			return;
		}

		iterator * i = Root;

		while(value != **i) {

			if (Comp(**i, value) && (i->Right == nullptr || *i->Right == End)) {
				iterator * newBranch = new iterator;
				newBranch->Up = i;
				newBranch->Value = value;
				i->Right = newBranch;
				++Size;
				i = newBranch;
			}
			else if (Comp(value, **i) && i->Left == nullptr) {
				iterator * newBranch = new iterator;
				newBranch->Up = i;
				newBranch->Value = value;
				i->Left = newBranch;
				++Size;
				i = newBranch;
			}
			else if (Comp(**i, value))
				i = i->Right;
			else
				i = i->Left;

		}

		this->reIt();

	}

	void erase(const_iterator it) {

		value_type value = *it;

		if (!count(value))
			return;

		iterator buf(find(value));
		iterator * pBuf(nullptr);

		if (value == **Root) {

			if (buf.Left != nullptr && (buf.Right == nullptr && *buf.Right == End)) {
				Root = buf.Left;
				pBuf = Root->Up;
				Root->Up = nullptr;
				this->reIt();
			}
			else if (buf.Right != nullptr && *buf.Right != End)
			{
				Root = buf.Right;
				pBuf = Root->Up;
				Root->Up = nullptr;
				this->reIt();
				if (buf.Left != nullptr) {
					this->insertBranch(buf.Left);
				}
			}

			if (pBuf == nullptr) {
				delete Root;
				Root = nullptr;
			}
			else 
				delete pBuf;

			--Size;

			return;
		}


		if (buf.Up->Left != nullptr && **buf.Up->Left == *buf) {
			pBuf = buf.Up->Left;
			buf.Up->Left = nullptr;
		}
		else {
			pBuf = buf.Up->Right;
			buf.Up->Right = nullptr;
		}

		this->reIt();

		if (buf.Left != nullptr)
			this->insertBranch(buf.Left);
		if (buf.Right != nullptr) 
			this->insertBranch(buf.Right);

		--Size;
		delete pBuf;

	}

	void erase(const_reference value) {
		erase(find(value));
	}

	void swap(TSet & set) {
		if (set.Root == Root)
			return;
		TSet buf(set);
		set = *this;
		*this = buf;
	}

	void clear() {
		if (empty())
			return;
		for (auto it = Begin;;) {
			this->erase(*it++);
			if (it == End)
				break;
			it = find(*it);
		}
	}

	//////////////////////////////////////////////////// value_compare()
	const value_compare & value_comp() const {
		Compare compare;
		return compare;
	}

	//////////////////////////////////////////////////// begin(), cbegin(), end(), cend()
	iterator begin() const {
		if (empty())
			throw std::exception("appeal to empty tree");
		return Begin;
	}

	const_iterator cbegin() const {
		if (empty())
			throw std::exception("appeal to empty tree");
		return Begin;
	}

	iterator end() const {
		if (empty())
			throw std::exception("appeal to empty tree");
		return End;
	}

	const_iterator cend() const {
		if (empty())
			throw std::exception("appeal to empty tree");
		return End;
	}


	size_type empty() const {
		return !Size;
	}

	size_type size() const {
		return Size;
	}

	//////////////////////////////////////////////////// find(), count()
	iterator find(const_reference value) const {

		if (empty())
			throw std::exception("appeal to empty tree");

		iterator it(*Root);

		while (1) {
			if (*it == value)
				return it;
			else if (Comp(*it, value) && it.Right != nullptr && *it.Right != End)
				it = *it.Right;
			else if (Comp(value, *it) && it.Left != nullptr)
				it = *it.Left;
			else
				return End;
		}

	}


	size_type count(const_reference value) const {
		return (*find(value) == value);
	}

	// reIt(), insertBranch() private функции, используемые только в данном классе (в функциях insert, erase())
	private:
	
	// переопределяет Begin и End
	void reIt() {
		iterator * it = Root;
		while (it->Left != nullptr)
			it = it->Left;
		Begin = *it;
		it = Root;
		while (it->Right != nullptr && *it->Right != End)
			it = it->Right;
		if (*it->Right != End) {
			it->Right = &End;
			End.Up = it;
			End.Value = **Root;
		}
	}

	// добавляет ветку в дерево без учёта Size
	void insertBranch(iterator * branch) {

		iterator * it(Root);

		branch->Up = nullptr;

		while (branch->Up == nullptr) {
			if (Comp(**it, **branch) && it->Right != nullptr && *it->Right != End)
				it = it->Right;
			else if (Comp(**branch, **it) && it->Left != nullptr)
				it = it->Left;
			else if (Comp(**it, **branch)) {
				it->Right = branch;
				branch->Up = it;
			}
			else {
				it->Left = branch;
				branch->Up = it;
			}

		}

		this->reIt();

	}

};

template <typename T, class Compare>
std::ostream & operator << (std::ostream & out, TSet<T, Compare> & set) {
	if (set.empty())
		return out;
	for (auto it = set.begin(); it != set.end(); ++it)
		out << *it << " ";
	return out;
}
