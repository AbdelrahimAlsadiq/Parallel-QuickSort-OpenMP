#include <iostream>
#include <thread>
#include <vector>
#include <omp.h>

#define MAX_THREADS thread::hardware_concurrency()

using namespace std;

// Function to partition the array
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

// Serial Quicksort algorithm
void serialQuickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        serialQuickSort(arr, low, pi - 1);
        serialQuickSort(arr, pi + 1, high);
    }
}

// Parallel Quicksort algorithm
void parallelQuickSort(vector<int>& arr, int low, int high, int max_threads) {
    if (low < high) {
        int pi = partition(arr, low, high);

        // If the number of threads is less than the maximum, create threads for each partition
        if (max_threads > 1) {
#pragma omp parallel sections
            {
#pragma omp section
                parallelQuickSort(arr, low, pi - 1, max_threads / 2);
#pragma omp section
                parallelQuickSort(arr, pi + 1, high, max_threads / 2);
            }
        }
        else { // If the maximum number of threads reached, continue with serial sorting
            serialQuickSort(arr, low, pi - 1);
            serialQuickSort(arr, pi + 1, high);
        }
    }
}


void run_test(const int ARRAY_SIZE, const int N_THREADS = MAX_THREADS) {
    srand(time(NULL));

    vector<int> arr_serial(ARRAY_SIZE);
    vector<int> arr_parallel(ARRAY_SIZE);

    // Filling the arrays with random numbers
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        arr_serial[i] = arr_parallel[i] = rand() % ARRAY_SIZE;
    }

    // Timing serial quicksort
    double start_serial = omp_get_wtime();
    serialQuickSort(arr_serial, 0, ARRAY_SIZE - 1);
    double end_serial = omp_get_wtime();
    double time_serial = end_serial - start_serial;

    // Timing parallel quicksort
    double start_parallel = omp_get_wtime();
    parallelQuickSort(arr_parallel, 0, ARRAY_SIZE - 1, N_THREADS);
    double end_parallel = omp_get_wtime();
    double time_parallel = end_parallel - start_parallel;

    // Output the timing results
    cout << "Serial Quicksort Time for " << ARRAY_SIZE << " elements:\t" << time_serial << " seconds" << endl;
    cout << "Parallel Quicksort Time for " << ARRAY_SIZE << " elements:\t" << time_parallel << " seconds" << endl;
    cout << "-----------------------------------------------" << endl;
}

int main() {
    int default_value = 0;

    cout << "---[ Enter an array size to run the test to it ]---" << endl;
    cout << "--> Enter 0 for default test cases" << endl;
    cout << "--> Enter -1 to quit the program";

    while (true) {
        cout << "\n\nInput Value: ";
        cin >> default_value;

        if (default_value == -1)
            return 0;

        if (default_value == 0) {
            int test_cases[3] = { 100000, 1000000, 10000000 };
            for (int i = 0; i < 3; i++) {
                run_test(test_cases[i]);
            }
        }

        else if (default_value > 1e7 || default_value < -1) {
            cout << "Error: Please enter a valid array size..";
        }

        else {
            int n_threads;
            cout << "Enter Number of threads (MAX " << MAX_THREADS << "): ";
            cin >> n_threads;
            run_test(default_value, n_threads);
        }
    }

    return 0;
}
