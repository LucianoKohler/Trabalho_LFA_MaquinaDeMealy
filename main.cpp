#include <bits/stdc++.h>

// Expressões recebidas:
// 1. (1+2+4)*3(2+4)*3(1+2+3+4)*
// 2. (12+14+32+34+21+23+41+43)*
// 3. (1+3)*(2+4)*

using namespace std;

struct transicao{
    char entrada; 
    string saida;
    string estadoSaida;
    transicao(char entrada, string saida, string estadoSaida) : entrada(entrada), saida(saida), estadoSaida(estadoSaida){};
};

int main(int argc, char* argv[]){

    if(argc < 2){
        cout << "Erro: arquivo de entrada não passado" << endl;
        return 1;
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
    map<string, vector<transicao>> transicoes;

    // 2.1 Primeira linha = estados
    string linha;
    getline(f, linha);
    stringstream ss(linha);
    string estado;
    while(ss >> estado) estados.push_back(estado);

    // 2.2 Segunda linha = estado inicial
    getline(f, linha);
    estadoInicial = linha;

    // 2.3 Terceira linha = estados finais
    getline(f, linha);
    string finais;
    ss.clear();       
    ss.str(linha);
    while(ss >> finais) estadosFinais.push_back(finais);

    // 2.4 Quarta linha = alfabeto de entrada
    getline(f, linha);
    char c;
    ss.clear();       
    ss.str(linha);
    while(ss >> c) alfabetoEntrada.push_back(c);

    // 2.5 Quinta linha = alfabeto de saida
    getline(f,linha);
    ss.clear();       
    ss.str(linha);
    string saida;
    while(ss >> saida) alfabetoSaida.push_back(saida);

    // 3. Lendo as transições
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

    string arquivoPalavra = argv[2];
    ifstream fIn(arquivoPalavra.c_str());
    string palavra;
    getline(fIn, palavra);

    string tam = to_string(1ll << (find(palavra.begin(), palavra.end(), '.') - palavra.begin()));
    string nomeSaida = "out/w" + tam + "saida.ppm";
    ofstream fOut(nomeSaida);

    fOut << "P1" << endl;
    fOut << tam << " " << tam << endl;

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
