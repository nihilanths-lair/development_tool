void driv3r()
{
    char memory[] =
    {
        0
    };
    void * opcodes[ 0x100 ] =
    {
        [0 ... 0xFF] = &&__1
    };
    goto * opcodes[* memory];
    __1:
    {
        printf(" logical_opcode_%u | %s ; %s", 1, "HLT", "Прекратить выполнение каких-либо инструкций");
        return;
    }
}