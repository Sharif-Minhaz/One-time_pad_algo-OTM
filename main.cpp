#include <cctype>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

const char alphabets[] = "abcdefghijklmnopqrstuvwxyz";

string toLowerCase(string text) {
    string str = text;

    // Convert each character in the string to lowercase
    for (char& c : str) {
        c = tolower(c);
    }

    return str;
}

vector<int> getAlphabetNumber(const string& text) {
    std::vector<int> resArr(text.length(), 0);  // Initialize vector with zeros

    for (size_t i = 0; i < text.length(); i++) {
        for (int j = 0; j < 26; j++) {
            if (text[i] == alphabets[j]) {
                resArr[i] = j + 1;
                break;  // Once a match is found, exit the inner loop
            }
        }
    }

    return resArr;
}

vector<int> vectorSum(const vector<int>& vec1, const vector<int>& vec2) {
    // Check if the vectors have the same size
    if (vec1.size() != vec2.size()) {
        cerr << "Error: Vectors must have the same size for summation." << endl;
        return vector<int>();  // Return an empty vector indicating an error
    }

    // Create a new vector to store the result
    vector<int> result(vec1.size(), 0);

    // Perform vector summation
    for (size_t i = 0; i < vec1.size(); i++) {
        result[i] = vec1[i] + vec2[i];
    }

    return result;
}

vector<int> rangeFixer(const vector<int>& vec) {
    // Create a new vector to store the result
    vector<int> result(vec.size(), 0);

    // Perform vector iteration
    for (size_t i = 0; i < vec.size(); i++) {
        int value = vec[i];

        if (value > 26) {
            float res = ((value / 26) - 1) * 26;
            result[i] = res;  // TODO: logical error
        } else if (value < 1) {
            float res = value + (ceil(abs(value) / 26) * 26);
            result[i] = res;
        } else {
            result[i] = value;
        }
    }

    return result;
}

int main() {
    string plainTextInput = "APPLE", keyInput = "ELEPHANT";

    // user input for plaintext
    // cout << "Enter the plain text: ";
    // cin >> plainText;

    // user input for key
    // cout << "Enter key: ";
    // cin >> key;

    string plainText = toLowerCase(plainTextInput);
    string key = toLowerCase(keyInput);

    // if the plain text's length is greater than key's length, then the key will be repeated
    if (key.length() < plainText.length()) {
        for (int i = 0; i < plainText.length(); i++) {
            // checking if the key string is full with repeated string
            if (key.length() > plainText.length()) break;
            key += key;
        }
    }

    // slicing out the overflow string
    key = key.substr(0, plainText.length());

    // get alphabet number from the string
    vector<int> plainTextNum = getAlphabetNumber(plainText), keyNum = getAlphabetNumber(key);

    vector<int> summation = vectorSum(plainTextNum, keyNum);
    vector<int> fixedRange = rangeFixer(summation);

    cout << plainText << " " << key << " ";

    for (size_t i = 0; i < fixedRange.size(); i++) {
        std::cout << fixedRange[i] << " ";
    }

    return 0;
}