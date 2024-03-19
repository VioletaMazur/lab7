#include <iostream> 

#include <fstream> 

#include <algorithm> 

#include <cmath> 

#include <clocale> 



const int MAX_SIZE = 30; // Максимальний розмір масиву 



// Функція для читання масиву з потоку вводу 

void readArray(std::istream& input, int* array, int size) {

    for (int i = 0; i < size; ++i) {

        input >> *(array + i);

    }

}



// Функція для запису масиву в потік виводу 

void writeArray(std::ostream& output, const int array[], int size) {

    for (int i = 0; i < size; ++i) {

        output << array[i] << " ";

    }

    output << std::endl;

}



// Функція для об'єднання та сортування двох масивів 

void mergeAndSortArrays(const int a[], int sizeA, const int b[], int sizeB, int merged[], int& sizeMerged) {

    int even[MAX_SIZE], odd[MAX_SIZE];

    int sizeEven = 0, sizeOdd = 0;



    // Розділення елементів на парні та непарні 

    for (int i = 0; i < sizeA; ++i) {

        if (a[i] % 2 == 0) {

            even[sizeEven++] = a[i];

        }

        else {

            odd[sizeOdd++] = a[i];

        }

    }



    for (int i = 0; i < sizeB; ++i) {

        if (b[i] % 2 == 0) {

            even[sizeEven++] = b[i];

        }

        else {

            odd[sizeOdd++] = b[i];

        }

    }



    // Сортування парних та непарних елементів 

    std::sort(even, even + sizeEven, std::greater<int>());

    std::sort(odd, odd + sizeOdd);



    // Об'єднання відсортованих масивів 

    sizeMerged = 0;

    for (int i = 0; i < sizeEven; ++i) {

        merged[sizeMerged++] = even[i];

    }

    for (int i = 0; i < sizeOdd; ++i) {

        merged[sizeMerged++] = odd[i];

    }

}



// Функція для знаходження добутку елементів між максимальним та мінімальним за модулем 

int productBetweenExtremes(const int array[], int size) {

    int minIndex = 0, maxIndex = 0;



    for (int i = 1; i < size; ++i) {

        if (std::abs(array[i]) < std::abs(array[minIndex])) {

            minIndex = i;

        }

        if (std::abs(array[i]) > std::abs(array[maxIndex])) {

            maxIndex = i;

        }

    }



    if (minIndex > maxIndex) {

        std::swap(minIndex, maxIndex);

    }



    int product = 1;

    for (int i = minIndex + 1; i < maxIndex; ++i) {

        product *= array[i];

    }



    return product;

}



// Функція для сортування масиву за спаданням модулів елементів 

void sortArrayByMagnitude(int array[], int size) {

    std::sort(array, array + size, [](int a, int b) {

        return std::abs(a) > std::abs(b);

        });

}



int main() {

    setlocale(LC_CTYPE, "ukr");



    int choice;

    std::cout << "Виберiть спосiб вводу даних:\n";

    std::cout << "1. Читати з файлу\n";

    std::cout << "2. Вводити з клавiатури\n";

    std::cin >> choice;



    int a[MAX_SIZE], b[MAX_SIZE], c[MAX_SIZE * 2];

    int n, m, sizeC;


    
    if (choice == 1) {

        std::ifstream inputFile("C:/Users/Slim/Desktop/input.txt");

        std::ofstream outputFile("C:/Users/Slim/Desktop/output.txt");


        if (!inputFile.is_open() || !outputFile.is_open()) {

            std::cerr << "Помилка вiдкриття файлу вводу або виводу." << std::endl;

            return 1;

        }

        inputFile >> n;

        readArray(inputFile, a, n);

        inputFile >> m;

        readArray(inputFile, b, m);

        inputFile.close();



        mergeAndSortArrays(a, n, b, m, c, sizeC);

        writeArray(outputFile, c, sizeC);



        int product = productBetweenExtremes(a, n);

        outputFile << "Добуток мiж екстремальними елементами в A: " << product << std::endl;



        sortArrayByMagnitude(a, n);

        writeArray(outputFile, a, n);



        sortArrayByMagnitude(b, m);

        writeArray(outputFile, b, m);



        outputFile.close();

        std::cout << "Результати записано у файл output.txt" << std::endl;

    }

    else if (choice == 2) {

        std::cout << "Введiть кiлькiсть елементiв у масивi A: ";

        std::cin >> n;

        std::cout << "Введiть елементи масиву A: ";

        readArray(std::cin, a, n);

        std::cout << "Введiть кiлькiсть елементiв у масивi B: ";

        std::cin >> m;

        std::cout << "Введiть елементи масиву B: ";

        readArray(std::cin, b, m);



        mergeAndSortArrays(a, n, b, m, c, sizeC);

        std::cout << "Об'єднаний та вiдсортований масив C: ";

        writeArray(std::cout, c, sizeC);



        int product = productBetweenExtremes(a, n);

        std::cout << "Добуток мiж екстремальними елементами в A: " << product << std::endl;



        sortArrayByMagnitude(a, n);

        std::cout << "Масив A, вiдсортований за модулем: ";

        writeArray(std::cout, a, n);



        sortArrayByMagnitude(b, m);

        std::cout << "Масив B, вiдсортований за модулем: ";

        writeArray(std::cout, b, m);

    }

    else {

        std::cerr << "Невiрний вибiр. Завершення програми." << std::endl;

        return 1;

    }

    return 0;

}