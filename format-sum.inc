/*
*
*   - Author: jrius ( vk.com/s.fridom | t.me/dcapybarov ) -
*   - Include: format-sum
*   - ������ ���������� �� ������ ����������� 3.10.8 -
*
*   - ������ ������������� ��������� ������� ��� ������ � �������:
*
*       * FormatNumberWithDots(input_value, format_number[] = ".") - ����������� �����, �������� ����������� ����� ���������.
*           - input_value � �����, ������� ����� ��������� �� �����. [!] ������������ ��������
*           - format_number � ������-�����������. [!] ��������������
*
*       * ������:
*           - FormatNumberWithDots(2147483647);
*
*           - input_value: 2_147_483_647
*           - return: 2.147.483.647 (������� �������)
*       
*       * FormatNumShort(input_value) - ����������� ������� ����� � ������� ����� (����������� �����������: ����, ���, ���).
*           - input_value � ����� ��� ��������������. [!] ������������ ��������
*       
*       * ������: 
*           - FormatNumShort(2147483647);
*
*           - input_value: 2_147_483_647
*           - return: 2 ���� 147 ��� 483 ��� (������� �������)
*
*       * CalculatePercentage(input_value, procent) - ��������� ������� �� ��������� �����.
*           - input_value � �������� �����, �� �������� ��������� �������. [!] ������������ ��������
*           - procent � �������, ������� ����� ���������. [!] ������������ ��������
*
*       * ������: 
*           - CalculatePercentage(1500, 5);
*
*           - input_value: 1500
*           - procent: 5
*           - return: 75 (������� �������)
*
*           - ������������� � ����������:  
*               new price = 1500,
*                   discount = CalculatePercentage(price, 5),
*                   final_price = price - discount;
*
*       * GetAverage(...) - ������ ������� ������� ������� ����� ����� ������� 
*           ... - ������������ �������� �������� ���������� ��� �����.
*       
*       * ������:
*           - GetAverage(400, 600, 800);
*           
*           ... : 400 600 800
*           return: 600 (������� �������)
*
*           - GetAverage(5000, 600, 15000);
*           
*           ... : 5000, 600, 15000
*           return: 6866 (������� �������)
*
*           - GetAverage(5000, 600);
*           
*           ... : 5000, 600
*           return: 2800 (������� �������)
*      
*   - ����������:
*      [1] � �������� ������ _ � ������ �������� ������ ��� ��������������� � �� ������ �� ������ �������.
*      [2] ��� ������� ���������� ��������� ��� ��������� ��������� �����.
*      [3] ����� ���������� � ������ �������, ���������� ����������� ������ � ����� � ���������: pawno/include .
*      [4] � ���� ����������: #include <format_sum> ��� #include format_sum .
*
*/

const f_MAX_SIZE_FORMAT_NUMBER = 16;
const f_MAX_VALUE_NUMBER = 3;

static const levels[][16] = {"����", "���", "���", " "};
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
        printf("[Error] GetAverage | ������ ������� �������� ������� 2 ������������ ���������! | this function use min 2 args.");
        return 0;
    }

    new sum;

    for new i; i < num; i++ do
    {
        sum += getarg(i);
    }

    return sum / num;
}




