﻿#include <iostream>
#include <fstream>

#define MAX_STACK_SIZE 50       //Макс размер стека

using namespace std;

int t;                          //индекс в стеке
char stack[MAX_STACK_SIZE];     //стек
void init();                    //инициализация
void Push(int);
int Pop();
int Top();
bool IsEmpty();
void lines();

int main()
{
    ifstream fin;               //чтение файла
    fin.open("C:/Users/danil/Desktop/Lab1/start.txt");
    if (!fin.is_open())
        cout << "Error! File can't be opened\n\n";
    ofstream fout;
    fout.open("C:/Users/danil/Desktop/Lab1/fin.txt");
    if (!fout.is_open())
        cout << "Error! File can't be opened\n\n";
    else
    {
        int a = 0; // переменная для чтения из файла и занесения числа в массив
        init(); // инициализация массива

        while (true && !fin.eof()) // пока не конец файла и нет команды break цикл крутится
        {
            fin >> a; // считываем число из файла
            Push(a); //вносим в стэк (т.к. стэк был пустой мы ни с чем не сравниваем)
            while (!fin.eof()) // цикл, где идет сравнение, занесение в стэк и вывод стэка (крутится пока не дойдет до конца файла)
            {
                fin >> a; // берем следующее число из файла
                if (a >= Top()) // сравниваем его с вершиной стэка (с последним числом занесенным в стэк)
                    Push(a); // если новое число больше или равно вершине стэка, то заносим его в стэк и оно становится новой вершиной (т.к. было занесено в стэк последним)
                else if (a < Top()) // если же следующее число меньше чем вершина стэка, то получается что последовательность у нас прерывается, соответсвенно переходим к выводу и опустошению  стэка
                {
                    while (!IsEmpty()) // пока у нас стэк не пустой мы крутим цикл
                    {
                        int vivod = 0; // переменная нужна только для того, чтоб можно было вывести число и в консоль и в файл
                        vivod = Pop(); // берем число из стэка
                        cout << vivod << " "; //выводим его в консоль
                        fout << vivod << " "; // выводим его в файл
                    }                                       //тут у нас пустой стэк, поэтому
                    Push(a); //заносим в него число, которое осталось после сравнения (которое и прерывает последовательность) тем самым начиная новую последовательность заносить в стэк
                    cout << endl; // т.к. стэки должны быть разграничены по строкам, то преносим указатель на новую строку и в консоли
                    fout << endl; // и в файле
                }
            } //это у нас продолжается до конца файла, но т.к. последнее число не с чем сранить, то у нас прога не переходит к выводу последнего стэка
            while (!IsEmpty()) //поэтому принудительно выводим его (алгоритм один в один как и раньше и переделывается без переменной как и раньше)
            {
                int vivod = 0;
                vivod = Pop();
                cout << vivod << " ";
                fout << vivod << " ";
            }
            break; //т.к. все данные выведены и работа закончена выходим из общего цикла
        }
    }
    return 0;
}

void init() { t = -1; }         //Инициализация стека (-1)

void Push(int a)                //Добавление элемента в стек
{
    if (t == MAX_STACK_SIZE)    // если стек заполнен - выдает ошибку
    {
        cout << "Error! Stack is full\n" << t << endl;
        exit(EXIT_FAILURE);
    }
    else
        stack[++t] = a;
}

int Pop()                       //взять элеменет из стека
{
    IsEmpty();
    if (t == -1)
    {
        cout << "Attempt to read from an empty stack\n"; //выдает ошибку, если идет попытка взятия пустого стека
        //exit(EXIT_FAILURE);
    }
    else
        return (stack[t--]);
}

int Top()                       //нахождение верхнего элеменета
{
    if (!IsEmpty())             //Если стек не пустой, то мы обращаемся к самому верхнему его элементу
        return (stack[t]);
    else
        return EOF;
}

bool IsEmpty() { return(t == -1); }     //Проверка на пустоту стека