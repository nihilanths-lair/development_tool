#include <stdio.h>
#include <stdint.h>

void driv3r()
{
    // Гибридная модель памяти
    uint8_t m8[0x100] = {0}; // для хранения строк
    uint64_t m64[0x100] = {0}; // для хранения чисел
    uint64_t pc = 0;

    // --- НАЧАЛО СТАРТОВОГО ИМПУЛЬСА ---
    // 1. Копируем строку прямо внутрь массива m8, начиная с 10-й ячейки
    ///sprintf((char *) &m8[10], "computing_module/meta_language");

    // 2. Передаем параметры в m64 для службы открытия файла
    m64[0] = 0; // Открыть файл
    printf("\n m64[0] = %p", &m64[0]);
    printf("\n m64[0] = %02X - %u\n", m64[0], m64[0]);
    ///m64[1] = 10;  // Аргумент 1: Адрес начала строки с именем файла внутри m8

    m64[1] = (uint64_t) "computing_module/meta_language"; // Путь к файлу (его название)
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
    m8[0] = 1; // SYS / INT
    m64[0] = 1; // Получить символ с файла (перетирает предыдущее состояние...)
    m8[1] = 1; // SYS / INT
    // --- КОНЕЦ СТАРТОВОГО ИМПУЛЬСА ---

    // Таблица опкодов мета-языка
    static void *opcodes[0x100] =
    {
        [0] = &&__1,
        [1] = &&__2,
        [2] = &&__3,
        [3 ... 0xFF] = &&__4
    };
    // Векторная таблица системных служб хоста
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
        printf("\n logical opcode: 1 | HLT / STOP ; Прекратить выполнение каких-либо инструкций");
        return;
    }
    __2:
    {
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
    __3:
    {
        printf("\n logical_opcode_3 | MOV MEM64 <- IMM64 ; Перемещение");
        m64[pc+1] = pc+2;
        pc += 3;
        goto *opcodes[m8[pc]];
    }
    __4:
    {
        printf("\n logical_opcode_4 | - ; (Неизвестный / Несуществующий) опкод");
        return;
    }
    //printf(" {{ TRACING }} logical_opcode_%u | %s ; %s", * memory, "-", "-");
}
/*
//number_of_clock_cycles++;
//printf("\n logical_opcode_%u | %s ; %s", 2, "NOP / SKIP / IGNORE / STEP_FORWARD", "Пропустить / Игнорировать / Сделать шаг вперёд");
*/