#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Function to apply Vigenère Cipher (Substitution)
string vigenereCipher(string text, string key) {
    string result = "";
    int keyIndex = 0;

    for (char &c : text) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            char keyChar = tolower(key[keyIndex % key.length()]);
            int shift = keyChar - 'a';
            result += (char)((((c - base) + shift) % 26) + base);
            keyIndex++;
        } else {
            result += c; // Non-alphabetic characters are not changed
        }
    }

    return result;
}

// Function to apply columnar transposition cipher
string transpositionCipher(string text, vector<int> key) {
    int numRows = (text.length() + key.size() - 1) / key.size(); // Calculate number of rows
    vector<vector<char>> grid(numRows, vector<char>(key.size(), ' '));

    // Fill the grid row by row
    int index = 0;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < key.size() && index < text.length(); j++) {
            grid[i][j] = text[index++];
        }
    }

    // Read the grid column by column according to the key order
    string result = "";
    for (int j : key) {
        for (int i = 0; i < numRows; i++) {
            if (grid[i][j - 1] != ' ') { // Correct indexing for column
                result += grid[i][j - 1]; // Add character to result
            }
        }
    }

    return result;
}

// Function to perform Double Transposition Cipher
string doubleTranspositionCipher(string text, vector<int> key1, vector<int> key2) {
    // First transposition
    string firstTransposition = transpositionCipher(text, key1);

    // Second transposition
    string secondTransposition = transpositionCipher(firstTransposition, key2);

    return secondTransposition;
}

int main() {
    string text, key;

    // Input the plain text
    cout << "Enter the plain text: ";
    getline(cin, text);

    // Input the Vigenère cipher key
    cout << "Enter the key for Vigenère cipher: ";
    getline(cin, key);

    // Input the keys for the Double Transposition cipher (two integer arrays)
    vector<int> key1 = {3, 1, 4, 2};  // Example key for first transposition
    vector<int> key2 = {2, 3, 1, 4};  // Example key for second transposition

    // Apply Vigenère cipher (Substitution)
    string substitutedText = vigenereCipher(text, key);
    cout << "Ciphertext after Vigenère Cipher: " << substitutedText << endl;

    // Apply Double Transposition cipher
    string finalCiphertext = doubleTranspositionCipher(substitutedText, key1, key2);
    cout << "Final Ciphertext after Double Transposition Cipher: " << finalCiphertext << endl;

    return 0;
}