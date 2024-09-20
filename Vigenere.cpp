#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// Function to generate the key by repeating it only for alphabetic characters
string generateKey(string str, string key) {
    string newKey = "";
    int keyIndex = 0;

    // Extend the key only for alphabetic characters
    for (int i = 0; i < str.size(); i++) {
        if (isalpha(str[i])) {
            newKey += key[keyIndex % key.size()];
            keyIndex++;
        } else {
            newKey += str[i];  // Non-alphabetic characters are not encrypted
        }
    }
    return newKey;
}

// Function to encrypt the text using the Vigenere cipher
string vigenereEncrypt(string text, string key) {
    string cipher_text = "";

    for (int i = 0; i < text.size(); i++) {
        if (isalpha(text[i])) {
            // Encrypt only alphabetic characters, preserving case
            char base = islower(text[i]) ? 'a' : 'A';
            char x = (text[i] - base + (tolower(key[i]) - 'a')) % 26 + base;
            cipher_text += x;
        } else {
            cipher_text += text[i];  // Non-alphabetic characters remain unchanged
        }
    }
    return cipher_text;
}

// Function to decrypt the cipher text using the Vigenere cipher
string vigenereDecrypt(string cipher_text, string key) {
    string orig_text = "";

    for (int i = 0; i < cipher_text.size(); i++) {
        if (isalpha(cipher_text[i])) {
            // Decrypt only alphabetic characters, preserving case
            char base = islower(cipher_text[i]) ? 'a' : 'A';
            char x = (cipher_text[i] - base - (tolower(key[i]) - 'a') + 26) % 26 + base;
            orig_text += x;
        } else {
            orig_text += cipher_text[i];  // Non-alphabetic characters remain unchanged
        }
    }
    return orig_text;
}

int main() {
    string text, key;

    // Input text from the user, which can include spaces
    cout << "Enter the text to encrypt (spaces allowed): ";
    getline(cin, text);

    // Input the key
    cout << "Enter the key (minimum 12 characters): ";
    getline(cin, key);

    // Ensure the key is long enough
    while (key.size() < 12) {
        cout << "Key too short. Please enter a key with at least 12 characters: ";
        getline(cin, key);
    }

    // Generate the key for encryption based on the text length, considering only alphabetic characters
    string keyGenerated = generateKey(text, key);

    // Encrypt and decrypt the text
    string encrypted = vigenereEncrypt(text, keyGenerated);
    string decrypted = vigenereDecrypt(encrypted, keyGenerated);

    // Output the results
    cout << "Encrypted Text: " << encrypted << endl;
    cout << "Decrypted Text: " << decrypted << endl;

    return 0;
}

