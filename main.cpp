#include <iostream>

using namespace std;

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
    bool loop = true;

    while (loop) {
        menuDeOpcoes();
        cout << "Digite a opção desejada: ";
        cin >> opcao;

        switch(opcao) {
            case 'a':
                cout << "a. Representações: " << endl;
                break;
            case 'b':
                cout << "b. Remoções e Inserções" << endl;
                break;
            case 'c':
                cout << "c. Verificações" << endl;
                break;
            case 'd':
                cout << "d. Árvores" << endl;
                break;
            default:
                cout << "Opção inválida!" << endl;
        }

        if (opcao == 's') {
            loop = false;
        }
    }
}

int main()
{

    menu();

    return 0;
}
