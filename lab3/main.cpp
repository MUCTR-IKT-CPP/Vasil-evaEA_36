#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

/*
 * Структура "String" для хранения строк с длиной и указателем на массив символов
 */
struct String {
    int length;           // Длина строки
    char* data;           // Указатель на массив символов строки
};

/*
 * Структура "Employee" для хранения данных о работнике
 * Содержит ФИО и возраст (до 70 лет)
 */
struct Employee {
    string firstName;    // Имя
    string lastName;     // Фамилия
    int age;             // Возраст
};

/*
 * Структура "Banknote" для хранения данных о банкноте
 * Содержит номинал и валюту
 */
struct Banknote {
    int denomination;    // Номинал
    string currency;     // Валюта
};

/*
 * Структура "Shape" для хранения данных о геометрической фигуре
 * Содержит тип фигуры и её размер (до 100 единиц)
 */
struct Shape {
    string type;         // Тип фигуры (круг, квадрат, треугольник)
    int size;            // Размер (не более 100 единиц)
};

/*
 * Генерация случайного символа из английского алфавита
 * return: случайный символ (a-z)
 */
char generateRandomChar() {
    return 'a' + rand() % 26;
}

/*
 * Генерация случайной строки заданной длины
 * Параметры:
 *   length: длина строки (по умолчанию 50)
 * return: строка, содержащая случайные символы
 */
string generateRandomString(int length = 50) {
    string str(length, ' ');
    for (int i = 0; i < length; ++i) {
        str[i] = generateRandomChar();
    }
    return str;
}

/*
 * Инициализация массива структур типа "String" случайными строками
 * Параметры:
 *   arr: массив структур String
 *   n: количество строк в массиве
 */
void initializeStringArray(String* arr, int n) {
    for (int i = 0; i < n; ++i) {
        arr[i].length = 50;  // Длина каждой строки фиксирована на 50 символов
        arr[i].data = new char[50];
        for (int j = 0; j < 50; ++j) {
            arr[i].data[j] = generateRandomChar();
        }
    }
}

/*
 * Генерация случайного работника с именем, фамилией и возрастом
 * return: структура Employee с заполненными полями
 */
Employee generateRandomEmployee() {
    const string firstNames[] = {"John", "Jane", "Paul", "Anna", "Mark"};
    const string lastNames[] = {"Smith", "Doe", "Brown", "Johnson", "White"};
    int age = rand() % 70 + 1;  // Возраст от 1 до 70

    Employee emp;
    emp.firstName = firstNames[rand() % 5];
    emp.lastName = lastNames[rand() % 5];
    emp.age = age;

    return emp;
}

/*
 * Генерация случайной банкноты с номиналом и валютой
 * return: структура Banknote с заполненными полями
 */
Banknote generateRandomBanknote() {
    const int denominations[] = {1, 5, 10, 20, 50, 100, 500};
    const string currencies[] = {"USD", "EUR", "GBP", "RUB"};

    Banknote bn;
    bn.denomination = denominations[rand() % 7];  // Выбираем случайный номинал
    bn.currency = currencies[rand() % 4];         // Выбираем случайную валюту

    return bn;
}

/*
 * Генерация случайной геометрической фигуры с типом и размером
 * return: структура Shape с заполненными полями
 */
Shape generateRandomShape() {
    const string types[] = {"circle", "square", "triangle"};
    int size = rand() % 100 + 1;  // Размер от 1 до 100

    Shape sh;
    sh.type = types[rand() % 3];  // Выбираем случайный тип фигуры
    sh.size = size;

    return sh;
}

/*
 * Подсчет количества вхождений символа в массиве строк std::string
 * Параметры:
 *   arr: массив строк std::string
 *   symbol: символ для поиска
 * return: количество вхождений символа
 */
int countCharOccurrences(const vector<string>& arr, char symbol) {
    int count = 0;
    for (const auto& str : arr) {
        for (char c : str) {
            if (c == symbol) {
                ++count;
            }
        }
    }
    return count;
}

/*
 * Поиск самой длинной последовательности повторяющихся символов в массиве строк
 * Параметры:
 *   arr: массив строк std::string
 * return: самая длинная последовательность символов в виде строки
 */
string findLongestRepetition(const vector<string>& arr) {
    string longestSequence;
    for (const auto& str : arr) {
        int currentLength = 1;
        string currentSequence(1, str[0]);
        for (int i = 1; i < str.length(); ++i) {
            if (str[i] == str[i - 1]) {
                currentSequence += str[i];
                currentLength++;
            } else {
                currentLength = 1;
                currentSequence = str[i];
            }

            if (currentSequence.length() > longestSequence.length()) {
                longestSequence = currentSequence;
            }
        }
    }
    return longestSequence;
}

/*
 * Конкатенация всех строк в массиве в одну итоговую строку
 * Параметры:
 *   arr: массив строк std::string
 * return: итоговая строка
 */
string concatenateStrings(const vector<string>& arr) {
    string result;
    for (const auto& str : arr) {
        result += str;
    }
    return result;
}

/*
 * Подсчет количества вхождений подстроки в массиве строк
 * Параметры:
 *   arr: массив строк std::string
 *   substring: подстрока для поиска
 * return: количество вхождений подстроки
 */
int countSubstringOccurrences(const vector<string>& arr, const string& substring) {
    int count = 0;
    for (const auto& str : arr) {
        size_t pos = str.find(substring);
        while (pos != string::npos) {
            ++count;
            pos = str.find(substring, pos + 1);
        }
    }
    return count;
}

/*
 * Основная функция программы
 * Выполняет взаимодействие с пользователем и выводит результаты генерации данных
 */
int main() {
    srand(static_cast<unsigned>(time(0)));  // Инициализация генератора случайных чисел

    // Получаем количество строк от пользователя
    int N;
    cout << "Enter the number of lines N: ";
    cin >> N;

    // Создание массива структур String + выделение памяти
    String* stringArray = new String[N];
    initializeStringArray(stringArray, N);

    // Создание массива std::string и его заполнение случайными строками
    vector<string> stdStringArray(N);
    for (int i = 0; i < N; ++i) {
        stdStringArray[i] = generateRandomString();
    }

    // Подсчет повторений символа
    char symbol;
    cout << "Enter a character to count its repetitions: ";
    cin >> symbol;
    int count = countCharOccurrences(stdStringArray, symbol);
    cout << "The number of repetitions of the symbol '" << symbol << "' in the array: " << count << endl;

    // Поиск самой длинной повторяющейся последовательности
    string longestRepetition = findLongestRepetition(stdStringArray);
    cout << "The longest sequence of repeated characters: " << longestRepetition << endl;

    // Складывание всех строк в одну итоговую строку
    string concatenatedString = concatenateStrings(stdStringArray);
    cout << "Concatenation of all strings: " << concatenatedString << endl;

    // Поиск вхождений подстроки
    string substring;
    cout << "Enter a substring to search for: ";
    cin >> substring;
    int substringCount = countSubstringOccurrences(stdStringArray, substring);
    cout << "The number of occurrences of the substring '" << substring << "' in the array: " << substringCount << endl;

    // Генерация и вывод данных о работниках, банкнотах и фигурах
    cout << "\nGeneration of workers, banknotes and figures:\n";

    // Генерация работника
    Employee emp = generateRandomEmployee();
    cout << "Worker: " << emp.firstName << " " << emp.lastName << ", age: " << emp.age << endl;

    // Генерация банкноты
    Banknote bn = generateRandomBanknote();
    cout << "The banknote: " << bn.denomination << " " << bn.currency << endl;

    // Генерация геометрической фигуры
    Shape sh = generateRandomShape();
    cout << "Figure: " << sh.type << ", size: " << sh.size << endl;

    // Освобождение памяти для массива структур String
    for (int i = 0; i < N; ++i) {
        delete[] stringArray[i].data;
    }
    delete[] stringArray;

    return 0;
}
