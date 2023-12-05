#include "Casino.h"
#include "Uteis.h"
#include "Relogio.h"


Casino::Casino(string nome, int numMaquinas)
{
	nomeC = nome;
	LM = *GerarMaquinas(numMaquinas);
	DinheiroPerdido = 0;
	DinheiroRecebido = 0;
}

Casino::~Casino()
{
	/*for (auto& maqPtr : LM) {
		delete maqPtr;
	}
	LM.clear();

	for (auto& pessoaPtr : LP) {
		delete pessoaPtr;
	}
	LP.clear();*/
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

void Casino::MostrarListaPessoas(list<Pessoa*> lista) {
	for (list<Pessoa*>::iterator it = lista.begin(); it != lista.end(); it++) {
		(*it)->MostrarPessoa();
	}
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

Pessoa* Casino::GetPessoa() {

	int index = Util::RandNumInt(0, LPT.size());

	auto it = LPT.begin();
	std::advance(it, index);

	return *it;
}


void Casino::AddPessoa(Pessoa *pessoa) {
	pessoa->PessoaParaCasino(this);
	LP.push_back(pessoa);
	LPJ.push_back(pessoa);
	LPT.remove(pessoa);
	pessoa->adicionaSaldo(Util::RandNumInt(100, 500));
}

void Casino::RmvPessoa(Pessoa* pessoa) {
	pessoa->PessoaParaFora();
	LP.remove(pessoa);
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
	else
		cout << "Erro ao procurar maquina. Nao existe uma maquina com ID=" << id_maq << endl << "\n";
}

list<Maquina*>* Casino::GerarMaquinas(int numMaquinas)
{
	list<Maquina*>* lista = new list<Maquina*>();
	for (int i = 0; i < numMaquinas; i++)
	{
		TIPO_MAQUINA randomTipo = static_cast<TIPO_MAQUINA>(1 + (rand() % 4));//tipo de jogo na maquina aleatorio
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

			Maquina* maq = new Maquina(i + 1, randomTipo, randomx, randomy);
		lista->push_back(maq);
	}
	return lista;
}

void Casino::Run(bool Debug)
{
	int x = 0;
	Relogio relogio;
	relogio.StartRelogio(1, "15:00:00"); // Inicia o relógio às 15:00:00 com velocidade 1

	bool loopAtivo = true;

	while (loopAtivo) {
		time_t tempoAtual = relogio.VerTimeRelogio();

		// Obter o tempo de término (03:00:00) e o tempo de início (15:00:00)
		std::tm tempoTermino = relogio.StringParaTM("03:00:00");
		std::tm tempoInicio = relogio.StringParaTM("15:00:00");

		// Converter a estrutura tm para time_t usando mktime()
		time_t tempoTermino_t = std::mktime(&tempoTermino);
		time_t tempoInicio_t = std::mktime(&tempoInicio);

		// Verificar se o tempo atual está dentro do intervalo [tempoInicio_t, tempoTermino_t)
		if ((tempoAtual >= tempoInicio_t && tempoAtual < tempoTermino_t) || (tempoAtual >= 0 && tempoAtual < tempoTermino_t)) {
			loopAtivo = false;
		}
		else {
			// Adicione sua lógica para o período do loop aqui
			// ...
			
			cout << x;
			x++;

			// Aguarda um segundo antes de avançar para o próximo ciclo
			relogio.Wait(1);
		}
	}

}
