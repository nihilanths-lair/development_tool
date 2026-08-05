void driv3r()
{
    unsigned char memory[] =
    {
        0x01, // 1
        0x01, // 2
        0x01, // 3
        0x01, // 4
        0x01, // 5
        0x01, // 6
        0x01, // 7
        0x01, // 8
        0x01, // 9
        0x01, // 10
        0x01, // 11
        0x01, // 12
        0x01, // 13
        0x01, // 14

        0x00  // 15
    };
    unsigned char program_counter = 0;
    void * opcodes[ 0x100 ] =
    {
        [0         ] = &&__1,
        [1         ] = &&__2,
        [2 ... 0xFF] = &&__3
    };
    //unsigned char number_of_clock_cycles = 0; // Количество тактов
    //printf(" {{ TRACING }} logical_opcode_%u | %s ; %s", * memory, "-", "-");
    goto ** (opcodes + * (memory + program_counter));
    __1:
    {
        //number_of_clock_cycles++;
        printf("\n logical_opcode_%u | %s ; %s", 1, "HLT / STOP", "Прекратить выполнение каких-либо инструкций");
        return;
    }
    __2:
    {
        //number_of_clock_cycles++;
        printf("\n logical_opcode_%u | %s ; %s", 2, "NOP / SKIP / IGNORE / STEP_FORWARD", "Пропустить / Игнорировать / Сделать шаг вперёд");
        program_counter++;
        goto ** (opcodes + * (memory + program_counter));
    }
    __3:
    {
        //number_of_clock_cycles++;
        printf("\n logical_opcode_%u | %s ; %s", 3, "-", "(Неизвестный / Несуществующий) опкод");
        return;
    }
    //printf(" {{ TRACING }} logical_opcode_%u | %s ; %s", * memory, "-", "-");
}