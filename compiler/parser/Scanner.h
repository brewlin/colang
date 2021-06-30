
#ifndef CO_LANG_PARSER_SCANNER_H
#define CO_LANG_PARSER_SCANNER_H
/**
 *@ClassName ParserToken
 *@Author brewlin
 *@Date 2021/6/29 0019 上午 11:05
 *@Version 1.0
 **/

#include "Block.h"
#include <tuple>
#include "Log.h"
#include "Ast.h"
#include "Utils.h"
#include <fstream>
#include <sstream>
#include <memory>
#include <unordered_map>

using namespace std;

struct Scanner 
{
    Scanner(const string filepath);
    ~Scanner();

	ifstream     fs;
	stringstream buffer;
	int 		 pos;

	Token	     prevToken;
	string	     prevLex;
	Token		 curToken;
	string	     curLex;
    //记录当前词法分析行|列
    int line = 1;
    int column = 0;
public:
    Token     token()const;
    string    value()const;
    Token     scan();
    char      next();
    char      peek();
	void  	  print();

	string    consumeLine(); 			
	short precedence(Token op);

private:
	tuple<Token,string> get_next();
	tuple<Token,string> parseNumber(char first);
	tuple<Token,string> parseKeyword(char c);
	tuple<Token,string> parseMulOrDelref(char c);
};

extern unordered_map<string,Token > keywords;

#endif //CO_LANG_PARSER_H