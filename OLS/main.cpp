#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// =============================================================
#define _DEBUG
#ifdef _DEBUG
    #define DEBUG
#else
    #define DEBUG if(0)
#endif // _DEBUG


#define VarPrint( var )                                     \
    {                                                       \
        std::cout << "\x1b[32m" << #var << " = " << var << "\x1b[0m" << endl;          \
    }                                                       \

// =============================================================

enum ErrCode
{
    INVALID_INPUT = -1,

    OK = 0
};

/// Opens file and counts lines in file
fstream OpenFile(string filename);

/// Counts strings in file
int CountLines(int* n_lines);

/// Fills arrays with X and Y
int ReadFile(double* x, double* y, size_t points_amnt);

/// Counts X*Y sum
double CountXY(double* x, double* y, size_t points_amnt);

/// Counts Y sum
double CountX(double* x, double* y, size_t points_amnt);

/// Counts X sum
double CountY(double* x, double* y, size_t points_amnt);

/// Counts X*X sum
double CountXX(double* x, double* y, size_t points_amnt);

/// Counts A
double CountA(double XY, double X, double Y, double XX, int points_amnt);

/// Counts B
double CountB(double XY, double X, double Y, double XX, int points_amnt, double A);

/// Counts A_0
double CountA_0(double XY, double X, double Y, double XX, int points_amnt, double A);

/// Writes LaTeX code for line
int WriteLine(double* x, size_t points_amnt, double A, double B, double A_0);

// =============================================================

string def_input  = "input.txt";
string def_output = "output.txt";

fstream input  = OpenFile(def_input);
fstream output = OpenFile(def_output);

// =============================================================

int main(int argc, char* argv[])
{
    int points_amnt = 0;
    CountLines(&points_amnt);

    double* x = new double [points_amnt];
    double* y = new double [points_amnt];

    ReadFile(x, y, points_amnt);

    cout << endl;
    double XY = CountXY(x, y, points_amnt);
    VarPrint(XY);
    double X  = CountX (x, y, points_amnt);
    VarPrint(X);
    double Y  = CountY (x, y, points_amnt);
    VarPrint(Y);
    double XX = CountXX(x, y, points_amnt);
    VarPrint(XX);

    cout << endl;
    double A   = CountA(XY, X, Y, XX, points_amnt);
    VarPrint(A);
    double B   = CountB(XY, X, Y, XX, points_amnt, A);
    VarPrint(B);
    double A_0 = CountA_0(XY, X, Y, XX, points_amnt, A);
    VarPrint(A_0);

    WriteLine(x, points_amnt, A, B, A_0);

}

// =============================================================

fstream OpenFile(string filename)
{
    fstream input(filename);
    if(!input.is_open()){
        cout << "File " << filename << " wasn't found :(\n" << endl;
        exit(0);
    }
    return input;
}

int CountLines(int* n_lines)
{
    string tmp;

    (*n_lines) = 0;
    while(!input.eof()){
        getline(input, tmp);
        (*n_lines)++;
    }
    (*n_lines)--;
    VarPrint(*n_lines);

    input.clear();
    input.seekg(0);

    return OK;
}

int ReadFile(double* x, double* y, size_t points_amnt)
{
    string line;

    for(int i = 0; i < points_amnt; i++){
        getline(input, line);

        int digit = 0;
        while(line[digit] != '(')
            digit++;
        digit++;

        string num;
        while(line[digit] != ',')
            num += line[digit++];

        VarPrint(num);
        x[i] = stod(num);

        digit++;
        num = "";
        while(line[digit] != ')')
            num += line[digit++];
        y[i] = stod(num);

        VarPrint(num);
    }

    return OK;
}

double CountXY(double* x, double* y, size_t points_amnt)
{
    double XYsum = 0;
    for(int i = 0; i < points_amnt; i++)
        XYsum += x[i] * y[i];

    return XYsum;
}

double CountX(double* x, double* y, size_t points_amnt)
{
    double Xsum = 0;
    for(int i = 0; i < points_amnt; i++)
        Xsum += x[i];

    return Xsum;
}

double CountY(double* x, double* y, size_t points_amnt)
{
    double Ysum = 0;
    for(int i = 0; i < points_amnt; i++)
        Ysum += y[i];

    return Ysum;
}

double CountXX(double* x, double* y, size_t points_amnt)
{
    double XXsum = 0;
    for(int i = 0; i < points_amnt; i++)
        XXsum += x[i] * x[i];

    return XXsum;
}

double CountA(double XY, double X, double Y, double XX, int points_amnt)
{
    double up   = (points_amnt * XY - X * Y);
    double down = (points_amnt * XX - X * X);

    return up / down;
}

double CountB(double XY, double X, double Y, double XX, int points_amnt, double A)
{
    double up   = (Y - A * X);
    double down = points_amnt;

    return up / down;
}

double CountA_0(double XY, double X, double Y, double XX, int points_amnt, double A)
{
    return XY / XX;
}

int WriteLine(double* x, size_t points_amnt, double A, double B, double A_0)
{
    output << "A and B counted\n";
    output << "Ending near first and last\n\n";

    output << "\\addplot [mark = none]\ncoordinates{\n";
    output << "\t(" << x[0]               << ", " << x[0] * A + B               << ")" << "\n"
           << "\t(" << x[points_amnt - 1] << ", " << x[points_amnt - 1] * A + B << ")\n";
    output << "};\n";

    output << "\nEnding near zero\n\n";

    output << "\\addplot [mark = none]\ncoordinates{\n";
    output << "\t(" << 0                  << ", " << B                          << ")" << "\n"
           << "\t(" << x[points_amnt - 1] << ", " << x[points_amnt - 1] * A + B << ")\n";
    output << "};\n";


    output << "\n// ===================================";


    output << "\n\nB = 0\n";
    output << "Ending near first and last\n\n";

    output << "\\addplot [mark = none]\ncoordinates{\n";
    output << "\t(" << x[0]               << ", " << x[0] * A_0               << ")" << "\n"
           << "\t(" << x[points_amnt - 1] << ", " << x[points_amnt - 1] * A_0 << ")\n";
    output << "};\n";

    output << "\nEnding near zero\n\n";

    output << "\\addplot [mark = none]\ncoordinates{\n";
    output << "\t(" << 0                  << ", " << 0                          << ")" << "\n"
           << "\t(" << x[points_amnt - 1] << ", " << x[points_amnt - 1] * A_0 << ")\n";
    output << "};\n";

    return OK;
}

