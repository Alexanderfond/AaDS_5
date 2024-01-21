#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <fstream>

int Small_Size[10];
int Medium_Size[100];
int Large_Size[1000];

int ArrayFilling(int* arrayType, int size) {
    for (int i = 0; i < size; i++) {
        arrayType[i] = rand() % 100 + 1;
    }
    return *arrayType;
}

void fillArrayFromFile(const std::string& fileName, int* arr, int size) {
    std::ifstream file(fileName);

    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << fileName << std::endl;
        return;
    }

    for (int i = 0; i < size; ++i) {
        if (file >> arr[i]) {
            // Successfully read an integer from the file
        }
        else {
            std::cerr << "Error reading from file: " << fileName << std::endl;
            break;
        }
    }

    file.close();
}

void writeArrayToFile(const std::string& fileName, const int* arr, int size) {
    std::ofstream file(fileName);

    if (!file.is_open()) {
        std::cerr << "Unable to open file for writing: " << fileName << std::endl;
        return;
    }

    for (int i = 0; i < size; ++i) {
        file << arr[i] << " ";
    }

    file.close();
}

void print(int* array, int size) {
    for (int i = 0; i < size; i++) {
        if (i % 40 == 0) std::cout << std::endl;
        std::cout << array[i] << "  ";
    }
    std::cout << std::endl << std::endl;
}

void linearSearch(const int* array, int size, int value, const char* arrayName) {
    for (int i = 0; i < size; ++i) {
        if (array[i] == value) {
            std::cout << arrayName << ": " << i << " :: " << array[i] << std::endl; // Возвращаем индекс, если найден элемент
        }
    }
    return; // Если элемент не найден
}

void BarierSearch( int* array, int size, int value, const char* arrayName) {
    int last = array[size - 1]; // Сохраняем последний элемент
    array[size - 1] = value; // Устанавливаем искомое значение как последний элемент

    int i = 0;
    while (array[i] != value) {
        ++i;
    }

    array[size - 1] = last; // Восстанавливаем последний элемент

    if (i < size - 1 || value == last) {
        std::cout << arrayName << "\n\tFounded element: " << array[i] << "\n\tIndex: " << i << "\n\n"; // Возвращаем индекс, если найден элемент
    }
    else {
        std::cout << arrayName <<":  <<< Element not founded >>>  \n\n"; // Если элемент не найден
    }
}

void bubbleSort(int* array, int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (array[j] > array[j + 1]) {
                std::swap(array[j], array[j + 1]);
            }
        }
    }
}

void binarySearch(const int* array, int size, int value, const char* arrayName) {
    int left = 0;
    int right = size - 1;
    bool found = false;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (array[mid] == value) {
            std::cout << arrayName << "\n\tFounded Element: " << array[mid] << "\n\tIndex: " << mid << "\n\n"; // Выводим индекс, если найден элемент
            found = true;
            break; // Если элемент найден, выходим из цикла
        }
        else if (array[mid] < value) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    if (!found) {
        std::cout << arrayName << ":  <<< Element not found >>>  \n\n"; // Если элемент не найден
    }
}

void subarraySearch(const int* array, int arraySize, const int* subarray, int subarraySize, const char* arrayName) {
    bool checkSubarray = false;

    std::cout << "\nArray: " << arrayName;
    for (int i = 0; i <= arraySize - subarraySize; ++i) {
        int j;
        for (j = 0; j < subarraySize; ++j) {
            if (array[i + j] != subarray[j]) {
                checkSubarray = true;
                break; 
            }
        }


        if (j == subarraySize) {
            std::cout << " Subarray found at index " << i << std::endl;
            return; 
        }
    }

    if (checkSubarray == true) {
        std::cout << " Subarray: ";
        for (int i = 0; i < subarraySize; i++) {
            std::cout << subarray[i] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Subarray not found" << std::endl;
    return;
}

void computePrefixFunction(const int* pattern, int patternSize, int* prefixFunction) {
    prefixFunction[0] = 0;
    int k = 0;

    for (int i = 1; i < patternSize; ++i) {
        while (k > 0 && pattern[k] != pattern[i]) {
            k = prefixFunction[k - 1];
        }

        if (pattern[k] == pattern[i]) {
            ++k;
        }

        prefixFunction[i] = k;
    }
}

// Function to perform substring search using the KMP algorithm
void KMPSubstringSearch(const int* text, int textSize, const int* pattern, int patternSize, const char* arrayName) {
    int* prefixFunction = new int[patternSize];
    computePrefixFunction(pattern, patternSize, prefixFunction);

    int i = 0; // Index for text
    int j = 0; // Index for pattern

    while (i < textSize) {
        if (pattern[j] == text[i]) {
            ++i;
            ++j;

            if (j == patternSize) {
                std::cout << arrayName << "\n\tSubarray found at index " << i - j << std::endl;
                j = prefixFunction[j - 1];
            }
        }
        else {
            if (j != 0) {
                j = prefixFunction[j - 1];
            }
            else {
                ++i;
            }
        }
    }

    delete[] prefixFunction;
}

int boyerMooreSearch(const int* text, int textSize, const int* pattern, int patternSize) {
    int lastOccurrence[256];

    for (int i = 0; i < 256; ++i) {
        lastOccurrence[i] = -1;
    }

    for (int i = 0; i < patternSize; ++i) {
        lastOccurrence[pattern[i]] = i;
    }

    int i = patternSize - 1;
    int j = patternSize - 1;

    while (i < textSize) {
        if (pattern[j] == text[i]) {
            if (j == 0) {
                return i; // Pattern found
            }
            --i;
            --j;
        }
        else {
            i = i + patternSize - std::min(j, 1 + lastOccurrence[text[i]]);
            j = patternSize - 1;
        }
    }

    return -1; // Pattern not found
}

void boyerMooreSubstringSearch(const int* text, int textSize, const int* pattern, int patternSize, const char* arrayName) {
    int result = boyerMooreSearch(text, textSize, pattern, patternSize);

    if (result != -1) {
        std::cout << arrayName << "\n\tSubarray found at index " << result << std::endl;
    }
    else {
        std::cout << arrayName << ":  <<< Subarray not found >>>  \n\n";
    }
}

// Function to perform substring search using the Rabin-Karp algorithm
void searchRabinKarp(const int* array, int arraySize, const int* pattern, int patternSize, const char* arrayName, const int PRIME) {
    // Вычисление хеша для паттерна и первого окна в массиве
    int patternHash = 0;
    int windowHash = 0;
    for (int i = 0; i < patternSize; ++i) {
        patternHash += pattern[i] * pow(PRIME, i);
        windowHash += array[i] * pow(PRIME, i);
    }

    // Проход по массиву
    int j = 0;
    for (int i = 0; i <= arraySize - patternSize; ++i) {
        // Проверка совпадения хешей
        if (windowHash == patternHash) {
            // Проверка на совпадение каждого элемента в окне
            
            for (j = 0; j < patternSize; ++j) {
                if (array[i + j] != pattern[j]) {
                    break;
                }
            }

            // Если все элементы совпали, выведем индекс начала подстроки
            if (j == patternSize) {
                std::cout << arrayName << "\n\tSubarray found at index  " << i << " in array " << arrayName << std::endl;
            }
        }

        // Пересчет хеша для следующего окна
        if (i < arraySize - patternSize) {
            windowHash = (windowHash - array[i]) / PRIME + array[i + patternSize] * pow(PRIME, patternSize - 1);
        }
    }
    if (j != patternSize) {
        std::cout << arrayName << ":  <<< Subarray not found >>>  \n\n";
    }
}

int main() {
    srand(time(0));

    int choise = 0;
    int choiseToFilling = 0;
    int valueToSearch;
    int searchResult;
    int subarray[1000];  // for substring search
    int subarraySize;  // for substring search
    const int PRIME = 101;  // for Rabin-Karp algorithm

    do {
        std::cout
            << "\n1 - Fill arrays"
            << "\n2 - Print"
            << "\n3 - Sinear search"
            << "\n4 - Search by barier"
            << "\n5 - Sort and Binary search"
            << "\n6 - Substring search"
            << "\n7 - KMP algorithm"
            << "\n8 - BM algorithm"
            << "\n9 - RK algorithm"
            << "\n10 - Fill arrays from file"
            << "\n11 - Save arrays to file"
            << "\nYour choise: ";

        std::cin >> choise;
        switch (choise) {
        case 1:
            std::cout << "Choose array size to fill (10, 100, 1000 or 3 to all types): ";
            std::cin >> choiseToFilling;

            switch (choiseToFilling) {
            case 10:
                Small_Size[10] = ArrayFilling(Small_Size, choiseToFilling);
                break;

            case 100:
                Medium_Size[10] = ArrayFilling(Small_Size, choiseToFilling);
                break;

            case 1000:
                Large_Size[10] = ArrayFilling(Small_Size, choiseToFilling);
                break;

            case 3:
                Small_Size[10] = ArrayFilling(Small_Size, 10);
                Medium_Size[10] = ArrayFilling(Medium_Size, 100);
                Large_Size[10] = ArrayFilling(Large_Size, 1000);
                break;

            default:
                return 0;
            }
            break;
        case 2:
            if (sizeof(Small_Size) >= 10) print(Small_Size, 10);
            if (sizeof(Medium_Size) >= 100) print(Medium_Size, 100);
            if (sizeof(Large_Size) >= 1000) print(Large_Size, 1000);
            break;

        case 3:
            
            std::cout << "Enter a search value: ";
            std::cin >> valueToSearch;

            if (sizeof(Small_Size) >= 10) linearSearch(Small_Size, 10, valueToSearch, "Small_Size");
            if (sizeof(Medium_Size) >= 100) linearSearch(Medium_Size, 100, valueToSearch, "Medium_Size");
            if (sizeof(Large_Size) >= 1000) linearSearch(Large_Size, 1000, valueToSearch, "Large_Size");

            break;

        case 4:
            std::cout << "Enter a search value: ";
            std::cin >> valueToSearch;

            if (sizeof(Small_Size) >= 10) BarierSearch(Small_Size, 10, valueToSearch, "Small_Size");
            if (sizeof(Medium_Size) >= 100) BarierSearch(Medium_Size, 100, valueToSearch, "Medium_Size");
            if (sizeof(Large_Size) >= 1000) BarierSearch(Large_Size, 1000, valueToSearch, "Large_Size");
            
            break;

        case 5:
            std::cout << "Enter a search value: ";
            std::cin >> valueToSearch;

            if (sizeof(Small_Size) >= 10) bubbleSort(Small_Size, 10); binarySearch(Small_Size, 10, valueToSearch, "Small_Size");
            if (sizeof(Medium_Size) >= 100) bubbleSort(Medium_Size, 100); binarySearch(Medium_Size, 100, valueToSearch, "Medium_Size");
            if (sizeof(Large_Size) >= 1000) bubbleSort(Large_Size, 1000); binarySearch(Large_Size, 1000, valueToSearch, "Large_Size");

            break;

        case 6:
            //int subarray[1000]; // Предположим, что максимальный размер подмассива - 100 элементов
            //int subarraySize;

            std::cout << "Enter the size of the subarray: ";
            std::cin >> subarraySize;

            std::cout << "Enter the elements of the subarray:\n";
            for (int i = 0; i < subarraySize; ++i) {
                std::cin >> subarray[i];
            }

            if (sizeof(Small_Size) >= 10) subarraySearch(Small_Size, 10, subarray, subarraySize, "Small_Size");
            if (sizeof(Medium_Size) >= 100) subarraySearch(Medium_Size, 100, subarray, subarraySize, "Medium_Size");
            if (sizeof(Large_Size) >= 1000) subarraySearch(Large_Size, 1000, subarray, subarraySize, "Large_Size");

            break;

        case 7:
            //int subarray[1000]; // Предположим, что максимальный размер подмассива - 100 элементов
            //int subarraySize;

            std::cout << "Enter the size of the subarray: ";
            std::cin >> subarraySize;

            std::cout << "Enter the elements of the subarray:\n";
            for (int i = 0; i < subarraySize; ++i) {
                std::cin >> subarray[i];
            }

            if (sizeof(Small_Size) >= 10) KMPSubstringSearch(Small_Size, 10, subarray, subarraySize, "Small_Size");
            if (sizeof(Medium_Size) >= 100) KMPSubstringSearch(Medium_Size, 100, subarray, subarraySize, "Medium_Size");
            if (sizeof(Large_Size) >= 1000) KMPSubstringSearch(Large_Size, 1000, subarray, subarraySize, "Large_Size");
            break;

        case 8:
            std::cout << "Enter the size of the subarray: ";
            std::cin >> subarraySize;

            std::cout << "Enter the elements of the subarray:\n";
            for (int i = 0; i < subarraySize; ++i) {
                std::cin >> subarray[i];
            }

            if (sizeof(Small_Size) >= 10) boyerMooreSubstringSearch(Small_Size, 10, subarray, subarraySize, "Small_Size");
            if (sizeof(Medium_Size) >= 100) boyerMooreSubstringSearch(Medium_Size, 100, subarray, subarraySize, "Medium_Size");
            if (sizeof(Large_Size) >= 1000) boyerMooreSubstringSearch(Large_Size, 1000, subarray, subarraySize, "Large_Size");

            break;

        case 9: 
            std::cout << "Enter the size of the subarray: ";
            std::cin >> subarraySize;

            std::cout << "Enter the elements of the subarray:\n";
            for (int i = 0; i < subarraySize; ++i) {
                std::cin >> subarray[i];
            }

            if (sizeof(Small_Size) >= 10) searchRabinKarp(Small_Size, 10, subarray, subarraySize, "Small_Size", PRIME);
            if (sizeof(Medium_Size) >= 100) searchRabinKarp(Medium_Size, 100, subarray, subarraySize, "Medium_Size", PRIME);
            if (sizeof(Large_Size) >= 1000) searchRabinKarp(Large_Size, 1000, subarray, subarraySize, "Large_Size", PRIME);


            break;

        case 10:
            fillArrayFromFile("Small_Size.txt", Small_Size, 10);
            fillArrayFromFile("Medium_Size.txt", Medium_Size, 100);
            fillArrayFromFile("Large_Size.txt", Large_Size, 1000);

            break;

        case 11:
            writeArrayToFile("result_Small.txt", Small_Size, 10);
            writeArrayToFile("result_Medium.txt", Medium_Size, 100);
            writeArrayToFile("result_Large.txt", Large_Size, 1000);

            break;

        default:
            std::cout << "  <<< Wrong choise >>>  ";
            break;
        }

    } while (choise != 0);
 
}
