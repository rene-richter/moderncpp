// memory leak without virtual destructor

#include <string>
#include <memory>

class Base
{
public:
  // virtual ~Base() {}
};

class Derived : public Base
{
public:
  Derived()
  : data("string length exceeds small string optimization (SSO)") 
  {
  }

private:
  std::string data;
};


int main()
{
  while (true)
  {
	// polymorphic pointer, Liskov's substitution principle 
    Base* p = new Derived(); 
    delete p;

    // std::shared_ptr<Base> p = std::make_shared<Derived>();	
  } // eating up all memory ...
}
