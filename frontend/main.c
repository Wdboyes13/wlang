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
#include <unistd.h>
#include <sys/wait.h>
#include "config.h" // Generated at build time from top level Makefile

void run_command(const char *cmd, char *const argv[]) {
    pid_t pid = fork();
    if (pid == 0) {
        execvp(cmd, argv);
        perror("execvp");
        exit(1);
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
            fprintf(stderr, "Command failed: %s\n", argv[0]);
            exit(1);
        }
    } else {
        perror("fork");
        exit(1);
    }
}

void genir(char* input, char* output){
        pid_t pid = fork();
        if (pid == 0) {
            // Setup pipe: input file -> stdin
            FILE *f = fopen(input, "r");
            if (!f) {
                perror("fopen input");
                exit(1);
            }
            dup2(fileno(f), STDIN_FILENO);
            fclose(f);
            execl(IRGEN, "wlang-irgen", output, (char *)NULL);
            perror("execl IRGEN");
            exit(1);
        } else if (pid > 0) {
            int status;
            waitpid(pid, &status, 0);
            if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
                fprintf(stderr, "IRGEN failed\n");
                exit(1);
            }
        } else {
            perror("fork");
            exit(1);
        }
}

void genc(char* output)   {
        char *args[] = { TOC, "output.wir", output, NULL };
        run_command(args[0], args);
}

void comp(char* output){
        printf("Calling cc\n");
        char *args[] = { CC, "-o", output, "out.c", NULL };
        run_command(args[0], args);
}

int main(int argc, char *argv[]) {
    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        printf("Usage: %s [Input.wlang] [Output] [Options]\n", argv[0]);
        printf("Normal behavior: Generate IR, Transpile to C, Compile\n");
        printf("Options:\n");
        printf("  -h, --help     Show this help message\n");
        printf("  -c             Only IR Generation and Transpiling to C\n");
        printf("  -i             Only IR Generation\n");
        printf("  -v, --version  Show program info");
        return 0;
    }
    if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0) {
        printf("%s (WLang) - Version %s\n", argv[0], VER);
        printf("\nCopyright (C) 2025 Wdboyes13\n");
        printf("License GPLv3+: GNU GPL version 3 or later\n");
        printf("<https://www.gnu.org/licenses/gpl-3.0.html>\n");
        printf("This is free software: you are free to change and redistribute it.\n");
        printf("There is NO WARRANTY, to the extent permitted by law.\n");
        printf("\nWritten by Wdboyes13 <https://github.com/Wdboyes13>.\n");
        return 0;
    }
    if (argc < 3) {
        fprintf(stderr, "Missing Argument\n");
        fprintf(stderr, "Usage: %s [Input.wlang] [Output] [Options]\n", argv[0]);
        fprintf(stderr, "For help, run `%s -h`\n", argv[0]);
        return 1;
    }

    char *input = argv[1];
    char *output = argv[2];

    if (argv[3]) {
        if (strcmp(argv[3], "-c") == 0){
            genir(input, "output.wir");
            genc(output);
            remove("output.wir");
            return 0;
        }
        if (strcmp(argv[3], "-i") == 0){
            genir(input, output);
            return 0;
        } else {
            fprintf(stderr, "Unknown arguement: %s", argv[3]);
            return 1;
        }
    }

    // Step 1: cat input | wlang-irgen outir
    genir(input, "output.wir");
    // Step 2: wlang-toc output.wir out.c
    genc("out.c");
    // Step 3: cc -o [output] out.c
    comp(output);
    // Step 4: cleanup
    remove("output.wir");
    remove("out.c");
    printf("Done!\n");
    return 0;
}