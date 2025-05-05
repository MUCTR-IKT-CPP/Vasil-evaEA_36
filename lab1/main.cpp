#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include <iomanip>

using namespace std;
using namespace chrono;

/**
 * @brief Структура для хранения результатов одного запуска сортировки
 */
struct SortResult {
    double time_ms;
    size_t passes;
    size_t swaps;
};

/**
 * @brief Реализация пузырьковой сортировки с подсчетом проходов и обменов
 * @param arr массив для сортировки
 * @param passes количество проходов
 * @param swaps количество обменов
 */
void bubbleSort(vector<double>& arr, size_t& passes, size_t& swaps) {
    bool swapped;
    size_t n = arr.size();
    passes = 0;
    swaps = 0;

    for (size_t i = 0; i < n - 1; ++i) {
        swapped = false;
        ++passes;
        for (size_t j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                ++swaps;
                swapped = true;
            }
        }
        if (!swapped) break; // Оптимизация: если ничего не поменялось — массив уже отсортирован
    }
}

/**
 * @brief Выполняет серию тестов сортировки и сохраняет результаты
 * @param size размер массива
 * @param trials количество запусков в серии
 * @param engine генератор случайных чисел
 * @param gen распределение случайных чисел
 * @return вектор результатов сортировок
 */
vector<SortResult> runSeries(size_t size, size_t trials, mt19937& engine, uniform_real_distribution<double>& gen) {
    vector<SortResult> results;

    for (size_t i = 0; i < trials; ++i) {
        vector<double> arr(size);
        for (auto& el : arr)
            el = gen(engine);

        size_t passes = 0;
        size_t swaps = 0;

        auto start = high_resolution_clock::now();
        bubbleSort(arr, passes, swaps);
        auto end = high_resolution_clock::now();
        /* Упрощенный способ для замера времени, так как подобные массивы больше миллисикунды  */
        duration<double, milli> elapsed = end - start;
        results.push_back({elapsed.count(), passes, swaps});
    }

    return results;
}

int main() {
    vector<size_t> sizes = {1000, 2000, 4000, 8000, 16000, 32000};
    const size_t trials = 5;

    mt19937 engine(time(0));
    uniform_real_distribution<double> gen(-1.0, 1.0);

    ofstream timeLog("time_results.csv");
    ofstream statsLog("stats_results.csv");

    timeLog << "Size,MinTime,MaxTime,AvgTime\n";
    statsLog << "Size,AvgPasses,AvgSwaps\n";

    for (size_t size : sizes) {
        cout << "Running size: " << size << endl;
        vector<SortResult> results = runSeries(size, trials, engine, gen);

        double min_time = results[0].time_ms;
        double max_time = results[0].time_ms;
        double total_time = 0;
        size_t total_passes = 0;
        size_t total_swaps = 0;

        for (const auto& res : results) {
            min_time = min(min_time, res.time_ms);
            max_time = max(max_time, res.time_ms);
            total_time += res.time_ms;
            total_passes += res.passes;
            total_swaps += res.swaps;
        }

        double avg_time = total_time / trials;
        double avg_passes = static_cast<double>(total_passes) / trials;
        double avg_swaps = static_cast<double>(total_swaps) / trials;

        timeLog << size << "," << min_time << "," << max_time << "," << avg_time << "\n";
        statsLog << size << "," << avg_passes << "," << avg_swaps << "\n";
    }

    timeLog.close();
    statsLog.close();

    cout << "All series completed. Data saved to CSV files." << endl;

    return 0;
}
