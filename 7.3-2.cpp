// 7.3-2.cpp :


#include <iostream>
#include<list>
#include<future>
#include<iterator>

void function(int a, std::promise<int> p) {
	p.set_value(++a);
}

void foreach(std::list<int>::iterator s, std::list<int>::iterator e, void(*f)(int, std::promise<int>)) {
	if (s == e) return;
	std::promise<int> prom;
	std::future<int> fut = prom.get_future();
	std::async(f, *s, std::move(prom));
	*s = fut.get();
	foreach(++s, e, f);
}

int main()
{
	std::list<int> list(11);

	std::list<int>::iterator start = list.begin();
	std::list<int>::iterator end = list.end();

	for (auto it = start; it != end; it++) {
		*it = std::rand();
		std::cout << *it << " ";
	}
	std::cout << "\n\n";


	foreach(start, end, *function);

	for (auto n : list) {
		std::cout << n << " ";
	}
}