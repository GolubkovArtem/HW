

template<class It, class Cmp>
void qsort(It beg, It end, Cmp cmp) {

	It el(beg);

	for (It i = beg; i != end; ++i)
		if (cmp(*i, *el)) {
			for (It j = i; j != el;) {
				It k = j;      		
				std::iter_swap(k, --j); 
			}
			++el;
		}

	if (beg != end)
		qsort(beg, el, cmp);
	if (beg != end)
		qsort(++el, end, cmp);

}
