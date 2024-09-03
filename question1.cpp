#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>  

using namespace std;

class BigUnsignedInt {
    string number; // Store the number as a string
    int size; // The actual length of the number

public:
    // Constructor to initialize from unsigned long long
    BigUnsignedInt(unsigned long long n = 0) {
        number = to_string(n);
        size = number.length();
    }

    // Constructor to initialize from a string
    BigUnsignedInt(const string& num) {
        number = num;
        size = number.length();
    }

    // Return the length of the number
    int getSize() const {
        return size;
    }

    // Overload the addition operator
    friend BigUnsignedInt operator+(const BigUnsignedInt& lhs, const BigUnsignedInt& rhs) {
        string result = "";
        int carry = 0;
        int lhs_len = lhs.number.length();
        int rhs_len = rhs.number.length();

        // Start adding from the least significant digit
        for (int i = 0; i < max(lhs_len, rhs_len); ++i) {
            int digit1 = i < lhs_len ? lhs.number[lhs_len - 1 - i] - '0' : 0;
            int digit2 = i < rhs_len ? rhs.number[rhs_len - 1 - i] - '0' : 0;

            int sum = digit1 + digit2 + carry;
            carry = sum / 10;
            result.push_back(sum % 10 + '0');
        }

        if (carry > 0) {
            result.push_back(carry + '0');
        }

        reverse(result.begin(), result.end());
        return BigUnsignedInt(result);
    }

    // Overload the subtraction operator
    friend BigUnsignedInt operator-(const BigUnsignedInt& lhs, const BigUnsignedInt& rhs) {
        if (rhs.number.length() > lhs.number.length() || 
            (rhs.number.length() == lhs.number.length() && rhs.number > lhs.number)) {
            throw invalid_argument("Cannot subtract a larger number from a smaller one in this implementation.");
        }

        string result = "";
        int borrow = 0;
        int lhs_len = lhs.number.length();
        int rhs_len = rhs.number.length();

        // Start subtracting from the least significant digit
        for (int i = 0; i < lhs_len; ++i) {
            int digit1 = lhs.number[lhs_len - 1 - i] - '0';
            int digit2 = i < rhs_len ? rhs.number[rhs_len - 1 - i] - '0' : 0;

            int diff = digit1 - digit2 - borrow;
            if (diff < 0) {
                diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }

            result.push_back(diff + '0');
        }

        // Remove leading zeros
        while (result.length() > 1 && result.back() == '0') {
            result.pop_back();
        }

        reverse(result.begin(), result.end());
        return BigUnsignedInt(result);
    }

    // Overload the stream insertion operator to print BigUnsignedInt
    friend ostream& operator<<(ostream& os, const BigUnsignedInt& obj) {
        os << obj.number;
        return os;
    }
};

int main() {
    string num1, num2; 
    ifstream inputFile("numbers.txt");
    if (!inputFile) {
        cerr << "Error opening file." << endl; 
        return 1;
    }

    inputFile >> num1 >> num2; 
    inputFile.close();

    BigUnsignedInt bigInt1(num1);
    BigUnsignedInt bigInt2(num2);

    BigUnsignedInt sum = bigInt1 + bigInt2;
    BigUnsignedInt difference = bigInt1 - bigInt2;

    cout << "First number: " << bigInt1 << endl;
    cout << "Second number: " << bigInt2 << endl;
    cout << "Sum: " << sum << endl;
    cout << "Difference: " << difference << endl;

    return 0;
}
