#include <bits/stdc++.h>
#include <unistd.h>         
#include <limits.h>  
#include <fstream>

using namespace std;

struct pergunta {
    string texto;
    string op[4];
    char resp;
};

vector<pergunta> carregar() {
    ifstream arq("perguntas.txt");
    vector<pergunta> per;
    string linha;

    if (!arq.is_open()) {
        cout << "Erro: Arquivo 'perguntas.txt' nao encontrado ou invalido." << endl;
        exit(1);
    }

    while (getline(arq, linha)) {
        if (linha.empty()) {
            continue;
        }

        pergunta p;
        p.texto = linha;

        for (int i = 0; i < 4; i++) {
            getline(arq, linha);
            p.op[i] = linha;
        }

        getline(arq, linha);
        p.resp = linha[0];

        per.push_back(p);

        // Lê linha em branco entre perguntas
        getline(arq, linha);
    }

    return per;
}

int rodar(const vector<pergunta>& per) {
    int pontuacao = 0;
    char resposta;

    for (size_t i = 0; i < per.size(); i++) {
        cout << "Pergunta " << (i + 1) << ":" << endl;
        cout << per[i].texto << endl;
        for (const auto& opcao : per[i].op) {
            cout << opcao << endl;
        }

        cout << "Digite sua resposta (A-D): ";
        
        while (cin >> resposta && (toupper(resposta) != 'A' && toupper(resposta) != 'B' && toupper(resposta) != 'C' && toupper(resposta) != 'D')) {
            cout << "Opcao invalida. Digite novamente (A-D): ";
        }

        if (toupper(resposta) == toupper(per[i].resp)) {
            pontuacao++;
        }

        cout << endl;
    }

    return pontuacao;
}

void aturanking(const string& nomeJogador, int pontuacao) {
    map<string, int> rank;
    ifstream arquivoIn("ranking.txt");
    string nome;
    int pontos;

    while (arquivoIn >> nome >> pontos) {
        rank[nome] = pontos;
    }

    arquivoIn.close();

    if (rank.find(nomeJogador) != rank.end() && rank[nomeJogador] < pontuacao) {
        rank[nomeJogador] = pontuacao;
    } else if (rank.find(nomeJogador) == rank.end()) {
        rank[nomeJogador] = pontuacao;
    }

    vector<pair<string, int>> rankingOrdenado(rank.begin(), rank.end());
    sort(rankingOrdenado.begin(), rankingOrdenado.end(), [](auto& a, auto& b) {
        return a.second > b.second;
    });

    ofstream arquivoOut("ranking.txt");
    for (const auto& jogador : rankingOrdenado) {
        arquivoOut << jogador.first << " " << jogador.second << endl;
    }
}

void mostrarRanking() {
    ifstream arquivo("ranking.txt");

    if (!arquivo.is_open()) {
        cout << "Nenhum ranking encontrado." << endl;
        return;
    }

    cout << "\n--- Ranking ---" << endl;

    string nome;
    int pontos;

    while (arquivo >> nome >> pontos) {
        cout << nome << " " << pontos << endl;
    }

    arquivo.close();
}

int main() {
    vector<pergunta> perguntas = carregar();

    string nome;
    

    

    int pontuacao = rodar(perguntas);
    cout << "Quiz finalizado!" << endl;
    cout << "Você acertou " << pontuacao  << " de " << perguntas.size() << " perguntas."<< endl;
    cout << endl;

    cout << "Digite seu nome: ";
    cin >> nome;

    aturanking(nome, pontuacao);

    cout << "Ranking atualizado com sucesso!" << endl;
    mostrarRanking();
    return 0;
}
