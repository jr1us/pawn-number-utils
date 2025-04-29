/*
*
*   - Author: jrius ( vk.com/s.fridom | t.me/dcapybarov ) -
*   - Include: format-sum
*   - Модуль разработан на версии компилятора 3.10.8 -
*
*   - Модуль предоставляет следующие функции для работы с числами:
*
*       * FormatNumberWithDots(input_value, format_number[] = ".") - Форматирует число, добавляя разделители между разрядами.
*           - input_value — Число, которое нужно разделить на части. [!] Обязательный аргумент
*           - format_number — символ-разделитель. [!] Необязательный
*
*       * Пример:
*           - FormatNumberWithDots(2147483647);
*
*           - input_value: 2_147_483_647
*           - return: 2.147.483.647 (Вернула функция)
*       
*       * FormatNumShort(input_value) - Преобразует большое число в краткую форму (сокращённые обозначения: млрд, млн, тыс).
*           - input_value — Число для преобразования. [!] Обязательный аргумент
*       
*       * Пример: 
*           - FormatNumShort(2147483647);
*
*           - input_value: 2_147_483_647
*           - return: 2 млрд 147 млн 483 тыс (Вернула функция)
*
*       * CalculatePercentage(input_value, procent) - Вычисляет процент от заданного числа.
*           - input_value — исходное число, от которого считается процент. [!] Обязательный аргумент
*           - procent — процент, который нужно вычислить. [!] Обязательный аргумент
*
*       * Пример: 
*           - CalculatePercentage(1500, 5);
*
*           - input_value: 1500
*           - procent: 5
*           - return: 75 (Вернула функция)
*
*           - Использование в вычисление:  
*               new price = 1500,
*                   discount = CalculatePercentage(price, 5),
*                   final_price = price - discount;
*
*       * GetAverage(...) - Данная функция считает среднее число между числами 
*           ... - Обязательный аргумент включает минимально два числа.
*       
*       * Пример:
*           - GetAverage(400, 600, 800);
*           
*           ... : 400 600 800
*           return: 600 (Вернула функция)
*
*           - GetAverage(5000, 600, 15000);
*           
*           ... : 5000, 600, 15000
*           return: 6866 (Вернула функция)
*
*           - GetAverage(5000, 600);
*           
*           ... : 5000, 600
*           return: 2800 (Вернула функция)
*      
*   - Примечания:
*      [1] В примерах символ _ в числах добавлен только для удобочитаемости и не влияет на работу функций.
*      [2] Все функции возвращают результат без изменения исходного числа.
*      [3] Чтобы подключить к своему проекту, необходимо переместить инклуд в папку с инклудами: pawno/include .
*      [4] В моде подключить: #include <format_sum> или #include format_sum .
*
*/

const f_MAX_SIZE_FORMAT_NUMBER = 16;
const f_MAX_VALUE_NUMBER = 3;

static const levels[][16] = {"млрд", "млн", "тыс", " "};
static const divisors[] = {1_000_000_000, 1_000_000, 1_000};

stock FormatNumberWithDots(input_value, format_number[] = ".")
{
    new string_value[f_MAX_SIZE_FORMAT_NUMBER], output[f_MAX_SIZE_FORMAT_NUMBER];

    if (input_value < -2_147_483_647 || input_value > 2_147_483_647)
    {
        return string_value;
    }

	new pos = 0, temp;

    format(string_value, sizeof(string_value), "%d", input_value);
    
    for new i = strlen(string_value) - 1, k = 0; i >= 0; i--, k++ do
    {
        output[pos++] = string_value[i];
        
        if(k % 3 == 2 && i != 0)
        {
            output[pos++] = format_number[0];
        }
    }
    
    for new i = 0; i < pos / 2; i++ do
    {
        temp = output[i];

        output[i] = output[pos - 1 - i];
        output[pos - 1 - i] = temp;
    }
    
    return output;
}

stock FormatNumShort(input_value)
{   
    new string_value[64];

    format(string_value, sizeof string_value, "%d", input_value);

    if (strlen(string_value) <= 3)
    {
        format(string_value, sizeof(string_value), "%d$", input_value);
        return string_value;
    }

    new values[f_MAX_VALUE_NUMBER];

    string_value[0] = EOS;

    if (input_value < -2_147_483_647 || input_value > 2_147_483_647)
    {
        string_value = "ERROR_INPUT_VALUE";
        return string_value;
    }

    for new i = 0; i < f_MAX_VALUE_NUMBER; i++ do
    {   
        values[i] = input_value / divisors[i];

        if (values[i] > 0)
        {   
            input_value -= values[i] * divisors[i];

            format(string_value, sizeof string_value , "%s %d %s", string_value, values[i], levels[i]);
        }
    }

    return string_value;
}

stock CalculatePercentage(input_value, procent) 
{   
    return input_value * procent / 100; 
}

stock GetAverage(...) 
{   
    new num = numargs();

    if (!num || num == 1) 
    {    
        printf("[Error] GetAverage | Данная функция содержит минимум 2 обязательный аргумента! | this function use min 2 args.");
        return 0;
    }

    new sum;

    for new i; i < num; i++ do
    {
        sum += getarg(i);
    }

    return sum / num;
}




