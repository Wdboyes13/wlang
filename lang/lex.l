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
#include "parser.tab.h"
%}

%%

"clear"                   { return CLEAR; }
"exit"                    { return EXIT; }
"print"                   { return PRINT; }
[0-9.]+                    { yylval.num = atof(yytext); return NUMBER; }
[a-zA-Z_][a-zA-Z0-9_]*    { yylval.id = strdup(yytext); return IDENTIFIER; }

[ \t\r\n]+                { /* skip whitespace */ }
";"                       { return SEMICOLON; }
"="                       { return '='; }
"+"                       { return '+'; }
"-"                       { return '-'; }
"*"                       { return '*'; }
"/"                       { return '/'; }

\"([^\\\"]|\\.)*\" {
    yylval.str = strdup(yytext); // Save the raw string including quotes
    return STRING;
}

.               { return *yytext; }

%%