using namespace std;
#include "Lexser.h"

struct node
{	
    char info; //�������������� ����
    node *left, *right;//����� � ������ ����� ������
};

node *tree=NULL;

void makeNode(){
	node childnode;
	

}

int main()
{   
 	setlocale(LC_ALL,"Rus");
	initmap();
	Lexser *l = new Lexser();
	fin >> noskipws;	
	 Token *cur;
	   try {
        while (cur = l->get_token()) {
				if (tips!="coment" && tips!="per" && tips!=""){
            cur->print();
				}
            delete cur;
        }
    }catch ( Errors *e) { e->print(); return 0;}
	fin.close();	
	fout.close();	
}