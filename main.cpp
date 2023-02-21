#include <cstdlib>
#include <iostream>
#include <random>
#include <vector>

using namespace std;
random_device rd;

vector<int> Individual(int numItens, int pesosValores[][2], int pesoMaximo) {
  // Cria indivíduo da popula��o
  vector<int> individuo;
  int pesoTotal = 0;

  mt19937 mt(rd());
  uniform_real_distribution<float> dist(0, 1);

  for (int i = 0; i < numItens; i++) {
    individuo.push_back(round(dist(mt)));
  }

  // Corrige indivíduo caso ultrapasse o peso máximo
  while (true) {
    for (auto i : individuo) {
      if (i == 1) {
        pesoTotal += pesosValores[i][1];
      }
    }
    if (pesoTotal > pesoMaximo) {
      pesoTotal = 0;
      individuo[rand() % individuo.size()] = 0;
    } else {
      return individuo;
    }
  }
}

vector<vector<int>> Population(int numCromossomos, int numItens,
                               int pesosValores[][2], int pesoMaximo) {
  // Cria população/conjunto de indivíduos
  vector<vector<int>> population;

  for (int i = 0; i < numCromossomos; i++) {
    population.push_back(Individual(numItens, pesosValores, pesoMaximo));
  }
  return population;
};

// int Avaliacao(int *individuo, int pesosValores) {
//   // Faz avaliação do indivíduo
//   int valorTotal = 0;
//   cout << "inicio: " << sizeof(individuo) << endl;

//   for (int i = 0; i < sizeof(individuo); i++) {
//     // valorTotal += (individuo[i] * pesosValores[i][1]);
//     cout << sizeof(individuo[i]) << endl;
//   }

//   return valorTotal;
// }

float MediaAvaliacao(int **populacao, int pesosValores) {
  // Encontra avaliação média da população
  int somatorio = 0;
  cout << sizeof(populacao) << endl;

  // for (int i = 0; i < sizeof(populacao); i++) {

  // }

  return 8.9;
}

int main() {
  int pesosValores[10][2] = {{4, 30},    {8, 10},   {8, 30},  {25, 75},
                             {2, 10},    {50, 100}, {6, 300}, {12, 50},
                             {100, 400}, {8, 300}};
  int pesoMaximo = 140;
  int numCromossomos = 100;
  int geracoes = 70;
  int numItens = 10;

  auto populacao =
      Population(numCromossomos, numItens, pesosValores, pesoMaximo);
  // int teste = MediaAvaliacao(populacao, pesosValores[10][2]);
  // cout << "TESTE: " << teste << endl;

  return 0;
}
