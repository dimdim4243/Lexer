#pragma once
#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <cctype>

using namespace std;

ofstream fout("output.txt");
#include "Token.h"


ifstream fin("input.txt");
char ops_second_char[] = {'/','+','*',' :','-','>', '^', '<', '@', '.', '='};
char sep[] = {';' ,',','(','[',')',']',};
char ops[] = {'>','<','/','+','*',':','-','^','=','@',';',',','(','[',')',']','.'};
string lexsem=("");
string tips="";
int col=0, row=1;
char c = 0;
int old_col=1, old_row=row;
	
Token *tokenbuf=NULL;

class Lexser
{
private:
	Token*  parsinteger(int row, int old_col, string type, string lexsem);
	Token*  parsstring(int row, int old_col, string type, string lexsem);
	Token *parsreal(int row, int old_col, string type, string lexsem);
	Token *parshex(int row, int old_col, string type, string lexsem);
	Token *parschar(int row, int old_col, string type, string lexsem);
	Token *parscharhex(int row, int old_col, string type, string lexsem);
	Token *buf(int row, int old_col, string type, string lexsem);
	Token *sepreal(int row, int old_col, string type, string lexsem);
	void ReplaceAll(string *str, string from, string to);
	void next_simvol();
	void probel_sim();
	bool in_mas(char s, char *mas, int len);
	bool ishex(char c);
	string lexsem;
	string tips;
public:
	Lexser(void);
	~Lexser(void);
	Token *get_token();
};

