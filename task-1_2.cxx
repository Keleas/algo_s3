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
#include <vector>
#include <iterator>

using namespace std;

vector <int>  SimpleDividers ( int n )
{
    vector <int> result;
    int curNum = n, probe = 2;
            while ( curNum != 1) {
                if ( curNum % probe != 0 ) probe++;
                        else {
                    curNum /= probe;
                   result.insert( result.end(), probe );
                }
            }
    return result;
}

int main()
{
    int n;
    cin >> n;
    vector <int> dividers = SimpleDividers( n );
    for ( int i = 0; i < dividers.size(); ++i)
    {
        cout << dividers[i] << ' ';
    }
    return 0;
}


