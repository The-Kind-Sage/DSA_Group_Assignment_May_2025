// Required Dependency to execute program
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

// Quick Sort
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


// Merge Sort
void merge(std::vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    std::vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; ++i) L[i] = arr[l + i];
    for (int j = 0; j < n2; ++j) R[j] = arr[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(std::vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}


// Binary Search
int binarySearch(const std::vector<int>& arr, int key) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == key) return mid;
        else if (arr[mid] < key) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}


// Exponential Search
int exponentialSearch(const std::vector<int>& arr, int key) {
    if (arr.empty()) return -1;
    if (arr[0] == key) return 0;
    int i = 1;
    while (i < arr.size() && arr[i] <= key) i *= 2;
    int left = i / 2, right = std::min(i, (int)arr.size() - 1);
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == key) return mid;
        else if (arr[mid] < key) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

// To print vector if small
void printVector(const std::vector<int>& arr) {
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << arr[i];
        if (i != arr.size() - 1) std::cout << ", ";
    }
    std::cout << std::endl;
}



int main() {
    int N;
    std::cout << "-----------------------------------\n";
    std::cout << "WELCOME TO SORTING & SEARCHING DEMO\n";
    std::cout << "-----------------------------------\n\n";

   do {
    std::cout << "How many random numbers do you want? (N): ";
    std::cin >> N;
    if (N <= 0) {
        std::cerr << "Please enter a positive number.\n";
    }
} while (N <= 0);


    std::vector<int> numbers(N);
    for (int i = 0; i < N; ++i)
        numbers[i] = i + 1;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(numbers.begin(), numbers.end(), gen);

    std::vector<int> randomArr = numbers;
    std::vector<int> sortedArr(N), reverseArr(N);
    for (int i = 0; i < N; ++i) {
        sortedArr[i] = i + 1;
        reverseArr[i] = N - i;
    }

    std::vector<int> quickSorted = numbers;
    auto start = std::chrono::high_resolution_clock::now();
    quickSort(quickSorted, 0, N - 1);
    auto end = std::chrono::high_resolution_clock::now();
    auto quickSortTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "\nUnsorted array:\n";
    if (N <= 50) printVector(numbers);
    else std::cout << "[Array is too large to display]\n";

    std::cout << "\nSorted array (Quick Sort):\n";
    if (N <= 50) printVector(quickSorted);
    else std::cout << "[Array is too large to display]\n";
    std::cout << "Quick Sort took " << quickSortTime << " microseconds.\n";

    std::vector<int> mergeSorted = numbers;
    start = std::chrono::high_resolution_clock::now();
    mergeSort(mergeSorted, 0, N - 1);
    end = std::chrono::high_resolution_clock::now();
    auto mergeSortTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "\nSorted array (Merge Sort):\n";
    if (N <= 50) printVector(mergeSorted);
    else std::cout << "[Array is too large to display]\n";
    std::cout << "Merge Sort took " << mergeSortTime << " microseconds.\n";

    // Time measuring lambda in microseconds
    auto time_sort = [](auto sort_func, std::vector<int> arr, const std::string& name) {
        auto start = std::chrono::high_resolution_clock::now();
        sort_func(arr);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << name << ": " << duration << " microseconds\n";
    };

    std::string choice;
    while (true) {
        std::cout << "\nNOTE: If the input value of (N) is very big it might crash program.";
        std::cout << "\nDo you want to see best/average/worst case sorting times? (y/n): ";
        std::cin >> choice;
        std::transform(choice.begin(), choice.end(), choice.begin(), ::tolower);

        if (choice == "y" || choice == "yes") {
            std::cout << "----- Quick Sort -----\n";
            time_sort([&](std::vector<int>& a){ quickSort(a, 0, static_cast<int>(a.size()) - 1); }, randomArr, "Best/Average (Random) Case");
            time_sort([&](std::vector<int>& a){ quickSort(a, 0, static_cast<int>(a.size()) - 1); }, sortedArr, "Worst (Sorted) Case");
            time_sort([&](std::vector<int>& a){ quickSort(a, 0, static_cast<int>(a.size()) - 1); }, reverseArr, "Worst (Reverse Sorted) Case");

            std::cout << "\n----- Merge Sort -----\n";
            time_sort([&](std::vector<int>& a){ mergeSort(a, 0, static_cast<int>(a.size()) - 1); }, randomArr, "Random Case");
            time_sort([&](std::vector<int>& a){ mergeSort(a, 0, static_cast<int>(a.size()) - 1); }, sortedArr, "Sorted Case");
            time_sort([&](std::vector<int>& a){ mergeSort(a, 0, static_cast<int>(a.size()) - 1); }, reverseArr, "Reverse Sorted Case");
            break;
        } else if (choice == "n" || choice == "no") {
            break;
        } else {
            std::cout << "Invalid input. Please type 'y' or 'n'.\n";
        }
    }

    std::cout << "\n*******************************************************************\n";

// For searching Interface

    int key;
    std::cout << "\n----- Searching -----\n";
    std::cout << "Enter a number to search for: ";
    std::cin >> key;

    start = std::chrono::high_resolution_clock::now();
    int binIndex = binarySearch(quickSorted, key);
    end = std::chrono::high_resolution_clock::now();
    auto binSearchTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    if (binIndex != -1)
        std::cout << "Binary Search: Found at index " << binIndex << "\n";
    else
        std::cout << "Binary Search: Not found\n";
    std::cout << "Binary Search time: " << binSearchTime << " microseconds\n\n";

    start = std::chrono::high_resolution_clock::now();
    int expIndex = exponentialSearch(quickSorted, key);
    end = std::chrono::high_resolution_clock::now();
    auto expSearchTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    if (expIndex != -1)
        std::cout << "Exponential Search: Found at index " << expIndex << "\n";
    else
        std::cout << "Exponential Search: Not found\n";
    std::cout << "Exponential Search time: " << expSearchTime << " microseconds\n";

    return 0;
}