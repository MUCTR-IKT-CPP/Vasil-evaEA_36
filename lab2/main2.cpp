#include <iostream>  // Для ввода и вывода данных
#include <cctype>  // Для работы с символами (функция проверки символов - isdigit())
#include <string>  // Для работы со строками, содержит класс std::string для хранения и обработки строк текста
#include <limits>  // Для работы с предельными значениями типов данных (numeric_limits<streamsize>::max())
#include <random>  // Для генерации случайных чисел (random_device, mt19937)
#include <algorithm>  // Для работы с контейнерами: сортировка, поиск, перестановка и другие (shuffle())
#include <vector>  // Предоставляет контейнер std::vector (vector<pair<int, int>>)


using namespace std;
/**
 * @brief Функция проверки, является ли строка целым числом
 *
 * @param str Строка, которую нужно проверить
 * @param mode Режим проверки ("positive_int" для положительных чисел, "int" для любых целых чисел)
 * @return true Если строка является целым числом в заданном режиме
 * @return false Если строка не является целым числом
 */
bool isValidInteger (const string& str, const string& mode) {
    if (str.empty()) {
        return false;  // Пустая строка не является допустимым числом
    }

    // Проверка на положительное целое число
    if (mode == "positive_int") {
        // Проверка, что все символы строки являются цифрами
        for (char c : str) {  // Перебор каждого символа в строке
            if (!isdigit(c)) {  // Если хотя бы один символ не является цифрой
                return false;
            }
        }

        /* Конструкция try-catch используется для безопасного преобразования строки в целое
         * число с помощью функции stoi, которая может выбросить исключение,
         * если преобразование не удаётся.
         */
        try {
            int number = stoi(str);  // Преобразование строки в целое число
            return number > 0;  // Возвращает true, если число положительное
        } catch (const out_of_range&) {  // Если строка не может быть преобразована в int (например, слишком длинная),
            return false;               // возвращает false
        }
    }

    if (mode == "int") {  // Проверка на любое целое число
        int i = 0;
        if (str[0] == '-') {  // Если первый символ '-' (минус), пропускаем его для проверки цифр
            i = 1;
        }
        // Проверка, что все символы после возможного минуса являются цифрами
        for (; i < str.size(); i++) {
            if (!isdigit(str[i])) {
                return false;  // Если найден нецифровой символ, строка не является числом
            }
        }
        try {
            stoi(str);  // Попытка преобразования строки в целое число
            return true;
        } catch (const out_of_range&) {
            return false;  // Если строка слишком длинная для типа int, возвращает false
        }
    }
    return false;  // Если mode не соответствует ни одному из поддерживаемых значений, возвращает false
}


/**
 * @brief Функция для получения размера массива от пользователя
 *
 * @return Возвращает размер массива в виде целого числа
 */
int arrSizeInput () {
    string input;
    while (true) {
        cout << "Enter the desired array size (positive integer):" << endl;
        cin >> input;

        // Проверка, что введенное значение является допустимым положительным целым числом
        if (isValidInteger(input, "positive_int")) {
            break;  // Ввод корректен, выход из цикла
        } else {
            // Вывод сообщения об ошибке, если введенное значение некорректно
            cout << "~{ ERROR! You must enter a positive integer! }~\n" << endl;
        }
    }
    return stoi(input);  // Преобразование строки в целое число и возврат этого значения
}


/**
 * @brief Функция для создания и инициализации нулями двумерного массива размером size x size
 *
 * @param size Размер массива (количество строк и столбцов)
 * @return Указатель на созданный и инициализированный двумерный массив
 */
int** createAndInitializeArr(int size) {
    /* Функция создает двумерный массив динамически и заполняет его нулями.
     * Используются указатели, т.к. нужно динамически выделять память для массива,
     * размер которого неизвестен во время компиляции. Указатели
     * позволяют работать с динамически выделенной памятью, что дает гибкость
     * в управлении массивами, особенно при работе с большими объемами данных.
     */

    int** arr = new int*[size];  // Выделение памяти для массива указателей на строки

    for (int i = 0; i < size; i++) {
        arr[i] = new int[size];  // Выделение памяти для каждой строки массива под столбцы
        for (int j = 0; j < size; j++) {  // Инициализация всех элементов строки нулями
            arr[i][j] = 0;
        }
    }
    cout << "OK! An array with dimension [" << size << "x" << size << "] is created!" << endl;
    cout << "Array was successfully initialized!\n" << endl;
    return arr;  // Возврат указателя на созданный массив
}


/**
 * @brief Вывод двумерного массива в виде таблицы.
 *
 * @param arr Указатель на двумерный массив
 * @param size Размер массива (N x N)
 */
void printArr(int** arr, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            // Вывод текущего элемента массива, добавление табуляции для удобства
            cout << arr[i][j] << "\t";
        }
        // После вывода одной строки переход на следующую строку
        cout << endl;
    }
}


/**
 * @brief Освобождение памяти, выделенной под двумерный массив
 *
 * Функция проходит по каждой строке массива, освобождая выделенную память для каждой строки,
 * а затем освобождает память, выделенную под указатели на строки.
 * Это предотвращает утечки памяти.
 * @param arr Указатель на двумерный массив
 * @param size Размер массива (N x N)
 */
void freeArr(int** arr, int size) {
    for (int i = 0; i < size; i++) {
        delete[] arr[i];
    }
    delete[] arr;
}


/**
 * @brief Очищение массива и заполнение его нулями
 *
 * @param arr Указатель на двумерный массив
 * @param size Размер массива (N x N)
 */
void clearAndFillWithZeros(int** arr, int size) {
    cout << "\n{ You chose the 1st action! }" << endl;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            arr[i][j] = 0;
        }
    }
    // Вывод результатов очищения массива
    cout << "{ DONE! The array was filled with zeros: }" << endl;
    printArr(arr, size);
}


/**
 * @brief Заполнение массива симметрично относительно главной диагонали
 *
 * Пользователю предлагается ввести значения для верхней треугольной матрицы (включая главную диагональ).
 * Затем массив заполняется симметрично относительно главной диагонали.
 * @param arr Указатель на двумерный массив
 * @param size Размер массива (N x N)
 */
void fillArrMainDiagonal(int** arr, int size) {
    string input;
    cout << "\n{ You chose the 2nd action! }" << endl;
    cout << "Enter the values for the upper triangle of the matrix (including the diagonal):" << endl;

    // Прохождение по верхнему треугольнику, включая главную диагональ
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            // Цикл для ввода корректного значения для каждого элемента
            while (true) {
                cout << "Value for element [" << i << "][" << j << "]:\n";
                cin >> input;
                if (isValidInteger(input, "int")) {
                    arr[i][j] = stoi(input);  // Заполнение верхнего треугольника
                    arr[j][i] = arr[i][j];  // Симметричное заполнение нижнего треугольника
                    break;
                } else {
                    cout << "~{ ERROR! Enter a valid integer! }~\n" << endl;
                }
            }
        }
    }
    // Вывод результатов заполнения массива
    cout << "{ DONE! The array now looks like this: }" << endl;
    printArr(arr, size);
}


/**
 * @brief Заполнение массива симметрично относительно побочной диагонали
 *
 * Пользователю предлагается ввести значения для верхней треугольной матрицы (включая побочную диагональ).
 * Затем массив заполняется симметрично относительно побочной диагонали.
 * @param arr Указатель на двумерный массив
 * @param size Размер массива (N x N)
 */
void fillArrSecDiagonal(int** arr, int size) {
    string input;
    cout << "\n{ You chose the 3rd action! }" << endl;
    cout << "Enter the values for the upper triangle of the matrix (including the diagonal):" << endl;

    // Прохождение по верхнему треугольнику, включая побочную диагональ
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - i; j++) {
            while (true) {
                cout << "Value for element [" << i << "][" << j << "]:\n";
                cin >> input;
                // Цикл для ввода корректного значения для каждого элемента
                if (isValidInteger(input, "int")) {
                    arr[i][j] = stoi(input);  // Заполнение верхнего треугольника
                    arr[size - 1 - j][size - 1 - i] = arr[i][j];  // Симметричное заполнение нижнего треугольника
                    break;
                } else {
                    cout << "~{ ERROR! Enter a valid integer! }~\n" << endl;
                }
            }
        }
    }
    // Вывод результатов заполнения массива
    cout << "{ DONE! The array now looks like this: }" << endl;
    printArr(arr, size);
}


/**
 * @brief Заполнение массива значениями треугольника Паскаля
 *
 * Если все элементы массива равны 0, функция заполняет его значениями треугольника Паскаля.
 * Если массив не очищен (содержит не-нулевые элементы), выводится уведомление о необходимости
 * очистки массива с помощью 1-й команды.
 *
 * Если размер массива меньше 35, функция заполняет массив по правилам треугольника Паскаля:
 * - Каждый элемент является суммой двух элементов, находящихся над ним.
 * - Первые и последние элементы каждой строки равны 1.
 * Если размер массива >= 35, функция сообщает, что операция невозможна, т.к. по условию
 * тип массива - int, а при данном размере происходит переполнение памяти, из-за чего некоторые
 * числа в массиве становятся отрицательными.
 * @param arr Указатель на двумерный массив
 * @param size Размер массива (N x N)
 */
void fillArrPascalsTriangle(int** arr, int size) {
    // Проверка, что массив очищен (все элементы равны 0)
    bool is_cleared = true;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (arr[i][j] != 0) {
                is_cleared = false;
                break;
            }
        }
        if (!is_cleared) {
            break;
        }
    }
    // Если массив не очищен, вывод предупреждения и выход из функции
    if (!is_cleared) {
        cout << "\n{ ERROR! The array is not cleared. "
                "Please clear the array before proceeding. }\n" << endl;
        return;
    }

    // Ограничение выполнения функции для размеров < 35, чтобы вывод не перегружался
    if (size < 35) {
        cout << "\n{ You chose the 4th action! }" << endl;

        for (int i = 0; i < size; i++) {  // Заполнение массива значениями треугольника Паскаля
            arr[i][0] = 1;  // Первый элемент каждой строки равен 1
            arr[i][i] = 1;  // Последний элемент строки всегда равен 1
            for (int j = 1; j <= i; j++) {
                // Каждый элемент равен сумме двух элементов над ним
                arr[i][j] = arr[i - 1][j - 1] + arr[i - 1][j];
            }
        }
        // Вывод результатов заполнения массива
        cout << "{ DONE! The array was filled as Pascal's triangle: }" << endl;
        printArr(arr, size);
    } else {
        cout << "\n{ You can't choose the 4th action! Your array's size >= 35 }" << endl;
    }
}


/**
 * @brief Заполнение массива для игры "Сапёр"
 *
 * Функция заполняет массив минами в случайных клетках. Максимальное количество мин
 * составляет половину от общего количества клеток массива, для того чтобы игра не была бессмысленной.
 * После расстановки мин, оставшиеся клетки заполняются числами, показывающими количество мин в соседних клетках.
 *
 * @param arr Указатель на двумерный массив
 * @param size Размер массива (N x N)
 */
void fillArrMines (int** arr, int size) {
    cout << "\n{ You chose 5th action! }" << endl;
    int max_mines = size * size / 2;  // Установка максимального количества мин
    cout << "The maximum number of mines: " << max_mines << endl;

    // Ввод количества мин на поле
    string num_mines_str;
    while (true) {
        cout << "Enter the desired number of mines: " << endl;
        cin >> num_mines_str;

        if (isValidInteger(num_mines_str, "int")) {  // Проверка корректности ввода
            if (stoi(num_mines_str) < 0) {
                cout << "~{ ERROR! You must enter an integer is more or equal 0! }~\n" << endl;
            } else {
                break;
            }
        } else {
            cout << "~{ ERROR! You must enter an integer is more or equal 0! }~\n" << endl;
        }
    }
    int num_mines = stoi(num_mines_str);  // Преобразование строки в число

    // Генерация случайных позиций для мин
    random_device rd;
    mt19937 generator(rd());  // Инициализация генератора случайных чисел

    /*
     * Вектор `cells` используется для хранения всех возможных координат поля,
     * т.к. это позволяет легко перемешать их и затем выбирать случайные координаты для размещения мин.
     * Вектору не надо задавать размер, так как он сам управляет им; позволяет использовать
     * метод 'shuffle'; упрощает доступ к парам координат, которые обрабатываются с помощью метода
     * `emplace_back`, сохраняя пары (i, j) для всех клеток поля.
     */
    vector<pair<int, int>> cells;
    // Заполнение вектора всеми возможными координатами поля
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cells.emplace_back(i, j);  // Добавление каждой координаты (i, j)
        }
    }
    // Перемешивание координат для случайного распределения мин
    shuffle(cells.begin(), cells.end(), generator);

    // Размещение мины на случайных координатах
    for (int i = 0; i < num_mines; i++) {
        arr[cells[i].first][cells[i].second] = -1; // Обозначение мины '-1'
    }

    // Заполнение остальных клеток числами, обозначающими количество соседних мин
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (arr[i][j] == -1) {
                continue;  // Пропуск клеток с минами
            }
            int count = 0;  // Счетчик мин вокруг текущей клетки

            // Прохождение по соседним клеткам
            for (int di = -1; di <= 1; di++) {  // Прохождение по всем возможным смещениям по строкам
                for (int dj = -1; dj <= 1; dj++) {  // Прохождение по всем возможным смещениям по столбцам
                    int ni = i + di;  // Вычисление индекса строки соседней ячейки
                    int nj = j + dj;  // Вычисление индекса столбца соседней ячейки

                    // Проверка нахождения соседней клетки в пределах массива и содержания мины
                    if (ni >= 0 && ni < size && nj >= 0 && nj < size && arr[ni][nj] == -1) {
                        count++; // Увеличение счетчика мин, если в соседней ячейке находится мина
                    }
                }
            }
            // Установка количества мин вокруг текущей ячейки
            arr[i][j] = count;  // Присваивание ячейке (i, j) количества мин вокруг
        }
    }

    cout << "{ DONE! The array was filled for MineSweeper: }" << endl;
    printArr(arr, size);
}


int main() {
    // 1. Ввод желаемой размерности двумерного массива
    int n;
    n = arrSizeInput();  // Получение размера массива от пользователя

    // 2. Создание и заполнение массива
    int** array = createAndInitializeArr(n);
    cout << "An initialized array:" << endl;
    printArr(array, n);

    // 3. Выполнение желаемого действия
    int num_action = 0;  // Переменная для выбора действия
    while (num_action != 6) {  // Цикл продолжается, пока не выбрана команда выхода (6)
        cout << "\n==[Array Manipulation Menu]==\n"
                "Enter the desired action (enter 0 for help):" << endl;
        cin >> num_action;

        // Проверка, находится ли поток ввода в состоянии ошибки
        if (cin.fail()) {  // Возвращает true, если предыдущий ввод не соответствовал ожидаемому типу данных
            cin.clear(); // Сброс состояния потока, позволяет продолжить ввод данных

            // Игнорирование оставшихся символов в текущей строке ввода
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Unknown command.\n" << endl;
            continue;  // Пропуск оставшейся части текущей итерации цикла и переход к следующей
        }

        // Обработка выбора пользователя
        switch (num_action) {
            case 0:  // Вывод доступных команд
                cout << "\n~~[ LIST OF ACTIONS WITH ARRAY ]~~\n"
                        "[1] Clear the array and fill it with zeros.\n"
                        "[2] Fill the array so that it has the property of "
                        "symmetry with respect to the main diagonal.\n"
                        "[3] Fill the array so that it has the property of symmetry "
                        "with respect to the secondary diagonal.\n"
                        "[4] Fill the array so that it forms Pascal's triangle.\n"
                        "[5] Fill in the array for playing minesweeper.\n"
                        "[6] Exit.\n" << endl;
                break;
            case 1:  // Очищение массива и заполнение нулями
                clearAndFillWithZeros(array, n);
                break;
            case 2:  // Заполнение массива симметрично относительно главной диагонали
                fillArrMainDiagonal(array, n);
                break;
            case 3:  // Заполнение массива симметрично относительно побочной диагонали
                fillArrSecDiagonal(array, n);
                break;
            case 4:  // Заполнение массива треугольником Паскаля
                fillArrPascalsTriangle(array, n);
                break;
            case 5:  // Заполнение массива для игры "Сапёр"
                fillArrMines(array, n);
                break;
            case 6:  // Выход из программы
                cout << "\n{ You chose 6th action! }" << endl;
                cout << "You exited from the menu.\n" << endl;
                break;
            default:
                // Сообщение о неизвестной команде
                cout << "Unknown command.\n" << endl;
                break;
        }
    }

    freeArr(array, n);  // Освобождение памяти, выделенной под массив
    return 0;
}