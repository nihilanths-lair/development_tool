// <!-- Encoding: Windows-1251 -->

#include <locale.h>
#include <conio.h>

#include "actuator/driv3r.c"
#include "compiler/frontend/parser.c"

int main(int argc, char *argv[])
{
    setlocale(0, "");
    //SetConsoleCP(1251);       // Кодировка ввода
    //SetConsoleOutputCP(1251); // Кодировка вывода
    printf(  "  ___________________________");
    printf("\n |                           |");
    printf("\n |  Мета-платформа запущена  |");
    printf("\n |___________________________|");
    putchar('\n');
    printf("\n argc = %u", argc);
    for (int i = 0; i < argc; i++) printf("\n argv[%u] = %s", i, argv[i]);
    putchar('\n');
    parser();
    //printf("\n 1. Загрузка пакета actuator/driv3r.c");
    __loop:
    printf("\n 1. Мета-платформа передала управление подпрограмме driv3r из каталога actuator");
    while (driv3r()) // if (driv3r())
    {
        printf("\n 2. Подпрограмма driv3r из каталога actuator вернула управление мета-платформе");
        goto __loop;
    }
    printf("\n 2. Подпрограмма driv3r из каталога actuator вернула управление мета-платформе");
    //printf("\n Ожидание ввода команды от пользователя ...");
    printf("\n  ____________________________________");
    printf("\n |                                    |");
    printf("\n |  Завершение работы мета-платформы  |");
    printf("\n |____________________________________|");
    printf("\n\n Нажмите любую клавишу для выхода из приложения ...");
    _getch();
    return 0;
}