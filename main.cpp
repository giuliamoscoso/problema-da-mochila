#include <cstdlib>
#include <iostream>
#include <random>

using namespace std;
random_device rd;

int* Individual(int numItens, int pesosValores[][2], int pesoMaximo){
//  Cria indiv�duo da popula��o
    int *individuo = (int*)malloc(numItens * sizeof(int));
    int pesoTotal = 0;

    mt19937 mt(rd());
    uniform_real_distribution<float> dist(0,1);
		for(int i=0; i < numItens; i++){
			individuo[i] = round(dist(mt));
    }
	while(true){
		for(int i=0; i < numItens; i++){
			if(individuo[i] == 1){
				pesoTotal += pesosValores[i][1];
						// cout<<pesosValores[i][1]<<endl;
						// cout<<"maximo"<<pesoMaximo<<endl;
					
					}
			cout<<individuo[i];
			}

		cout<<endl;
		if(pesoTotal > pesoMaximo){
			pesoTotal=0;
			individuo[rand()%numItens] = 0;
		}else{
			return individuo;
		}

		}

}

int** Population(int numCromossomos,int numItens, int pesosValores[][2], int pesoMaximo){
//	Cria popula��o/conjunto de indiv�duos
	int **population = (int**)malloc(numCromossomos * sizeof(int*));
	
	for(int i = 0; i < numCromossomos; i++){
		cout<<"chamada"<<i<<endl;
	    	population[i] = Individual(numItens, pesosValores, pesoMaximo);
		
	}
	// for(int i=0;i<numCromossomos;i++){
	// 	for(int j=0;j<numItens;j++){
	// 		cout<<population[1][j]<<" ";
	// 	}
	// }
	return population;
};

//int Avaliacao(int *individuo, int pesoMaximo, int pesosValores){
////	Faz avalia��o do indiv�duo
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
////		Encontra avalia��o m�dia da popula��o
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
    int numItens = 10;
	cout<<numItens;
    
	int **populacao;
	populacao = Population(numCromossomos, numItens, pesosValores, pesoMaximo);
//	cout<<sizeof(populacao);
	
//	for(int i = 0; i < 10; i++){
//		for(int j = 0; j < 10; j++){
//		    cout << populacao[i][j] << " ";		
//		}
//		cout<<endl;
//	}

    return 0;
}
