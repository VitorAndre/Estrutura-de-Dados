#include <iostream>
#include <string>

using namespace std;

class Animal
{
private:
    string nome;
    string especie;
    string localResgate;
    string dataResgate;
    int totalAnimais;

public:
    Animal(int qtd_animais);
    ~Animal();
    void cadastraAnimal();
    void imprimeAnimais();
};

Animal::Animal(int qtdAnimais = 5)
{
    nome.clear();
    especie.clear();
    localResgate.clear();
    dataResgate.clear();
    totalAnimais = qtdAnimais;
}

Animal::~Animal()
{
    nome.clear();
    especie.clear();
    localResgate.clear();
    dataResgate.clear();
    totalAnimais = 0;
}

void Animal::cadastraAnimal()
{
    cout << "Digite as seguintes informações sobre o animal: " << endl
         << "Nome: ";
    cin >> nome;

    cout << "Espécie: ";
    cin >> especie;

    cout << "Local do Resgate: ";
    cin >> localResgate;

    cout << "Data do Resgate: ";
    cin >> dataResgate;
    cout << endl;
}
void Animal::imprimeAnimais()
{
    cout << "Nome: " << nome << endl;

    cout << "Espécie: " << especie << endl;

    cout << "Local do Resgate: " << localResgate << endl;

    cout << "Data do Resgate: " << dataResgate << endl
         << endl;
};

class Benfeitor
{
private:
    int idBenfeitor;
    string nome;
    string tipo;
    int totalDoacoes;
    float listaDoacoes[];
    // int totalBenfeitores;

public:
    Benfeitor();
    ~Benfeitor();
    void cadastraBenfeitor();
    void cadastraDoacao();
    Benfeitor procuraMaiorDoacao();
    bool procuraDoacoesBenfeitor(int id);
};

Benfeitor::Benfeitor()
{
    idBenfeitor = 0;
    nome.clear();
    tipo.clear();
    totalDoacoes = 0;
}

Benfeitor::~Benfeitor()
{
    idBenfeitor = 0;
    nome.clear();
    tipo.clear();
    totalDoacoes = 0;
    for (int i = 0; i < totalDoacoes; i++)
    {
        listaDoacoes[i] = 0;
    }
}

void Benfeitor::cadastraBenfeitor()
{

    cout << "Digite as seguintes informações sobre o Benfeitor: " << endl
         << "Id do Benfeitor: ";
    cin >> idBenfeitor;

    cout << "Nome: ";
    cin >> nome;

    cout << "Tipo: ";
    cin >> tipo;

    cout << "Quantidade de Doações realizadas: ";
    cin >> totalDoacoes;
    cout << endl;
}

void Benfeitor::cadastraDoacao()
{
    for (int i = 0; i < totalDoacoes; i++)
    {
        cout << "Digite o valor da " << i + 1 << "ª doação: ";
        cin >> listaDoacoes[i];
        cout << endl;
    }
}

bool Benfeitor::procuraDoacoesBenfeitor(int id)
{
    if (id == idBenfeitor)
    {
        cout << "O Benfeitor " << nome << " fez as seguintes doações: " << endl;
        for (int i = 0; i < totalDoacoes; i++)
        {
            cout << "Doação " << i + 1 << ": " << listaDoacoes[i] << endl;
        }
        return true;
    }
    return false;
}

int main()
{
    cout << "Olá, para começarmos digite: " << endl;
    int qtd_animais;
    cout << "A quantidade de animais a serem cadastrados: ";
    cin >> qtd_animais;

    cout << "Vamos cadastrá-los?" << endl;
    Animal *animal = new Animal(qtd_animais);
    //for (int i = 0; i < qtd_animais; i++)
    //  {
    //  animal[i] = new Animal();
    //  animal[i]->cadastraAnimal();
    //}

    cout << "Agora digite a quantidade de benfeitores a serem cadastrados: ";
    int qtd_benfeitores;
    cin >> qtd_benfeitores;

    cout << "Vamos cadastrá-los?" << endl;
    Benfeitor *benfeitores[qtd_benfeitores];
    for (int i = 0; i < qtd_benfeitores; i++)
    {
        benfeitores[i] = new Benfeitor();
        benfeitores[i]->cadastraBenfeitor();
        benfeitores[i]->cadastraDoacao();
    }

    cout << "Agora devemos verificar as doações de um certo benfeitor. Você poderia informar o id dele?" << endl;
    int id;
    cin >> id;
    for (int i = 0; i < qtd_benfeitores; i++)
    {
        if (benfeitores[i]->procuraDoacoesBenfeitor(id))
            i = qtd_benfeitores;
    }

    cout << "Para acabar, serão listados os animais cadastrados no início do programa: " << endl;
    // for (int i = 0; i < qtd_animais; i++)
    // {
    animal->imprimeAnimais();
    // }
}
