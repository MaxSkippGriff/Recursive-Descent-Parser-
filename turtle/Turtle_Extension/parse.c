
/*
    Extended Parser
    ---------------

   This is the extended version of the recursive descent parser
   for turtle graphics, the simple drawing language.

   After the parser has been executed and before the execution
   of the interpreter, you will be prompted to enter your name
   and password. You will then be shown the name, key and the
   encrypted output of your password. This data is stored in
   the file "oldPass.txt".

   You will have to do this before every new turtle shape.
   I have included a delete function to delete passwords
   after they've been used.

   Continue this process and try out different passwords. It's a
   little bit laborous but that's the nature of the password
   manager beast.

   NB:- Please don't use special characters - the password
   cipher only decodes upper/lowercase letters and numbers.

*/

#include "parser.h"


int main(int argc, char** argv)
{
   parser prog;
   polish_stack s;

   check_inputs(argc);

   initialise_stack(&s);

   check_file(&prog, &s, argv[1]);

   check_and_start(&prog, &s);

   free_stack(&s);


   return 0;
}


/*
   Checks whether the correct number of arguments have been
   entered.
*/
bool check_inputs(int argc)
{
   int clear=0;

   if(argc != CORRECT_INPUT){
      clear_the_screen(clear);
      fprintf(stderr, "Error: Too few arguments entered.\n");
      return false;
      exit(1);
   }
   return true;
}

/*
   Clears the screen when an error has occurred and the program
   needs to start again.
*/
bool clear_the_screen(int clear)
{
   clear = system("clear");

   if(clear != CLEAR){
      fprintf(stderr, "Error: failed to clear screen.\n");
      return false;
   }
   return clear;
   return true;
}

/*
   Initialises the stack.
*/
bool initialise_stack(polish_stack *s)
{
   s->tp = (stack_elem *) calloc(1, sizeof(stack_elem));

   if(s->tp == NULL){
      ERROR("Failed to create stack.");
      return false;
   }
   s->tp->prev = NULL;
   return true;
}

/*
   Initialises the program structure and checks whether
   the file will open.
*/
void check_file(parser *prog, polish_stack *s, char *f)
{
   int i;
   FILE *file;

   prog->num = 0;
   prog->current = 0;
   s->counter = 0;

   for(i = 0; i < LIMIT; i++){
      prog->prog_line[i][0] = '\0';
   }
   if(!(file = fopen(f, "r"))){
      fprintf(stderr, "Unable to open file.\n");
      exit(2);
   }
   i=0;
   while(fscanf(file, "%s", prog->prog_line[i++]) == SCAN && i < LIMIT){
      prog->num += 1;
   }
   if(prog->num == 0){
      ERROR("No Words Scanned");
   }
   fclose(file);
}

/*
   Checks if first instruction is opening bracket "{" and
   pushes onto stack.
*/
bool check_and_start(parser *p, polish_stack *s)
{
   if(!string_same(p->prog_line[p->current], "{")){
      ERROR("'{' is missing. Please check file.");
      return false;
   }

   push_on_stack(s, p->prog_line[p->current]);

   p->current += 1;

   process_instruct_list(p, s);

   return true;
}

/*
   Checks whether strings are the same. Returns true if they
   are and false if they are not.
*/
bool string_same(char *str1, char *str2)
{
   if(strcmp(str1, str2) == 0){
      return true;
   }
   else{
      return false;
   }
}

/*
   Pushes a string onto the stack.
*/
bool push_on_stack(polish_stack *s, char *c)
{
   stack_elem *e;

   e = (stack_elem *) calloc(1, sizeof(stack_elem));

   if(e == NULL){
      ERROR("A problem occurred when pushing string onto stack. \
            Please check file.");
      return false;
   }

   e->prev = s->tp;
   s->tp->i = *c;
   s->tp = e;

   return true;
}

/*
   Check if instruction is closing bracket "}" to pop last
   item "{" off the stack.
*/
void process_instruct_list(parser *p, polish_stack *s)
{
   if(string_same(p->prog_line[p->current], "}")){
      if(s->tp != NULL){
         if(pop_off_stack(s) == '{'){
            if(s->tp->prev == NULL){
               return;
            }
            else{
               p->current += 1;
         }
       }
     }
   }
   process_instruction(p, s);
   process_instruct_list(p, s);
}

/*
   Pops the last character off the stack.
*/
char pop_off_stack(polish_stack *s)
{
   free(s->tp);
   s->tp = s->tp->prev;

   if(s->tp == NULL){
      ERROR("Problem with number of variables on stack.");
   }

   if(s->tp != NULL){
      return s->tp->i;
   }
   return '\0';
}

/*
   Goes through the list of possible grammar rules and checks
   whether the instructions comply with those rules.
*/
bool process_instruction(parser *p, polish_stack *s)
{
   int clear=0;

   if(string_same(p->prog_line[p->current], "FD")){
      p->current += 1;
      return check_FD(p);
   }
   else if(string_same(p->prog_line[p->current], "LT")){
      p->current += 1;
      return check_LT_RT(p);
   }
   else if(string_same(p->prog_line[p->current], "RT")){
      p->current += 1;
      return check_LT_RT(p);
   }
   else if(string_same(p->prog_line[p->current], "DO")){
      p->current += 1;
      return check_DO(p, s);
   }
   else if(string_same(p->prog_line[p->current], "SET")){
      p->current += 1;
      check_SET(p, s);
      return true;
   }
   else if(string_same(p->prog_line[p->current], "}")){
      return true;
   }
   else{
      clear_the_screen(clear);
      ERROR("Instruction did not comply with rules of grammar. \
             Please check file.");
      return false;
   }
}

/*
   Checks whether the forward instruction is in the correct
   format.
*/
bool check_FD(parser *p)
{
   int clear=0;

   if(check_varnum(p)){
      p->current += 1;
      return true;
   }
   if(check_var(p)) {
      p->current += 1;
      return true;
   }
   clear_the_screen(clear);
   ERROR("String does not contain an FD.\
         Please check file.\n");
   return false;
}

/*
   Checks whether string contains a number and an uppercase
   letter.
*/
bool check_varnum(parser *p)
{
   int clear=0;
   float number;
   char* string;

   string = p->prog_line[p->current];

   if(sscanf(string, "%f", &number)==1){
      return true;
   }
   if(isupper(string[0]) && strlen(string)==1){
      return 0;
   }
   clear_the_screen(clear);
   ERROR("String does not contain a number or a letter.\
         Please check file.\n");
   return false;
}

/*
   Converts string to character type.
*/
bool check_var(parser *p)
{
   int clear=0;
   char test_letter;

   test_letter = *p->prog_line[p->current];

   if((test_letter >= A) && (test_letter <= Z)){
      return test_letter;
      return true;
   }
   clear_the_screen(clear);
   ERROR("String does not contain a Letter.\
          Please check file.\n");
   return false;
}

/*
   Checks LT and RT instructions. Since the functions for
   LT and RT detection are the same, I merged them into
   one.
*/
bool check_LT_RT(parser *p)
{
  int clear=0;

  if(check_varnum(p)){
    p->current += 1;
    return true;
  }
  if(check_var(p)){
    p->current += 1;
    return true;
  }
  clear_the_screen(clear);
  ERROR("String does not contain a LT or RT.\
         Please check file.\n");
  return false;
}

/*
   Check if SET instruction is valid
*/
bool check_SET(parser *p, polish_stack *s)
{
   int clear=0;

   p->current += 1;

   if(string_same(p->prog_line[p->current], ":=")){
      p->current += 1;
      return check_polish(p, s);
      return true;
   }
   clear_the_screen(clear);
   ERROR("String does not contain a ':='.\
          Please check file.\n");
   return false;
}

/*
   Check if the polish expressions used are valid.
*/
bool check_polish(parser *p, polish_stack *s)
{
  if(string_same(p->prog_line[p->current], ";")){
    p->current += 1;
    return 1;
  }
  if(check_op(p)){
     p->current += 1;
     return check_polish(p, s);
  }
  if(!check_varnum(p)){
     p->current += 1;
     return check_polish(p, s);
  }
  if(check_varnum(p)){
     p->current += 1;
     return check_polish(p, s);
  }
  return false;
}

/*
   Check whether operators used are valid.
*/
bool check_op(parser *p)
{
   char c;

   c = p->prog_line[p->current][0];

   if(strlen(p->prog_line[p->current])== 1){
      switch(c){
         case '+':
         case '-':
         case '*':
         case '/':
            return true;
         default:
            return false;
      }
   }
   return false;
}

/*
   Check if DO instruction is valid. This function is fairly
   long. I wasn't able to break it into smaller functions
   without it generating errors.
*/
bool check_DO(parser *p, polish_stack *s)
{
   int clear=0;

   p->current += 1;

   if(string_same(p->prog_line[p->current], "FROM")){
      p->current += 1;
      if(check_varnum(p) || check_var(p)){
         p->current += 1;
      }
      if(string_same(p->prog_line[p->current], "TO")){
         p->current += 1;
         if(check_varnum(p) || check_var(p)){
            p->current += 1;
         }
         if(string_same(p->prog_line[p->current], "{")){
            push_on_stack(s, p->prog_line[p->current]);
            p->current += 1;
            return true;
         }
         clear_the_screen(clear);
         ERROR("No '{'? Please check file.");
         return false;
       }
       clear_the_screen(clear);
       ERROR("No 'TO'? Please check file.");
       return false;
    }
    clear_the_screen(clear);
    ERROR("No 'FROM'? Please check file.");
    return false;
}

/*
   Frees all stack memory
*/
void free_stack(polish_stack *s)
{
   if(s->tp == NULL){
      ERROR("Cannot free stack.");
   }
   if(s != NULL){
      while(s->tp != NULL){
         free(s->tp);
         s->tp = s->tp->prev;
      }
   }
}
