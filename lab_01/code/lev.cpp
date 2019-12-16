#include <iostream>
#include <cstring>
#include <cmath>

#define MAX_LEN_STRING 80

using namespace std;

int my_min(int a, int b, int c)
{
    int min;
    if (a < b)
    {
        if (a < c)
        {
            min = a;
        }
        else
        {
            min = c;
        }
    }
    else
    {
        if (b < c)
        {
            min = b;
        }
        else
        {
            min = c;
        }
    }

    return min;
}

int my_min(int a, int b, int c, int d)
{
    return std::min(std::min(std::min(a, b), c), d);
}

int levensteinRecursiveDistance(char *str1, int lenStr1, char *str2, int lenStr2)
{
    bool isNotSame;
    int result;

    if (lenStr1 == 0)
    {
        return lenStr2;
    }
    if (lenStr2 == 0)
    {
        return lenStr1;
    }

    isNotSame = str1[lenStr1 - 1] != str2[lenStr2 - 1];

    result = my_min(levensteinRecursiveDistance(str1, lenStr1 - 1, str2, lenStr2) + 1, levensteinRecursiveDistance(str1, lenStr1, str2, lenStr2 - 1),
            levensteinRecursiveDistance(str1, lenStr1 - 1, str2, lenStr2 - 1) + isNotSame);

    if (lenStr1 > 1 && lenStr2 > 1)
    {
        if (str1[lenStr1 - 1] == str2[lenStr2 - 2] && str1[lenStr1 - 2] == str2[lenStr2 - 1])
        {
            result = std::min(result, levensteinRecursiveDistance(str1, lenStr1 - 2, str2, lenStr2 - 2) + 1);
        }
    }

    return result;
}
int levensteinDistance(char *str1, char *str2)
{
    unsigned lenStr1 = strlen(str1);
    unsigned lenStr2 = strlen(str2);
    unsigned rows, columns;
    bool isNotSame;
    int result;

    if (lenStr1 == 0 || lenStr2 == 0)
    {
        return (lenStr1 > lenStr2) ? lenStr1 : lenStr2;
    }

    rows = lenStr1 + 1;
    columns = lenStr2 + 1;

    int *data[2];
    data[0] = new int[columns];
    data[1] = new int[columns];

    for (unsigned i = 0; i < columns; i++)
    {
        data[0][i] = i;
    }

    for (unsigned i = 1; i < rows; i++)
    {
        data[1][0] = data[0][0] + 1;

        for (unsigned j = 1; j < columns; j++)
        {
            isNotSame = (str1[i - 1] != str2[j - 1]) ? 1 : 0;

            data[1][j] = my_min(data[1][j - 1] + 1, data[0][j] + 1, data[0][j - 1] + isNotSame);

            cout << data[1][j] << " ";
        }

        cout << endl;

        std::swap(data[1], data[0]);
    }

    result = data[0][columns - 1];

    delete data[0];
    delete data[1];

    return result;
}

int levensteinDistanceTransposition(char *str1, char *str2)
{
    unsigned lenStr1 = strlen(str1);
    unsigned lenStr2 = strlen(str2);
    unsigned rows, columns;
    bool isNotSameTrans;
    bool isNotSame;
    int result;

    if (lenStr1 == 0 || lenStr2 == 0)
    {
        return (lenStr1 > lenStr2) ? lenStr1 : lenStr2;
    }

    if (lenStr1 < 2 || lenStr2 < 2)
    {
        return levensteinDistance(str1, str2);
    }

    rows = lenStr1 + 1;
    columns = lenStr2 + 1;

    int *data[3];
    data[0] = new int[columns];
    data[1] = new int[columns];
    data[2] = new int[columns];

    for (unsigned i = 0; i < columns; i++)
    {
        data[0][i] = i;
    }

    data[1][0] = 1;

    for (unsigned j = 1; j < columns; j++)
    {
        isNotSame = (str1[0] != str2[j - 1]) ? 1 : 0;

        data[1][j] = my_min(data[1][j - 1] + 1, data[0][j] + 1, data[0][j - 1] + isNotSame);
    }

    for (unsigned i = 2; i < rows; i++)
    {
        data[2][0] = data[1][0] + 1;

        isNotSame = (str1[i - 1] != str2[0]) ? 1 : 0;

        data[2][1] = my_min(data[1][1] + 1, data[2][0] + 1, data[1][0] + isNotSame);

        for (unsigned j = 2; j < columns; j++)
        {
            //isNotSameTrans = ((str1[i - 1] != str2[j - 2]) && (str1[i -2] != str2[j - 1])) ? 1 : 0 ;
            isNotSame = (str1[i - 1] != str2[j - 1]) ? 1 : 0;

            if (((str1[i - 1] == str2[j - 2]) && (str1[i -2] == str2[j - 1])) ? 1 : 0)
            {
                data[2][j] = my_min(data[2][j - 1] + 1, data[1][j] + 1, data[1][j - 1] + isNotSame, data[0][j - 2] + 1);
            }
            else
            {
                data[2][j] = my_min(data[2][j - 1] + 1, data[1][j] + 1, data[1][j - 1] + isNotSame);
            }
        }

        for (int j = 1; j < columns; j++)
        {
            cout << data[1][j] << " ";
        }

        cout << endl;

        std::swap(data[0], data[1]);
        std::swap(data[1], data[2]);
    }

    for (int i = 1; i < columns; i++)
    {
        cout << data[1][i] << " ";
    }

    cout << endl;

    result = data[1][columns - 1];

    delete data[0];
    delete data[1];
    delete data[2];

    return result;
}


int main(int argc, char ** argv)
{
    char str1[MAX_LEN_STRING];
    char str2[MAX_LEN_STRING];
    int flag;
    int result;

    flag = argv[1][0] - '0';

    //cout << "Enter the first string: ";
    cin >> str1;

    //cout << "Enter the second string: ";
    cin >> str2;

    switch(flag)
    {
        case 1:
            result = levensteinDistance(str1, str2);
            break;
        case 2:
            result = levensteinDistanceTransposition(str1, str2);
            //result = 4;
            break;
        case 3:
            result = levensteinRecursiveDistance(str1, strlen(str1), str2, strlen(str2));
            break;
    }

    cout << result << endl;

    return 0;
}

