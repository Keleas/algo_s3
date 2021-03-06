/****************************************************************************
Жадные алгоритмы

**Атлеты.**

В город *N* приехал цирк с командой атлетов. Они хотят удивить горожан
города *N* --- выстроить из своих тел башню максимальной высоты. Башня
--- это цепочка атлетов, первый стоит на земле, второй стоит у него на
плечах, третий стоит на плечах у второго и т.д.

Каждый атлет характеризуется силой *s*~*i*~ (kg) и массой *m*~*i*~ (kg).
Сила --- это максимальная масса, которую атлет способен держать у себя
на плечах.

К сожалению ни один из атлетов не умеет программировать, так как всю
жизнь они занимались физической подготовкой, и у них не было времени на
изучение языков программирования. Помогите им, напишите программу,
которая определит максимальную высоту башни, которую они могут
составить.

Известно, что если атлет тяжелее, то он и сильнее:

если *m*~*i*~\>*m*~*j*~, то *s*~*i*~ \> *s*~*j*~.

Атлеты равной массы могут иметь различную силу.

*Формат входных данных:*

Вход содержит только пары целых чисел --- массу и силу атлетов. Число
атлетов 1 ≤ *n* ≤ 100000. Масса и сила являются положительными целыми
числами меньше, чем 2000000.

*Формат выходных данных:*

Выход должен содержать натуральное число --- максимальную высоту башни.

  ------ -----
  in     out
  ------ -----
  3 4\   3
  2 2\
  7 6\
  4 5
  ------ -----
****************************************************************************/

/****************************************************************************
Идея:

Создаем два массива для массы и веса, сортируем. Далее по нарастающему весу
и силе сторим башню. Такая логика решения алгоритма применима из-за того, что
в условии оговорено, что если атлет весит больше, значит он сильнее. Таким
образом, не произойдет ситуации, что мы потеряем соотношение массы и силы
атлетов прри их отдельной сортировке. Однозначно мы не сможем установить при
равной массе и разной силе (или и равной силе), но для решения задачи в этом нет
необходимости.
****************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>


int main() {

    std::vector<long> weight;
    std::vector<long> power;

    long m, p;
    while(scanf("%ld %ld", &m, &p) == 2) {
        weight.push_back(m);
        power.push_back(p);
    }

    std::sort(weight.begin(), weight.end());
    std::sort(power.begin(), power.end());

    long curMass = weight[0]; //счетчик массы башни
    long curHeight = 1; // высота башни
    for(size_t i = 1; i < weight.size(); ++i) {
        if( power[i] >= curMass ) {
            curMass += weight[i];
            curHeight++;
        }
    }
    std::cout << curHeight;

    return 0;
}
