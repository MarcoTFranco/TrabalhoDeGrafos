#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

/**
 * Estrutura de dados para representar um grafo
*/
class Grafo
{
private:
    string textoGrafo; // Texto do grafo
    int qtdVertices; // Número de vértices
    int qtdArestas; // Número de arestas
    vector <int> vertices; // Vetor de vértices
    vector <pair<int, int>> arestas; // Vetor de arestas
    vector <vector<int>> listaDeAdjacencia; // Lista de adjacência

    void retiraVertices();
    void retiraArestas();
    void listaAdjacencia(); // Função que faz uma lista de adjacência
    void matrizAdjacencia(); // Função que faz uma matriz de adjacência

public:
    Grafo(string texto);
    ~Grafo();
    int getQtdVertices();
    int getQtdArestas();
    bool conexo();
};

Grafo::Grafo(string textoGrafo)
{
    this->textoGrafo = textoGrafo;
    retiraVertices();
    retiraArestas();
    
}

Grafo::~Grafo()
{
}

/**
 * Função que retira os vertices de uma string 1,2,3,4,5 e armazena em um vetor
*/
void Grafo::retiraVertices() {
    string verticeRetirado = textoGrafo.substr(textoGrafo.find("V = {") + 5, textoGrafo.find("};") - textoGrafo.find("V = {") - 5);
    string vertice;
    
    for (int i = 0; i < (int) verticeRetirado.size(); i++) {
        if (verticeRetirado[i] != ',' && verticeRetirado[i] != ';') {
            vertice += verticeRetirado[i];
            vertices.push_back(stoi(vertice));
            vertice = "";
        }
    }

    qtdVertices = (int) vertices.size();
}

/**
 * Função que retira as arestas de uma string (1,2),(2,3),(3,1),(4,5) e armazena em um vetor
*/
void Grafo::retiraArestas() {
    string arestasRetiradas = textoGrafo.substr(textoGrafo.find("A = {") + 5, textoGrafo.find(")};") - textoGrafo.find("A = {") - 4);
    
    string aresta;
    for (int i = 0; i < (int) arestasRetiradas.size(); i++) {
        if (arestasRetiradas[i] != ',' && arestasRetiradas[i] != ';') {
            aresta += arestasRetiradas[i];
            if (aresta.size() == 4) {
                arestas.push_back(make_pair(stoi(aresta.substr(1, 1)), stoi(aresta.substr(2, 1))));
                aresta = "";
            }
        }
    }

    qtdArestas = (int) arestas.size();
}

/**
 * Função que retorna a quantidade de arestas
*/
int Grafo::getQtdVertices() {
    return qtdVertices;
}

/**
 * Função que retorna a quantidade de vértices
*/
int Grafo::getQtdArestas() {
    return qtdArestas;
}

/**
 * Função que verifica se o grafo é conexo
*/
bool Grafo::conexo() {

    listaAdjacencia();

    vector <bool> visitados(vertices.size(), false);
    vector <int> pilha;
    pilha.push_back(vertices[0]);
    visitados[0] = true;

    while (!pilha.empty()) {
        int vertice = pilha.back();
        pilha.pop_back();

        for (int i = 0; i < (int) listaDeAdjacencia[vertice - 1].size(); i++) {
            if (!visitados[listaDeAdjacencia[vertice - 1][i] - 1]) {
                pilha.push_back(listaDeAdjacencia[vertice - 1][i]);
                visitados[listaDeAdjacencia[vertice - 1][i] - 1] = true;
            }
        }
    }

    for (int i = 0; i < (int) visitados.size(); i++) {
        if (!visitados[i]) {
            return false;
        }
    }

    return true;
}

/**
 * Função que faz uma matriz de adjacência
*/
void Grafo::matrizAdjacencia() {
    int matriz[vertices.size()][vertices.size()];
    for (int i = 0; i < (int) vertices.size(); i++) {
        for (int j = 0; j < (int) vertices.size(); j++) {
            matriz[i][j] = 0;
        }
    }

    for (int i = 0; i < (int) arestas.size(); i++) {
        matriz[arestas[i].first - 1][arestas[i].second - 1] = 1;
    }
}


/**
 * Função que faz uma lista de adjacência
*/
void Grafo::listaAdjacencia() {
    listaDeAdjacencia.resize(vertices.size());
    for (int i = 0; i < (int) vertices.size(); i++) {
        for (int j = 0; j < (int) arestas.size(); j++) {
            if (arestas[j].first == vertices[i]) {
                listaDeAdjacencia[i].push_back(arestas[j].second);
            }
        }
    }
}

/**
 * Leitura do grafo V = {1,2,3,4,5}; A = {(1,2),(2,3),(3,1),(4,5)}; em arquivo txt separando
 * os vértices por vírgula e as arestas por ponto e vírgula
 */
string leituraArquivo() {
    ifstream arquivo;
    string linha, vertice, aresta;
    arquivo.open("grafo.txt");
    if (arquivo.is_open()) {
        getline(arquivo, linha);
        arquivo.close();
    } else {
        cout << "Não foi possível abrir o arquivo!" << endl;
    }
    return linha;
}

/**
* Função que imprime o menu de opções
*/
void menuDeOpcoes() {
    cout << "1. Verificar" << endl;
    cout << "   a. Quantidade de vertices" << endl;
    cout << "   b. Quantidade de arestas" << endl;
    cout << "   c. Conexo" << endl;
    cout << "   d. Bipartido" << endl;
    cout << "   e. Euleriano" << endl;
    cout << "   f. Hamiltoniano" << endl;
    cout << "   g. Ciclico" << endl;
    cout << "   h. Planar" << endl;
    cout << "2. Listar" << endl;
    cout << "   a. Vertices" << endl;
    cout << "   b. Arestas" << endl;
    cout << "   c. Componentes conexas" << endl;
    cout << "   d. Um caminho Euleriano" << endl;
    cout << "   e. Um caminho Hamiltoniano" << endl;
    cout << "   f. Vertices de articulacao" << endl;
    cout << "   g. Arestas ponte" << endl;
    cout << "3. Gerar" << endl;
    cout << "   a. Matriz de adjacencia" << endl;
    cout << "   b. Lista de adjacencia" << endl;
    cout << "   c. Arvore de profundidade" << endl;
    cout << "   d. Arvore de largura" << endl;
    cout << "   e. Arvore geradora minima" << endl;
    cout << "   f. Ordem topologica (Esta funcao nao fica disponivel em grafos nao direcionado)" << endl;
    cout << "   g. Caminho minimo entre dois vertices (Esta funcao nao fica disponivel em grafos nao ponderados)" << endl;
    cout << "   h. Fluxo maximo (Esta funcao nao fica disponivel em grafos nao ponderados)" << endl;
    cout << "   i. Fechamento transitivo (Esta funcao nao fica disponivel em grafos nao ponderados)" << endl;
}

/**
 * Função que exibe o menu e chama as funções de acordo com a opção escolhida
*/
void menu() {

    char opcao;
    string opcao2;
    bool loop = true;

    Grafo grafo(leituraArquivo());

    while (loop) {
        menuDeOpcoes();
        cout << "Digite a opcao desejada: ";
        cin >> opcao;

        switch(opcao) {
            case '1':
                cout << "1. Verificar" << endl;
                cin >> opcao2;
                if (opcao2 == "a") {
                    cout << "a. Quantidade de vertices" << endl;
                    cout << "Quantidade de vertices: " << grafo.getQtdVertices() << endl;
                } else if (opcao2 == "b") {
                    cout << "b. Quantidade de arestas" << endl;
                    cout << "Quantidade de arestas: " << grafo.getQtdArestas() << endl;
                } else if (opcao2 == "c") {
                    cout << "c. Conexo" << endl;
                    if (grafo.conexo()) {
                        cout << "O grafo e conexo!" << endl;
                    } else {
                        cout << "O grafo nao e conexo!" << endl;
                    }
                } else if (opcao2 == "d") {
                    cout << "d. Bipartido" << endl;
                } else if (opcao2 == "e") {
                    cout << "e. Euleriano" << endl;
                } else if (opcao2 == "f") {
                    cout << "f. Hamiltoniano" << endl;
                } else if (opcao2 == "g") {
                    cout << "g. Ciclico" << endl;
                } else if (opcao2 == "h") {
                    cout << "h. Planar" << endl;
                } else {
                    cout << "Opcao invalida!" << endl;
                }
                break;
            case '2':
                cout << "2. Listar" << endl;
                cin >> opcao2;
                if (opcao2 == "a") {
                    cout << "a. Vertices" << endl;
                    cout << endl;
                } else if (opcao2 == "b") {
                    cout << "b. Arestas" << endl;
                    cout << endl;
                } else if (opcao2 == "c") {
                    cout << "c. Componentes conexas" << endl;
                } else if (opcao2 == "d") {
                    cout << "d. Um caminho Euleriano" << endl;
                } else if (opcao2 == "e") {
                    cout << "e. Um caminho Hamiltoniano" << endl;
                } else if (opcao2 == "f") {
                    cout << "f. Vertices de articulacao" << endl;
                } else if (opcao2 == "g") {
                    cout << "g. Arestas ponte" << endl;
                } else {
                    cout << "Opcao invalida!" << endl;
                }
                break;

            case '3':
                cout << "3. Gerar" << endl;
                cin >> opcao2;
                if (opcao2 == "a") {
                    cout << "a. Matriz de adjacencia" << endl;
                } else if (opcao2 == "b") {
                    cout << "b. Lista de adjacencia" << endl;
                } else if (opcao2 == "c") {
                    cout << "c. Arvore de profundidade" << endl;
                } else if (opcao2 == "d") {
                    cout << "d. Arvore de largura" << endl;
                } else if (opcao2 == "e") {
                    cout << "e. Arvore geradora minima" << endl;
                } else if (opcao2 == "f") {
                    cout << "f. Ordem topologica" << endl;
                } else if (opcao2 == "g") {
                    cout << "g. Caminho minimo entre dois vertices" << endl;
                } else if (opcao2 == "h") {
                    cout << "h. Fluxo maximo" << endl;
                } else if (opcao2 == "i") {
                    cout << "i. Fechamento transitivo" << endl;
                } else {
                    cout << "Opcao invalida!" << endl;
                }
                break;

            case 's':
                cout << "Saindo..." << endl;
                loop = false;
                break;
                
            default:
                cout << "Opcao invalida!" << endl;
        }

    }
}

int main()
{
    menu();
    
    return 0;
}
