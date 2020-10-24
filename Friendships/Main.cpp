#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <cstdlib>
#include <list>

//Moves vector element from original index to destination, shifting all existing values between
//destination and origin 1 position towards origin, 
//and then changing the destination index's value to the origin index's value
template <typename T>
void moveVectorElement(std::vector<T>& vector, int originIndex, int destinationIndex) {
    T valueAtOriginIndex = vector.at(originIndex);
    if(originIndex > destinationIndex) {
        for(int i = originIndex; i > destinationIndex; i--) {            
            vector.at(i) = vector.at(i - 1);
        }
    }
    else if(destinationIndex > originIndex) {
        for(int i = originIndex; i < destinationIndex; i++) {
            vector.at(i) = vector.at(i + 1);
        }
    }
    vector.at(destinationIndex) = valueAtOriginIndex;
}

template <typename T>
void insertionSort_numeric(std::vector<T>& inputList) {
    for(int i = 0; i < inputList.size(); i++) {
        T currentVal = inputList.at(i);
        for(int j = 0; j < i; j++) {
            if(currentVal < inputList.at(j)) {
                moveVectorElement(inputList, i, j);
                break;
            }
        }
    }
}

//Merge 2 smaller vectors into 1 bigger vector
template <typename T>
void mergeVectors(std::vector<T>& firstHalf, std::vector<T>& secondHalf, std::vector<T>& result) {
    result.reserve(firstHalf.size() + secondHalf.size());

    //Saving indices so that we don't have to delete the first element in the vector every time we move one element
    //to the result vector, since that's really inefficient
    int firstHalfIndex = 0;
    int secondHalfIndex = 0;

    while(firstHalf.size() > firstHalfIndex || secondHalf.size() > secondHalfIndex) {
        if(firstHalf.size() > firstHalfIndex && secondHalf.size() > secondHalfIndex) {
            if(firstHalf.at(firstHalfIndex) <= secondHalf.at(secondHalfIndex)) {
                result.push_back(firstHalf.at(firstHalfIndex));
                firstHalfIndex++;
            }
            else {
                result.push_back(secondHalf.at(secondHalfIndex));
                secondHalfIndex++;
            }
        }
        else if(firstHalf.size() > firstHalfIndex) {
            result.push_back(firstHalf.at(firstHalfIndex));
            firstHalfIndex++;
        }   
        else {
            result.push_back(secondHalf.at(secondHalfIndex));
            secondHalfIndex++;
        }
    }
}

template<typename T>
void mergeSort_numeric(std::vector<T>& inputList, std::vector<T>& result) {
    //If list is less than 16 long, just use insertion sort.
    if(inputList.size() > 15) {
        //Initializing firstHalf and secondHalf with vector range constructor
        auto middleIterator = inputList.begin() + (int(inputList.size()) / 2);
        std::vector<T> firstHalf(inputList.begin(), middleIterator);
        std::vector<T> secondHalf(middleIterator, inputList.end());

        std::vector<T> firstHalfSorted;
        firstHalfSorted.reserve(firstHalf.size());
        mergeSort_numeric(firstHalf, firstHalfSorted);

        std::vector<T> secondHalfSorted;
        secondHalfSorted.reserve(firstHalf.size());
        mergeSort_numeric(secondHalf, secondHalfSorted);

        mergeVectors(firstHalfSorted, secondHalfSorted, result); 
    }
    else if (inputList.size() > 1) {
        insertionSort_numeric(inputList);
        result = inputList;
    }
    
    //In case it's just one element
    else {
        result = inputList;
    }
}

template<typename T>
void printVector(std::vector<T> vector) {
    for(int i = 0; i < vector.size(); i++) {
        std::cout << vector[i] << " ";
    }
    std::cout << std::endl;
} 

int main() {
    std::string input;
    int n;
    std::getline(std::cin, input); 
    n = std::stoi(input);

    std::vector<int> array, sortedArray;
    array.reserve(n);
    sortedArray.reserve(n);
    
    //Clearing input
    input = "";
    std::getline(std::cin, input);

    //Storing the curent characters of the int that is being parsed.
    std::string currentInt;
    for(unsigned long long int i = 0; i < input.length(); i++) {
        char c = input.at(i);
        if(c != ' ') {
            currentInt += c;
        }
        else {
            int parsedInt = std::stoi(currentInt);
            array.push_back(parsedInt);
            currentInt = "";
        }
    }

    if(currentInt != "") {
        int parsedInt = std::stoi(currentInt);
        array.push_back(parsedInt);
        currentInt = "";
    }

    mergeSort_numeric(array, sortedArray);
    
    printVector(sortedArray);

    return 0;
}