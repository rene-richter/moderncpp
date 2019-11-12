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
	void operator()(Cat x) { std::cout << "mew ";  }
	void operator()(Dog x) { std::cout << "woof ";  }
	void operator()(Donkey x) { std::cout << "hee-haw ";  }
	void operator()(Rooster x) { std::cout << "cock-a-doodle-doo ";  }
};

struct EvilVisitor
{
	void operator()(Cat x) { std::cout << "scratch!\n";  }
	void operator()(Dog x) { std::cout << "bite!\n";  }
	void operator()(Donkey x) { std::cout << "bash!\n";  }
	void operator()(Rooster x) { std::cout << "hack!\n";  }
};

void demo7() 
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
		std::visit(FriendlyVisitor{}, animal);
		std::visit(EvilVisitor{}, animal);
	}
}

int main()
{
	std::cout << "The Bremen musicians...\n";
	demo7();
}
