// #include <iostream>
#include <memory>
#include <vector>
#include "test/A.h"

using namespace std;

template <typename T>
struct my_allocator
: allocator<T>
{
	using propagate_on_container_copy_assignment = std::true_type;
	using propagate_on_container_move_assignment = std::true_type;
	using propagate_on_container_swap = std::true_type;

	template<typename U>
	struct rebind
	{ typedef my_allocator<U> other; };

	my_allocator()
	{ cout << "ctor\n"; }

	my_allocator(const my_allocator& other)
	: allocator<T>(other)
	{ cout << "ctor copy\n"; }

	my_allocator(my_allocator&&)
	{ cout << "ctor move\n"; }
};

namespace std {
	template<typename T>
	void swap(my_allocator<T>&, my_allocator<T>&)
	{ cout << "swap\n"; }
}

int main(/*int argc, char **argv*/)
{
	std::cout.sync_with_stdio(false);

	typedef std::vector<A, my_allocator<A>> container_t;
	container_t vec({2,3});
	cout << "-------\n";
	container_t vec2(vec);
	cout << "-------\n";
	container_t vec3;
	cout << "-------\n";
	vec3.swap(vec2);
	cout << "-------\n";
	container_t vec4(std::move(vec));
}

