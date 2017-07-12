%{
  // C++ headers

  #include <iostream>
  using namespace std;
  #define YY_DECL extern "C" int yylex()
%}

%%

[0-9]+          { cout << "Found an integer:" << yytext << endl; }

%%

int main() {
    yylex();
    return 0;
}