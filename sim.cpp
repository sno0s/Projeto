#include <iostream>
#include <string>
#include <queue>

using namespace std;


typedef struct POKE
{
	string number;
	string pokemon;
} POKE;

typedef struct Node
{
	POKE data;
	Node * right;
	Node * left;
} Node;

Node * insert(Node * aux, POKE newData)
{
	if(aux == NULL)
	{
		Node * n = new Node;
		n->data = newData;
		n->right = NULL;
		n->left = NULL;
		return n;
	}
	else
	{
		if(newData.number > aux->data.number)
		{
			//inserir na direita
			aux->right = insert(aux->right, newData);
		}
		else if(newData.number < aux->data.number)
		{
			//inserir na esquerda
			aux->left = insert(aux->left, newData);
		}
		else
		{
			if(newData.pokemon >= aux->data.pokemon)
			{
				//inserir na direita
				aux->right = insert(aux->right, newData);
			}
			else if(newData.pokemon < aux->data.pokemon)
			{
				//inserir na esquerda
				aux->left = insert(aux->left, newData);
			}
		}
	}
	return aux;
}

Node * search(Node * curr, string number){
	if(curr == NULL)
		return NULL;
	if(number == curr->data.number){
		return curr;
	} else {
		if(number >= curr->data.number){
			return search(curr->right, number);
		} else {
			return search(curr->left, number);
		}
	}
	
}


void show_ordered(Node * aux)
{
	//varredura a esquerda
	if(aux->left != NULL)
		show_ordered(aux->left);
	cout << aux->data.number << ". " << aux->data.pokemon << endl;
	//varredura a direita
	if(aux->right != NULL)
		show_ordered(aux->right);
	
}

Node * menor(Node *& curr)
{
	Node * aux = curr;
	if(aux == NULL)
		return NULL;
	if(aux->left == NULL)
	{
		curr = curr->right;
		return aux;
	}
	else
	{
		return menor(aux->left);
	}
}
Node * disconnect_lesser(Node *& curr){
	
	Node * aux = curr;
	if(aux->left == NULL){ 	// encontrou o menor elemento da subárvore
		curr = curr->right; // temos que salvar os filhos da direita
		return aux;			// retornamos a referência para esse nó
	} else {				// senão continua a busca na subárvore da esquerda
		return disconnect_lesser(curr->left); 
	}
	
}

int remove(Node *& curr, string number){
	if(curr == NULL){
		return 0;
	}
	Node * aux;
	if(curr->data.number == number){
		aux = curr;		
		if(curr->left == NULL){
			curr = aux->right;
		} else if(curr->right == NULL){
			curr = aux->left;
		} else {
			
			aux = disconnect_lesser(curr->right);
			
			curr->data = aux->data;
			
		}		
		delete aux;
		return 1;		
	} else {
		if(number >= curr->data.number){
			return remove(curr->right, number);
		} else {
			return remove(curr->left, number);
		}
	}
}

void destroy(Node *& aux)
{
	if(aux->left != NULL)
		destroy(aux->left);
	if(aux->right != NULL)
		destroy(aux->right);
	delete aux;
	aux = NULL;
}



int main()
{
	int n;
	int k = 1;
	Node * root;
	root = NULL;
	POKE newData;

	cout << "Digite:\n 1-para adicionar um pokemon da Pokedex\n 2-para remover um pokemon\n 3-";
	cout << "para procurar um pokemon\n 4-para ver quais sao os pokemons cadastrados" << endl;

	cin >> n;

	while(n != 0)
	{

		switch(n)
		{
		case 1:
		{

			while(k == 1)
			{
				cout << "\nNumber: ";
				cin >> newData.number;
				cout << "\nName: ";
				cin >> newData.pokemon;
				root = insert(root, newData);
				cout << "Pokemon adicionado!" << endl;
				cout << "Quer cadastrar outro pokemon?\n";
				cout << "1-sim " << " 2-nao\n" << endl;
				cin >> k;
			}

			break;
		}
		case 2:
		{
			cout << "Digite o numero do pokemon para remover:" << endl;
			cin >> newData.number;
			
			remove(root, newData.number);
			cout<<"O pokemon foi removido da pokedex"<<endl;

			break;
		}
		case 3:
		{
			cout << "Digite o numero do pokemon para iniciar a busca:" << endl;
			cin >> newData.number;

			Node * result = search(root, newData.number);
			if(result != NULL)
			{
				cout << "O pokemon numero " << newData.number << " da pokedex e o ";
				cout << result->data.pokemon << endl;
			}
			else
				cout << "Pokemon not found!" << endl;

			
			break;
		}
		case 4:
		{
			cout << "\n" << "Pokemons registrados em sua pokedex:\n";
			show_ordered(root);

			break;
		}
		}
		cout << "\nDigite:\n 1-para adicionar um pokemon da Pokedex\n 2-para remover um pokemon\n 3-";
		cout << "para procurar um pokemon\n 4-para ver quais sao os pokemons cadastrados" << endl;
		cin >> n;
		k = 1;
	}


	destroy(root);
	return 0;
}