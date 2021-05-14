
/*
    Extended Interpreter
    --------------------

   This is the extended version of the recursive descent parser
   for turtle graphics, the simple drawing language.


   After the parser has been executed and before the execution
   of the interpreter, you will be prompted to enter your name
   and password. You will then be shown the name, key and the
   encrypt output of your password. This data is stored in
   the file "oldPass.txt".

   You will have to do this before every new turtle shape.
   I have included a delete function to delete passwords
   after they've been used.

   Continue this process and try out different passwords. It's a
   little bit laborous but that's the nature of the password
   manager beast.

   NB:- Please don't use special characters - the password
   cipher only decodes upper/lowercase letters and numbers.

   2. For the extended grammar:

   I have included some examples of the if statements in a
   .txt file entitled .

*/

#include "interp.h"
#include "password.h"

int main(int argc, char** argv)
{
 interp prog;
 SDL_Simplewin w;
 turtle xy_coords;
 polish_stack s;

 check_inputs(argc);

 initialise_stack(&s);

 check_file(&prog, &s, argv[1], &xy_coords);

 start_pass();

 start_SDL(&w, &xy_coords);

 check_and_start(&prog, &s, &w, &xy_coords);

 SDL_Quit();

 atexit(SDL_Quit);

 free_stack(&s);

 return 0;

}

/*
   Starts the password function.
*/
void start_pass(void)
{
   save_password();

   delete_pass();

}


/*
	A random string is generated using key_generator() and is passed to cipher()
	and the resulting string is written to the password vault.
*/
void save_password()
{
 	FILE *fp;
  char password[100], ref[100], encrypt[100], key[100], decrypt[100];

  printf("\nEnter your name: ");
  scanf("%s", ref);

  printf("Enter your password: ");
  scanf("%s", password);

  key_generator(key,strlen(password));

  cipher(password, encrypt, key);

  printf("\nName: %s", ref);
  printf("\nKey: %s", key);
  printf("\nEncrypted: %s", encrypt);

  fp=fopen("oldPass.txt","a");

  if(fp == NULL){
	    printf("Searching...can't find anything.\n");
  }
  else{
	    fprintf(fp,"%s %s %s", ref, encrypt, key);
  }
  fclose(fp);
 	printf("\n\nYour password has been encrypt and saved.\n");


  open_password(password, ref, encrypt, key, decrypt);
}

/*
	After prompting the user to enter the ref, password vault is opened
	and the refs are compared.
	When found, the encrypt string and the key is passed to cipher() for
	decrypting
*/

void open_password(char password[100], char ref[100], char encrypt[100], char key[100], char decrypt[100])
{
   int i;
   char name[40];
   FILE *fp;

   printf("\nEnter your name: ");
   scanf("%s", name);

   fp=fopen("oldPass.txt","r");
   if(fp == NULL){
      printf("File failed to open");
   }
   else{
      for(i=0;i<40;i++){
          fscanf(fp,"%s %s %s \n", ref, encrypt, key);
          if(strcmp(ref, name)==0){
             cipher(encrypt, decrypt, key);
          }
      }
   }
   printf("Your decrypt password is: %s", decrypt);

    display_names(password, ref, encrypt, key, decrypt);
}

/*
	The password vault is read and the refs are printed out to STDOUT until EOF
*/

void display_names(char password[100], char ref[100], char encrypt[100], char key[100], char decrypt[100])
{
   FILE *file;

   printf("\nThe name associated is: ");

   file=fopen("oldPass.txt","r");

   if(file == NULL){
      printf("File failed to open");
   }
   else{
      while(!feof(file)){
         fscanf(file, "%s %s %s \n", ref, encrypt, key);
         printf("%s", ref);
      }
   }

    start_turtle(password, ref, encrypt, key, decrypt);
}

/*
   With the help of rand() from stdlib.h, a random character
   from the character array is taken is repeated n times to
   create a random string of length n.
*/
extern void key_generator(char *key, int n)
{
   int index = 0;
   char strings[100] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

   srand((unsigned int)(time(NULL)));

   for(index = 0; index <n; index++){
      key[index] = strings[rand() % (sizeof strings - 1)];
   }
   key[index]='\0';
}

/*
	cipher() implements the XOR cipher. The result is stored into *output
*/
void cipher(char *input, char *output, char *key)
{
   int i;
   int len;

   len = strlen(input);

   for(i = 0; i < len; i++){
      output[i] = input[i] ^ key[i];
   }
   output[i]='\0';
}



void start_turtle(char password[100], char ref[100], char encrypt[100], char key[100], char decrypt[100])
{
   char name[40];
   FILE *fp;
   int i;

  	printf("\nTo start the turtle, enter your name: ");
  	scanf("%s", name);
   printf("Enter your password: ");
  	scanf("%s", password);

   fp=fopen("oldPass.txt","r");

   if(fp == NULL){
      printf("\nFile failed to open");
   }
   else{
      for(i=0;i<40;i++){
         fscanf(fp,"%s %s %s \n", ref, encrypt, key);
         if(strcmp(ref, name)==0){
            break;
         }
      }
   }
   cipher(encrypt, decrypt, key);

   while(strcmp(password, decrypt)!=0){
      printf("Incorrect entry. Please try again: ");
      scanf("%s", password);
   }
   printf("Decrypted password %s matches password %s. \n", decrypt, password);
}


/*
	Deletes the password vault.
*/
void delete_pass()
{
   if(remove("oldPass.txt") == 0){
      printf("Password deleted successfully.\n");
   }
   else{
    	printf("Unable to delete the vault");
   }
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
      return false;
      ERROR("Failed to create stack.");
   }
   s->tp->prev = NULL;
   return true;

}

/*
   Initialises the program structure and checks whether
   the file will open.
*/
void check_file(interp *prog, polish_stack *s, char *f,
                turtle *xy_coords)
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
      fprintf(stderr, "Cannot open.\n");
      exit(1);
   }
   i = 0;
   while(fscanf(file, "%s", prog->prog_line[i++]) == SCAN && i < LIMIT){
      prog->num = prog->num + 1;
   }
   fclose(file);

   for(i = 0; i < SIZE; i++){
      xy_coords->array[i] = 0;
      xy_coords->values[i] = 0;
   }
}

/*
   Initialises SDL window, sets the line colour to white and
   checks that the initial coordinates are correct.
*/
void start_SDL(SDL_Simplewin *w, turtle *xy_coords)
{
   Neill_SDL_Init(w);
   Neill_SDL_SetDrawColour(w, COL_WHITE, COL_WHITE, COL_WHITE);

   xy_coords->next_x = START_VAL_X;
   xy_coords->next_y = START_VAL_Y;
   xy_coords->angle = 0;

   SDL_Delay(GRAPHICS_PAUSE);
}

/*
   Check if first prog_lineruction is "{" and
   push onto stack
*/
bool check_and_start(interp *p, polish_stack *s, SDL_Simplewin *w,
                     turtle *xy_coords)
{
  if (!string_same(p->prog_line[p->current], "{")) {
    ERROR("No Opening Bracket");
    return false;
  }

  push_on_stack(s, p->prog_line[p->current]);

  p->current += 1;

  process_instruct_list(p, s, w, xy_coords);

  SDL_Delay(GRAPHICS_PAUSE);
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
bool push_on_stack(polish_stack *s, char* c)
{
   stack_elem *e;

   e = (stack_elem *) calloc(1, sizeof(stack_elem));

   if(e == NULL){
      ERROR("Creation of polish_stack stack_element Failed");
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
void process_instruct_list(interp *p, polish_stack *s,
                           SDL_Simplewin *w, turtle *xy_coords)
{
   if(string_same(p->prog_line[p->current], "}")){
      if(s->tp != NULL){
         if(pop_off_stack(s) == '{'){
            if(s->tp->prev == NULL){
               return;
            }
            else{
               p->current += 1;
               return;
           }
        }
     }
   }
   process_instruction(p, s, w, xy_coords);
   process_instruct_list(p, s, w, xy_coords);
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
bool process_instruction(interp *p, polish_stack *s, SDL_Simplewin *w,
                        turtle *xy_coords)
{
   int clear=0;

   if(string_same(p->prog_line[p->current], "FD")){
      p->current += 1;
      return check_FD(p, w, xy_coords);
      return true;
   }
   if(string_same(p->prog_line[p->current], "LT")){
      p->current += 1;
      return check_LT_RT(p, xy_coords);
      return true;
   }
   if(string_same(p->prog_line[p->current], "RT")){
      p->current += 1;
      return check_LT_RT(p, xy_coords);
      return true;
   }
   if(string_same(p->prog_line[p->current], "DO")) {
      p->current += 1;
      return check_DO(p, s, w, xy_coords);
   }
   if(string_same(p->prog_line[p->current], "SET")) {
      p->current += 1;
      return check_SET(p, s, xy_coords);
   }
   if(string_same(p->prog_line[p->current], "}")) {
      return true;
   }
   clear_the_screen(clear);
   ERROR("Instruction did not comply with rules of grammar. \
          Please check file.");
   return false;
}

/*
   Checks whether the forward instruction is in the correct
   format, and checks previous coordinates and calculates the
   new coordinates.
*/
double check_FD(interp *p, SDL_Simplewin *w, turtle *xy_coords)
{
   int value;
   double num;
   char check_letter;

   if(check_varnum(p)){
      num = check_var_dec(p);
      p->current += 1;
   }
   else{
      check_letter = check_var(p);
      value = check_letter - A;
      num = xy_coords->array[value];
      p->current += 1;
   }

   xy_coords->prev_x = xy_coords->next_x;
   xy_coords->prev_y = xy_coords->next_y;
   xy_coords->next_x = xy_coords->next_x + \
                       num*cos(xy_coords->angle);
   xy_coords->next_y = xy_coords->next_y + \
                       num*sin(xy_coords->angle);

   return draw_line(w, xy_coords, num);
}

/*
   Draws line in SDL based on previous and new coordinates
*/
double draw_line(SDL_Simplewin *w, turtle *xy_coords, double num)
{
   SDL_RenderDrawLine(w->renderer, xy_coords->prev_x,
                      xy_coords->prev_y, xy_coords->next_x, \
                      xy_coords->next_y);
   Neill_SDL_UpdateScreen(w);

   Neill_SDL_Events(w);

   SDL_Delay(WAIT_TIME);

  return num;
}

/*
   Checks LT and RT instructions. Since the functions for
   LT and RT detection are the same, I merged them into
   one. Sets the new angle based on the previous angle.
*/
double check_LT_RT(interp *p, turtle *xy_coords)
{
   double num;
   char check_letter;
   int val;

   if(check_varnum(p)){
      num = check_var_dec(p);
   }
   else{
      check_letter = check_var(p);
      val = check_letter - A;
      num = xy_coords->array[val];
   }
   xy_coords->angle = xy_coords->angle - num * PI/TURN_DEGREES;
   p->current += 1;

   return num;
}

/*
   Checks whether string contains a number and an uppercase
   letter.
*/
bool check_varnum(interp *p)
{
   float num;
   char* str;

   str = p->prog_line[p->current];

   if(sscanf(str, "%f", &num)==1){
      return true;
   }
   if(isupper(str[0]) && strlen(str)==1){
     return 0;
   }
   ERROR("No letter or number?");
   return false;
}


double check_var_dec(interp *p)
{
   double num;

   num = atof(p->prog_line[p->current]);

   return num;
}

/*
   Converts string to character type.
*/
bool check_var(interp *p)
{
   char letter;

   letter = *p->prog_line[p->current];

   if((letter >= A) && (letter <= Z)) {
      return letter;
      return true;
   }
   ERROR("Problem with letter.");
   return false;
}

/*
   Check if SET instruction is valid.
*/
bool check_SET(interp *p, polish_stack *s, turtle *xy_coords)
{
   char character;
   int value;
   double calculate;

   character = check_var(p);
   value = character - A;

   p->current += 1;

   if(string_same(p->prog_line[p->current], ":=")){
      p->current += 1;
      calculate = check_polish(p, s, xy_coords);
      xy_coords->array[value] = calculate;

      return true;
   }
   ERROR("No :=?");
   return false;
}

/*
   Check if the polish expressions used are valid.
*/
bool check_polish(interp *p, polish_stack *s, turtle *xy_coords)
{
   double calculate=0;

   if(string_same(p->prog_line[p->current], ";")){
      if(s->counter == 0){
         ERROR("No value?");
         return false;
      }

      pop_off_stack(s);
      s->counter -= 1;
      calculate = xy_coords->values[s->counter];

      while(s->counter > 0){
         pop_off_stack(s);
         s->counter -= 1;
      }

      p->current += 1;
      return calculate;

   }
   return polish_check_op(p, s, xy_coords, calculate);
   return true;
}


bool polish_check_op(interp *p, polish_stack *s, turtle *xy_coords,
                       double calc)
{
   int maths_symbol;
   char buffer[SIZE];

   if(check_op(p)){
      if(s->counter < 2){
         ERROR("Not 2?");
         return false;
      }

      maths_symbol = check_op(p);
      calc = do_maths(s, xy_coords, maths_symbol);
      xy_coords->values[s->counter] = calc;

      sprintf(buffer, "%f", calc);
      push_on_stack(s, buffer);

      s->counter += 1;
      p->current += 1;

      return check_polish(p, s, xy_coords);

   }
   return polish_varnum(p, s, xy_coords);
   return true;
}

/*
   Checks whether string contains a character. If it does,
   push onto stack and continue. If string contains a number,
   push onto stack and continue.
*/
bool polish_varnum(interp *p, polish_stack *s, turtle *xy_coords)
{
   double num;

     if(!check_varnum(p)){
        push_on_stack(s, p->prog_line[p->current]);

        s->counter += 1;
        p->current += 1;

        return check_polish(p, s, xy_coords);
     }
     if(check_varnum(p)){
        num = check_var_dec(p);
        xy_coords->values[s->counter] = num;

        push_on_stack(s, p->prog_line[p->current]);

        s->counter += 1;
        p->current += 1;

        return check_polish(p, s, xy_coords);
     }
     return false;
}

/*
   Check whether operators used are valid.
*/
bool check_op(interp *p)
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
   Arithmetic calculation of two operands and an operator.
*/
bool do_maths(polish_stack *s, turtle *xy_coords, int op)
{
   double a, b;

   a = get_value(s, xy_coords);

   b = get_value(s, xy_coords);

   switch (op){
      case 1:
         return a + b;
      case 2:
         return a - b;
      case 3:
         return a * b;
      case 4:
         return a / b;
      default:
         ERROR("Invalid operator.");
         return false;
    }
    return false;
}

/*
   Retrieves the value saved by popping off its reference
   from the stack.
*/
double get_value(polish_stack *s, turtle *xy_coords)
{
   int value;
   double integer;
   char character[SIZE];

   character[0] = pop_off_stack(s);
   character[1] = '\0';

   s->counter -= 1;

   if(atoi(character)){
      integer = xy_coords->values[s->counter];
      return integer;
   }
   if((character[0] >= A) && (character[0] <= Z)){
      value = character[0] - A;
      integer = xy_coords->array[value];
      return integer;
  }
  return 0;
}

/*
   Check if DO program prog_lineruction is valid. This function
   is fairly long. I wasn't able to break it into smaller functions
   without it generating errors.
*/
bool check_DO(interp *p, polish_stack *s, SDL_Simplewin *w,
             turtle *xy_coords)
{
   int row=0, value=0, clear=0, val=0;
   double a=0, b=0, min_val=0, max_val=0;
   char letter='\0', check_letter='\0';

   check_letter = check_var(p);
   val = check_letter - A;

   p->current += 1;
   if(string_same(p->prog_line[p->current], "FROM")){
      p->current = p->current + 1;
      if(check_varnum(p)){
         a = check_var_dec(p);
         min_val = a;
         xy_coords->array[val] = min_val;
      }
      else{
         letter = check_var(p);
         value = letter - A;
         min_val = xy_coords->array[value];
         xy_coords->array[val] = min_val;
      }
      p->current += 1;
      if(string_same(p->prog_line[p->current], "TO")){
         p->current = p->current + 1;
         if(check_varnum(p)){
            b = check_var_dec(p);
            max_val = b;
         }
         else{
            letter = check_var(p);
            value = letter - A;
            max_val = xy_coords->array[value];
        }
        p->current += 1;
        if(string_same(p->prog_line[p->current], "{")){
           return check_brackets(p, s, w, xy_coords,
                                 max_val, row, val);
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
   Checks for closing bracket.
*/
bool check_brackets(interp *p, polish_stack *s, SDL_Simplewin *w,
                   turtle *xy_coords, double max_val, int row, int val)
{
   push_on_stack(s, p->prog_line[p->current]);

   p->current = p->current + 1;
   row = p->current;

   while(xy_coords->array[val] <= max_val){
      process_instruct_list(p, s, w, xy_coords);
      if(string_same(p->prog_line[p->current], "}")){
         xy_coords->array[val] = xy_coords->array[val] + 1;
         if(xy_coords->array[val] <= max_val){
            p->current = row;
            push_on_stack(s, "{");
         }
      }
   }
  return true;
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
