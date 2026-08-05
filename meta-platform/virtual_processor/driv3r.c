void driv3r()
{
    unsigned char memory[] =
    {
        0
    };
    void * opcodes[ 0x100 ] =
    {
        [0         ] = &&__1,
        [1 ... 0xFF] = &&__2
    };
    printf(" [<<{ TRACING }>>] logical_opcode_%u | %s ; %s", * memory, "-", "-");
    goto * (opcodes + * memory);
    __1:
    {
        printf(" logical_opcode_%u | %s ; %s", 1, "HLT", "Прекратить выполнение каких-либо инструкций");
        return;
    }
    __2:
    {
        printf(" logical_opcode_%u | %s ; %s", 2, "-", "(Неизвестный / Несуществующий) опкод");
        return;
    }
    //printf(" logical_opcode_%u | %s ; %s", * memory, "-", "-");
}