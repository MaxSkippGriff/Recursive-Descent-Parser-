#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include "neillsdl2.h"



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

#define ERROR(PHRASE) fprintf(stderr, \
  "Fatal Error '%s' occurred in %s, line %d\n", \
  PHRASE, __FILE__, __LINE__ ); exit(1)

/* Contains value for ASCII uppercase A */
#define A 65

/* Contains value for ASCII uppercase Z */
#define Z 90

/* Contains RGB value for the colour white */
#define COL_WHITE 255

/* Pi - 20 decimal places */
#define PI 3.14159265358979323846

/* 180 degrees */
#define TURN_DEGREES 180

/* Array size */
#define SIZE 256

/* Sets the start value of x */
#define START_VAL_X 400

/* Sets the start value of y */
#define START_VAL_Y 300

/* Pause between lines drawn */
#define WAIT_TIME 200

/* Pause at beginning and end of graphics */
#define GRAPHICS_PAUSE 900


/*----------------------STRUCTURES------------------------*/



typedef struct interp {
  char prog_line[LIMIT][MAX_LEN];
  int current;
  int num;
} interp;


typedef struct turtle {
  double prev_x;
  double prev_y;
  double next_x;
  double next_y;
  double angle;
  double array[SIZE];
  double values[SIZE];
} turtle;


typedef struct stack_elem {
  char i;
  struct stack_elem *prev;
} stack_elem;


typedef struct polish_stack {
  stack_elem *tp;
  int counter; /* polish_stack counter */
} polish_stack;


typedef enum bool {false, true} bool;



/*---------------------FUNCTIONS--------------------------*/

/*
   Initial functions to setup parser/interp
  ----------------------------------------------
*/

bool check_inputs(int argc);


bool clear_the_screen(int clear);


void check_file(interp *prog, polish_stack *s, char *f, turtle *cd);


bool string_same(char *str1, char *str2);


/*
   Main functions for interp
  ---------------------------------
*/

void start_SDL(SDL_Simplewin *w, turtle *cd);


bool check_and_start(interp *p, polish_stack *s, SDL_Simplewin *w, turtle *cd);


void process_instruct_list(interp *p, polish_stack *s, SDL_Simplewin *w, turtle *cd);


bool process_instruction(interp *p, polish_stack *s, SDL_Simplewin *w, turtle *cd);


double check_FD(interp *p, SDL_Simplewin *w, turtle *cd);


double draw_line(SDL_Simplewin *w, turtle *xy_coords, double num);


double check_LT_RT(interp *p, turtle *xy_coords);


bool check_varnum(interp *p);


double check_var_dec(interp *p);


bool check_var(interp *p);


bool check_SET(interp *p, polish_stack *s, turtle *cd);


bool check_polish(interp *p, polish_stack *s, turtle *cd);


bool polish_check_op(interp *p, polish_stack *s, turtle *xy_coords, double calc);


bool polish_varnum(interp *p, polish_stack *s, turtle *xy_coords);


bool check_op(interp *p);


bool do_maths(polish_stack *s, turtle *cd, int op);


double get_value(polish_stack *s, turtle *cd);


bool check_DO(interp *p, polish_stack *s, SDL_Simplewin *w,
             turtle *xy_coords);


bool check_brackets(interp *p, polish_stack *s, SDL_Simplewin *w,
                   turtle *xy_coords, double max, int row, int val);


/*
   Functions for stack
  ---------------------
*/

bool initialise_stack(polish_stack *s);


bool push_on_stack(polish_stack *s, char *c);


char pop_off_stack(polish_stack *s);


void free_stack(polish_stack *s);
