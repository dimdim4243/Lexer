#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <map>
#include <cctype>
#include <windows.h>

using namespace std;

string lexsem=("");
string tips="";
int col=0, row=1;
char c = 0;
int old_col=1, old_row=row;
ifstream fin("input.txt");
ofstream fout("output.txt");

class Errors {	
protected:
	int l;
	int q;
	string errors;
public:
	Errors (int L, int C, string ERRORS){
		l=L;
		q=C;
		errors=ERRORS;		
	
	}
	virtual void print(){
		fout<<l<<"\t" <<q<<"\t"<<errors<<'\n';

	}
	~Errors(){}
};

class Token
{
protected:
    int l;
    int c;
    string tok;
    string leks;
public:
    Token (int L, int C, string TOK, string LEKS)
    {
        l = L;
        c = C;
        tok = TOK;
        leks = LEKS;
    }
    virtual void print(){
        fout << l << "\t" << c << "\t" << tok << "\t" << leks << endl;
    }
    ~Token(){}
};
template<class V>
class ValToken: public Token
{
    V val;
public:
    ValToken(int L, int C, string TOK, string LEKS, V val):
            val(val),
            Token(L, C, TOK, LEKS){}
    void print(){
        fout << l << "\t" << c << "\t" << tok << "\t" << leks << "\t" << val << endl;
    }
};
template<>
void ValToken<double>::print() {
    char buf[11];
    sprintf(buf, "%.4E", val);
    buf[8] = buf[9]; buf[9] = buf[10]; buf[10] = 0;
    fout << l << "\t" << c << "\t" << tok <<"\t" << leks << "\t" << buf << endl;
}

 Token *tokenbuf=NULL;

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
ident_type["end"] = KEYWORDS;
ident_type["and"] = OP;
ident_type["div"]= OP;
ident_type["mod"] = OP;
ident_type["not"] = OP;
ident_type["or"] = OP;
ident_type["xor"] = OP;
	}
 void next_simvol(){
	 lexsem+=c;
	 fin>>c;	
	 col++;	
		if (fin.eof()) {
			c = '%';}
 }

 void probel_sim(){
	 int m;
		if  (c == '\t'  || c == ' ' || c == '\n') {
			while( c =='\t' || c == ' ' || c == '\n'){
			if (c == '\t'){ col =(((col-1)/4+1)*4);}
			if (c=='\n') {old_col=col = 0; row++;	tips ="per"; m=1;}
				next_simvol();
				lexsem="";
			}
			old_col = col; }	
 }



 char ops_second_char[] = {'/','+','*',' :','-','>', '^', '<', '@', '.', '='};
 char sep[] = {';' ,',','(','[',')',']',};
 char ops[] = {'>','<','/','+','*',':','-','^','=','@',';',',','(','[',')',']','.'};
 bool in_mas(char s, char *mas, int len){
	 for(int i = 0; i < len; i++){
		if (s == mas[i]) return true;
	 }
	 return false;
 }

Token *get_token(){		
		string eror;
		lexsem="";
		string type = "";
		probel_sim();
		if (tokenbuf != 0) {
			Token *t = new Token(row, old_col, type, lexsem);
			t = tokenbuf;
				tips="sep";
			tokenbuf=NULL;
			return t;
			
		}
		   if (fin.eof()) return 0;
		if (isalpha(c) || c == '_') {
			type = "ident";		
			next_simvol();
			while(isalpha(c) || isdigit(c) || c == '_'){	
				next_simvol();	
			}
		 }	
		else	
		if (c == '$') {
			next_simvol();
			while(isdigit(c) || (c>='a' && c<='f') || (c>='A' && c<='F'))
			{next_simvol();
			}
			if  (lexsem == "$" ) {
				if (c == '%') {old_col=2;}
				if (  (c>'f' ) || (c>'F')){
					old_col++;
				}
				eror="NoHex";	
				throw new Errors(row, old_col, eror);}
			type="hex";
		}
		else
		if (isdigit(c)){
			type=tips="integer";
			next_simvol();
			while(isdigit(c) || c == '.'){
				if (c == '.') {
					type="real"; 
					next_simvol();
					if (c == '%') {
							eror="NoFract";	
				throw new Errors(row, col, eror);
					}
				}				
			
				if (c == '.') {
					type="real"; 
				if (c == '.') {
				string s;
				double a;
				s= lexsem.substr(0, lexsem.size()-1); 
				cout<<s;
				a = atoi(s.c_str());
				ValToken<int> *tokenVal= new ValToken <int>(row, old_col, "int", s, a); old_col=col;
				tips=type;
				lexsem='.';
				next_simvol();
				type="sep";
				Token *q = new Token(row, old_col, type, lexsem);
				tips=type;
				tokenbuf=q;
				old_col=col;
				return tokenVal;
				}
		

				}
				next_simvol();			
				if (c == 'e' || c == 'E') {next_simvol();	
				if (c == '+' || c == '-') {next_simvol(); 
				if ((c<'1' && c>'9') || c == '%') eror="NoExp";	

				throw new Errors(row, col, eror);
				}				else if ((c<'1' && c>'9') || c == '%') {eror="NoExp";	

				throw new Errors(row, col, eror);}
			}}

		}
		else  if (in_mas(c, sep, sizeof(sep)/sizeof(sep[0])))  {  	
			type="sep";
			if (c == '('){
				next_simvol();{
				if (c=='*') {
					next_simvol();
					
						while(1){
							next_simvol();
							if (c == '*') { 
								next_simvol();
								if (c == ')') {type="coment";	next_simvol();break;}}
							if (c == '%') { eror="BadEOF";	
				throw new Errors(row, col, eror);    }
						}
				    }
				}
			}
			else {	next_simvol();}
		}
		else if (in_mas(c, ops, sizeof(ops)/sizeof(ops[0]))){
			if (c == ':') {  next_simvol();  
			if (c == '=') {type="op"; next_simvol();}
			else {type="sep";}} 
			else if (c == '<') { type="op";  next_simvol(); if (c == '>' || c == '=') {next_simvol();}}
			else if (in_mas(c, ops_second_char, sizeof(ops_second_char)/sizeof(ops_second_char[0]))){	
				type="op"; 
				if (c == '/') {next_simvol(); if (c == '/'){
					while(1){	
						if (c == '%' || c=='\n') {break;}
								next_simvol();
				}
					type="coment";
					tips=type;
					}
				else if  (c == '=') {next_simvol();}
				}
				else
				if (c == '.') {
					next_simvol(); if (c == '.') {type="sep"; next_simvol();  } else type="op"; }
				else
			   { next_simvol();
				if (c=='=')  {next_simvol();}}		
			}
		}		
			else if (c == '{') { 
			while(c!='}'){
			next_simvol();
			probel_sim();
			}
			old_col = col;
			next_simvol();
			type="coment";
		}
			else if (c == '#'){
			next_simvol();
			if (c == '$' || (c >= 'a' && c <= 'f' ) || (c >= 'A' && c <= 'F') || isdigit(c)){
				next_simvol();
					while((c >= 'a' && c <= 'f' ) || (c >= 'A' && c <= 'F') || isdigit(c)){
						next_simvol();
					}
			
			}	type="char";
			}
		
			if (c =='\'') {next_simvol();
			type = "string";
			while(c != '\'') {
				next_simvol();
			
			}	
				next_simvol();
			if (lexsem == "''" && c == '\'') {next_simvol(); next_simvol();  next_simvol();  type="char";
			ValToken<char> *tokenVal = new ValToken<char>(row, old_col, "char", lexsem, '\''); 
			return tokenVal; }
			}
			else if (c == '`') { next_simvol; eror="BadChar";	
			old_col=col;
			throw new Errors(row, old_col, eror);
			}
			if (type == "integer" ){ 
				int a;
				a = atoi(lexsem.c_str());
				ValToken<int> *tokenVal= new ValToken <int>(row, old_col, type, lexsem, a); old_col=col;
				tips=type;
				return tokenVal;
			}

			if (type == "string" ){ 
				string s;
				int k;
				s= lexsem.substr(1, lexsem.size()-2); 
				k=s.length();
				if (k==1) {type="char";}
				else {type="string";}
				 ValToken<string> *tokenVal= new ValToken <string>(row, old_col, type, lexsem, s); old_col=col;tips=type;
				return tokenVal;
				
			}
			if (type == "real" ){ 
				double a;
				a = atof(lexsem.c_str());
				ValToken<double> *tokenVal= new ValToken <double>(row, old_col, type, lexsem, a); old_col=col;
				tips=type;
				return tokenVal;
			}
			if (type == "hex" ){ 
				string s;
				s=lexsem.substr (1); 
				long long int res = std::stoll(s, 0, 16);
				ValToken<int> *tokenVal= new ValToken <int>(row, old_col, type, lexsem, res); old_col=col;
				tips=type;
				return tokenVal;
			}

			if (type == "char") 
				{ 
				string s; 
				int a; 
				char d; 
				if (lexsem == "#") {
						eror="NoCC";	
				throw new Errors(row, col, eror);
				}
				if (lexsem[0] == '#' && lexsem[1] == '$'){
				s = lexsem.substr(2); 
				a = strtol (s.c_str(), NULL, 16); }
				else {
				s = lexsem.substr(1); 
				a = atoi(s.c_str()); }
				d = (char)a; 
				if (d!=0 && d<127){
				ValToken<char> *tokenVal = new ValToken<char>(row, old_col, "char", lexsem, d); 
				tips=type;
				return tokenVal; }
				else { 	eror="BadCC";	

				throw new Errors(row, col, eror);}
				} 
		if (type=="ident" && ident_type[lexsem] == KEYWORDS)
				{ type="keyword"; }
		if (type=="ident" && ident_type[lexsem]== OP)
				{ type="op";}
		Token *t = new Token(row, old_col, type, lexsem);
		old_col=col;
		tips=type;
		return t;
	}

int main()
{   
 	setlocale(LC_ALL,"Rus");
	initmap();
	fin >> noskipws;	
	next_simvol();
	 Token *cur;
	   try {
        while (cur = get_token()) {
				if (tips!="coment" && tips!="per" && tips!=""){
            cur->print();
				}
            delete cur;
        }
    }catch ( Errors *e) { e->print(); return 0;}
	fin.close();	
	fout.close();	
}