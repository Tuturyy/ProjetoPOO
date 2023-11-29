#include"Casino.h"
#include <random>
#define PESSOASFORA = 0


Casino::Casino(string nome, int numMaquinas)
{
	nomeC = nome;
	//LM = *GerarMaquinas(numMaquinas);
}

Casino::~Casino()
{
	for (auto& maqPtr : LM) {
		delete maqPtr;
	}
	LM.clear();

	for (auto& pessoaPtr : LP) {
		delete pessoaPtr;
	}
	LP.clear();
}

void Casino::LerFicheiro()
{
	string fich = "pessoas.txt";
	ifstream file(fich);
	if (!file.is_open())
	{
		cout << "Erro ao abrir ficheiro" << endl;
		return;
	}
	string line;
	while (getline(file, line))
	{
		istringstream iss(line);
		int ID;
		string Nome;
		string Localidade;
		int Idade;
		string token;
		int tokenPosition = 0;
		while (getline(iss, token, '\t'))
		{
			if (tokenPosition == 0)
			{
				ID = stoi(token);
			}
			else if (tokenPosition == 1)
			{
				Nome = token;
			}
			else if (tokenPosition == 2)
			{
				Localidade = token;
			}
			else if (tokenPosition == 3)
			{
				Idade = stoi(token);
			}
			tokenPosition++;
		}
		Pessoa* pessoa = new Pessoa(ID, Nome, Localidade, Idade);
		LPT.push_back(pessoa);

	}
	file.close();
}

void Casino::MostrarPessoasFora(){
	for (list<Pessoa*>::iterator it = LPT.begin(); it != LPT.end(); it++) {
		(*it)->MostrarPessoa();
	}
}

void Casino::MostrarPessoasCasino()
{
	for (list<Pessoa*>::iterator it = LP.begin(); it != LP.end(); it++) {
		(*it)->MostrarPessoa();
	}
}

void Casino::AddPessoa() {

	//srand(time(NULL));

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(100, 500);

	int index = rand() % LPT.size();

	auto it = LPT.begin();
	std::advance(it, index);

	Pessoa* pessoaSelecionada = *it;

	Pessoa* novaPessoa = new Pessoa(pessoaSelecionada->getID(), pessoaSelecionada->getNome(), pessoaSelecionada->getLocalidade() , pessoaSelecionada->getIdade());
	novaPessoa->adicionaSaldo(dis(gen));
	LP.push_back(novaPessoa);
	LPT.erase(it);

}

