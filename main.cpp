#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
using namespace std;

//Função que gera o número aleatório
inline unsigned long long int RandD(unsigned long long int x){
    unsigned long long int a = 2685821657736338717; //multiplicador
    x = x * a;
    return x >> 32;
}

//Transfera as probabilidades do txt para um vetor
void leituraProbabilidades(int *probabilidades){
    string line;
    ifstream prob;
    prob.open("pProbabilidades.txt");

    int i = 0;
    while (!prob.eof()){
        getline(prob, line);
        stringstream aux(line);
        int nAux;
        aux >> nAux;
        probabilidades[i] = nAux;
        i++;
    }
    prob.close();
}

//Transfere as temperaturas do txt para um vetor
void leituraTemperaturas(string *temperaturas){
    string line;
    ifstream temp;
    temp.open("pMedias.txt");

    int i = 0;
    while (!temp.eof()){
        getline(temp, line);
        temperaturas[i] = line;
        i++;
    }
    temp.close();
}

//Cria os intervalos usados na simulação
void criacaoIntervalos(int *intervalos, int *probabilidades){
    int aux = 0;
    intervalos[40] = -1;
    for (int i = 39; i >=0; i--){
        aux = probabilidades[i] + aux;
        intervalos[i] = aux;
    }
}

int main() {
    unsigned long long int x = time(NULL); //semente do gerador
    int probabilidades[40];                //guarda as probabilidades lidas do txt
    string temperaturas[40];               //guarda as temperaturas lidas do txt
    int intervalos[41];                    //guarda os intervalos obtidos usando as probabilidades
    int numLeitura;                        //guarda quantas temepraturas serão simuladas
    int num;                               //recebe o valor aleatório do gerada no intervalo 0 - 10000000

    leituraProbabilidades(probabilidades);
    leituraTemperaturas(temperaturas);

    criacaoIntervalos(intervalos, probabilidades);

    cout << "Informe o numero de meses: \n";
    cin >> numLeitura;

    for (int i = 0; i < numLeitura; i++){
        x = RandD(x);
        num = x % 10000000;

        for (int j = 0; j < 40; j ++){
            if (num <= intervalos[j] && num > intervalos[j+1]){
                cout << temperaturas[j] << " - " << (float) probabilidades[j] / 10000000 << "%" << endl;
            }
        }
    }
}