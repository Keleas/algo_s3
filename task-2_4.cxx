/****************************************************************************
Задача 2_4. "Считалочка".

В круг выстроено N человек, пронумерованных числами от 1 до N.
Будем исключать каждого k-ого до тех пор, пока не уцелеет только один человек.
(Например, если N=10, k=3, то сначала умрет
3-й, потом 6-й, затем 9-й, затем 2-й, затем 7-й, потом 1-й, потом 8-й,
за ним - 5-й, и потом 10-й. Таким образом, уцелеет 4-й.) Необходимо
определить номер уцелевшего.
N, k ≤ 10000.

  in    | out
  ------|-----
  10 3  | 4
****************************************************************************/

/*

#include <iostream>

int counted ( int n, int k )
{
    return n > 1 ? (( counted(n-1, k) + k - 1 ) % n + 1) : 1;
}

int main()
{

    int n,k;
    std::cin >> n >> k;

    std::cout <<  counted(n, k) << std::endl;

    return 0;
}
*/

#include <iostream>

struct node
{
    int key;
    node *next;

    node ( int a, node *p )
        : key{a}, next{p}
    {}
};

int main()
{
    int n, k;
    std::cin >> n >> k;

    node *frst = new node (1, 0);
    frst->next = frst;

    node *ppl = frst;
    for ( int i = 2; i <= n; ++i ) // создаю циклический список
        ppl = ( ppl->next = new node (i, frst) );

    while ( ppl != ppl->next )
    {
        for ( int i = 1; i < k; ++i ) // беру k-ый элемент
            ppl = ppl->next;

        ppl->next = ppl->next->next; // удаляю его
    }

    std::cout << ppl->key << std::endl;

    return 0;
}



