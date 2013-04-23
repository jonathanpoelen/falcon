#include <iostream>
#include <falcon/number.hpp>

int main()
{
	falcon::number<> number2(CPP0X(255, 255));
	// 	std::cout << number << std::endl;
	std::cout << number2 << std::endl;
	// 	number += number2;
	// 	std::cout << number << std::endl;
	number2 <<= 1;
	std::cout << number2 << std::endl;
	number2 <<= 3;
	std::cout << number2 << std::endl;
	number2 <<= 10;
	std::cout << number2 << std::endl;
	number2 <<= 8;
	std::cout << number2 << std::endl;
	number2 >>= 1;
	std::cout << number2 << std::endl;
	number2 >>= 3;
	std::cout << number2 << std::endl;
	number2 >>= 10;
	std::cout << number2 << std::endl;
	number2 >>= 8;
	std::cout << number2 << std::endl;
	number2 >>= 16;
	std::cout << number2 << std::endl;


	// 	std::cout << number.not_remove_unused_zero() << std::endl;
	// 	number >>= 1;
	// 	std::cout << number.not_remove_unused_zero() << std::endl;
	// 	std::cout << number2.not_remove_unused_zero() << std::endl;
	// 	number2 >>= 10;
	// 	std::cout << number2.not_remove_unused_zero() << std::endl;
}
FALCON_GROUP_TEST_TO_MAIN(number_test)
