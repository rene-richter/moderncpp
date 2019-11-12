// a Brothers Grimm's tale

#include <iostream>
#include <stack>
#include <variant>

class Cat{};
class Dog{};
class Donkey{};
class Rooster{};
using Animal = std::variant<Donkey, Dog, Cat, Rooster>;

struct FriendlyVisitor
{
	auto operator()(Cat x) { return "mew ";  }
	auto operator()(Dog x) { return "woof ";  }
	auto operator()(Donkey x) { return "hee-haw ";  }
	auto operator()(Rooster x) { return "cock-a-doodle-doo ";  }
};

struct EvilVisitor
{
	auto operator()(Cat x) { return "scratch!\n";  }
	auto operator()(Dog x) { return "bite!\n";  }
	auto operator()(Donkey x) { return "bash!\n";  }
	auto operator()(Rooster x) { return "hack!\n";  }
};

auto demo7() 
{
	std::stack<Animal> s;
	
	s.push(Donkey{});
	s.push(Dog{});
	s.push(Cat{});
	s.push(Rooster{});
	
	while (!s.empty())
	{
		Animal animal = s.top();
		s.pop();
		std::cout << std::visit(FriendlyVisitor{}, animal);
		std::cout << std::visit(EvilVisitor{}, animal);
	}
}

int main()
{
	std::cout << "The Bremen musicians...\n";
	demo7();
}
