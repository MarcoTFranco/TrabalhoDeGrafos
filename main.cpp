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
    int V; // Número de vértices
    vector <int> vertices; // Vetor de vértices
    vector <pair<int, int>> arestas; // Vetor de arestas
public:
    Grafo(string texto);
    ~Grafo();
    void retiraVertices();
    void retiraArestas();
    void matrizAdjacencia();
    void listaAdjacencia();
    
};

Grafo::Grafo(string textoGrafo)
{
    this->textoGrafo = textoGrafo;
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
    
    for (int i = 0; i < verticeRetirado.size(); i++) {
        if (verticeRetirado[i] != ',' && verticeRetirado[i] != ';') {
            vertice += verticeRetirado[i];
            vertices.push_back(stoi(vertice));
            vertice = "";
        }
    }

    cout << "Vértices: ";
    for (int i = 0; i < vertices.size(); i++) {
        cout << vertices[i] << " ";
    }
}

/**
 * Função que retira as arestas de uma string (1,2),(2,3),(3,1),(4,5) e armazena em um vetor
*/
void Grafo::retiraArestas() {
    string arestasRetiradas = textoGrafo.substr(textoGrafo.find("A = {") + 5, textoGrafo.find(")};") - textoGrafo.find("A = {") - 4);
    
    string aresta;
    for (int i = 0; i < arestasRetiradas.size(); i++) {
        if (arestasRetiradas[i] != ',' && arestasRetiradas[i] != ';') {
            aresta += arestasRetiradas[i];
            if (aresta.size() == 4) {
                arestas.push_back(make_pair(stoi(aresta.substr(1, 1)), stoi(aresta.substr(2, 1))));
                aresta = "";
            }
        }
    }

    cout << "Arestas: ";
    for (int i = 0; i < arestas.size(); i++) {
        cout << "(" << arestas[i].first << "," << arestas[i].second << ") ";
    }
}

/**
 * Função que imprime a matriz de adjacência
*/
void Grafo::matrizAdjacencia() {
    int matriz[vertices.size()][vertices.size()];
    for (int i = 0; i < vertices.size(); i++) {
        for (int j = 0; j < vertices.size(); j++) {
            matriz[i][j] = 0;
        }
    }

    for (int i = 0; i < arestas.size(); i++) {
        matriz[arestas[i].first - 1][arestas[i].second - 1] = 1;
    }

    cout << "Matriz de Adjacência: " << endl;
    for (int i = 0; i < vertices.size(); i++) {
        for (int j = 0; j < vertices.size(); j++) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
}

/**
 * Função que imprime a lista de adjacência
*/
void Grafo::listaAdjacencia() {
    vector <vector<int>> listaAdjacencia(vertices.size());
    for (int i = 0; i < vertices.size(); i++) {
        for (int j = 0; j < arestas.size(); j++) {
            if (arestas[j].first == vertices[i]) {
                listaAdjacencia[i].push_back(arestas[j].second);
            }
        }
    }

    cout << "Lista de Adjacência: " << endl;
    for (int i = 0; i < vertices.size(); i++) {
        cout << vertices[i] << ": ";
        for (int j = 0; j < listaAdjacencia[i].size(); j++) {
            cout << listaAdjacencia[i][j] << " ";
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

    cout << " ############ Menu: ############ " << endl;

    cout << "a. Representações: " << endl;
    cout << "   i.Matriz de Adjacência" << endl;
    cout << "   ii.Lista de Adjacência" << endl;

    cout << "b. Remoções e Inserções" << endl;
    cout << "   i.Arestas" << endl;
    cout << "       1. Remover" << endl;
    cout << "       2. Adicionar" << endl;
    cout << "   ii.Vértices" << endl;
    cout << "       1. Remover" << endl;
    cout << "       2. Adicionar" << endl;

    cout << "c. Verificações" << endl;
    cout << "   i.Quantidade de vértices" << endl;
    cout << "   ii.Quantidade de arestas" << endl;
    cout << "   iii.Grau de um vértice" << endl;
    cout << "   iv.O grafo é conexo?" << endl;
    cout << "   v.O grafo é fortemente conexo?" << endl;
    cout << "   vi.O grafo possui ciclos?" << endl;
    cout << "   vii.O grafo é Euleriano?" << endl;

    cout << "d. Árvores" << endl;
    cout << "   i.Busca em Largura" << endl;
    cout << "   ii.Busca em Profundidade" << endl;
    cout << "   iii.Geradora mínima" << endl;
    cout << "       1. Kruskall" << endl;
    cout << "       2. Prim !" << endl;

}

/**
 * Função que exibe o menu e chama as funções de acordo com a opção escolhida
*/
void menu() {

    char opcao;
    string opcao2;
    bool loop = true;

    while (loop) {
        menuDeOpcoes();
        cout << "Digite a opção desejada: ";
        cin >> opcao;


        switch(opcao) {
            case 'a':
                cout << "a. Representações: " << endl;
                cin >> opcao2;
                if (opcao2 == "i") {
                    cout << "i.Matriz de Adjacência" << endl;
                } else if (opcao2 == "ii") {
                    cout << "ii.Lista de Adjacência" << endl;
                } else {
                    cout << "Opção inválida!" << endl;
                }
                break;

            case 'b':
                cout << "b. Remoções e Inserções" << endl;
                cin >> opcao2;
                if (opcao2 == "i") {
                    cout << "i.Arestas" << endl;
                    cin >> opcao2;
                    if (opcao2 == "1") {
                        cout << "1. Remover" << endl;
                    } else if (opcao2 == "2") {
                        cout << "2. Adicionar" << endl;
                    } else {
                        cout << "Opção inválida!" << endl;
                    }
                } else if (opcao2 == "ii") {
                    cout << "ii.Vértices" << endl;
                    cin >> opcao2;
                    if (opcao2 == "1") {
                        cout << "1. Remover" << endl;
                    } else if (opcao2 == "2") {
                        cout << "2. Adicionar" << endl;
                    } else {
                        cout << "Opção inválida!" << endl;
                    }
                } else {
                    cout << "Opção inválida!" << endl;
                }
                break;

            case 'c':
                cout << "c. Verificações" << endl;
                break;

            case 'd':
                cout << "d. Árvores" << endl;
                break;
            
            case 's':
                cout << "Saindo..." << endl;
                loop = false;
                break;
                
            default:
                cout << "Opção inválida!" << endl;
        }

    }
}

int main()
{

    Grafo grafo(leituraArquivo());

    grafo.retiraVertices();
    grafo.retiraArestas();
    grafo.matrizAdjacencia();
    grafo.listaAdjacencia();


    menu();

    return 0;
}
