#include <bits/stdc++.h>

// Expressões recebidas:
// 1. (1+2+4)*3(2+4)*3(1+2+3+4)*
// 2. (12+14+32+34+21+23+41+43)*
// 3. (1+3)*(2+4)*

using namespace std;


int main(int argc, char* argv[]){

    if(argc < 2){
        cout << "Erro: arquivo de entrada não passado" << endl;
    }
    // 1. Recebendo o autômato à partir da expressão regular escolhida
    string nomeArquivo = argv[1];

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

    char linha[100];

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
    token = strtok(linha, delimitador);
    while(token != NULL){ // Elemento por elemento
        estadosFinais.push_back(token);
        token = strtok(NULL, delimitador);
    }

    // 2. Quarta linha = alfabeto de entrada
    fgets(linha, sizeof(linha), f);
    token = strtok(linha, delimitador);
    while(token != NULL){ // Elemento por elemento
        alfabetoEntrada.push_back(token);
        token = strtok(NULL, delimitador);
    }

    // 2. Quinta linha = alfabeto de saida
    fgets(linha, sizeof(linha), f);
    token = strtok(linha, delimitador);
    while(token != NULL){ // Elemento por elemento
        alfabetoSaida.push_back(token);
        token = strtok(NULL, delimitador);
    }

    // 3. Lendo as transições
    struct transicao{
        string entrada; // 1, 2, 3, 4, ., N
        string saida; // 1, 0, e, \n
        string estadoSaida;
        transicao(string entrada, string saida, string estadoSaida) : entrada(entrada), saida(saida), estadoSaida(estadoSaida){};
    };

    map<string, vector<transicao>> transicoes;

    while(fgets(linha, sizeof(linha), f) != NULL){
        string estadoAtual = strtok(linha, delimitador);
        string charEntrada = strtok(NULL, delimitador);
        string estadoDepois = strtok(NULL, delimitador);
        string charSaida = strtok(NULL, delimitador);

        transicoes[estadoAtual].emplace_back(charEntrada, charSaida, estadoDepois);
    }

    // Printando as transições de q0
    for(transicao t : transicoes["q0"]){
        //cout << "q0 " << t.entrada << " " << t.estadoSaida << " " << t.saida << endl;
    }
    
    string arquivoPalavra = argv[2];
    string  tam = arquivoPalavra.substr(10, find(arquivoPalavra.begin(), arquivoPalavra.end(), '.') - arquivoPalavra.begin() - 10);
    
    ofstream fOut("out/saida.ppm");
    ifstream fIn(arquivoPalavra.c_str());

    fOut << "P1" << endl;
    fOut << tam << " " << tam << endl;

    string palavra;
    getline(fIn, palavra);
    cout << palavra << endl;; 
}
