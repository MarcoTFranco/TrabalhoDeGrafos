#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

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
    vector <vector<int>> matrizDeAdjacencia; // Matriz de adjacência

    void retiraVertices();
    void retiraArestas();
    bool auxiliarBipartido(int v, int c, vector<int>& color); // Função auxiliar para verificar se o grafo é bipartido
    void listaAdjacencia(); // Função que faz uma lista de adjacência
    void matrizAdjacencia(); // Função que faz uma matriz de adjacência
    bool verificaCicloHamiltoniano(int v, vector<bool>& visitado, vector<int>& caminho, int pos); // Função que verifica se o grafo é hamiltoniano
    void dfs(int v, vector<bool>& visitado); // Função que faz uma busca em profundidade
    void bfs(int v, vector<bool>& visitado); // Função que faz uma busca em largura


public:
    Grafo(string texto);
    ~Grafo();
    //1
    int getQtdVertices();
    int getQtdArestas();
    bool conexo();
    bool bipartido();
    bool euleriano();
    bool hamiltoniano();
    //2
    void listarVertices();
    void listarArestas();
    //3
    void imprimirMatrizAdjacencia();
    void imprimirListaAdjacencia();
};

Grafo::Grafo(string textoGrafo)
{
    this->textoGrafo = textoGrafo;
    retiraVertices();
    retiraArestas();
    listaAdjacencia();
    matrizAdjacencia();
    
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
 * Função que faz uma matriz de adjacência
*/
void Grafo::matrizAdjacencia() {
    matrizDeAdjacencia.resize(vertices.size(), vector<int>(vertices.size(), 0));

    for (int i = 0; i < (int) arestas.size(); i++) {
        matrizDeAdjacencia[arestas[i].first - 1][arestas[i].second - 1] = 1;
        matrizDeAdjacencia[arestas[i].second - 1][arestas[i].first - 1] = 1;
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
 * Função que faz uma busca em profundidade
*/
void Grafo::dfs(int v, vector<bool>& visitado) {
    stack<int> pilha;
    pilha.push(v);

    while (!pilha.empty()) {
        int vertice = pilha.top();
        pilha.pop();

        if (!visitado[vertice]) {
            visitado[vertice] = true;

            for (int u : listaDeAdjacencia[vertice - 1]) {
                if (!visitado[u]) {
                    pilha.push(u);
                }
            }
        }
    }
}

void Grafo::bfs(int v, vector<bool>& visitado) {
    queue<int> fila;
    fila.push(v);

    while (!fila.empty()) {
        int vertice = fila.front();
        fila.pop();

        if (!visitado[vertice]) {
            visitado[vertice] = true;

            for (int u : listaDeAdjacencia[vertice - 1]) {
                if (!visitado[u]) {
                    fila.push(u);
                }
            }
        }
    }
}

/**
 * Função que verifica se o grafo é conexo
*/
bool Grafo::conexo() {
    vector<bool> visitado(qtdVertices + 1, false);
    dfs(vertices[0], visitado);

    for (int i = 1; i <= qtdVertices; i++) {
        if (!visitado[i]) {
            return false;
        }
    }
    return true;
}

/**
 * Função auxiliar para verificar se o grafo é bipartido
*/
bool Grafo::auxiliarBipartido(int v, int c, vector<int>& color) {
    color[v] = c; // atribua cor c a v

    for (int u : listaDeAdjacencia[v]) { // para cada vizinho u de v
        if (color[u] == c) {
            return false; // se algum vizinho colorido de v tem cor c, então diga não
        }
        if (color[u] == -1 && !auxiliarBipartido(u, 1 - c, color)) {
            return false; // se A(w, 1−c) diz não para algum vizinho incolor w de v, então diga não
        }
    }

    return true; // diga sim
}

/**
 * Função que verifica se o grafo é bipartido
*/
bool Grafo::bipartido() {
    int n = listaDeAdjacencia.size();
    vector<int> color(n, -1); // -1 representa cor não visitada

    for (int i = 0; i < n; ++i) {
        if (color[i] == -1 && !auxiliarBipartido(i, 0, color)) {
            return false;
        }
    }

    return true;
}

/**
 * Função que verifica se o grafo é euleriano
*/
bool Grafo::euleriano() {
    if (!conexo()) {
        return false;
    }

    for (int i = 0; i < (int) matrizDeAdjacencia.size(); i++) {
        int grau = 0;
        for (int j = 0; j < (int) matrizDeAdjacencia[i].size(); j++) {
            grau += matrizDeAdjacencia[i][j];
        }
        if (grau % 2 != 0) {
            return false;
        }
    }

    return true;
}

/**
 * Função que verifica se o grafo é hamiltoniano
*/
bool Grafo::verificaCicloHamiltoniano(int v, vector<bool>& visitado, vector<int>& caminho, int pos) {
    if (pos == qtdVertices) {
        // Verifica se o último vértice está conectado ao primeiro
        if (find(listaDeAdjacencia[v-1].begin(), listaDeAdjacencia[v-1].end(), caminho[0]) != listaDeAdjacencia[v-1].end()) {
            return true;
        } else {
            return false;
        }
    }

    for (int u : listaDeAdjacencia[v-1]) {
        if (!visitado[u-1]) {
            visitado[u-1] = true;
            caminho[pos] = u;

            if (verificaCicloHamiltoniano(u, visitado, caminho, pos + 1)) {
                return true;
            }

            visitado[u-1] = false;
        }
    }

    return false;
}

bool Grafo::hamiltoniano() {
    vector<bool> visitado(qtdVertices, false);
    vector<int> caminho(qtdVertices, -1);

    // Inicia do vértice 1 (ou qualquer vértice inicial)
    visitado[0] = true;
    caminho[0] = 1;

    return verificaCicloHamiltoniano(1, visitado, caminho, 1);
}

/**
 * Função que lista os vértices
*/
void Grafo::listarVertices() {
    for (int i = 0; i < (int) vertices.size(); i++) {
        cout << vertices[i] << " ";
    }
    cout << endl;
}

/**
 * Função que lista as arestas
*/
void Grafo::listarArestas() {
    for (int i = 0; i < (int) arestas.size(); i++) {
        cout << "(" << arestas[i].first << "," << arestas[i].second << ") ";
    }
    cout << endl;
}

/**
 * Função que imprime a matriz de adjacência
*/
void Grafo::imprimirMatrizAdjacencia() {

    for (int i = 0; i < (int) matrizDeAdjacencia.size(); i++) {
        for (int j = 0; j < (int) matrizDeAdjacencia[i].size(); j++) {
            cout << matrizDeAdjacencia[i][j] << " ";
        }
        cout << endl;
    }
}

/**
 * Função que imprime a lista de adjacência
*/
void Grafo::imprimirListaAdjacencia() {

    for (int i = 0; i < (int) listaDeAdjacencia.size(); i++) {
        cout << vertices[i] << ": ";
        for (int j = 0; j < (int) listaDeAdjacencia[i].size(); j++) {
            cout << listaDeAdjacencia[i][j] << " ";
        }
        cout << endl;
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
    cout << endl;
    cout << "Menu de opcoes" << endl;
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
    cout << "4. Sair" << endl;
    cout << endl;
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
                    if (grafo.bipartido()) {
                        cout << "O grafo e bipartido!" << endl;
                    } else {
                        cout << "O grafo nao e bipartido!" << endl;
                    }
                } else if (opcao2 == "e") {
                    cout << "e. Euleriano" << endl;
                    if (grafo.euleriano()) {
                        cout << "O grafo e euleriano!" << endl;
                    } else {
                        cout << "O grafo nao e euleriano!" << endl;
                    }
                } else if (opcao2 == "f") {
                    cout << "f. Hamiltoniano" << endl;
                    if (grafo.hamiltoniano()) {
                        cout << "O grafo e hamiltoniano!" << endl;
                    } else {
                        cout << "O grafo nao e hamiltoniano!" << endl;
                    }
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
                    grafo.listarVertices();
                    cout << endl;
                } else if (opcao2 == "b") {
                    cout << "b. Arestas" << endl;
                    grafo.listarArestas();
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
                    grafo.imprimirMatrizAdjacencia();
                } else if (opcao2 == "b") {
                    cout << "b. Lista de adjacencia" << endl;
                    grafo.imprimirListaAdjacencia();
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

            case '4':
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
