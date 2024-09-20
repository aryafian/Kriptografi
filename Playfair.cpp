#include <iostream>
#include <string>
#include <vector>
using namespace std;

char playfairMatrix[5][5];

// Function to generate Playfair Cipher matrix
void generatePlayfairMatrix(string key) {
    vector<int> letters(26, 0);
    letters['J' - 'A'] = 1; // Treat 'J' as 'I'

    int row = 0, col = 0;

    // Loop through the key to fill the matrix
    for (int i = 0; i < key.length(); i++) {
        char c = toupper(key[i]);
        if (c == 'J') c = 'I'; // Treat 'J' as 'I'
        if (letters[c - 'A'] == 0) {
            playfairMatrix[row][col] = c;
            letters[c - 'A'] = 1;
            col++;
            if (col == 5) {
                col = 0;
                row++;
            }
        }
    }

    // Fill the remaining matrix with other letters
    for (char c = 'A'; c <= 'Z'; c++) {
        if (letters[c - 'A'] == 0 && c != 'J') { // Skip 'J'
            playfairMatrix[row][col] = c;
            col++;
            if (col == 5) {
                col = 0;
                row++;
            }
        }
    }
}

// Function to remove spaces from the input text
string removeSpaces(string text) {
    string result = "";
    for (int i = 0; i < text.size(); i++) {
        if (text[i] != ' ') {
            result += toupper(text[i]); // Convert to uppercase
        }
    }
    return result;
}

// Function to encrypt using Playfair Cipher
string playfairEncrypt(string text) {
    string encrypted = "";

    // Iterate through pairs of characters
    for (int i = 0; i < text.length(); i += 2) {
        char first = text[i];
        char second = (i + 1 < text.length()) ? text[i + 1] : 'X';

        if (first == second) {
            second = 'X'; // If both characters are the same, replace the second with 'X'
        }

        // Find the position of both characters in the matrix
        int row1, col1, row2, col2;
        for (int row = 0; row < 5; row++) {
            for (int col = 0; col < 5; col++) {
                if (playfairMatrix[row][col] == first) {
                    row1 = row;
                    col1 = col;
                }
                if (playfairMatrix[row][col] == second) {
                    row2 = row;
                    col2 = col;
                }
            }
        }

        // Same row
        if (row1 == row2) {
            encrypted += playfairMatrix[row1][(col1 + 1) % 5];
            encrypted += playfairMatrix[row2][(col2 + 1) % 5];
        }
        // Same column
        else if (col1 == col2) {
            encrypted += playfairMatrix[(row1 + 1) % 5][col1];
            encrypted += playfairMatrix[(row2 + 1) % 5][col2];
        }
        // Rectangle swap
        else {
            encrypted += playfairMatrix[row1][col2];
            encrypted += playfairMatrix[row2][col1];
        }
    }

    return encrypted;
}

int main() {
    string key, text;
    cout << "Enter key (A-Z): ";
    cin >> key;
    cin.ignore();  // To clear the newline character after the key input
    cout << "Enter text (A-Z, spaces allowed): ";
    getline(cin, text);  // Use getline to allow spaces in the input

    generatePlayfairMatrix(key);

    // Remove spaces and prepare the text for encryption
    string processedText = removeSpaces(text);

    // Encrypt the processed text
    string encrypted = playfairEncrypt(processedText);
    cout << "Encrypted Text: " << encrypted << endl;

    // Decryption can be implemented similarly by reversing the steps.
    return 0;
}

