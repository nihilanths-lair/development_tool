// <!-- Encoding: Windows-1251 -->

#include <locale.h>
//#include <stdio.h>
#include <conio.h>

#include "actuator/driv3r.c"
#include "compiler/frontend/parser.c"

int main()
{
    setlocale(0, "");
    //SetConsoleCP(1251);       // Кодировка ввода
    //SetConsoleOutputCP(1251); // Кодировка вывода
    printf("\n   ___________________________");
    printf("\n  |                           |");
    printf("\n  |  Мета-платформа запущена  |");
    printf("\n  |___________________________|");
    putchar('\n');
    parser();
    driv3r();
    printf("\n Ожидание ввода команды ...");
    printf("\n\n Нажмите любую клавишу для выхода из приложения ...");
    _getch();
    return 0;
}