# include <stdio.h>
# include <iostream>
#include <string>
#include <string.h>
# include <fstream>
#include <map>
#include <cctype>
 using namespace std;

 string lexsem=("");
 int col=1, row=1;
 char c = 0;
 int old_col=1, old_row=row;
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
		if (c)
			lexsem += c;	
		col++;	
		if (c=='\n') { old_col = 1; col=1; row++; }
		fin>>c;	
		if (fin.eof()) {
			c = '%';}
 }
 char ops_second_char[] = {'/','+','*',' :','-','>', '^', '@', '='};
 char sep[] = {';' ,',','(','[',')',']','.'};
 char ops[] = {'>','<','/','+','*',':','-','^','=','@',';',',','(','[',')',']','.'};
 bool in_mas(char s, char *mas, int len){
	 for(int i = 0; i < len; i++){
		if (s == mas[i]) return true;
	 }
	 return false;
 }


Token *get_token(){		
		string type;	
		if (c == ' ') {next_simvol(); old_col = col; return 0;}
		else	if (isalpha(c) || c == '_') {
			type = "ident";		
			next_simvol();
			while(isalpha(c) || isdigit(c) || c == '_'){	
				next_simvol();	
			}
		 }
		 	
		 else	
		if (isdigit(c)){
			type = "integer";
			next_simvol();
			while(isdigit(c) || c == '.'){
				next_simvol();
				if (c == '.') {
					type="real"; 
				}				
			}	
		}
		else
		if (in_mas(c, ops, sizeof(ops)/sizeof(ops[0]))){
			if (c == ':') {  next_simvol();  if (c == '=') {type="op"; next_simvol();}
			else type="sep";} else
			if (c == '<') { type="op";  next_simvol(); if (c == '>' || c == '=') {next_simvol();}}
			else if (in_mas(c, ops_second_char, sizeof(ops_second_char)/sizeof(ops_second_char[0]))){	
				type="op";
			    next_simvol();
					if (c=='=')  {next_simvol();}
					else if (c=='/') {
						while(old_row==row){
						next_simvol();
						}
					return 0;
					}
					else if (c=='*') {
					next_simvol();
						while(1){
							if (c == '*') { 
								next_simvol();
							if (c == '/') {	next_simvol(); return 0;}}
						next_simvol();	
						}
					}
				}
				else 	if (in_mas(c, sep, sizeof(sep)/sizeof(sep[0])))  {  next_simvol(); type = "sep"; }
		}	
		else if (c == '{') { 
			while(c!='}'){
			next_simvol();
			}
			old_col = col;
			next_simvol();
			return 0;
		}
		else {next_simvol(); return 0;}
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
	while(1){		
		if (fin.eof())  {return 0;}			
		get_token();	
		lexsem="";
	}	
	fin.close();	
	fout.close();	
}