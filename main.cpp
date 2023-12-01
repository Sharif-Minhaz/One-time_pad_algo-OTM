#include <cctype>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
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

string removeSpaces(string str) {
    string result;

    for (char c : str) {
        if (c != ' ') {
            result += c;
        }
    }

    return result;
}

vector<int> getAlphabetNumber(const string& text) {
    vector<int> resArr(text.length(), 0);  // Initialize vector with zeros

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

vector<int> vectorSub(const vector<int>& vec1, const vector<int>& vec2) {
    // Check if the vectors have the same size
    if (vec1.size() != vec2.size()) {
        cerr << "Error: Vectors must have the same size for substraction." << endl;
        return vector<int>();  // Return an empty vector indicating an error
    }

    // Create a new vector to store the result
    vector<int> result(vec1.size(), 0);

    // Perform vector summation
    for (size_t i = 0; i < vec1.size(); i++) {
        result[i] = vec1[i] - vec2[i];
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
            float res = ((value / 26.0) - 1) * 26;  // overflow handling 26<
            result[i] = res;
        } else if (value < 1) {
            float res = value + (ceil(abs(value) / 26.0) * 26);  // underflow handling <1
            result[i] = res;
        } else {
            result[i] = value;
        }
    }

    return result;
}

string getCipherText(const vector<int>& vec) {
    vector<char> charsPart;

    for (int index : vec) {
        // Check if the index is within the valid range of the alphabets array
        if (index >= 0 && index < 26) {
            charsPart.push_back(alphabets[index - 1]);
        } else {
            cerr << "Error: Out of range";
        }
    }

    // Convert the character vector to a string
    string result(charsPart.begin(), charsPart.end());

    return result;
}

void printIntVector(vector<int>& vec) {
    for (size_t i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;
}

int oneTimePadEncryption() {
    string plainTextInput = "", keyInput = "";

    // user input for plaintext
    cout << "Enter the plain text: ";
    getline(cin, plainTextInput);

    while (plainTextInput.empty()) {
        getline(cin, plainTextInput);
    }

    // user input for key
    cout << "Enter the key: ";
    getline(cin, keyInput);

    string plainText = removeSpaces(toLowerCase(plainTextInput));
    string key = removeSpaces(toLowerCase(keyInput));

    if (plainText.length() == 0 || key.length() == 0) {
        cout << "Plain text and key both required." << endl;
        return 0;
    }

    // if the plain text's length is greater than key's length, then the key will be repeated
    if (key.length() < plainText.length()) {
        for (int i = 0; i < plainText.length(); i++) {
            // checking if the key string is full with repeated string
            if (key.length() > plainText.length()) break;
            key += key;
        }
    }

    // slicing out the overflow string from key, exact key length will be plain text's length
    key = key.substr(0, plainText.length());

    // get alphabet number from the string
    vector<int> plainTextNum = getAlphabetNumber(plainText), keyNum = getAlphabetNumber(key);

    // get summation of plain text vector and key text vector
    vector<int> summation = vectorSum(plainTextNum, keyNum);

    // handling overflow and underflow
    vector<int> fixedRange = rangeFixer(summation);

    // getting final cipherText
    string cipherText = getCipherText(fixedRange);

    cout << endl
         << "P: " << plainText << endl;
    cout << "P1: ";
    printIntVector(plainTextNum);

    cout << "K: " << key << endl;
    cout << "K1: ";
    printIntVector(keyNum);

    cout << "Ci: ";
    printIntVector(summation);

    cout << "C1: ";
    printIntVector(fixedRange);

    cout << "C (Ciphertext) : " << cipherText;
}

int oneTimePadDecryption() {
    string cipherTextInput = "", keyInput = "";

    // user input for ciphertext
    cout << "Enter the Ciphertext: ";
    getline(cin, cipherTextInput);

    while (cipherTextInput.empty()) {
        getline(cin, cipherTextInput);
    }

    // user input for key
    cout << "Enter the key: ";
    getline(cin, keyInput);

    string cipherText = removeSpaces(toLowerCase(cipherTextInput));
    string key = removeSpaces(toLowerCase(keyInput));

    if (cipherText.length() == 0 || key.length() == 0) {
        cout << "Ciphertext and key both required." << endl;
        return 0;
    }

    // if the plain text's length is greater than key's length, then the key will be repeated
    if (key.length() < cipherText.length()) {
        for (int i = 0; i < cipherText.length(); i++) {
            // checking if the key string is full with repeated string
            if (key.length() > cipherText.length()) break;
            key += key;
        }
    }

    // slicing out the overflow string from key, exact key length will be plain text's length
    key = key.substr(0, cipherText.length());

    // get alphabet number from the string
    vector<int> cipherTextNum = getAlphabetNumber(cipherText), keyNum = getAlphabetNumber(key);

    // get subtraction of plain text vector and key text vector
    vector<int> subtraction = vectorSub(cipherTextNum, keyNum);

    // handling overflow and underflow
    vector<int> fixedRange = rangeFixer(subtraction);

    // getting final plaintext
    string plainText = getCipherText(fixedRange);

    cout << endl
         << "C: " << cipherText << endl;
    cout << "C1: ";
    printIntVector(cipherTextNum);

    cout << "K: " << key << endl;
    cout << "K1: ";
    printIntVector(keyNum);

    cout << "Pi: ";
    printIntVector(subtraction);

    cout << "P1: ";
    printIntVector(fixedRange);

    cout << "P (Plain text) : " << plainText;
}

int main() {
    int choice = 1;
    cout << "Choose operation: " << endl;
    cout << "-> Encryption (1)" << endl;
    cout << "-> Decryption (2)" << endl;

    try {
        cout << "Your answer: ";
        cin >> choice;
        cout << endl;
    } catch (const exception& e) {
        cerr << e.what() << endl;
    }

    switch (choice) {
        case 1:
            cout << "<---One Time Pad Encryption--->" << endl;
            oneTimePadEncryption();
            break;
        case 2:
            cout << "<---One Time Pad Decryption--->" << endl;
            oneTimePadDecryption();
            break;
        default:
            cout << "Invalid choice" << endl;
            break;
    }

    return 0;
}
