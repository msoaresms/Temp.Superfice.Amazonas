#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
const long int TAM = 100000;
using namespace std;

inline unsigned long long int RandD(unsigned long long int x){
    unsigned long long int a = 2685821657736338717;
    x = x * a;
    return x >> 32;
}

int main() {
    unsigned long long int x = time(NULL);
    int v[TAM];
    int proba[40];
    string tempe[40];
    int intervalos[41];
    int m[2][40];
    string line;
    int num;
    int auxL;

    ifstream prob;
    prob.open("pProbabilidades.txt");

    int i = 0;
    while (!prob.eof()){
        getline(prob, line);
        stringstream aux(line);
        int nAux;
        aux >> nAux;
        proba[i] = nAux;
        i++;
    }
    prob.close();

    ifstream temp;
    temp.open("pMedias.txt");

    i = 0;
    while (!temp.eof()){
        getline(temp, line);
        tempe[i] = line;
        i++;
    }
    temp.close();

    intervalos[40] = -1;
    int pX = 0;
    for (int i = 39; i >=0; i--){
        pX = proba[i] + pX;
        intervalos[i] = pX;
    }

    cout << "Informe o numero de meses: \n";
    cin >> auxL;

    for (int i = 0; i < auxL; i++){
        x = RandD(x);
        num = x % 10000000;

        for (int j = 0; j < 40; j ++){
            if (num <= intervalos[j] && num > intervalos[j+1]){
                cout << tempe[j] << endl;
            }
        }
    }
}