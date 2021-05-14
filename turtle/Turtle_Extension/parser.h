#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>



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
  PHRASE, __FILE__, __LINE__ ); exit(1)

/* Contains value for ASCII uppercase A */
#define A 65

/* Contains value for ASCII uppercase Z */
#define Z 90

/* Array size */
#define SIZE 256




/*----------------------STRUCTURES------------------------*/

/*
   Structure contains the program line, current
   instruction and number of instructions.
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


typedef enum bool {false, true} bool;




/*---------------------FUNCTIONS--------------------------*/


/*
   Initial functions to setup parser
  -----------------------------------
*/

void check_file(parser *prog, polish_stack *s, char *f);


bool check_inputs(int argc);


bool clear_the_screen(int clear);


bool check_and_start(parser *p, polish_stack *s);


bool string_same(char *str1, char *str2);


/*
   Main functions for Parser
  ----------------------------
*/

void process_instruct_list(parser *p, polish_stack *s);


bool process_instruction(parser *p, polish_stack *s);


bool check_FD(parser *p);


bool check_LT_RT(parser *p);


bool check_DO(parser *p, polish_stack *s);


bool check_varnum(parser *p);


bool check_var(parser *p);


bool check_SET(parser *p, polish_stack *s);


bool check_polish(parser *p, polish_stack *s);


bool check_op(parser *p);


/*
   Functions for stack
  ---------------------
*/

bool initialise_stack(polish_stack *s);


bool push_on_stack(polish_stack *s, char *c);


char pop_off_stack(polish_stack *s);


void free_stack(polish_stack *s);
