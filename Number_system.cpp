#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

void converter(string num, int orig_sys, int trans_sys);
double from_any_to_dec(string num, int orig_sys, bool* input_err);
string from_dec_to_any(double num, int trans_sys);
int char_to_int(char c);
char int_to_char(int c);

int main() {
    string num;
    int orig_sys, trans_sys;
    cout << "Input number: " << endl;
    cin >> num;
    cout  << "Input original number system: " << endl;
    cin >> orig_sys;
    cout  << "Input translate number system: " << endl;
    cin >> trans_sys;
    converter(num, orig_sys, trans_sys);
    return 0;
}

void converter(string num, int orig_sys, int trans_sys) {
    double dec_num;
    string convert_num;
    bool input_err = 0;
    dec_num = from_any_to_dec(num, orig_sys, &input_err);
    if(input_err) {
        cout << "Invalid input!";
        return;
    }
    convert_num = from_dec_to_any(dec_num, trans_sys);
    cout << convert_num;
    return;
}

double from_any_to_dec(string num, int orig_sys, bool* input_err) {
    for(int i = 0; i < num.length(); i++) {
        if (!(((num[i] >= '0' && num[i] <= '9') || (num[i] >= 'A' && num[i] <= 'Z') || num[i] == '.')&& ((num[i] - '0') < orig_sys || (num[i] - 'A') < orig_sys))) {
            *input_err = 1;
            return 0 ;
        }
    }
    int dot_pos = (int)num.find('.');
    double dec_num = 0.0;
    if(dot_pos < 0) {
        for(int i = 0; i < num.length(); i++) {
            dec_num += (double)char_to_int(num[i]) * pow((double)orig_sys, (double)(num.length() - 1 - i));
        }
    } else {
        for(int i = 0; i < dot_pos; i++) {
            dec_num += (double)char_to_int(num[i]) * pow((double)orig_sys, (double)(dot_pos - 1 - i));
        }
        num.erase(0, dot_pos + 1);
        for (int i = 0; i < num.length(); i++) {
            dec_num += (double)char_to_int(num[i]) * pow((double)orig_sys, (double)(-1 * (i + 1)));
        }
    }
    return dec_num;
}

string from_dec_to_any(double num, int trans_sys) {
    string convert_num, reverse_int_part;
    double stop = pow(10.0, -8.0);
    int int_part = (int)num;
    double frac_part = num - (double)int_part;
    do {
        int remind = int_part % trans_sys;
        int_part /= trans_sys;
        reverse_int_part.push_back(int_to_char(remind));
    } while(int_part != 0);
    for(int i = (int)reverse_int_part.length() - 1; i >=0; i--) {
        convert_num.push_back(reverse_int_part[i]);
    }
    if(frac_part != 0) {
        convert_num.push_back('.');
        while (stop != 1) {
            frac_part *= trans_sys;
            stop *= 10;
            convert_num.push_back(int_to_char((int) frac_part));
            frac_part -= (int) frac_part;
        }
    }
    return convert_num;
}

int char_to_int(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 10;
    }
}

char int_to_char(int c) {
    if ( c >= 0 && c <= 9 ){
        return c + '0';
    }else{
        return c + 'A' - 10;
    }
}