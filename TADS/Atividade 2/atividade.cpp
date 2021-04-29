//Vitor André de Oliveira Tenório
//Turma 10A - Ciência da Computação

#include <iostream>
#include <string>

using namespace std;
struct Doacao
{
    float valorDoacao;
};

struct Animal
{
    string nome;
    string especie;
    string localResgate;
    string dataResgate;
};

struct Benfeitor
{
    int id;
    string nome;
    string tipo;
    int qtd_doacoes;
    Doacao *listaDoacoes;
};

class Ong
{
private:
    Animal *listaAnimais;
    Benfeitor *listaBenfeitores;
    int totalAnimais;
    int totalBenfeitores;

public:
    Ong(int t_animais, int t_benfeitores);
    ~Ong();
    void cadastraAnimal();
    void cadastraBenfeitor();
    void procuraMaiorDoacao();
    void imprimeAnimais();
    void imprimeDoacoesBenfeitor(int id);
};

Ong::Ong(int t_animais, int t_benfeitores)
{
    totalAnimais = t_animais;
    totalBenfeitores = t_benfeitores;
    listaAnimais = new Animal[totalAnimais];
    listaBenfeitores = new Benfeitor[totalBenfeitores];
}

Ong::~Ong()
{
    //cout << "chegou";
    delete[] listaAnimais;
    delete[] listaBenfeitores;
    totalAnimais = 0;
    totalBenfeitores = 0;
}

void Ong::cadastraAnimal()
{
    for (int i = 0; i < totalAnimais; i++)
    {
        cout << "Digite as seguintes informações sobre o " << i + 1 << "º animal: " << endl
             << "Nome: ";
        cin >> listaAnimais[i].nome;

        cout << "Espécie: ";
        cin >> listaAnimais[i].especie;

        cout << "Local do Resgate: ";
        cin >> listaAnimais[i].localResgate;
        cout << "Data do Resgate: ";
        cin >> listaAnimais[i].dataResgate;
        cout << endl;
    }
};

void Ong::cadastraBenfeitor()
{
    for (int i = 0; i < totalBenfeitores; i++)
    {
        cout << "Digite as seguintes informações sobre o " << i + 1 << "º Benfeitor e sua doação: " << endl
             << "id: ";
        cin >> listaBenfeitores[i].id;
        cout << "Nome: ";
        cin >> listaBenfeitores[i].nome;

        cout << "Tipo: ";
        cin >> listaBenfeitores[i].tipo;

        cout << "Quantidade de doações realizadas (máx: 10): ";
        cin >> listaBenfeitores[i].qtd_doacoes;

        if (listaBenfeitores[i].qtd_doacoes > 10)
        {
            cout << "O número é muito alto. A quantidade de doações foi limitada a 10." << endl;
            listaBenfeitores[i].qtd_doacoes = 10;
        }

        listaBenfeitores[i].listaDoacoes = new Doacao[listaBenfeitores[i].qtd_doacoes];

        cout << "Suas doações:" << endl;
        for (int j = 0; j < listaBenfeitores[i].qtd_doacoes; j++)
        {
            cout << j + 1 << "º valor a ser doado: ";
            cin >> listaBenfeitores[i].listaDoacoes[j].valorDoacao;
        }
        cout << endl;
    }
}
void Ong::imprimeAnimais()
{
    cout << "Lista de animais cadastrados: " << endl;
    for (int i = 0; i < totalAnimais; i++)
    {
        cout << "Nome: " << listaAnimais[i].nome << endl;

        cout << "Espécie: " << listaAnimais[i].especie << endl;

        cout << "Local do Resgate: " << listaAnimais[i].localResgate << endl;

        cout << "Data do Resgate: " << listaAnimais[i].dataResgate << endl;
    }
};

void Ong::imprimeDoacoesBenfeitor(int id)
{
    for (int i = 0; i < totalBenfeitores; i++)
    {
        if (id == listaBenfeitores[i].id)
        {
            cout << "O Benfeitor ";
            cout << listaBenfeitores[i].nome;

            cout << " realizou ";
            cout << listaBenfeitores[i].qtd_doacoes;
            cout << " doações. O valor de cada uma é descrito a seguir: " << endl;
            for (int j = 0; j < listaBenfeitores[i].qtd_doacoes; j++)
            {
                cout << j + 1 << "º valor doado: ";
                cout << listaBenfeitores[i].listaDoacoes[j].valorDoacao;
                cout << endl;
            }
            cout << endl;
            i = totalBenfeitores;
        }
    }
}

//Método para procurar qual Benfeitor fez a maior doação para a ONG
void Ong::procuraMaiorDoacao()
{
    float aux = 0, total = 0;
    Benfeitor maior_doador;
    for (int i = 0; i < totalBenfeitores; i++)
    {
        for (int j = 0; j < listaBenfeitores[i].qtd_doacoes; j++)
        {
            aux += listaBenfeitores[i].listaDoacoes[j].valorDoacao;
        }
        if (aux > total)
        {
            total = aux;
            maior_doador = listaBenfeitores[i];
        }
    }
    cout << "A maior doação é de: " << maior_doador.nome << " com " << total << " doados" << endl;
}

int main()
{
    cout << "Olá, para começarmos digite: " << endl;
    int qtd_animais, qtd_benfeitores;
    cout << "A quantidade de animais a serem cadastrados: ";
    cin >> qtd_animais;
    cout << "A quantidade de benfeitores a serem cadastrados: ";
    cin >> qtd_benfeitores;

    Ong *ong = new Ong(qtd_animais, qtd_benfeitores);

    cout << "Vamos cadastrar os animais no sistema?" << endl;
    ong->cadastraAnimal();

    cout << "Vamos cadastrar os benfeitores no sistema?" << endl;
    ong->cadastraBenfeitor();

    int escolha;
    while (escolha != 9)
    {
        cout << "Temos algumas opções de ações disponíveis no sistema!" << endl
             << "O que deseja fazer?" << endl
             << "---" << endl
             << "1 - Imprimir animais cadastrados" << endl
             << "2 - Imprimir doações de um Benfeitor específico" << endl
             << "3 - Imprimir benfeitor com maior doação" << endl
             << endl
             << "9 - Sair" << endl
             << "---" << endl;
        cin >> escolha;
        switch (escolha)
        {
        case 1:
            ong->imprimeAnimais();
            break;
        case 2:
            cout << "Digite o id do benfeitor a ser procurado: ";
            int id_benfeitor;
            cin >> id_benfeitor;
            ong->imprimeDoacoesBenfeitor(id_benfeitor);
            break;
        case 3:
            ong->procuraMaiorDoacao();
            break;
        case 9:
            cout << "Obrigado por utilizar o sistema!";
            delete ong;
            break;
        default:
            cout << "Valor inválido!" << endl;
            break;
        }
    }
}
