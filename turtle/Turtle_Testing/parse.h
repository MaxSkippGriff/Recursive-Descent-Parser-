#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include "sput.h"




/*------------------- DEFINITIONS----------------------- */


/* Correct number of inputs required in command line */
#define CORRECT_INPUT 2

/* Value used for clearing screen */
#define CLEAR 0

/* Checks whether file scanned correctly. */
#define SCAN 1

/* Max number of tokens */
#define LIMIT 100

/* Max length of each token */
#define MAX_LEN 20

/* Error message based on Dr Neill Carpenter's */
#define ERROR(PHRASE) fprintf(stderr, \
  "Fatal Error '%s' occurred in %s, line %d\n", \
  PHRASE, __FILE__, __LINE__ ); exit(2)

/* ASCII code for uppercase A */
#define A 65

/* ASCII code for uppercase Z */
#define Z 90

/* Array size */
#define SIZE 256

/* Array size for test array */
#define TEST_SIZE 256




/*----------------------STRUCTURES------------------------*/

/*
   Structure contains the program line, current
   instruction and number of instructions .
*/
typedef struct parser {
  char prog_line[LIMIT][MAX_LEN];
  int current;
  int num;
} parser;


/*
   Structure contains the elements of the stack.
*/
typedef struct stack_elem {
  char i;
  struct stack_elem *prev;
} stack_elem;


/*
   Structure contains the elements of the stack including
   the top pointer ('tp') and a stack counter.
*/
typedef struct polish_stack {
  stack_elem *tp;
  int counter;
} polish_stack;




typedef struct test_array {
  char* test_arr[TEST_SIZE];
  int test_count;
} test_array;



typedef enum bool {false, true} bool;




/*---------------------FUNCTIONS--------------------------*/


/*
   Initial functions to setup parser
  -----------------------------------
*/


bool check_inputs(int argc);


bool clear_the_screen(int clear);


bool initialise_stack(polish_stack *s);


void check_file(parser *prog, polish_stack *s, char *f);


bool check_and_start(parser *p, polish_stack *s);


bool string_same(char *str1, char *str2);


bool push_on_stack(polish_stack *s, char *c);


/*
   Main functions for Parser
  ----------------------------
*/

void process_instruct_list(parser *p, polish_stack *s);


char pop_off_stack(polish_stack *s);


bool process_instruction(parser *p, polish_stack *s);


bool check_FD(parser *p);


bool check_LT_RT(parser *p);


bool check_DO(parser *p, polish_stack *s);


bool check_varnum(parser *p);


bool check_var(parser *p);


bool check_SET(parser *p, polish_stack *s);


bool check_polish(parser *p, polish_stack *s);


bool check_op(parser *p);


void free_stack(polish_stack *s);





/*
    Unit testing functions
   ------------------------
*/

int unit_tests();


void test_check_inputs(void);


void test_clear_the_screen(void);


void test_check_file(void);


void test_check_file_2(void);


void test_check_start(void);


void test_same_string(void);


void test_instrctlist(void);


void test_instrctlist_check(parser *prog, polish_stack *s);


void test_instruction(void);


void test_fd(void);


bool test_fd_check(parser *prog, char* first, char* second);


void test_lt(void);


bool test_lt_check(parser *prog, char* first, char* second);


void test_rt(void);


bool test_rt_check(parser *prog, char* first, char* second);


void test_do_loop(void);


bool test_do_check(parser *prog, polish_stack *s, test_array *test);


void test_set(void);


bool test_set_check(parser *prog, polish_stack *s, test_array *test);


void test_varnum(void);


bool test_varnum_check(parser *prog, test_array *test);


void test_var(void);


bool test_var_check(parser *prog, test_array *test);


void test_polish(void);


bool test_polish_check(parser *prog, polish_stack *s, test_array *test);


void test_op(void);


bool test_op_check(parser *prog, char *test);


void test_init_stack(void);


void test_push_stack(void);


void test_pop_stack(void);


void test_free_stack(void);
