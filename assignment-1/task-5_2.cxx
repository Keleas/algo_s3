//
// Решение предполагает использование стека.
// Способ реализации стека может быть любым (список/динамический массив).
//

/****************************************************************************

Задача 5_2. Стековые анаграммы

Пара слов называется стековой анаграмой, если одно слово можно получить
из другого, проведя последовательность стековых операций с его буквами
(взять очередную букву исходного слова и поместить ее в стек; взять
букву из стека и добавить ее в конец выходного слова).

Для заданной пары слов требуется определить, можно ли выполнить
последовательность стековых операций, переводящую первое слово во
второе. Все буквы в слове различные.

Длина анаграммы ≤ 10000.

*Формат входных данных.* Пара слов, являющихся анаграммой.

*Формат выходных данных.* **YES**, если последовательность стековых
операций существует и **NO** в противном случае.

  in         | out
  -----------|-----
  STOL SLOT  | YES
  ABC CAB    | NO

****************************************************************************/


//бежим сразу по двум словам и проверяем на наличие совпадения букв,
//если расхождение, тогда запихиваем все букву в стек, нет - оставляем на месте
// по двум словам я буду бегать до тех пор пока не смгу получить искомое слово,
//т.е. нет ограничения на количество итераций пробежки по слову
//Херовый код...

#include <stdio.h>
#include <string.h>

bool GenerateChild(char *source_alphabet, size_t alphabet_size, char *source_stack, char *source_result, bool to_stack, char *target) {
    char *alphabet = new char[alphabet_size];//исходное слово
    char *stack = new char[alphabet_size];//стек изначально пуст
    char *result = new char[alphabet_size];//2 стек изначально пуст нужен, чтобы перевернуть первый стек для правльной проверки с target

    memcpy(alphabet, source_alphabet, alphabet_size *  sizeof(char));   // выделение памяти и копирование
    memcpy(stack, source_stack, alphabet_size *  sizeof(char));
    memcpy(result, source_result, alphabet_size *  sizeof(char));

    size_t alphabet_front_index = 0;
    while (!alphabet[alphabet_front_index] && alphabet_front_index < alphabet_size) alphabet_front_index++; // первый символ в слове
    //он заполняет нулями места, которые пихнул в стек, поэтому он пропустит эти места в исходном слове
    size_t stack_top_index = 0;
    while (stack[stack_top_index]) stack_top_index++; // это он так врехушку стека берет в свем недостеке

    size_t result_back_index = 0;
    while (result[result_back_index]) result_back_index++; // верхушка стека result

    if (to_stack) { // если в стеке
        stack[stack_top_index] = alphabet[alphabet_front_index]; // кидаем в стек букву
        alphabet[alphabet_front_index] = 0; // и зануляем ее в слове
    } else {//не в стеке
        result[result_back_index] = stack[--stack_top_index]; // переворачиваем
        stack[stack_top_index--] = 0;
    }
    //если это не конец слова, то запускаем снова
    if (alphabet_front_index < alphabet_size && GenerateChild(alphabet, alphabet_size, stack, result, true, target)) {
        return true;
    } else if (stack[stack_top_index] && GenerateChild(alphabet, alphabet_size, stack, result, false, target)) {
        return true;
    }

    bool correct = true;

    for (size_t i = 0; i < alphabet_size; i++) {
        if (result[i] != target[i]) {
            correct = false;
            break;
        }
    }

    return correct;
}

int main() {
    char *source = new char[64];
    char *target = new char[64];

    scanf("%s %s", source, target);

    size_t length = strlen(source);

    char *stack = new char[length];
    char *result = new char[length];

    stack[0] = 0;

    if (GenerateChild(source, length, stack, result, true, target)) {
        puts("YES");
    } else {
        puts("NO");
    }

    return 0;
}
