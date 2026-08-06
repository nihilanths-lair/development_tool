#include <stdio.h>
#include <stdint.h>

void driv3r()
{
    // гибридная модель памяти
    uint8_t m8[0x100] = {0}; // для хранения строк
    uint64_t m64[0x100] = {0}; // для хранения чисел
    //uint64_t pc;

    FILE * fp = fopen("virtual_processor/meta_language", "r");
    if (!fp)
    {
        printf("\n /!\\: Не удалось открыть файл ...");
        return;
    }

    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    unsigned char ascii = 0;
    for (unsigned char i = 0; fscanf(fp, "%hhx", &m8[i]) != EOF; i++, ascii++) {}
    fclose(fp);
    for (unsigned short i = 0; i < ascii; i++) printf("\n [%+2u] = %02X", i+1, m8[i]);
    putchar('\n');
    unsigned char program_counter = 0;
    void *opcodes[0x100] =
    {
        [0         ] = &&__1,
        [1         ] = &&__2,
        [2 ... 0xFF] = &&__3
    };
    //unsigned char number_of_clock_cycles = 0; // Количество тактов
    //printf(" {{ TRACING }} logical_opcode_%u | %s ; %s", * m8, "-", "-");
    goto *opcodes[m8[program_counter]];
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
        goto *opcodes[m8[program_counter]];
    }
    __3:
    {
        //number_of_clock_cycles++;
        printf("\n logical_opcode_%u | %s ; %s", 3, "-", "(Неизвестный / Несуществующий) опкод");
        return;
    }
    //printf(" {{ TRACING }} logical_opcode_%u | %s ; %s", * memory, "-", "-");
}