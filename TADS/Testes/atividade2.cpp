#include <iostream>
#include <string>

using namespace std;

struct AnimalCadastro
{
	string nome;
	string especie;
	string localResgate;
	string dataResgate;
};

class Animal
{
private:
	AnimalCadastro *listaAnimais;
	int totalAnimais;

public:
	Animal(int qtd_animais);
	~Animal();
	void cadastraAnimal();
	void imprimeAnimais();
};

Animal::Animal(int qtdAnimais = 5)
{
	listaAnimais = new AnimalCadastro[qtdAnimais];
	totalAnimais = qtdAnimais;
}

Animal::~Animal()
{
	totalAnimais = 0;
}

void Animal::cadastraAnimal()
{
	for (int i = 0; i < totalAnimais; i++)
	{
		cin >> listaAnimais[i].nome;
		cin >> listaAnimais[i].especie;
		cin >> listaAnimais[i].localResgate;
		cin >> listaAnimais[i].dataResgate;
	}
}
void Animal::imprimeAnimais()
{
	cout << "Lista de animais cadastrados: " << endl;
	for (int i = 0; i < totalAnimais; i++)
	{
		cout << "Nome: " << listaAnimais[i].nome << endl;

		cout << "Espécie: " << listaAnimais[i].especie << endl;

		cout << "Local do Resgate: " << listaAnimais[i].localResgate << endl;

		cout << "Data do Resgate: " << listaAnimais[i].dataResgate << endl
			 << endl;
	}
};

int main()
{
	cout << "Olá, para começarmos digite: " << endl;
	int qtd_animais, qtd_benfeitores;
	cout << "A quantidade de animais a serem cadastrados: ";
	cin >> qtd_animais;

	//cout << "A quantidade de benfeitores a serem cadastrados: ";
	//cin >> qtd_benfeitores;

	Animal *animal = new Animal(qtd_animais);
	animal->cadastraAnimal();
	animal->imprimeAnimais();
}
