# include <stdio.h>
# include <iostream>
#include <string>
#include <string.h>
# include <fstream>
#include <map>

 using namespace std;

 string lexsem=("");
 int col=1, row=1;
 char c;
 int old_col=1, old_row=row;
 int spec;
 ifstream fin("input.txt");
 ofstream fout("output.txt");

class Token {	
	int l;
	int q;
	string tok;
	string leks;
public:
	Token (int L, int C, string TOK, string LEKS){ 
		l=L;
		q=C;
		tok=TOK;
		leks=LEKS;
		if (lexsem!="")  {
		fout<<l<<"\t" <<q<<" \t"<<tok<<" \t"<<leks<<'\n';	
		}
	}
	~Token(){}
};
 enum identType {IDENT= 0, KEYWORDS, OP};
	map<string, identType> ident_type;
	void initmap() {
ident_type["begin"] = KEYWORDS;
ident_type["forward"] = KEYWORDS;
ident_type["do"] = KEYWORDS;
ident_type["else"] = KEYWORDS;
ident_type["end"] = KEYWORDS;
ident_type["for"] = KEYWORDS;
ident_type["function"] = KEYWORDS;
ident_type["if"] = KEYWORDS;
ident_type["array"] = KEYWORDS;
ident_type["of"] = KEYWORDS;
ident_type["procedure"] = KEYWORDS;
ident_type["program"] = KEYWORDS;
ident_type["record"] = KEYWORDS;
ident_type["then"] = KEYWORDS;
ident_type["to"] = KEYWORDS;
ident_type["type"] = KEYWORDS;
ident_type["var"] = KEYWORDS;
ident_type["while"] = KEYWORDS;
ident_type["break"] = KEYWORDS;
ident_type["continue"] = KEYWORDS;
ident_type["downto"] = KEYWORDS;
ident_type["exit"] = KEYWORDS;
ident_type["repeat"] = KEYWORDS;
ident_type["until"] = KEYWORDS;
ident_type["and"] = OP;
ident_type["div"]= OP;
ident_type["mod"] = OP;
ident_type["not"] = OP;
ident_type["or"] = OP;
ident_type["xor"] = OP;
	}
 void next_simvol(){	
		if (c=='\n') { old_col = 1; col=1; row++; }
		fin>>c;	
			if  (c==' ' ) {
			col++;
		  c=NULL; 
		}	
			if (fin.eof()) {
				c = '%';}
 }
 
Token *get_token(){	
		
			if (fin.eof()){
				return 0;}
				
				string type;					
				if (spec!=1) {
					next_simvol();
					col++;
				}
				else if (spec=1) {spec=0;}

		 if ((c>='a' && c<='z') || (c>='A' && c<='Z') || (c>='_' && c<='_')) {
			 type = "ident";		
			lexsem += c;
			next_simvol();
			col++;	
		
			while((c>='a' && c<='z') || (c>='A' && c<='Z') || (c>='0') && (c<='9') || ((c>='-') && (c<='-')) || ((c>='_') && (c<='_'))   ){
				lexsem += c;
				next_simvol();	
				col++;			
			}
			spec=1;
		 }
		 	
		 else	
		if (c>='0' && c<='9'){
			type = "integer";
			lexsem += c;
			next_simvol();
			col++;
		while((c>='0') && (c<='9') || (c>='.') && (c<='.')){
			lexsem += c;	
				next_simvol();
				if ((c>='.') && (c<='.')) {
				type="real"; }				
				col++;	
		}	
			spec=1;
		}
		else
		if ((c=='>') || (c=='<') || (c=='/') || (c=='+')|| (c=='*') || (c=='/') || (c==':')  || (c=='-') || (c=='^') || (c=='=') || (c=='@' ) ||  (c==';') || (c==',')  ||( c=='(')   || (c=='[')  || (c==')')   || (c==']')   || (c=='.')  ) {
				type="op";
				lexsem += c;
				if (c=='<') {
				next_simvol();
				col++;
				if ((c=='>') || (c=='=')) { lexsem+=c; spec=0;} 
				else {spec=1;}
				}
				else if (c==':') { next_simvol();
				col++;	
				if (c=='=') { 	lexsem += c;}
				else 	{type="sep"; spec=1;}}
				else	if ((c!='^') &&  (c!='@' ) &&  (c!=';' ) && (c!=',')  && ( c!='(' )   && (c!='[' )  && (c!=')') && (c!=']') && (c!='.')){	
			next_simvol();
				col++;	
			spec=1;
			if (c=='=')  {lexsem+=c; spec=0;}
			else if (c=='/') {
				while(old_row==row){
				lexsem+=c; 
				next_simvol();
				col++;
				}
				return 0;
			}
			else if (c=='*') {
				lexsem+=c; 
				next_simvol();
				while(1){
				lexsem+=c; 
					if (c=='*') { 
					next_simvol();
					col++;
					if (c=='/') {	lexsem+=c; col++;spec=0; return 0;}}
					next_simvol();	
				}
			}
			else {spec=1;}			
				}
				else 	if (  (c==';' ) || (c==',')  || ( c=='(')   || (c=='[')  || (c==')')  || (c==']') || (c=='.')) { type = "sep"; }
		}	
		if (c=='{') { 
			while(c!='}'){
			lexsem += c;
			next_simvol();
			col++;
			}
			lexsem += c;
			return 0;
		}
			if (type=="ident" && ident_type[lexsem] == KEYWORDS)
				{ type="keybord"; }
			if (type=="ident" && ident_type[lexsem]== OP)
				{ type="op";}
		Token *t = new Token(row, old_col, type, lexsem);
		old_col=col;
		return t;
	}
int main()
{   setlocale(LC_ALL,"Rus");
	initmap();
	fin >> noskipws;	
	next_simvol();
	col++;
	spec=1;
	if (fin.eof())  {return 0;}
	while(1){		
		if (fin.eof())  {return 0;}			
		get_token();	
		lexsem=("");
	}	
	fin.close();	
		fout.close();	
}