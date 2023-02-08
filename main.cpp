#include <iostream>
#include <random>
using namespace std;


    int* Indiviual(int numItens){
        int individuo[numItens];

        random_device rd;
        mt19937 mt(rd());
        uniform_real_distribution<float> dist(0,1);

        for(int i=0;i<numItens;i++){
            individuo[i] = round(dist(mt));
        }
        return individuo;
    }

    // int Population(int numIndividuo,int numItens){
    //     for(int i=0;)
    //     return 
    // };

int main(){
    int pesosValores[10][2]={{4,30},{8,10},{8,30},{25,75},{2,10},{50,100},{6,300},{12,50},{100,400},{8,300}};
    int pesoMaximo=140;
    int numCromossomos=100;
    int geracoes=70;
    int numItens=(sizeof(pesosValores)/sizeof(*pesosValores));
    int * resto;
    // cout<<"itens"<<numItens;

    resto=Indiviual(numItens);
    for(int i=0;i<10;i++){
        cout<<resto[i]<<"resto";

    }

    return 0;
}