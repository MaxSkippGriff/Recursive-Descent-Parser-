#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>



void start_pass(void);

void start_turtle(char password[100], char ref[100], char encrypt[100], char key[100], char decrypt[100]);

void save_password(void);

extern void key_generator(char *key, int n);

void cipher(char *input, char *output, char *key);

void open_password(char password[100], char ref[100], char encrypt[100], char key[100], char decrypt[100]);

void display_names(char password[100], char ref[100], char encrypt[100], char key[100], char decrypt[100]);

void delete_pass(void);
