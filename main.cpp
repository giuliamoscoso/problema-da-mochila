#include <cstdlib>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

struct dadosGerais {
  int numItems;
  int pesoMax;
  int pesoOtimo;
  int valorOtimo;
};
using namespace std;
vector<pair<int, int>> valoresPesos;
dadosGerais dados;
random_device rd;

void lerArquivo(string filename) {
  // Ler arquivo de entrada
  ifstream indata;
  int num;
  indata.open("EntradasMochila//entradas//" + filename);

  if (!indata) {
    cerr << "Error: file could not be opened" << endl;
    exit(1);
  }

  indata >> num;
  int NumItems = num;
  dados.numItems = NumItems;

  indata >> num;
  dados.pesoMax = num;

  for (int i = 0; i < NumItems; i++) {
    if (indata.eof())
      break;

    pair<int, int> valorPeso;
    indata >> num;
    valorPeso.first = num;
    indata >> num;
    valorPeso.second = num;
    valoresPesos.push_back(valorPeso);
  }
  int TempPeso = 0, TempValor = 0;

  for (int i = 0; !indata.eof(); i++) {
    indata >> num;
    if (num) {
      TempValor += valoresPesos[i].first;
      TempPeso += valoresPesos[i].second;
    }
  }
  dados.pesoOtimo = TempPeso;
  dados.valorOtimo = TempValor;

  indata.close();
  // cout << "End-of-file reached.." << endl;
}

vector<int> Individual(int numItens, vector<pair<int, int>> valoresPesos,
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
        pesoTotal += valoresPesos[i].second;
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
                               vector<pair<int, int>> valoresPesos,
                               int pesoMaximo) {
  // Cria população/conjunto de indivíduos
  vector<vector<int>> population;

  for (int i = 0; i < numCromossomos; i++) {
    population.push_back(Individual(numItens, valoresPesos, pesoMaximo));
  }
  return population;
};

int Avaliacao(vector<int> individuo, vector<pair<int, int>> valoresPesos) {
  // Faz avaliação do indivíduo
  int valorTotal = 0;

  for (auto i : individuo) {
    valorTotal += (i * valoresPesos[i].second);
  }

  return valorTotal;
}

float MediaAvaliacao(vector<vector<int>> populacao,
                     vector<pair<int, int>> valoresPesos) {
  // Encontra avaliação média da população
  int somatorio = 0;

  for (auto individuo : populacao) {
    somatorio += Avaliacao(individuo, valoresPesos);
  }

  return somatorio / populacao.size();
}

int main() {
  lerArquivo("1");
  vector<float> medias;
  int numCromossomos = 100;
  int geracoes = 80;

  auto populacao =
      Population(numCromossomos, dados.numItems, valoresPesos, dados.pesoMax);
  medias.push_back(MediaAvaliacao(populacao, valoresPesos));
  cout << "Média da geração 0: " << medias[0] << endl;

  return 0;
}
