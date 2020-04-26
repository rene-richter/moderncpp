#include <cassert>
#include <memory>
#include <iostream>
#include <string>
#include <vector>

class Animal
{
public:
	virtual ~Animal() = default;
	virtual std::string say() const = 0;
};

class Tiger : public Animal
{
public:	
	std::string say() const override { return "roar"; }	
};

class Parrot : public Animal
{
public:	
	std::string say() const override { return "I'm not dead, I'm resting"; }	
};

auto create_zoo()
{
	std::vector<std::unique_ptr<Animal>> zoo;
	
	zoo.push_back(std::make_unique<Tiger>());
	zoo.push_back(std::make_unique<Parrot>());
	
	return zoo;
}

int main()
{
	auto zoo = create_zoo();
	
	for(auto const& animal : zoo) // no copies allowed: tiger is unique!
	{
		if (animal) std::cout << animal->say() << '\n';
	}
	zoo[1] = nullptr; // now the parrot is dead / or flown out?
	
	// auto zoo2 = zoo;           // error: can't copy a whole zoo
	auto zoo2{std::move(zoo)};   // but can move the whole zoo
	                              // or individual animals:
	zoo[0] = std::move(zoo2[0]); // tiger is back in first zoo, 
	                              
    assert(zoo2.size() == 2 && !zoo2[0] && !zoo2[1]); 
	                              // zoo2 has two empty cages							  
}
