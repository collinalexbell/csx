#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#include "lexer.h"
#include "parser.h"
#include "codegen.h"

#define MAX_PATH 1024

void process_file(const char* input_path, const char* output_dir);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_folder> <output_directory>\n", argv[0]);
        return 1;
    }

    const char* input_folder = argv[1];
    const char* output_dir = argv[2];

    // Create output directory if it doesn't exist
    struct stat st = {0};
    if (stat(output_dir, &st) == -1) {
        mkdir(output_dir, 0700);
    }

    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(input_folder)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_REG) { // If it's a regular file
                char input_path[MAX_PATH];
                snprintf(input_path, sizeof(input_path), "%s/%s", input_folder, ent->d_name);
                process_file(input_path, output_dir);
            }
        }
        closedir(dir);
    } else {
        perror("Could not open input directory");
        return 1;
    }

    return 0;
}

void process_file(const char* input_path, const char* output_dir) {
    // Here you would implement the actual processing of each file
    // This is just a placeholder implementation
    printf("Processing file: %s\n", input_path);

    // 1. Lexical analysis
    // token_stream = lex_file(input_path);

    // 2. Parsing
    // ast = parse(token_stream);

    // 3. Code generation
    // generate_code(ast, output_dir);

    printf("Processed file: %s\n", input_path);
}
