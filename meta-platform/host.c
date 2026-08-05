#include "executor/executor.c"
#include "compiler/frontend/parser.c"

int main()
{
    parser();
    executor();
    return 0;
}