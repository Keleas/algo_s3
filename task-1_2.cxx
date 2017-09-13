/****************************************************************************
Задача 1_2.

Вывести разложение натурального числа n на простые множители.
Простые множители должны быть упорядочены по возрастанию и разделены
пробелами.
2 ≤ n ≤ 10^6.

  in  | out
  ----|-------
  75  | 3 5 5
****************************************************************************/

#include <iostream>

int main()
{
  int n;
	std::cin >> n;

  int curNum = n, probe = 2;
  bool check = false; // checking for simplicity 
	while ( curNum != 1 && probe*probe <= n ) 
	{
		if ( curNum % probe != 0 ) probe++;
		else 
		{
			check = true;
      curNum /= probe;
			std::cout << probe << " ";
		}
	}
	if ( !check ) std::cout << n;

  return 0;
}


