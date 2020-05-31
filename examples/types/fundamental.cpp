#include <iostream>
#include <iomanip>
#include <limits>
#include <typeinfo>
#include <type_traits>

template <typename T>
auto show_type(T x)
{
	if constexpr (std::is_integral_v<T> || std::is_floating_point_v<T>)
	{
		std::cout 
			<< std::setw(20) << x
			<< std::setw(10) << typeid(x).name()
            << std::setw(20) << +std::numeric_limits<T>::min() << " ... "
            << std::setw(20) << +std::numeric_limits<T>::max();

		if (std::numeric_limits<T>::is_iec559)
			std::cout << " +/- " << std::numeric_limits<T>::epsilon();
		
		std::cout << '\n';
	}
	else
	{
		std::cout << x << " is not of fundamental arithmetic type\n";
	}
}

int main()
{
	std::cout 
		<< "               value  typename                 min                      max (+/- epsilon)\n";
	show_type(true);
	show_type('A');
	show_type(42);
	show_type(299'792'456L);
	show_type(-1ULL);
	show_type(3.14159f);
	show_type(1.6022e-19);
	show_type(299'792'456.0L);
	show_type(nullptr);
	show_type("cstring");
}