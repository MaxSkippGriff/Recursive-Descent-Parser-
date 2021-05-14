#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include "neillsdl2.h"
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

#define ERROR(PHRASE) fprintf(stderr, \
  "Fatal Error '%s' occurred in %s, line %d\n", \
  PHRASE, __FILE__, __LINE__ ); exit(1)

/* ASCII code for uppercase A */
#define A 65

/* ASCII code for uppercase Z */
#define Z 90

/* Contains expected value of stack count */
#define STACK_CNT 2

/* RGB value for colour white */
#define WHITE 255

/* Pi to 20 decimal places */
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

/* Array size for test array */
#define TEST_SIZE 256






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

/* polish_stack counter */

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
   Initial functions to setup parser/interp
  ----------------------------------------------
*/

bool check_inputs(int argc);


bool clear_the_screen(int clear);


bool initialise_stack(polish_stack *s);


void check_file(interp *prog, polish_stack *s, char *f, turtle *cd);


void start_SDL(SDL_Simplewin *w, turtle *cd);


bool check_and_start(interp *p, polish_stack *s, SDL_Simplewin *w, turtle *cd);


bool string_same(char *str1, char *str2);


bool push_on_stack(polish_stack *s, char *c);


void process_instruct_list(interp *p, polish_stack *s, SDL_Simplewin *w, turtle *cd);


char pop_off_stack(polish_stack *s);


bool process_instruction(interp *p, polish_stack *s, SDL_Simplewin *w, turtle *cd);


double check_FD(interp *p, SDL_Simplewin *w, turtle *cd);


double draw_line(SDL_Simplewin *w, turtle *xy_coords, double num);


double check_LT_RT(interp *p, turtle *xy_coords);


bool check_varnum(interp *p);


double check_var_dec(interp *p);


bool check_var(interp *p);


bool check_SET(interp *p, polish_stack *s, turtle *cd);


bool check_polish(interp *p, polish_stack *s, turtle *cd);


bool Polish_check_op(interp *p, polish_stack *s, turtle *xy_coords, double calc);


bool Polish_varnum(interp *p, polish_stack *s, turtle *xy_coords);


bool check_op(interp *p);


bool do_maths(polish_stack *s, turtle *cd, int op);


double get_value(polish_stack *s, turtle *cd);


bool check_DO(interp *p, polish_stack *s, SDL_Simplewin *w,
             turtle *xy_coords);
/*
int check_FROM(interp *p, turtle *xy_coords, double num1, double min,
               int value, int val, char letter);

int check_TO(interp *p, turtle *xy_coords, double num2, double max,
             int value, char letter);*/

bool check_brackets(interp *p, polish_stack *s, SDL_Simplewin *w,
                   turtle *xy_coords, double max, int row, int val);


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


void test_instrctlist_check(interp *prog_location, polish_stack *s);


void test_instruction(void);


void test_fd(void);


bool test_fd_check(interp *prog, turtle *xy_coords, char* first, char* second);


bool test_abs(double test);


void test_lt(void);


bool test_lt_check(interp *prog, turtle *xy_coords, char* first, char* second);


void test_rt(void);


bool test_rt_check(interp *prog, turtle *xy_coords, char* first, char* second);


void test_do_loop(void);


bool test_do_check(interp *prog, polish_stack *s, test_array *test);


void test_set(void);


bool test_set_check(interp *prog, polish_stack *s, turtle *xy_coords, test_array *test);


void test_varnum(void);


bool test_varnum_check(interp *prog, test_array *test);


void test_var(void);


bool test_var_check(interp *prog, test_array *test);


void test_polish(void);

/*
int test_polish_check(interp *prog, polish_stack *s, turtle *xy_coords, test_array *test);

*/
void test_op(void);


bool test_op_check(interp *prog, char *test);


void test_init_stack(void);


void test_push_stack(void);


void test_pop_stack(void);


void test_free_stack(void);
