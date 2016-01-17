#include <map>

using namespace std;

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
