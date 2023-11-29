#include"Casino.h"
#include <random>
#define PESSOASFORA = 0


Casino::Casino(string nome, int numMaquinas)
{
	nomeC = nome;
	LM = *GerarMaquinas(numMaquinas);
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

bool Casino::AddMaquina(Maquina* m)
{
	LM.push_back(m);
	return true;
}

Maquina* Casino::PesquisarMaquinaID(int id_maq)
{
	for (list<Maquina*>::iterator it = LM.begin(); it != LM.end(); ++it)
	{
		if ((*it)->getID() == id_maq)
		{
			return *it;
		}
	}
	return nullptr;
}

void Casino::MostrarMaquinas()
{
	for (list<Maquina*>::iterator it = LM.begin(); it != LM.end(); ++it)
	{
		(*it)->MostrarMaquina();
	}
}

void Casino::Desligar(int id_maq)
{
	Maquina* maq = PesquisarMaquinaID(id_maq);
	if (maq)
		maq->DesligarMaquina();
	else
		cout << "Erro ao desligar maquina. Nao existe uma maquina com ID=" << id_maq << endl << "\n";
}

ESTADO_MAQUINA Casino::Get_Estado(int id_maq)
{
	Maquina* M = PesquisarMaquinaID(id_maq);
	if (M)
	{
		return M->getEstado();
	}
}

list<Maquina*>* Casino::GerarMaquinas(int numMaquinas)
{
	list<Maquina*>* lista = new list<Maquina*>();
	for (int i = 0; i < numMaquinas; i++)
	{
		int randomTipo = 1 + (rand() % 4);
		int randomx, randomy;
			bool posicaoOcupada;
			do
			{
				posicaoOcupada = false;
				randomx = 0 + (rand() % (X_MAX_CASINO+1));
				randomy = 0 + (rand() % (Y_MAX_CASINO + 1));
				for (list<Maquina*>::iterator it = lista->begin(); it != lista->end(); ++it)
				{
					if (((*it)->getX() == randomx) && ((*it)->getY() == randomy))//se a posicao ja estiver ocupada
					{
						posicaoOcupada = true;
						break;
					}
				}
			} while (posicaoOcupada);

		Maquina* maq = new Maquina(i + 1, randomTipo,randomx,randomy);
		lista->push_back(maq);
	}
	return lista;
}
