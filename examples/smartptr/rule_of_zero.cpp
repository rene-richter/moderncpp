#include <memory>
#include <iostream>

struct Movable
{
	std::unique_ptr<int> p;
};

struct Shared
{
	std::shared_ptr<int> p;
};

auto sink(Movable m)
{
	std::cout << *m.p << '\n';	
}

auto no_sink(Shared s)
{
	std::cout << *s.p << " used by " << s.p.use_count() << '\n';
}

int main()
{
	Movable m;
	Shared s;
	
	m.p = std::make_unique<int>(1);
	s.p = std::make_shared<int>(2);
	
	sink(std::move(m));
	no_sink(s);
	
	if (!m.p) std::cout << "moved is gone\n";
	if (s.p)  std::cout << "shared is used by " << s.p.use_count() << '\n';
}
