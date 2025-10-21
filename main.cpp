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

    ifstream f(nomeArquivo.c_str());
    if (!f.is_open()){
        cout << "Erro: Arquivo não pôde ser aberto\n";
        return 1;
    }

    // 2. Traduzindo o texto para que o C entenda
    vector<string> estados;
    string estadoInicial;
    vector<string> estadosFinais; 
    vector<char> alfabetoEntrada;
    vector<string> alfabetoSaida;

    // 2. Primeira linha = estados
    string linha;
    getline(f, linha);
    stringstream ss(linha);
    string estado;
    while(ss >> estado){ // Elemento por elemento
        estados.push_back(estado);
    }

    // 2. Segunda linha = estado inicial
    getline(f, linha);
    estadoInicial = linha;

    // 2. Terceira linha = estados finais
    getline(f, linha);
    string finais;
    ss.clear();       
    ss.str(linha);
    while(ss >> finais){ // Elemento por elemento
        estadosFinais.push_back(finais);
    }

    // 2. Quarta linha = alfabeto de entrada
    getline(f, linha);
    char c;
    ss.clear();       
    ss.str(linha);
    while(ss >> c){ // Elemento por elemento
        alfabetoEntrada.push_back(c);
    }

    // 2. Quinta linha = alfabeto de saida
    getline(f,linha);
    ss.clear();       
    ss.str(linha);
    string saida;
    while(ss >> saida){ // Elemento por elemento
        alfabetoSaida.push_back(saida);
    }

    // 3. Lendo as transições
    struct transicao{
        char entrada; // 1, 2, 3, 4, ., N
        string saida; // 1, 0, e, \n
        string estadoSaida;
        transicao(char entrada, string saida, string estadoSaida) : entrada(entrada), saida(saida), estadoSaida(estadoSaida){};
    };

    map<string, vector<transicao>> transicoes;

    while(getline(f,linha)){
        ss.clear();       
        ss.str(linha);
        string estadoAtual;
        char charEntrada;
        string estadoDepois;
        string charSaida;

        ss >> estadoAtual >> charEntrada >> estadoDepois >> charSaida;

        transicoes[estadoAtual].emplace_back(charEntrada, charSaida, estadoDepois);
    }

    // Printando as transições de q0
    for(auto [e,v] : transicoes){
        //for(auto t : v) cout << e << " " << t.entrada << " " << t.estadoSaida << " " << t.saida << endl;
    }
    
    string arquivoPalavra = argv[2];
    string  tam = arquivoPalavra.substr(10, find(arquivoPalavra.begin(), arquivoPalavra.end(), '.') - arquivoPalavra.begin() - 10);
    
    string nomeSaida = "out/" + arquivoPalavra.substr(9, find(arquivoPalavra.begin(), arquivoPalavra.end(), '.') - arquivoPalavra.begin() - 9) + "saida.ppm";
    cout << nomeSaida << endl;
    ofstream fOut(nomeSaida);
    ifstream fIn(arquivoPalavra.c_str());

    fOut << "P1" << endl;
    fOut << tam << " " << tam << endl;

    string palavra;
    getline(fIn, palavra);

    string atual = "q0";
    for(char c: palavra){
        for(transicao t: transicoes[atual]){
            if(t.entrada == c){
                atual = t.estadoSaida;
                if(t.saida == "e") break;
                else if(t.saida == "\\n") fOut << endl;
                else fOut << t.saida;
                break;
            }
        }
        if(c == '.') atual = "q0";
    }
}
