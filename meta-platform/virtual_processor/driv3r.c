#include <stdio.h>

void driv3r()
{
    unsigned char memory[0x100] = {0};
    FILE * fp = fopen("virtual_processor/meta_language", "r");
    if (!fp)
    {
        printf("\n /!\\: Не удалось открыть файл ...");
        return;
    }
    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    for (unsigned short i = 0; i < file_size; i++) printf("\n [%+2u] = %02X", i+1, memory[i]);
    putchar('\n');
    unsigned char ascii = 0;
    for (unsigned char i = 0; fscanf(fp, "%hhx", &memory[i]) != EOF; i++, ascii++) {}
    fclose(fp);
    for (unsigned short i = 0; i < ascii; i++) printf("\n [%+2u] = %02X", i+1, memory[i]);
    putchar('\n');
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