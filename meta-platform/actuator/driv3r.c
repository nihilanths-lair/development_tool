// <!-- Encoding: Windows-1251 -->

#include <stdio.h>
#include <stdint.h>

#define macro__display_debug_information \
 printf("\n          _________________________"); \
 printf("\n ________/ Служебные ячейки памяти \\________"); \
 putchar('\n'); \
 printf("\n m64[0] = %llu", m64[0]); \
 printf("\n m64[1] = %llu", m64[1]); \
 printf("\n m64[2] = %llu", m64[2]); \
 printf("\n m64[3] = %llu", m64[3]); \
 printf("\n m64[4] = %llu", m64[4]); \
 printf("\n ___________________________________________");

char driv3r()
{
    // Гибридная модель памяти
    uint8_t m8[0x100] = {0}; // для хранения строк
    uint64_t m64[0x100] = {0}; // для хранения чисел
    uint8_t pc = 0;

    // --- НАЧАЛО СТАРТОВОГО ИМПУЛЬСА ---
    // 1. Копируем строку прямо внутрь массива m8, начиная с 10-й ячейки
    ///sprintf((char *) &m8[10], "computing_module/meta_language");

    // 2. Передаем параметры в m64 для службы открытия файла
    m64[0] = 0; // Открыть файл
    printf("\n m64[0] = %p", &m64[0]);
    printf("\n m64[0] = %02X - %u\n", m64[0], m64[0]);
    ///m64[1] = 10;  // Аргумент 1: Адрес начала строки с именем файла внутри m8

    m64[1] = (uint64_t) "actuator/meta_language"; // Путь к файлу (его название)
    for (int i = 0; m64[1+i] != 0; i++)
    {
        printf("\n m64[%u] = %p", 1+i, &m64[1+i]);
        printf("\n m64[%u] = %02X - %u\n", 1+i, m64[1+i], m64[1+i]);
    }
    m64[2] = (uint64_t) "r"; // Режим открытия файла (только на чтение)
    for (int i = 0; m64[2+i] != 0; i++)
    {
        printf("\n m64[%u] = %p", 2+i, &m64[2+i]);
        printf("\n m64[%u] = %02X - %u\n", 2+i, m64[2+i], m64[2+i]);
    }
    m8[0] = 0x01; // SYS / INT
    //m64[0] = 1; // Получить символ с файла (перетирает предыдущее состояние...)
    // чтобы не перетирало, перепишем код программы
    m8[1] = 0x02; // mem64[0] = imm64 ; поместить число в конкретно фиксированную (служебную) ячейку памяти
    // само число: 1 (порядок байт: little-endian, от старшего к младшему)
    m8[2] = 0x00;
    m8[3] = 0x00;
    m8[4] = 0x00;
    m8[5] = 0x00;
    m8[6] = 0x00;
    m8[7] = 0x00;
    m8[8] = 0x00;
    m8[9] = 0x01;

    m8[10] = 1; // SYS / INT
    // --- КОНЕЦ СТАРТОВОГО ИМПУЛЬСА ---

    // Таблица опкодов мета-языка
    static void *opcodes[0x100] =
    {
        [0] = &&__1,
        [1] = &&__2,
        [2] = &&__3,
        [3 ... 0xFF] = &&__4
    };
    // Векторная таблица системных служб хоста / host service
    static void *ivt[0x100] =
    {
        [0] = &&ivt_1, // Открыть файл
        [1] = &&ivt_2, // Считать ascii-символ (байт)
        [2] = &&ivt_3  // Закрыть файл
    };
    //unsigned char number_of_clock_cycles = 0; // Количество тактов
    //printf(" {{TRACING}} logical opcode: %u", m8[pc]);
    //return;
    goto *opcodes[m8[pc]];
    __1:
    {
        macro__display_debug_information;
        printf("\n logical opcode: 1 | HLT / STOP ; Прекратить выполнение каких-либо инструкций");
        return 0;
    }
    __2:
    {
        macro__display_debug_information;
        printf("\n logical opcode: 2 | SYS / INT ; Системный вызов хоста");
        goto *ivt[m64[0]];
        ivt_1:
        {
            printf("\n logical address: ivt_1");
            //char *filename = (char *) &m8[m64[1]]; // Достаем число 10 из m64[1] и получаем прямой указатель на текст внутри m8
            char *file_name = (char *) m64[1];
            printf("\n file_name: %s", file_name);

            char *mode = (char *) m64[2];
            printf("\n mode: %s", mode);

            m64[3] = (uint64_t) fopen(file_name, mode);
            printf("\n m64[3]: %llu", m64[3]);

            pc += 1;
            goto *opcodes[m8[pc]];
        }
        ivt_2:
        {
            printf("\n logical address: ivt_2");
            FILE *fp = (FILE *) m64[3];
            m64[4] = fp ? (uint64_t) fgetc(fp) : (uint64_t) - 1;
            printf("\n m64[4]: %llu - %c", m64[4], (char *) m64[4]);
            pc += 1;
            goto *opcodes[m8[pc]];
        }
        ivt_3:
        {
            printf("\n logical address: ivt_3");
            FILE *fp = (FILE *) m64[3];
            if (fp) fclose(fp);
            pc += 1;
            goto *opcodes[m8[pc]];
        }
    }
    __3: // mem64[0] = imm64 ; поместить число в конкретно фиксированную (служебную) ячейку памяти
    {
        macro__display_debug_information;
        printf("\n logical opcode: 3");
        m64[0] = // само число (порядок байт: big-endian, от младшего к старшему)
         ((uint64_t) m8[pc+1]) |
         ((uint64_t) m8[pc+2]<<8) |
         ((uint64_t) m8[pc+3]<<16) |
         ((uint64_t) m8[pc+4]<<24) |
         ((uint64_t) m8[pc+5]<<32) |
         ((uint64_t) m8[pc+6]<<40) |
         ((uint64_t) m8[pc+7]<<48) |
         ((uint64_t) m8[pc+8]<<56)
        ;
        printf("\n | (be) m64[0] = %llu | %02X %02X %02X %02X %02X %02X %02X %02X", m64[0],
         m8[pc+8], m8[pc+7], m8[pc+6], m8[pc+5], m8[pc+4], m8[pc+3], m8[pc+2], m8[pc+1]
        );
        m64[0] = // само число (порядок байт: little-endian, от старшего к младшему)
         ((uint64_t) m8[pc+1]<<56) |
         ((uint64_t) m8[pc+2]<<48) |
         ((uint64_t) m8[pc+3]<<40) |
         ((uint64_t) m8[pc+4]<<32) |
         ((uint64_t) m8[pc+5]<<24) |
         ((uint64_t) m8[pc+6]<<16) |
         ((uint64_t) m8[pc+7]<<8) |
         ((uint64_t) m8[pc+8])
        ;
        printf("\n | (le) m64[0] = %+17llu | %02X %02X %02X %02X %02X %02X %02X %02X", m64[0],
         m8[pc+1], m8[pc+2], m8[pc+3], m8[pc+4], m8[pc+5], m8[pc+6], m8[pc+7], m8[pc+8]
        );
        pc += 9;
        goto *opcodes[m8[pc]];
    }
    __4:
    {
        macro__display_debug_information;
        printf("\n logical_opcode_4 | - ; (Неизвестный / Несуществующий) опкод");
        return 0;
    }
    //printf(" {{ TRACING }} logical_opcode_%u | %s ; %s", * memory, "-", "-");
}
/*
//number_of_clock_cycles++;
//printf("\n logical_opcode_%u | %s ; %s", 2, "NOP / SKIP / IGNORE / STEP_FORWARD", "Пропустить / Игнорировать / Сделать шаг вперёд");
*/