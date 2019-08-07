#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define LINE_COUNT 256

int edit_distance(char * word1, int len1, char* word2, int len2){
    int matrix[len1 + 1][len2 + 1];
    int i;
    for (i = 0; i <= len1; i++) {
        matrix[i][0] = i;
    }
    for (i = 0; i <= len2; i++) {
        matrix[0][i] = i;
    }
    for (i = 1; i <= len1; i++) {
        int j;
        char c1;

        c1 = word1[i-1];
        for (j = 1; j <= len2; j++) {
            char c2;

            c2 = word2[j-1];
            if (c1 == c2) {
                matrix[i][j] = matrix[i-1][j-1];
            }
            else {
                int delete;
                int insert;
                int substitute;
                int minimum;

                delete = matrix[i-1][j] + 1;
                insert = matrix[i][j-1] + 1;
                substitute = matrix[i-1][j-1] + 1;
                minimum = delete;
                if (insert < minimum) {
                    minimum = insert;
                }
                if (substitute < minimum) {
                    minimum = substitute;
                }
                matrix[i][j] = minimum;
            }
        }
    }
    return matrix[len1][len2];
}

int main(int argc, char* argv[]){
    
    char filename[256];
    FILE* fp;

    /* RELATED TO SINGLE LINE */
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    
    /* RELATED TO ALL LINES */
    char** all_lines;
    int* all_line_lens;
    int end = 0;
    
    /* READ COMMAND-LINE ARGUMENTS */
    if(argc != 2){
        printf("usage: edit_dist FILE\n");        
    }else{
        strncpy(filename, argv[1], 256);
        printf("FILE: %s\n", filename);
    }
    
    /* CHECK THAT FILE EXISTS */
    if(access(filename, F_OK) == -1){
        printf("File %s does not exist\n", filename);
        return 1;
    }
    
    /* OPEN FILE */
    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("File could not be read.\n");        
        return 1;        
    }
    
    all_lines = malloc(LINE_COUNT*sizeof(char*));
    all_line_lens = malloc(LINE_COUNT*sizeof(int));
    while( (read = getdelim(&line, &len, (int)'\n', fp)) != -1 ){
        printf("%s", line);
        if(end >= LINE_COUNT){
            printf("Line capacity reached or exceeded.\n");
            fclose(fp);
            free(all_lines);
            free(all_line_lens);
            return 1;
        }
        /* STORE POINTER TO CURRENT LINE */
        all_lines[end] = line;
        all_line_lens[end] = len;
        end++;        
    }
    
    /* 
        At this point in the execution, the all_lines variables shold contain
        all the lines of the input file. Now we want to compare every line
        in the all_lines array with all the other lines.
    */
    
    
    char* str1;
    int len1;
    char* str2;
    int len2;
    int** mat;
    
    mat = malloc(LINE_COUNT * sizeof(int*))
    
    for(int i = 0; i < end; i++){
        for(int j = 0; j < i; j++){
            str1 = all_lines[i];
            str2 = all_lines[j];              
            len1 = all_line_lens[i];
            len2 = all_line_lens[i];                      
        }
    }   
    
    
    fclose(fp);
    return 0;
}
