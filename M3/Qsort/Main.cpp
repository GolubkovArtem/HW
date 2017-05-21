

template<class It, class Cmp>
void qsort(It beg, It end, Cmp cmp) {

	It el(beg);

	for (It i = beg; i != end; ++i)
		if (cmp(*i, *el)) {
			for (It j = i; j != el;) {
				It k = j;      // std::iter_swap(j, --j) не работает, т.к выполняется сначала --j
				std::iter_swap(k, --j); // странно я читал, что такое поведение бывает только у постфикса
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
