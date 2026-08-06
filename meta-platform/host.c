#include "computing_module/driv3r.c"
#include "compiler/frontend/parser.c"

int main()
{
    parser();
    driv3r();
    putchar('\n');
    return 0;
}