

template<class It, class Cmp>
void qsort(It beg, It end, Cmp cmp) {

	It el(beg);

	for (It i = beg; i != end; ++i)
		if (cmp(*i, *el)) {
			for (It j = i; j != el;) {
				std::iter_swap(j, j - 1); // std::iter_swap(j, --j) не работает, т.к выполняется сначала --j
				--j;                      // странно я читал, что такое поведение бывает только у префикса
			}
			++el;
		}
	
	std::cout << std::endl;
	for (It i = beg; i != end; ++i)
		std::cout << *i << " ";

	if (beg != end)
		qsort(beg, el, cmp);
	if (beg != end)
		qsort(++el, end, cmp);

}
