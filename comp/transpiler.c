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
#define MAX_VARS 100

typedef struct {
    char* name; 
    char* value;
} Variable;

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

void set_var(const char* name, char* val, FILE* file){
    int idx = find_var(name);
    if (idx == -1){
        if (var_count == MAX_VARS){
            fprintf(stderr, "Too many variables\n");
            exit(1);
        }
        symtable[var_count].name = strdup(name);
        symtable[var_count].value = val;
        fprintf(file, "float %s = %s;", name, val);
        var_count++;
    } else {
        fprintf(file, "%s = %s;", name, val);
        symtable[idx].value = val;
    }
}

void trim(char* str) {
    // Removes trailing newline
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') str[len - 1] = '\0';
}

int main(int argc, char** argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s input.wir output.c\n", argv[0]);
        return 1;
    }

    FILE* in = fopen(argv[1], "r");
    if (!in) {
        perror("Error opening input");
        return 1;
    }

    FILE* out = fopen(argv[2], "w");
    if (!out) {
        perror("Error opening output");
        fclose(in);
        return 1;
    }

    fprintf(out, "#include <stdio.h>\n\nint main() {\n");

    char line[128];
    while (fgets(line, sizeof(line), in)) {
        trim(line);

        char cmd[16], arg1[32], arg2[32];
        int matched = sscanf(line, "%15s %31s %31s", cmd, arg1, arg2);

        if (matched == 3 && strcmp(cmd, "SET") == 0) {
            set_var(arg1, arg2, out);
        } else if (matched == 2 && strcmp(cmd, "PRINT") == 0) {
            fprintf(out, "    printf(\"%%f\\n\", %s);\n", arg1);
        } else if (matched == 1 && strcmp(cmd, "CLEAR") == 0){
            fprintf(out, "    printf(\"\\033[2J\\033[H\");");
        } else if (matched == 1 && strcmp(cmd, "EXIT") == 0) {
            fprintf(out, "    return 0;\n");
        } else if (matched == 2 && strcmp(cmd, "PRINT_STR") == 0){
            fprintf(out, "    printf(\"%s\\n\");\n", arg1);
        } else {
            fprintf(stderr, "Unknown or invalid instruction: %s\n", line);
        } 
    }

    fprintf(out, "}\n");

    fclose(in);
    fclose(out);

    printf("Transpiled to %s\n", argv[2]);
    return 0;
}