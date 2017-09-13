
Даны два строго возрастающих массива целых чисел A[0..n) и
B[0..m) и число k. Найти количество таких пар индексов (i, j), что
A[i] + B[j] = k. Время работы O(n + m). n, m ≤ 100000.

*Указание.* Обходите массив B от конца к началу.

  in             | out
  ---------------|-----
  4              | 3
  -5 0 3 18      | 
  5              | 
  -10 -2 4 7 12  | 
  7              | 

****************************************************************************/

#include <iostream>

/*
    Idea:
run through two arrays:
left and right for array A[i], B[i] respectively
and further, depending on the proximity of the sum A [lt] + B [rt]
we will shift lt, rt.
*/
int main()
{
    int n;
    std::cin >> n;
    int *A = new int[n];
    for(int i = 0; i < n; ++i)
    std::cin >> A[i];

    int m;
    std::cin >> m;
    int *B = new int[m];
    for(int i = 0; i < m; ++i)
    std::cin >> B[i];

    int k;
    std::cin >> k;
    //"sliders"
    int lt = 0;
    int rt = m-1;
    int count = 0;

    while(lt != n && rt != -1)
    {
        int cursum = A[lt] + B[rt];
        //conditions for finding the desired sum k
        //move the "sliders"
        if(cursum < k)
            lt++;
        else if(cursum > k)
            rt--;
        else{
            count++;
            rt--;
        }
    }
    std::cout << count << std::endl;

    delete [] A;
    delete [] B;

    return 0;
}
