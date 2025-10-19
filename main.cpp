#include <bits/stdc++.h>

// Expressões recebidas:
// 1. (1+2+4)*3(2+4)*3(1+2+3+4)*
// 2. (12+14+32+34+21+23+41+43)*
// 3. (1+3)*(2+4)*

using namespace std;

int main(){

  // 1. Recebendo o autômato à partir da expressão regular escolhida
  string automatoEscolhido = "1"; // MM1.txt
  string nomeArquivo = "maquinas/MM" + automatoEscolhido + ".txt";

  FILE *f = fopen(nomeArquivo.c_str(), "rt");
  if (f == NULL){
    cout << "Erro: Arquivo não pôde ser aberto\n";
    return 1;
  }

  // 2. Traduzindo o texto para que o C entenda
  vector<string> estados;
  string estadoInicial;
  vector<string> estadosFinais; 
  vector<string> alfabetoEntrada;
  vector<string> alfabetoSaida;

  char linha[20];
  
  // 2. Primeira linha = estados
  fgets(linha, sizeof(linha), f);
  char* token;
  const char* delimitador = " ";
  token = strtok(linha, delimitador);
  while(token != NULL){ // Elemento por elemento
      estados.push_back(token);
      token = strtok(NULL, delimitador);
    }

  // 2. Segunda linha = estado inicial
  fgets(linha, sizeof(linha), f);
  estadoInicial = linha;

  // 2. Terceira linha = estados finais
  fgets(linha, sizeof(linha), f);
  char* token;
  const char* delimitador = " ";
  token = strtok(linha, delimitador);
  while(token != NULL){ // Elemento por elemento
      estadosFinais.push_back(token);
      token = strtok(NULL, delimitador);
    }

  // 2. Quarta linha = alfabeto de entrada
  fgets(linha, sizeof(linha), f);
  char* token;
  const char* delimitador = " ";
  token = strtok(linha, delimitador);
  while(token != NULL){ // Elemento por elemento
      alfabetoEntrada.push_back(token);
      token = strtok(NULL, delimitador);
    }

  // 2. Quinta linha = alfabeto de saida
  fgets(linha, sizeof(linha), f);
  char* token;
  const char* delimitador = " ";
  token = strtok(linha, delimitador);
  while(token != NULL){ // Elemento por elemento
      alfabetoSaida.push_back(token);
      token = strtok(NULL, delimitador);
    }

    // Automato traduzido
}
