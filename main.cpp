#include <cstdlib>
#include <iostream>
#include <random>
using namespace std;
random_device rd;

int* Individual(int numItens){
//  Cria indivíduo da população
    int *individuo = (int*)malloc(numItens * sizeof(int));

    mt19937 mt(rd());
    uniform_real_distribution<float> dist(0,1);

    for(int i=0;i<numItens;i++){
        individuo[i] = round(dist(mt));
    }
    return individuo;
}

int** Population(int numIndividuo,int numItens){
//	Cria população/conjunto de indivíduos
	int **population = (int**)malloc(numIndividuo * sizeof(int*));
	
	for(int i = 0; i < numIndividuo; i++){
	    population[i] = Individual(numItens);
	}
	return population;
};

//int Avaliacao(int *individuo, int pesoMaximo, int pesosValores){
////	Faz avaliação do indivíduo
//	int pesoTotal = 0;
//	int valorTotal = 0;
//
//	for(int i = 0; i < sizeof(individuo); i++){
//		pesoTotal += (individuo[i] * pesosValores[i][0]);
//		valorTotal += (individuo[i] * pesosValores[i][1]);
//	}
//	
////	Se o peso for extrapolado
//	if((pesoMaximo - pesoTotal) < 0){
//		return -1;
//	}
//	return valorTotal;
//}
//
//	float MediaAvaliacao(int **populacao, int pesoMaximo, int pesosValores){
////		Encontra avaliação média da população
//	int somatorio = 0;
//	
//	for(int i = 0; i < sizeof(individuo); i++){
//		
//	}
//	
//	return 8.9;
//}

int main(){
    int pesosValores[10][2] = {{4,30},{8,10},{8,30},{25,75},{2,10},{50,100},{6,300},{12,50},{100,400},{8,300}};
    int pesoMaximo = 140;
    int numCromossomos = 100;
    int geracoes = 70;
    int numItens = (sizeof(pesosValores)/sizeof(*pesosValores));
    
	int **populacao;
	populacao = Population(numCromossomos, numItens);
	cout<<sizeof(populacao);
	
//	for(int i = 0; i < 10; i++){
//		for(int j = 0; j < 10; j++){
//		    cout << populacao[i][j] << " ";		
//		}
//		cout<<endl;
//	}

    return 0;
}
