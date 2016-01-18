using namespace std;
#include "Lexser.h"

Token *cur;

class Node
{	
protected:
    string info; //Информационное поле
    Node *left, *right;//Левая и Правая часть дерева
public:
	Node (string I, Node *L, Node *R){
		info=I;
		left=L;
		right=R;
	}
	~Node(){}
};

 Node *node; //начальная вершина дерева
 Node *n;
 string b;

Lexser *l = new Lexser();
void next_token(){
	cur = l->get_token();
}

Node* pars_primary(){
	 if (cur->tok == "ident" || cur->tok == "integer") {
		 Node *t = new Node(cur->leks, NULL,  NULL);
		next_token();
		return node;
	 }
	 else {cout<<"Expected"; exit;}
 }

Node* pars_uzel(string info, Node *left, Node *right){
	Node *t = new Node(cur->leks, left,  right);
	return node;
}

void pars_mull(){
	pars_primary();
	string b = cur->leks;
	while(cur->leks == "*" || cur->leks == "/"){
		next_token();
		n=pars_uzel(cur->leks, NULL, NULL);
		next_token();
		node=pars_uzel(b, n, NULL);
	}
}

void pars_add(){
	pars_primary();
	string b = cur->leks;
	cout<<b;
	int k;
	cin>>k;
	while(b == "+" || b == "-"){
		next_token();
		n=pars_uzel(cur->leks, NULL, NULL);
		next_token();
		node=pars_uzel(b, n, NULL);
	}
}

int main()
{   
 	setlocale(LC_ALL,"Rus");
	initmap();
	fin >> noskipws;
	  /* try {
        while (cur = l->get_token()) {
				if (tips!="coment" && tips!="per" && tips!=""){
            cur->print();
				}
            delete cur;
        }
    }catch ( Errors *e) { e->print(); return 0;}
	*/
	
	next_token();
	pars_add();
	fin.close();	
	fout.close();	
}