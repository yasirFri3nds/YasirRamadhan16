#include <iostream>
#include <stack>
#include <sstream>
#include <cmath>
#include <string>
using namespace std;

class Stack {
private:
    stack<float> st;

public:
    void push(float value) {
        st.push(value);
    }

    float pop() {
        if (!st.empty()) {
            float value = st.top();
            st.pop();
            return value;
        } else {
            cout << "Stack kosong, tidak bisa pop.\n";
            return 0;
        }
    }

    bool isEmpty() {
        return st.empty();
    }
};

float evaluasiPostfix(const string& ekspresi) {
    Stack stack;
    istringstream iss(ekspresi);
    string token;

    cout << "Langkah-langkah evaluasi postfix:\n";

    while (iss >> token) {
        if (isdigit(token[0])) {  
            float nilai = stof(token);
            stack.push(nilai);
            cout << "Push " << nilai << " ke stack\n";
        } else {  
            float operand2 = stack.pop();
            float operand1 = stack.pop();
            float hasil;

            if (token == "+") {
                hasil = operand1 + operand2;
            } else if (token == "-") {
                hasil = operand1 - operand2;
            } else if (token == "*") {
                hasil = operand1 * operand2;
            } else if (token == "/") {
                hasil = operand1 / operand2;
            } else if (token == "^") {
                hasil = pow(operand1, operand2);
            } else {
                cout << "Operator tidak dikenal: " << token << endl;
                return 0;
            }

            stack.push(hasil);
            cout << "Evaluasi " << operand1 << " " << token << " " << operand2 << " = " << hasil << ", push hasil ke stack\n";
        }
    }

    return stack.pop(); 
}

int main() {
    string ekspresi;
    cout << "Masukkan ekspresi postfix (gunakan spasi untuk memisahkan setiap elemen): ";
    getline(cin, ekspresi);

    float hasil = evaluasiPostfix(ekspresi);
    cout << "Hasil akhir dari ekspresi postfix: " << hasil << endl;

    return 0;
}