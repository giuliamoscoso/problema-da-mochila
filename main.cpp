#include <cstdlib>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <algorithm>

struct dadosGerais {
  int numItens;
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
  dados.numItens = NumItems;

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
  uniform_int_distribution<int> aleatorio(0, (dados.numItens - 1));

  for (int i = 0; i < numItens; i++) {
    individuo.push_back(round(dist(mt)));
  }

  // Corrige indivíduo caso ultrapasse o peso máximo
  while (true) {
    for (int i = 0; i < individuo.size(); i++) {
      if (individuo[i] == 1) {
        pesoTotal += valoresPesos[i].second;
      }
    }
    if (pesoTotal > pesoMaximo) {
      pesoTotal = 0;
      int index = aleatorio(mt);
      individuo[index] = 0;
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

bool CompararIntervalo(const pair<int, vector<int>> &a, const pair<int, vector<int>> &b) {
  return (a.first > b.first);
}

vector<pair<int,vector<int>>> DividirVector(vector<pair<int,vector<int>>> &IndividuoValor, int i1, int i2){
  // Divide o vetor em dois
  auto primeiro = IndividuoValor.cbegin() + i1;
  auto ultimo = IndividuoValor.cbegin() + i2;
  vector<pair<int,vector<int>>> vetorDividido(primeiro, ultimo);
  return vetorDividido;
}

vector<pair<int,vector<int>>> Mutacao(vector<pair<int,vector<int>>> filhos, float taxaMutacao = 0.05){
  // Mutação dos indivíduos
  for(auto &filho: filhos){
    mt19937 mt(rd());
    uniform_real_distribution<float> dist(0, 1);
    uniform_int_distribution<int> aleatorio(0, (filho.second.size() - 1));

    if(dist(mt) <= taxaMutacao){
      int index = aleatorio(mt);
      filho.second[index] = !filho.second[index];
    }
  }
  return filhos;
}

vector<pair<int,vector<int>>> Cruzamento(vector<pair<int,vector<int>>> pais, vector<pair<int,vector<int>>> maes){
  // Cria filho (pai + mãe)
  vector<pair<int,vector<int>>> filhos;

  for(int index = 0; index < pais.size(); index++){
    pair<int, vector<int>> filho;
    vector<int> individuo;

    for(int i = 0; i < (pais[index].second.size()/2); i++){
      individuo.push_back(pais[index].second[i]);
    }
    for(int i = (maes[index].second.size()/2); i < maes[index].second.size(); i++){
      individuo.push_back(maes[index].second[i]);
    }
    filho.first = Avaliacao(individuo, valoresPesos);
    filho.second = individuo;
    filhos.push_back(filho);
  }
  return filhos;
}

vector<pair<int,vector<int>>> Evolution(vector<vector<int>> populacao, int pesoMaximo,
               vector<pair<int, int>> valoresPesos, int numCromossomos) {
  // Tabula cada individuo e sua avaliação
  vector<pair<int,vector<int>>> IndividuoValor;
  
  for (auto individuo : populacao) {
    IndividuoValor.push_back(make_pair(Avaliacao(individuo, valoresPesos), individuo));
  }
  sort(IndividuoValor.begin(), IndividuoValor.end(), CompararIntervalo);

  vector<pair<int,vector<int>>> maes = DividirVector(IndividuoValor, 0, IndividuoValor.size() / 2);
  vector<pair<int,vector<int>>> pais = DividirVector(IndividuoValor, 50, IndividuoValor.size());
  
  vector<pair<int,vector<int>>> filhos = Cruzamento(pais, maes);
  filhos = Mutacao(filhos);
  vector<pair<int,vector<int>>> novaPopulacao;

  for(int i = 0; i < (IndividuoValor.size()/2); i++){
    novaPopulacao.push_back(IndividuoValor[i]);
  }
  for(auto filho:filhos){
    novaPopulacao.push_back(filho);
  }
  return novaPopulacao;
}

int main() {
  lerArquivo("1");
  vector<float> medias;
  int geracoes = 80;

  auto populacao =
      Population(dados.numItens, dados.numItens, valoresPesos, dados.pesoMax);

  medias.push_back(MediaAvaliacao(populacao, valoresPesos));
  cout << "Média da geração 0: " << medias[0] << endl;

  vector<pair<int,vector<int>>> novaPopulacao;
  for (int i = 0; i < geracoes; i++) {
    novaPopulacao = Evolution(populacao, dados.pesoMax, valoresPesos, dados.numItens);
  }

  int index = 0;
  for(auto individuo: novaPopulacao){
    cout << "Individuo: " << index << endl;
    cout << "Avaliação: " << individuo.first << endl << endl;
    index++;
  }

  return 0;
}
