#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "utils.h"
#include "lexer.h"
#include "vector.h"
#include "map.h"
#include "token.h"
#include "reader.h"
#include "parser.h"
#include "preprocessor.h"
#include "ast.h"

extern char current_file[MAX_FILE_NAME_LENGTH];
extern int current_line;

/* helper function for deleting tokens inside vector and map */
void hlp_delete_token(void *t) {
    token_delete( (token*) t );
}

void compile(char *input_file_name) {
    strcpy(current_file, input_file_name);
    current_line = 1;
    buffered_reader *file_reader = br_open_file(input_file_name);

    /* lexical tokens */
    vector *tokens = vector_new(START_STRUCTURES_SIZE);
    map *words = map_new(START_STRUCTURES_SIZE);
    printf(">>> Tokens ===========================\n");
    lexer(file_reader, tokens, words);
    printf("\n");

    preprocess(tokens);

    stmt *ast = parse_topdown(tokens);
    //parse_bottomup(tokens);

    stmt_delete(ast);
    vector_delete(tokens, hlp_delete_token);
    map_delete(words, hlp_delete_token);
    br_close_file(file_reader);
}

int main(int argc, char *argv[]) {
    printf("Arguments: \n");
    for (int i=0; i<argc; i++) {
        printf("  %d: %s\n", i, argv[i]);
    }
    if (argc > 1) {
        compile(argv[1]);
    } else {
        InputError("No input files.", "");
    }
    return EXIT_SUCCESS;
}
