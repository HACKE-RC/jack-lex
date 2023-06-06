#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>
#include <cctype>
#include <filesystem>
#include "../pugixml/pugixml.hpp"

typedef std::vector<std::string> CODE;
typedef pugi::xml_node node;

class JackTokenizer{
private:
    CODE m_code;

    std::string m_outfName;
    std::string m_fName;

private:
    enum statusCodes{
        ERROR_FILE_NOT_FOUND = -1,
    };

    struct codeInfo{
        bool classDec = false;
        bool varDec = false;
        bool classVarDec = false;
        bool classDecBegin;
        bool varDecEnd = false;
        bool varDecBegin = false;
        bool subroutineDecBegin;
        bool subroutineDec = false;
        bool codeSwitch = false;
    } codeInfo;

    CODE validKeywords = {"if", "while", "class", "constructor", "function", "method", "field", "static", "var", "int",
                          "char", "boolean", "void", "true", "false", "this", "let", "do", "else", "return"};
    CODE validSymbols = {"{", "}", "(", ")", "[", "]", ".",  ",",  ";",  "+", "-", "*", "/", "&", "|", "<", ">", "=", "~"};
    CODE validVarDecs = {"static", "field", "var"};
    CODE validSubroutineDec = {"function", "method", "constructor"};


public:
   explicit JackTokenizer(std::string fName, std::string outfName);

public:
    void printCode();
    void cleanCode();

public:
    void tokenizeCode();
    static void splitComma(std::string& str, CODE& vec);
    static std::string addBrackets(std::string item, CODE &vec);
    static int addSemicolon(std::string& item, CODE &vec);
    static int addCurlyBrackets(std::string& item, CODE &vec);

private:
    static void to_lower(std::string &str);
    static bool isValid(CODE const& vec, std::string& str);
    static bool isNotEmpty(std::string& str);
    static CODE splitString(std::string str, char deli);
};