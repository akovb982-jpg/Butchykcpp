/*
 * Розділ 4, задача 10 (аудиторна).
 * Знайдіть машинний нуль для дійсного типу float вашого компілятора, тобто
 * таке число типу float a > 0, що 1 + a = 1 буде істиною. Як перевірити
 * це значення, користуючись стандартною бібліотекою?
 * Вказівка: в циклі виконуйте ділення a на 2 доки 1 + a != 1.
 */
#include <stdio.h>
#include <float.h>

int main(){
    /* volatile - щоб компілятор не тримав проміжні значення в регістрах
       підвищеної точності, а справді рахував у float */
    volatile float a = 1.0f, sum;
    do {
        a = a / 2;
        sum = 1.0f + a;
    } while (sum != 1.0f);

    printf("Machine zero for float: a = %e (1 + a == 1)\n", a);
    printf("Previous value 2a = %e is the smallest power of 2 with 1 + 2a != 1\n", 2 * a);
    /* У стандартній бібліотеці <float.h>: FLT_EPSILON - найменше x, що 1 + x != 1 */
    printf("FLT_EPSILON from <float.h> = %e\n", FLT_EPSILON);
    return 0;
}
