#include <locale.h>

#include "actuator/driv3r.c"
#include "compiler/frontend/parser.c"

int main()
{
    setlocale(0, "");
    parser();
    driv3r();
    putchar('\n');
    return 0;
}