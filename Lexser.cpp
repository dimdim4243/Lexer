#include "Lexser.h"
#include <string>
Lexser::Lexser(void)
{
}
Lexser::~Lexser(void)
{
}

 bool in_mas(char s, char *mas, int len){
	 for(int i = 0; i < len; i++){
		if (s == mas[i]) return true;
	 }
	 return false;
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

 void next_simvol(){
	 lexsem+=c;
	 fin>>c;	
	 col++;	
		if (fin.eof()) {
			c = '%';}
 }

 void ReplaceAll(string *str, string from, string to)
{
    unsigned int start_pos = 0;
    while((start_pos = (*str).find(from, start_pos)) != std::string::npos) {
        (*str).replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

Token *parsinteger(int row, int old_col, string type, string lexsem){
	 int a;
     a = atoi(lexsem.c_str());
     ValToken<int> *tokenVal = new ValToken<int>(row, old_col, type, lexsem, a);
	 return tokenVal;	
}

Token *parsstring(int row, int old_col, string type, string lexsem){
	 string s;
	 int k;
	 s= lexsem.substr(1, lexsem.size()-2); 
	 k=s.length();
	 if (k==1) {type="char";}
	 else {type="string";}
	 ValToken<string> *tokenVal= new ValToken <string>(row, old_col, type, lexsem, s); old_col=col;tips=type;
	 return tokenVal;
}

Token *parsreal(int row, int old_col, string type, string lexsem){
	 double a;
	 a = atof(lexsem.c_str());
	 ValToken<double> *tokenVal= new ValToken <double>(row, old_col, type, lexsem, a); old_col=col;
	 tips=type;
	 return tokenVal;
}

Token *parshex(int row, int old_col, string type, string lexsem){
	 string s;
	 s=lexsem.substr (1); 
	 long long int res = std::stoll(s, 0, 16);
	 ValToken<int> *tokenVal= new ValToken <int>(row, old_col, type, lexsem, res); old_col=col;
	 tips=type;
	 return tokenVal;
}

Token *parschar(int row, int old_col, string type, string lexsem){
	 char d;
     d = lexsem[1];
      ValToken<char> *tokenVal = new  ValToken<char>(row, old_col, type, lexsem, d);
	 return tokenVal;
}

Token *parscharhex(int row, int old_col, string type, string lexsem){
	string s;
      int a;
      char d;
      type = "char";
      if (lexsem[1] == '$')
	  {
		 s = lexsem.substr(2, lexsem.size());
         a = strtol (s.c_str(), NULL, 16);
      } else 
	  {
         s = lexsem.substr(1, lexsem.size());
         a = atoi(s.c_str());
      }
       cout << a << endl;
       if (a > 127) throw new Errors(row, old_col,"BadCC");
       d = (char)a;
       ValToken<char> *tokenVal = new ValToken<char>(row, old_col, type, lexsem, d);
	 return tokenVal;
}

Token *buf(int row, int old_col, string type, string lexsem){
	Token *t = new Token(row, old_col, type, lexsem);
	t = tokenbuf;
	tips="sep";
	tokenbuf=NULL;
	return t;
}

Token *sepreal(int row, int old_col, string type, string lexsem){
	string s;
	double a;
	s= lexsem.substr(0, lexsem.size()-1); 
	cout<<s;
	a = atoi(s.c_str());
	ValToken<int> *tokenVal= new ValToken <int>(row, old_col, "integer", s, a); old_col=col;
	tips=type;
	lexsem='.';
	next_simvol();
	type="sep";
	Token *q = new Token(row, old_col-1, type, lexsem);
	tips=type;
	tokenbuf=q;
	old_col=col;
	return tokenVal;
}

bool ishex(char c)
{
    return c >= '0' && c <= '9' || c >= 'a' && c <= 'f' || c >= 'A' && c <= 'F';
}

Token *Lexser::get_token(){		
	int k=0;
	if (k=0 ){
		next_simvol();
		k++;
	}
	string eror;
	lexsem="";
	string type = "";
	probel_sim();
	if (tokenbuf != 0) {
		return buf( row,  old_col,  type,  lexsem);
	}
	if (fin.eof()) return 0;
	if (isalpha(c) || c == '_') {
			type = "ident";		
			next_simvol();
			while(isalpha(c) || isdigit(c) || c == '_'){	
				next_simvol();	
			}
	}	
	else if (c == '$'){
			next_simvol();
			while(ishex(c)){
				next_simvol();
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
	else if (isdigit(c)){
			type=tips="integer";
			char g=c;
			next_simvol();
			if ( (isdigit(g) && c == 'e') || (isdigit(g) &&  c == 'E')){
				next_simvol(); next_simvol(); type="real";
			}
			while(isdigit(c) || c == '.'){
				if (c == '.') {
					type="real"; 
					next_simvol();
					if (c == 'e' || c == 'E') { 
					eror="NoFract";	
					throw new Errors(row, col, eror);
					}
					if (c == '%') {
						eror="NoFract";	
						throw new Errors(row, col, eror);
					}
				}				
				if (c == '.') {
					type="real"; 
					if (c == '.') {
				return sepreal(row,  old_col,  type,  lexsem);
					}
				}			
				next_simvol();	
				if (c == '.') {	type="real"; 	}
				if (c == 'e' || c == 'E') {
					next_simvol();  
					if ( c == '.') {eror="NoExp";	
						throw new Errors(row, col, eror);}
							if (c == '+' || c == '-') {next_simvol(); 
								if ((c>'9') || c == '%') {
									eror="NoExp";	
									throw new Errors(row, col, eror);}
							}				
								else if ((c<'1' && c>'9') || c == '%') {eror="NoExp";	
									throw new Errors(row, col, eror);}
				}
			}
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
			else {type="sep";}
		}
		else if (c == '<') { type="op";  next_simvol(); 
			if (c == '>' || c == '=') {next_simvol();}}
		else if (in_mas(c, ops_second_char, sizeof(ops_second_char)/sizeof(ops_second_char[0]))){	
			type="op"; 
				if (c == '/') {next_simvol(); 
					if (c == '/'){
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
					next_simvol(); 
					if (c == '.') {type="sep"; next_simvol();  } else type="op"; }
				else {
			    next_simvol();
					if (c=='=')  {next_simvol();}}		
		}
	}		
	else if (c == '{') { 
		while(c!='}'){
			next_simvol();
				if (c == '%') {
					eror="BadEOF";	
					throw new Errors(row, col-1, eror);
				}
			probel_sim();
		}
		old_col = col;
		next_simvol();
		type="coment";
	}
	else if (c == '#'){
		next_simvol();
		if (c == '$') {type="char#";}
		else {type="char";}
		if (c == '$' || ishex(c)){
			next_simvol();
			while(ishex(c)){
				next_simvol();
			}
		}	
	}
	else if (c == '\'')
    {
        int size = 0;
		next_simvol();
        while (1){
            if (c == '\n') throw new Errors(row, col,"BadNL");
            if (c == '%') throw new Errors(row, col,"BadEOF");
            else if (c == '\''){
                if (c == '\'') {
					lexsem += string(2, c);
                    size++;
                    next_simvol();
				}
                else
                {
                    lexsem += '\'';
                    string value = lexsem.substr(1, lexsem.size() - 2);
                    ReplaceAll(&value, "''", "'");
                    if (size == 1)
                        return new ValToken<char>(row, old_col, type, lexsem, lexsem[1]);
                    else
                        return new ValToken<string>(row, old_col, type, lexsem, value);
                }
            }
            else next_simvol(); size++;
        }
    }
			
	if (type == "integer" ){ 
		return parsinteger( row, old_col, type, lexsem);
	}
	if (type == "string" ){ 
		return parsinteger( row, old_col, type, lexsem);
	}
	if (type == "real" ){ 
		return parsinteger( row, old_col, type, lexsem);
	}
	if (type == "hex" ){ 
		return parsinteger( row, old_col, type, lexsem);
	}
	if (type == "char") {
		return parschar( row, old_col, type, lexsem);
	} 
	if (type == "char#") { 
		return parscharhex( row, old_col, type, lexsem);
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

