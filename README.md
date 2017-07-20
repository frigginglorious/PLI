# Programming Language Implementations
Parsing with Bison

## What is Bison?
Bison is a parser generator that can output a variety of parser types. In our case, we're going to be generating an LALR1 parser. This simply means it parses a file from the Top-down and from Left-to-Right with the ability to look ahead for tokens. When we hook Flex and Bison together, we get end up with a Lexical Analyzer and a Syntax Analyzer. As opposed to simply finding tokens and associating a value with the found token; Bison will try to make sense of what these tokens mean in our language. After which, we can construct our Abstract Syntax Tree (AST) and compile or interpret the nodes. 

## Installing Bison
This repository includes Bison v3.0.4 in the `util` directory. Most Linux and MacOSX distributions already include Bison by default. Newer and older versions of Bison may not be compatible with this tutorial. 

1. In order to install the version of Bison included in this repository, navigate to the `util` directory.

2. The Bison package is compressed using a gunzip and tarball compressor, use any standard tarball archive utility or run the following command

```bash
cd util/
tar xvzf file.tar.gz
```

The `x` flag tells the archive utility to extract the files.

`v` means "verbose", which will list all of the files one-by-one.

`z` The z option is very important and tells the tar command to uncompress the file (gzip).

`f` tells the archive utility that we're going to supply the file to extract.

3. Navigate to the Flex directory and run the configure command. This will ensure all dependencies are available in order to install Flex.

```bash
cd bison-3.0.4
./configure
```

Note:

You may have to resolve any dependencies that are not installed on your system. A quick google search of the error and your operating system will generally give you a good idea on how to install the missing dependency. If you are unable to resolve the issue, send me an issue on Github.


4. Build Bison
In order to build Bison, and to continue through this series, we need a tool called `Make`. You can read more about it and install it [here](https://www.gnu.org/software/make/). Most Linux and MacOSX distributions already come with make installed. You can test this by running ` make -v`.

If you're using Windows, you'll have to utilize `nmake`. You can read more about name [here](https://msdn.microsoft.com/en-us/library/dd9y37ha.aspx).

5. (Optional) Installing Bison
After running the make command, an executable called `bison` will be present. If you don't want to overwrite your systems installed version and header files; you can simply type in the path to this executable when running the `flex` command. IE `./util/bison-3.0.4/src/bison someFileName`. In the future we will also have to include some header files if you choose not to install this version of bison on your system.

To install Bison, run the following command:

```bash
make install
```

This will move the Bison executable and headers to their final destination.

## Backus Naur Form (BNF)
Bison utilizes a grammar syntax called BNF. BNF is an acronym for "Backus Naur Form". John Backus and Peter Naur introduced for the first time a formal notation to describe the syntax of a given language.

The meta-symbols of BNF are:
- ::= (is defined as)
- | (or)
- < > (categories)

For example, the BNF production for a mini-language is:

```bnf
<program> ::=  program
                   <declaration_sequence>
               begin
                   <statements_sequence>
               end ;
```

This shows that a mini-language program consists of the keyword "program" followed by the declaration sequence, then the keyword "begin" and the statements sequence, finally the keyword "end" and a semicolon.

- optional items are enclosed in meta symbols [ and ], example:
```bnf
<if_statement> ::=  if <boolean_expression> then
                         <statement_sequence>
                    [ else
                         <statement_sequence> ]
                    end if ;
```

- repetitive items (zero or more times) are enclosed in meta symbols { and }, example:
```bnf
<identifier> ::= <letter> { <letter> | <digit> }
```

- this rule is equivalent to the recursive rule:
```bnf
<identifier> ::= <letter> |
                 <identifier> [ <letter> | <digit> ]
```

- terminals of only one character are surrounded by quotes (") to distinguish them from meta-symbols, example:
```bnf
<statement_sequence> ::= <statement> { ";" <statement> }
```


## Generating a C++ Parser with Bison
The first step to generating a parser with bison, is to create a file. We'll name this file `parser.yy`. YY is a common extension used to describe yacc grammars (a parser generator for C).

```bash
touch parser.yy
```

### Bison Configuration
Bison is a parser generator, not a parser itself. In order to generate a parser, we set specified configurations, include various headers and code, and define our language syntax using a subset of BNF.

On the top of our file, we're going to add a few configurations:

```C++

// file: parser.yy

%skeleton "lalr1.cc"
%require  "3.0"
%debug 
%defines 
%define api.namespace {Frontend}
%define parser_class_name {Parser}

```

- `%skeleton "lalr1.cc"` declares that we're going to use the lalr1 skeleton file. This is a "Look-Ahead Left-to-Right parser."
- `%require  "3.0"` specifies the version of bison we want to use
- `%debug` allows debugging information
- `%defines` generates a parser header file to include in our scanner
- `%define api.namespace {Frontend}` the namespace our parser class will be in
- `%define parser_class_name {Parser}` the classname that will be generated


### Forward Declarations and Macros
When we want to define forward declarations and macros, we define a `%code requires{ }` section. In order for Bison to parse tokens, a scanner must be declared and passed in to the constructor. This can be a custom parser implemented by us, or the scanner generated by Flex. We'll be generating the C++ Scanner in Flex in the next tutorial. For now we'll simply define it as `Frontend::Scanner`.

```C++
// file: parser.yy

%skeleton "lalr1.cc"
%require  "3.0"
%debug 
%defines 
%define api.namespace {Frontend}
%define parser_class_name {Parser}

%code requires {
  namespace Frontend {
    class Scanner;
  }
}

```

The next step is to define the parameters that will be passed to our Parsers constructor. This is defined with the `%parse-param` directive. We'll be passing in the scanner class.

```C++
// file: parser.yy

%skeleton "lalr1.cc"
%require  "3.0"
%debug 
%defines 
%define api.namespace {Frontend}
%define parser_class_name {Parser}

%code requires {
  namespace Frontend {
    class Scanner;
  }
}

%parse-param { Frontend::Scanner &scanner }

```

### Including C++ code and Headers
Any code we want executed, headers included, or additional macros can be defined in a `%code{ }` section. Because we're not going to be utilizing C and, instead, are defining a Scanner class, we need to point the `yylex` function to a Scanner method. We'll call this function `yylex`.

 ```C++
// file: parser.yy

%skeleton "lalr1.cc"
%require  "3.0"
%debug 
%defines 
%define api.namespace {Frontend}
%define parser_class_name {Parser}

%code requires {
  namespace Frontend {
    class Scanner;
  }
}

%parse-param { Frontend::Scanner &scanner }

%code {

#undef yylex
#define yylex scanner.yylex

}

```

### Token Data Types
When we utilize our Scanner, we scan for `tokens`. Tokens can have values tied to them or just represent a structure in the syntax of our language. For example, when we parse a integer, we would create an INTEGER token with an integer value. Same case would go for strings, characters, or any other data types we would want in our language. We can create this with a `%union` declaration, or a `value.type` of variant like so:

```C++
// file: parser.yy

%skeleton "lalr1.cc"
%require  "3.0"
%debug 
%defines 
%define api.namespace {Frontend}
%define parser_class_name {Parser}

%code requires {
  namespace Frontend {
    class Scanner;
  }
}

%parse-param { Frontend::Scanner &scanner }

%code {

#undef yylex
#define yylex scanner.yylex

}

%define api.value.type variant

```

There are many other Bison symbols and directives to configure, you can read more (here)[http://www.gnu.org/software/bison/manual/html_node/Table-of-Symbols.html]. The only other directives to include in this section are: `%define parse.assert` and `%locations`.

- `%define parse.assert` Issues runtime assertions to catch invalid uses with variant datatypes.
- `%locations` Tracks the current location of the token and line number. Utilizing when handling errors.

Adding these two directives, we end up with

```C++
// file: parser.yy

%skeleton "lalr1.cc"
%require  "3.0"
%debug 
%defines 
%define api.namespace {Frontend}
%define parser_class_name {Parser}

%code requires {
  namespace Frontend {
    class Scanner;
  }
}

%parse-param { Frontend::Scanner &scanner }

%code {

#undef yylex
#define yylex scanner.yylex

}

%define api.value.type variant
%define parse.assert

```

### Tokens
Since Flex and Bison can be dependencies on one another, we can define tokens that can be utilized by both our Flex Scanner and Bison Parser. The syntax for tokens is defined by the `%token` directive. For example, if we want a STRING token to contain the value of a string, it would be defined like so:

```C++
%token <std::string> STRING
```

Anything between `< datatype >` specifies the type that variant will utilize when a string token is parsed by the scanner. If no value is going to be associated with the token, we define the token simply as `%token MYTOKEN`.

We're going to add four tokens: WORD, NEWLINE, CHAR, and END. These tokens will be utilized to count how many lines, words, and characters a file has. The END token will represent the end of file (EOF) token.

```C++
// file: parser.yy

%skeleton "lalr1.cc"
%require  "3.0"
%debug 
%defines 
%define api.namespace {Frontend}
%define parser_class_name {Parser}

%code requires {
  namespace Frontend {
    class Scanner;
  }
}

%parse-param { Frontend::Scanner &scanner }

%code {

#undef yylex
#define yylex scanner.yylex

}

%define api.value.type variant
%define parse.assert

%token <std::string> WORD
%token               NEWLINE
%token               CHAR
%token               END    0     "end of file"

```

## BNF Grammer
The last two sections on generating our parser consists of defining our languages "grammar" and any methods we'd like to add or override in our parser object. Like Flex, we define our grammar in-between opening and closing `%%`.

The BNF grammar Bison uses to describe how it parses tokens is a subset of what we described earlier in this tutorial. It's not exactly the same, but similar. Bison follows a general syntax of:

```C++
sequence:
  TOKEN or sequence   { optional C++ code }
  | TOKEN             { optional C++ code }
  ;
  
```

We're going to be parsing words, characters, and how many lines a file has. An example file:

```
This is a test
Really
```

Has two lines, 5 words, and 17 characters (excluding special characters and spaces). In BNF, we have describe what a file might contain when defining our sequences. So what can our file have that would be valid for our parser?

- It could be empty (containing only END/EOF token)
- It can consist of only 1 word (with X amount of characters)
- Or it can be a sequence of items

We have a few options for our list of items, in which these terms "options", "list", and "items" accurately describe our syntax sequences.

The first rule we would want to write is that we have the options of either an empty file, or have a list items.

```C++
// file: parser.yy

%skeleton "lalr1.cc"
%require  "3.0"
%debug 
%defines 
%define api.namespace {Frontend}
%define parser_class_name {Parser}

%code requires {
  namespace Frontend {
    class Scanner;
  }
}

%parse-param { Frontend::Scanner &scanner }

%code {

#undef yylex
#define yylex scanner.yylex

}

%define api.value.type variant
%define parse.assert

%token <std::string> WORD
%token               NEWLINE
%token               CHAR
%token               END    0     "end of file"

%%

list_option : END | list END;

%%

```

We've defined that our program enters its syntax rules through `list_option`, of which the file can have the EOF (END) token or a squence defined "list" that ends with the EOF/END token. We'll define the list sequence next.

```C++
// file: parser.yy

%skeleton "lalr1.cc"
%require  "3.0"
%debug 
%defines 
%define api.namespace {Frontend}
%define parser_class_name {Parser}

%code requires {
  namespace Frontend {
    class Scanner;
  }
}

%parse-param { Frontend::Scanner &scanner }

%code {

#undef yylex
#define yylex scanner.yylex

}

%define api.value.type variant
%define parse.assert

%token <std::string> WORD
%token               NEWLINE
%token               CHAR
%token               END    0     "end of file"

%%

list_option : END | list END;

list
  : item
  | list item
  ;

%%

```

This is where things get a little tricky. A list can consist of one item, or many items. We created the sequence rule "item" that yet has to be defined, this will contain rules of when a character, newline, or word is parsed. In order to state that a list can contain one or multiple items: we recursively reference the parent sequence, `list`, followed by a specific token (`item`).

Our last BNF definition is for parsing words, characters, and lines.

```C++
// file: parser.yy

%skeleton "lalr1.cc"
%require  "3.0"
%debug 
%defines 
%define api.namespace {Frontend}
%define parser_class_name {Parser}

%code requires {
  namespace Frontend {
    class Scanner;
  }
}

%parse-param { Frontend::Scanner &scanner }

%code {

#undef yylex
#define yylex scanner.yylex

}

%define api.value.type variant
%define parse.assert

%token <std::string> WORD
%token               NEWLINE
%token               CHAR
%token               END    0     "end of file"

%%

list_option : END | list END;

list
  : item
  | list item
  ;

item
  : WORD    { /* do nothing yet in c++ */ }
  | NEWLINE { /* do nothing yet in c++ */  }
  | CHAR    { /* do nothing yet in c++ */  }
  ;

%%

```

Our item grammar consists of only our tokens we've created for our parser and scanner to utilize. An item can be a WORD or a NEWLINE or a CHAR. When these are parsed, we can execute some C++ code. Next tutorial we'll be generating a scanner for bison to utilize. After which we'll then join the two objects to create our word, line, and character counting program.

## Adding and Overriding Parser Methods
The last section in Bison is reserved for additional class configuration. These can be custom methods or overriding methods. Most of these methods are exposed when specific options are added, for example, we added the `%locations` directive; which allows some debugging information to be send to the Parser error method. For now we're just going to add an error message handler and states the error and which line it occured at.

```C++
void 
Frontend::Parser::error( const location_type &l, const std::string &err_message )
{
   std::cerr << "Error: " << err_message << " at " << l << "\n";
}
```

Currently we don't have very verbose syntax errors. If you want to enable them, add the directive `%define parse.error "verbose"` to the parser file. This will report the unexpected token, and possibly the expected ones. There's a few issues to look out for when utilizing verbose error messages. We'll look into those in the future.

## Generating a Bison Parser
To generate our bison parser, we run the following command (use the one in util/bison/src if you do not have it installed).

```bash
bison -d -v parser.yy
```

- `-d` means compile with "defines"
- `-v` means "verbose", producing a verbose description of the grammar (parser.output).

Next tutorial we'll create a scanner Bison can utilize. Then we'll join the two classes together and compile our program.

## Copyrights
Benjamin J. Anderson - 2017