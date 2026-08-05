void driv3r()
{
    char opcodes[] =
    {
        0
    };
    void * dispatch[0x100] =
    {
        [0 ... 0xFF] = &&__0
    };
    goto * dispatch[ opcodes[0] ];
    __0:
     { return; }
}