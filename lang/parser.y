%{
    /*
    WLang - A Simple Programming Languge
    Copyright (C) 2025  Wdboyes13

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
    */
    
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    FILE* outfile;

    typedef struct {
        char* name; 
        float value;
    } Variable;

    #define MAX_VARS 100
    Variable symtable[MAX_VARS];
    int var_count = 0;

    int find_var(const char* name){
        for (int i = 0; i < var_count; i++ ) {
            if (strcmp(symtable[i].name, name) == 0){
                return i;
            }
        }
        return -1;
    }

    void set_var(const char* name, float val){
        int idx = find_var(name);
        if (idx == -1){
            if (var_count == MAX_VARS){
                fprintf(stderr, "Too many variables\n");
                exit(1);
            }
            symtable[var_count].name = strdup(name);
            symtable[var_count].value = val;
            var_count++;
        } else {
            symtable[idx].value = val;
        }
    }

    float get_var(const char* name){
        int idx = find_var(name);
        if (idx == -1){
            fprintf(stderr, "Error: variable '%s' not defined\n", name);
            exit(1);
        }
        return symtable[idx].value;
    }
    int yylex(void);
    void yyerror(const char* s) { fprintf(stderr, "Error: %s\n", s); }
%}

%union {
    float num;
    char* id;
    char* str;
}

%token <str> STRING
%token PRINT;
%token CLEAR;
%token EXIT;
%token <id> IDENTIFIER
%token <num> NUMBER
%token SEMICOLON
%type <num> expression


%%

program:
    /* empty */
    | program statement
    ;

statement:
    PRINT expression SEMICOLON          { 
        // printf("Result %d\n", $2); 
        fprintf(outfile, "PRINT %f\n", $2);
    }
  | IDENTIFIER '=' expression SEMICOLON   { 
        set_var($1, $3); 
        fprintf(outfile, "SET %s %f\n", $1, $3);
        free($1); 
    }
  | EXIT SEMICOLON { 
        fprintf(outfile, "EXIT\n");
        exit(0); 
    }
  | CLEAR SEMICOLON { 
        // printf("\033[2J\033[H");
        fprintf(outfile, "CLEAR\n");
    }
  | PRINT STRING SEMICOLON {
        $2[strlen($2) - 1] = 0;       // remove ending quote
        fprintf(outfile, "PRINT_STR %s\n", $2 + 1); // skip opening quote
        free($2);
    }
  ;

expression:
      NUMBER               { $$ = $1; }
    | IDENTIFIER           { $$ = get_var($1); free($1); }
    | expression '+' expression { $$ = $1 + $3; }
    | expression '-' expression { $$ = $1 - $3; }
    | expression '*' expression { $$ = $1 * $3; }
    | expression '/' expression { 
          if ($3 == 0) {
              fprintf(stderr, "Error: division by zero\n");
              exit(1);
          }
          $$ = $1 / $3; 
      }
    | '(' expression ')'    { $$ = $2; }
    ;

%%

int main(int argc, char** argv){
    if (argc > 1){

        outfile = fopen(argv[1], "w");
        if (!outfile) {
            perror("fopen");
            return 1;
        }
        printf("Generating IR\n");
        yyparse();
        fclose(outfile);
        return 0;
    } else {
        fprintf(stderr, "Missing Arguement\n");
    }
}