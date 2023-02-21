#include <cstdlib>
#include <iostream>
#include <random>
#include <vector>

using namespace std;
random_device rd;

vector<int> Individual(int numItens, vector<pair<int, int>> valorPeso,
                       int pesoMaximo) {
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
        pesoTotal += valorPeso[i].second;
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
                               vector<pair<int, int>> valorPeso,
                               int pesoMaximo) {
  // Cria população/conjunto de indivíduos
  vector<vector<int>> population;

  for (int i = 0; i < numCromossomos; i++) {
    population.push_back(Individual(numItens, valorPeso, pesoMaximo));
  }
  return population;
};

int Avaliacao(vector<int> individuo, vector<pair<int, int>> valorPeso) {
  // Faz avaliação do indivíduo
  int valorTotal = 0;

  for (auto i : individuo) {
    valorTotal += (i * valorPeso[i].second);
  }

  return valorTotal;
}

float MediaAvaliacao(vector<vector<int>> populacao,
                     vector<pair<int, int>> valorPeso) {
  // Encontra avaliação média da população
  int somatorio = 0;

  for (auto individuo : populacao) {
    somatorio += Avaliacao(individuo, valorPeso);
  }

  return somatorio / populacao.size();
}

int main() {
  vector<pair<int, int>> valorPeso = {{4, 30},    {8, 10},   {8, 30},  {25, 75},
                                      {2, 10},    {50, 100}, {6, 300}, {12, 50},
                                      {100, 400}, {8, 300}};
  vector<float> medias;
  int pesoMaximo = 140;
  int numCromossomos = 100;
  int geracoes = 80;
  int numItens = 10;

  auto populacao = Population(numCromossomos, numItens, valorPeso, pesoMaximo);
  medias.push_back(MediaAvaliacao(populacao, valorPeso));
  cout << "Média da geração 0: " << medias[0] << endl;

  return 0;
}
