#include <iostream>
#include <stack>
#include <string>

std::string multibaseOutput(int num, int b);


int main()
{
	std::cout << multibaseOutput(75, 16) << '\n';
	
}

std::string multibaseOutput(int num, int b)
{
	std::string digitChar = "0123456789ABCDEF";
	std::string numStr = "";

	std::stack<char> stk;

	do 
	{
		std::cout << "N = " << num << ", b = " << b 
			<< "\tN\%b = " << num % b << ", N/b = " << num / b << '\n';
		stk.push(digitChar[num % b]);
		num /= b;
	} while(num != 0);

	while (!stk.empty())
	{
		numStr += stk.top();
		stk.pop();
	}
	return numStr;
}
