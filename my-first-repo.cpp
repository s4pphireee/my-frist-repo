#include <iostream>
#include <cmath>
#include <algorithm>
#include <random>

void InputSize(int32_t& size){
    
    std::cout << "Input size: " << std::endl;
    std::cin >> size;
    
    if (size <= 0){
        throw std::invalid_argument("Wrong size");
    }
}

void createArray(double*& array, int32_t size){
    array = new double[size];
}

void fillArray(double* array, int32_t size){
    std::cout << "Input elements:" << std::endl;
    for (int32_t i{0}; i < size; ++i){
        std::cin >> array[i];
    }
}

void fillArrayWithRandom(double*& array, int32_t size, double lowerBound, double upperBound) {
    std::random_device rd;              
    std::mt19937 gen(rd());             
    std::uniform_real_distribution<> dis(lowerBound, upperBound); 

    for (int32_t i = 0; i < size; ++i) {
        array[i] = dis(gen);
    }
}

void menu(double*& array, int32_t size) {
    int8_t choice;
    std::cout << "Choose a method to fill:\n";
    std::cout << "1. Manual\n";
    std::cout << "2. Random\n"; 
    std::cout << "Your choice: ";
    std::cin >> choice;

    switch (choice) {
        case '1':
            fillArray(array, size);
            break;
        case '2': {
            double lowerBound;
            double upperBound;
            std::cout << "Enter a lower and upper bounds for rand: ";
            std::cin >> lowerBound >> upperBound;
            fillArrayWithRandom(array, size, lowerBound, upperBound);
            break;
        }
        default:
            std::cout << "Incorrect option.\n";
            menu(array, size);
            break;
    }
}

int32_t findMaxAbsIndex(double* array, int32_t size, double& maxAbsElement) {
    maxAbsElement = array[0];
    int32_t index = 0;

    for (int32_t i = 1; i < size; i++) {
        if (abs(array[i]) > abs(maxAbsElement)) {
            maxAbsElement = array[i];
            index = i;
        }
    }
    return index;
}

int32_t findBalancingIndex(double* array, int32_t size) {
    double totalSum = 0;
    for (int32_t i = 0; i < size; i++) {
        totalSum += array[i];   
    }
    
    double leftSum = 0;
    double minDiff = totalSum;
    int32_t index = -1;

    for (int32_t i = 0; i < size; i++) {
        double rightSum = totalSum - leftSum - array[i];
        double diff = abs(leftSum - rightSum);
        if (diff < minDiff) {
            minDiff = diff;
            index = i;
        }
        leftSum += array[i];
    }
    return index;
}

int32_t findNegative(double* array, int32_t size) {
    int32_t index = -1;
    for (int32_t i = 0; i < size; ++i) {
        if (array[i] < 0) {
            index = i;
            break;
        }
    }
    
    return index;
}

double findSumAfterNegative(double* array, int32_t size, int32_t negativeIndex) {
    double sum{0};
    for (int32_t i = negativeIndex + 1; i < size; ++i) { 
        sum += array[i];   
    }

    return sum;
}

void arrayOutput(double* array, int32_t size) {
    std::cout << "Compressed array: ";
    for (int32_t i = 0; i < size; ++i){
        std::cout << array[i] << ", ";
    }
    std::cout << std::endl;
}
void inputNumber(double& number){
    std::cout << "Enter a number to delete from array: \n";
    std::cin >> number;
}


void compressArray(double* array, int32_t size, double*& copy_array) {
    copy_array = new double[size];
    std::copy(array, copy_array + size, copy_array);
    double number{};
    inputNumber(number);
    int32_t index = 0;
    
    for (int32_t i = 0; i < size; ++i) {
        if (copy_array[i] != number) {
            copy_array[index++] = copy_array[i];
        }
    }
    
    for (int32_t i = index; i < size; ++i) {
        copy_array[i] = 0;
    }
    arrayOutput(copy_array, size);
    delete [] copy_array;
}
void checkBorders(double& left_border, double& right_border){
    if (left_border > right_border){
        std::swap(left_border,right_border);
    }
}

void inputInterval(double& left_border, double& right_border){
    std::cout << "Enter a left border index: \n";
    std::cin >> left_border;
    std::cout << "Enter a right border index: \n";
    std::cin >> right_border;
    checkBorders(left_border, right_border);
}

void compressArrayViaInterval(double*& array, int32_t size, double*& copy_array) {
    copy_array = new double[size];
    std::copy(array, copy_array + size, copy_array);
    double left_border{};
    double right_border{};
    inputInterval(left_border, right_border);
    int32_t index = 0;
    
    for (int32_t i = 0; i < size; ++i) {
        if (copy_array[i] <= left_border || copy_array[i] >= right_border) {
            copy_array[index++] = copy_array[i];
        }
    }
    
    for (int32_t i = index; i < size; ++i) {
        copy_array[i] = 0;
    }
    arrayOutput(copy_array, size);
    delete [] copy_array;
}


double findMinAbsMaxIndex(double* array, int32_t size) {
    int32_t minIndex = 0;
    double minAbsValue = std::abs(array[0]);

    for (int32_t i = 1; i < size; ++i) {
        double currentAbsValue = std::abs(array[i]);
        if (currentAbsValue < minAbsValue) {
            minAbsValue = currentAbsValue;
            minIndex = i;
        } 
        else if (currentAbsValue == minAbsValue) {
            minIndex = i; 
        }
    }

    return array[minIndex];
}

int main(){

    int32_t size{};
    
    try {
        
        InputSize(size);
        double* array = nullptr;

        createArray(array, size);
        menu(array, size);
        
        double maxAbsElement;
        int32_t maxAbsIndex = findMaxAbsIndex(array, size, maxAbsElement);
        std::cout << "Max abs element: " << maxAbsElement << ", its index: " << maxAbsIndex << std::endl;
        
        int32_t balancingIndex = findBalancingIndex(array, size);
        std::cout << "Index of an element where is diff is the less: " << balancingIndex << std::endl;
        
        int32_t negativeIndex = findNegative(array, size);
        if (negativeIndex == -1) {
            std::cout << "There are no negatives in array" << std::endl;
        }
        else {
            double sumAfterNegative = findSumAfterNegative(array, size, negativeIndex);
            std::cout << "Sum of elements after 1st negative: " << sumAfterNegative << std::endl;
        }
        
        double* copy_array = nullptr;
        
        compressArray(array, size, copy_array);
        compressArrayViaInterval(array, size, copy_array);
        
        std::cout << "Minimal element with max index: " << findMinAbsMaxIndex(array, size) << std::endl;
        
        delete [] array;
    }
    catch (std::invalid_argument &e){
        std::cout << e.what();
    }
    return 0;
}
