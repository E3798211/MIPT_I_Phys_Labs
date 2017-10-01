#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

int main()
{
    fstream  input ("1.txt");
    ofstream output("stats.txt");

    int num1    = 0;
    int num2    = 0;
    int enter   = 1;

    int n_num1 = 201;
    int n_num2 = 101;

    int* arr1 = new int [n_num1];
    int arr1_c = 0;
    int* arr2 = new int [n_num2];
    int arr2_c = 0;

    output << "Table for 40 sec:\n";
    output << "The very last num repeats last one in table and should be treated as meaningless while processing the table.\n\n";

    while(!input.eof()){
        input >> num1;
        arr1[arr1_c++] = num1;
        input >> num2;
        arr1[arr1_c++] = num2;

        output << num1 + num2;
        output << "\t";
        if(enter % 10 == 0)     output << '\n';
        enter++;

        arr2[arr2_c++] = num1 + num2;
    }

    //===================================================


    int _max = 0;
    for(int i = 0; i < n_num1 - 1; i++){
        if(arr1[i] > _max)      _max = arr1[i];
    }

    double* amnts1 = new double [_max];
    for(int i = 0; i < _max; i++){
        for(int k = 0; k < n_num1 - 1; k++){
            if(arr1[k] == i + 1)    amnts1[i]++;
        }
    }

    cout << "MAX = " << _max << endl;

    output << "\n\nPoints for LaTex, 20 sec:\n\n\\\\ ====================================================\n\n";
    output << "\\begin{flushleft}\n\\begin{tikzpicture}\n\\begin{axis}[\n" <<
              "height = 9cm,\n"     <<
              "width  = 14cm,\n"    <<
              "every axis y label/.style={at = {(ticklabel cs: 0.5)}, rotate = 90, anchor = near ticklabel},\n" <<
              "xlabel = {$n, \\text{частиц/40 с}$},\n"   <<
              "ylabel = {$\\omega$},\nybar,\nbar width = 4pt\n]\n" <<
              "\\addplot+[ybar] coordinates{\n";

    //ofstream output1("3.txt");
    for(int i = 0; i < _max; i++){
        if(amnts1[i] != 0)
            //output1 << "n = " << i + 1 << "\tTimes = " << amnts1[i] << "\tw = " << amnts1[i]/(n_num1 - 1) << "\n";
            //output1 << "(" << i + 1 << ", " << amnts1[i]/(n_num1 - 1) << ")\n";
            output << "(" << i + 1 << ", " << amnts1[i]/(n_num1 - 1) << ")\n";
    }

    output << "};\n\\end{axis}\n\\end{tikzpicture}\n\\end{flushleft}\n";
    output << "\\\\ ====================================================\n\n";

    output << "\n\nPoints, 20 sec:\n\n";
    for(int i = 0; i < _max; i++){
        if(amnts1[i] != 0)
            output << "n = " << i + 1 << "\tTimes = " << amnts1[i] << "\tw = " << amnts1[i]/(n_num1 - 1) << "\n";
            //output1 << "(" << i + 1 << ", " << amnts1[i]/(n_num1 - 1) << ")\n";
            //output << "(" << i + 1 << ", " << amnts1[i]/(n_num1 - 1) << ")\n";
    }

    delete [] amnts1;


    _max = 0;
    for(int i = 0; i < n_num2 - 1; i++){
        if(arr2[i] > _max)      _max = arr2[i];
    }

    double* amnts2 = new double [_max];
    for(int i = 0; i < _max; i++){
        for(int k = 0; k < n_num2 - 1; k++){
            if(arr2[k] == i + 1)    amnts2[i]++;
        }
    }

    cout << "MAX = " << _max << endl;

    output << "\n\nPoints for LaTex, 40 sec:\n\n\\\\ ====================================================\n\n";
    output << "\\begin{flushleft}\n\\begin{tikzpicture}\n\\begin{axis}[\n" <<
              "height = 9cm,\n"     <<
              "width  = 14cm,\n"    <<
              "every axis y label/.style={at = {(ticklabel cs: 0.5)}, rotate = 90, anchor = near ticklabel},\n" <<
              "xlabel = {$n, \\text{частиц/40 с}$},\n"   <<
              "ylabel = {$\\omega$},\nybar,\nbar width = 3pt\n]\n" <<
              "\\addplot+[ybar] coordinates{\n";

    //ofstream output2("4.txt");
    for(int i = 0; i < _max; i++){
        if(amnts2[i] != 0)
            //output2 << "n = " << i << "\tTimes = " << amnts2[i] << "\tw = " << amnts2[i]/(n_num2 - 1) << "\n";
            //output2 << "(" << i + 1 << ", " << amnts2[i]/(n_num2 - 1) << ")\n";
            output << "(" << i + 1 << ", " << amnts2[i]/(n_num2 - 1) << ")\n";
    }

    output << "};\n\\end{axis}\n\\end{tikzpicture}\n\\end{flushleft}\n";
    output << "\\\\ ====================================================\n\n";

    output << "\n\nPoints, 40 sec:\n\n";

    //ofstream output2("4.txt");
    for(int i = 0; i < _max; i++){
        if(amnts2[i] != 0)
            output << "n = " << i << "\tTimes = " << amnts2[i] << "\tw = " << amnts2[i]/(n_num2 - 1) << "\n";
            //output2 << "(" << i + 1 << ", " << amnts2[i]/(n_num2 - 1) << ")\n";
            //output << "(" << i + 1 << ", " << amnts2[i]/(n_num2 - 1) << ")\n";
    }

    // ================================================================

    output << "\n\nMiddle value for 10 sec:\n\n";

    double mid = 0;
    for(int i = 0; i < n_num1 - 1; i++)
        mid += arr1[i];

    int mid1 = mid/(n_num1 - 1) / 2;
    output << "Sum = " << mid << "\t";
    output << "Mid = " << mid/(n_num1 - 1) / 2;

    int mid2 = mid/(n_num1 - 1);
    output << "\n\nMiddle for value 20 sec:\n\n";
    output << "Sum = " << mid << "\t";
    output << "Mid = " << mid/(n_num1 - 1);

    output << "\n\nMiddle value for 40 sec:\n\n";

    mid = 0;
    for(int i = 0; i < n_num2 - 1; i++)
        mid += arr2[i];

    int mid4 = mid/(n_num2 - 1);
    output << "Sum = " << mid << "\t";
    output << "Mid = " << mid/(n_num2 - 1);

    // ====================================================


    double s = 0;
    for(int i = 0; i < n_num1 - 1; i++)
        s += (arr1[i] - mid2)*(arr1[i] - mid2);

    output << "\n\n\nsigma for 20 sec:\n";
    output << "sum = " << s << endl;
    cout   << "sum20 = " << s << endl;

    s /= (n_num1 - 1);
    s = sqrt(s);
    int s2 = s;

    output << "s20 = " << s << "\n";
    cout   << "s20 = " << s << endl;

    s = 0;
    for(int i = 0; i < n_num2 - 1; i++)
        s += (arr2[i] - mid4)*(arr2[i] - mid4);

    output << "\n\nsigma for 40 sec:\n";
    output << "sum = " << s << endl;
    cout   << "sum40 = " << s << endl;

    s /= (n_num2 - 1);
    s = sqrt(s);
    int s4 = s;

    output << "s40 = " << s << "\n";
    cout   << "s40 = " << s << endl;

    // ===================================================

    double event = 0;
    for(int i = 0; i < n_num1 - 1; i++){
        if((arr1[i] > mid2 - s2) && (arr1[i] < mid2 + s2))
            event++;
    }
    output << "\n\nEvents for 20 sec (1 sigma):\nevents = " << event;
    cout   << "\nEvents for 20 sec (1 sigma):\nevents = " << event;
    //cout    << "events = " << event << endl;


    event = 0;
    for(int i = 0; i < n_num1 - 1; i++){
        if((arr1[i] > mid2 - 2*s2) && (arr1[i] < mid2 + 2*s2))
            event++;
    }
    output << "\n\nEvents for 20 sec:(2 sigma)\nevents = " << event;
    cout   << "\n\nEvents for 20 sec:(2 sigma)\nevents = " << event;
    //cout << "events = " << event << endl;

    // =========

    event = 0;
    for(int i = 0; i < n_num2 - 1; i++){
        if((arr2[i] > mid4 - s4) && (arr2[i] < mid4 + s4))
            event++;
    }
    output << "\n\nEvents for 40 sec (1 sigma):\nevents = " << event;
    cout   << "\n\nEvents for 40 sec (1 sigma):\nevents = " << event;
    //cout << "events = " << event << endl;


    event = 0;
    for(int i = 0; i < n_num2 - 1; i++){
        if((arr2[i] > mid4 - 2*s4) && (arr2[i] < mid4 + 2*s4))
            event++;
    }
    output << "\n\nEvents for 40 sec:(2 sigma)\nevents = " << event;
    cout   << "\n\nEvents for 40 sec:(2 sigma)\nevents = " << event << endl;
    //cout << "events = " << event << endl;
}
