#include"Casino.h"


Casino::Casino(string nome, int numMaquinas)
{
	nomeC = nome;
	LM = *GerarMaquinas(numMaquinas);
}

Casino::~Casino()
{

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
		pessoa->MostrarPessoa();
	}
	file.close();
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
		int random = 1 + (rand() % 4);
		Maquina* maq = new Maquina(i + 1, random);
		lista->push_back(maq);
	}
	for (list<Maquina*>::iterator it = lista->begin(); it != lista->end(); ++it)
	{
		int randomx = 0 + (rand() % 50);
		int randomy = 0 + (rand() % 50);

	}
	return lista;
}

bool Casino::AddPessoa(Pessoa* pessoa) {
	LP.push_back(pessoa);
	return true;
}