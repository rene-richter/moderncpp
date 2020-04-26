#include <iostream>

class Wrong
{
	int* p_;

public:
	Wrong(int n) : p_(new int(n)) {}	
	~Wrong() { delete p_; }
	int use() { return *p_; }
};

void crash1()
{
	Wrong a{1};
	{
		Wrong b{2};
		a = b;
	}
	std::cout << a.use() << '\n';
}

void crash2()
{
	int* p = new int(1);
	int* q = new int(2);
	p = q;
	delete q;
	std::cout << *p << '\n';
	delete p;
}

void crash3()
{
	Wrong a{3};
	{
		Wrong b{a};
	}
	std::cout << a.use() << '\n';
}

void use_copy(Wrong param)
{
	std::cout << "copy: " << param.use() << '\n';
}

void crash4()
{

	Wrong w{4};
	use_copy(w);
	std::cout << w.use() << '\n';
}

void crash5()
{
	use_copy(Wrong{5}); // maybe ok: elided temporary
}

int main()
{
	crash1();
	std::cout << "You should never see this...1" << std::endl;
	crash2();
	std::cout << "You should never see this...2" << std::endl;
	crash3();
	std::cout << "You should never see this...3" << std::endl;
	crash4();
	std::cout << "You should never see this...4" << std::endl;
	crash5();
	std::cout << "You should never see this...5" << std::endl;
}
