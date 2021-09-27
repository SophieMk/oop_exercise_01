#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class FazzyNumer {
    double e1;
    double x;
    double er;
public:
    FazzyNumer() {
        this->x = 0;
        this->e1 = 0;
        this->er = 0;
    }

    FazzyNumer(double x, double e1, double er) {
        this->e1 = e1;
        this->x = x;
        this->er = er;
    }

    FazzyNumer ReverseNum() {
        FazzyNumer result(1 / (this->x + this->er), 1 / this->x,
                          1 / (this->x - this->e1));
        return result;
    }

    FazzyNumer operator+(FazzyNumer other) {
        FazzyNumer result(this->x + other.x - this->e1 - other.e1, this->x + other.x,
                          this->x + other.x + this->er + other.er);
        return result;
    }

    FazzyNumer operator-(FazzyNumer other) {
        FazzyNumer result(this->x - other.x - this->e1 - other.e1, this->x - other.x,
                          this->x - other.x + this->er + other.er);
        return result;
    }

    FazzyNumer operator*(FazzyNumer other) {
        FazzyNumer result(this->x * other.x - this->e1 * other.x - this->x * other.e1, this->x * other.x,
                          this->x * other.x + this->er * other.x + this->x * other.er);
        return result;
    }

    FazzyNumer operator/(FazzyNumer other) {
        FazzyNumer result((this->x - this->e1) / (other.x + other.er), this->x / other.x,
                          (this->x + this->er) / (other.x - other.e1));
        return result;
    }

    friend ostream& operator<<(ostream& os, FazzyNumer& com) {
        os << "(" << com.x << ", " << com.e1 << ", " << com.er << ")";
        return os;
    }

};

bool is_number(string x) {
    for (int i = 0; i < x.length(); i++) {
        if (x[i] < '0' || x[i] > '9') {
            return false;
        }
    }
    return true;
}

int main() {
    ifstream f("test_01.txt");
    if (!f) {
        cout << "Error! File not found!" << endl;
        return 1;
    }
    vector<double> e;
    vector<string> op;
    vector<double> temp;
    bool pr = false;
    while (!f.eof()) {
        string c;
        f >> c;
        if (is_number(c)) {
            if (c == "1") {
                pr = true;
            }
            e.push_back(atof(c.c_str()));
        } else if (c == "/" || c == "*" || c == "+" || c == "-") {
            if (c == "/" && pr) {
                e.push_back(0);
                pr = false;
            }
            op.push_back(c);
        } else {
            for(int h = 0; h < 4; h++) {
                e.push_back(0);
            }
            op.push_back(".");
        }
    }
    int n = e.size() / 4;
    FazzyNumer* res = new FazzyNumer[n];
    string* error = new string[n];
    for (int j = 0; j < n; j++) {
        error[j] = "0";
    }

    for (int l = 0; l < e.size() - 1; l += 4) {
        FazzyNumer a(e[l], e[l + 1], e[l + 1]);
        FazzyNumer b(e[l + 2], e[l + 3], e[l + 3]);
        int g = l / 4;
        if (op[g] == "+") {
            res[g] = a + b;
        } else if (op[g] == "-") {
            res[g] = a + b;
        } else if (op[g] == "*") {
            res[g] = a * b;
        } else if (op[g] == "/") {
            if (e[l + 2] == 0 && e[l + 3] == 0) {
                error[g] = "The operation is not defined";
            } else {
                res[g] = a / b;
            }
        } else if(op[g] == "."){
            error[g] = "Error! Wrong input";
        }
    }

    for (int k = 0; k < n; k++) {
        if (error[k] == "0") {
            cout << res[k] << endl;
        } else {
            cout << error[k] << endl;
        }
    }

    return 0;
}
