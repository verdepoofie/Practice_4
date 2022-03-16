#include <iostream>
using namespace std;

int roman_numerals();
int err_out();

int main() {
    int ans = roman_numerals();
    cout << ans;
    return 0;
}

int roman_numerals() {
    cout << "Roman numerals" << endl << "Input roman numeral:" << endl;
    string roman, next_err;
    int dec = 0;
    cin >> roman;
    for (int i = 0; i < roman.length(); i++) {
        if ((roman[i] != 'I') && (roman[i] != 'X') && (roman[i] != 'C') && (roman[i] != 'M') && (roman[i] != 'V') && (roman[i] != 'L') && (roman[i] != 'D')) {
            return err_out();
        }
        if ((roman[i] == 'I') || (roman[i] == 'X') || (roman[i] == 'C') || (roman[i] == 'M')) {
            int multiply = 0;
            char fivefold, tenfold;
            switch (roman[i]) {
                case 'I': {
                    fivefold = 'V';
                    tenfold = 'X';
                    multiply = 1;
                    next_err = {'L', 'C', 'D', 'M'};
                    break;
                }
                case 'X': {
                    fivefold = 'L';
                    tenfold = 'C';
                    multiply = 10;
                    next_err = {'D', 'M'};
                    break;
                }
                case 'C': {
                    fivefold = 'D';
                    tenfold = 'M';
                    multiply = 100;
                    next_err = {'u'};
                    break;
                }
                case 'M': {
                    multiply = 1000;
                    next_err = {'u'};
                    break;
                }
            }
            if (i != roman.length() - 1){
                for (int j = 0; j < next_err.length() - 1; j++) {
                    if(roman[i + 1] == next_err[j]) {
                        return err_out();
                    }
                }
                if (roman[i + 1] == fivefold) {
                    dec += 4 * multiply;
                }
                if (roman[i + 1] == tenfold) {
                    dec += 9 * multiply;
                }
                if (roman[i + 1] == roman[i]) {
                    dec += 2 * multiply;
                }
            } else {
                dec += multiply;
            }
            if (roman.length() >= 4) {
                if (i <= roman.length() - 4) {
                    if ((roman[i + 3] == roman[i]) && (roman[i + 2] == roman[i]) && (roman[i + 1] == roman[i])) {
                        return err_out();
                    }
                }
            }
            i++;
            continue;
        }
        if ((roman[i] == 'V') || (roman[i] == 'L') || (roman[i] == 'D')) {
            switch (roman[i]) {
                case 'V': {
                    dec += 5;
                    next_err = {'V', 'X', 'L', 'C', 'D', 'M'};
                    break;
                }
                case 'L': {
                    dec += 50;
                    next_err = {'L', 'C', 'D', 'M'};
                    break;
                }
                case 'D': {
                    dec += 500;
                    next_err = {'D', 'M'};
                    break;
                }
            }
            if (i != roman.length() - 1) {
                for (int j = 0; j < next_err.length() - 1; j++) {
                    if(roman[i + 1] == next_err[j]) {
                        return err_out();
                    }
                }
            }
        }
    }
    return dec;
}

int err_out() {
    cout << "Invalid input" << endl;
    return -1;
}