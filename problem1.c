#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_EQ 50

typedef struct node{
  char data;
  struct node *next;
} node_t;


int is_variable(char *str);
int is_equal(char *str);
void error_number(int n, char *eq);
void error_classifier(FILE *input);
int brackets(node_t *head, char *str);
char peek(node_t *top);
char pop(node_t **top);
void push(node_t **top, char c);

/*
 AUTHOR: Suchith Chandan Reddy Pinreddy & Vedant Supnekar
 FILENAME: problem1.c
 SPECIFICATION: Identify if open brackets matches with closed brackets in the equations.txt file and find out the errors in the equations
 FOR: CS 2413 Data Structures Section 002
*/


int main(){
    FILE *infile;
    infile = fopen("equations.txt", "r");
    error_classifier(infile);
    return 0;
}

/* NAME: main
PARAMETERS: void
PURPOSE: The main function initializes the file, checks whether its empty via a function and calls the function used to classify the equations
PRECONDITION: No parameters, function is called when program runs.
POSTCONDITION: The fucntions should return 0.
*/


int is_variable(char *str){
    if (isalpha(str[0]) == 0){
        return 0;
    }
}

/* NAME: is_variable
PARAMETERS: char *str
PURPOSE: This function checks if the first element of the string is a letter or not.
PRECONDITION: Function should input a string as a parameter.
POSTCONDITION: If the first element of the string is not a letter, function will return 0.
*/


int is_equal(char *str){
    for(int i = 0; i<=(strlen(str)-1); i++){
        if (str[i] == '='){
            return 0;
        }
    }
}

/* NAME: is_equal
PARAMETERS: char *str
PURPOSE: This function checks if there is '=' sign present anywhere in the given string.
PRECONDITION: Function should input a string as a parameter.
POSTCONDITION: If '=' sign is found, function will return 0.
*/


void error_number(int n, char *str){
    switch(n){
    case 0:
        printf("***ERROR ID 0 on %s", str);
        break;
    case 1:
        printf("***ERROR ID 1 on %s", str);
        break;
    case 2:
        printf("***ERROR ID 2 on %s", str);
        break;
    case 3:
        printf("***ERROR ID 3 on %s", str);
    }
}

/* NAME: error_number
PARAMETERS: int n, char *str
PURPOSE: This function has separate print statements for each error. This function uses switch case to classify the print statements and errors
PRECONDITION: Function should input a string and a number as a parameter.
POSTCONDITION: Function should not return anything as it is a void function. However, it should print the required statement.
*/


void error_classifier(FILE *input){
    node_t *top = NULL;
    char equation[MAX_EQ];
    int flag = 0;
    while(fgets(equation, MAX_EQ, input)){
        if(is_variable(equation) == 0){
            flag = 1;
            error_number(1, equation);
        }
        else if(is_equal(equation)){
            flag = 1;
            error_number(2, equation);
        }
        else if(brackets(top, equation)!=0){
            flag = 1;
            error_number(3, equation);
        }
        else{
            flag = 1;
            error_number(0, equation);
        }
    }
    if(flag==0){
       printf("***ERROR ID 1 and The file is empty");
    }
}

/* NAME: error_classifier
PARAMETERS: FILE *input
PURPOSE: This function stores a line of the input file into a string (which is the equation), and checks for errors in the equation. It also calls the error_number function to print the errors. This keeps on happening in a loop until the end of the file. it also declares the linked list which is later used to calculate error number 3.
PRECONDITION: The function uses a FILE pointer as a parameter
POSTCONDITION: Function should not return anything as it is a void function.
*/


int brackets(node_t *head, char *str){
    char x;
    int flag = 0;
    int flag1 = 0;
    for(int i = 0; i<=(strlen(str)-1); i++){
        if (str[i] == '(' || str[i] == '{' || str[i] == '['){
            push(&head,str[i]);
            flag = 1;
        }
        else if(str[i]==')'|| str[i]=='}' || str[i]==']'){
            if (flag){
                x = pop(&head);
                flag1 = 1;
                if(!((x=='('&& str[i]==')') || (x == '{' && str[i]=='}') || (x == '[' && str[i]==']'))){
                }
            }
            else{
                return 1;
            }
        }
    }
    if(head != 0){
        return 1;
    }
    if(flag==1 && head == 0){
        return 0;
    }
}

/* NAME: brackets
PARAMETERS: node_t *head, char *str
PURPOSE: This function checks for '(', '{' and '[' brackets inside the string and pushes them into a stack linked list. The function also searches for ')', '}' and ']' and pops top most element out of linked list when one of these are found. The function then compares the two brackets and returns 0 if the brackets are similar.
PRECONDITION: Function should input a string and a linked list head as parameter
POSTCONDITION: Function should return 0 if the two brackets are similar and should return 1 if the two brackets are not similar.
*/



char peek(node_t *top){
    if (top != NULL) { //checking to see if stack is empty or not if not then reads out topmost value
        return top->data;
    }
    //else{
      //  printf("The stack is empty\n");
    //}
}

/* NAME: peek
PARAMETERS: node_t *top
PURPOSE: This function extracts top most data for comparisons purposes in pop function
PRECONDITION: Function should input a pointer or addresses
POSTCONDITION: Function should return top most data if stack is not empty.
*/

char pop(node_t **top){
    node_t *temp;
    if (*top == NULL){ //Check is stack is empty
        printf("Stack Underflow\n");
    }
    char x = peek(*top); //Stores top most value in stack
    //printf("Removing %c\n", x);
    temp = *top; //temp variable to clear out the space
    *top = (*top)->next;//moving the top pointer to point to the next node
    free(temp);//free allocated memory

    return x;
}

/* NAME: pop
PARAMETERS: node_t **top
PURPOSE: This function to pop out open brackets via peek if the closed brackets are matched and free the memory
PRECONDITION: Function should input a pointer or address of current pointer which is head
POSTCONDITION: Function will remove the character if the condition is matched whenever it reads closed brackets
*/


void push(node_t **top, char c){
    node_t *newp = NULL;
    newp = (node_t *)malloc(sizeof(node_t)); //Dynamic Allocation of memory for the structure

    // check if stack is full.
    //if (!newp){
      //  printf("Heap Overflow\n");
    //}
   // printf("Inserting %c\n", c);
    newp->data = c; //storing the char data in the new node
    newp->next = *top; //linking next pointer of the new node to the current top node
    *top = newp; //updating the top pointer
}

/* NAME: push
PARAMETERS: node_t **top, char c
PURPOSE: This function to push open brackets via current address of stack
PRECONDITION: Function should input a pointer or addresses and open brackets
POSTCONDITION: Function will add the brackets to stack and move the address of top
*/


/*REPORT
Student name: 1.) Suchith Pinreddy - Created stacks.
                -Designed, implemented the following functions;
                    char peek(node_t *top);
                    char pop(node_t **top);
                    void push(node_t **top, char c);
                -Modified the following functions:
                    int brackets(node_t *head, char *str);
                    void error_classifier(FILE *input);

                2.) Vedant Supnekar - Came up with the basic logic functionality of the program. Helped figure out linked list stack logic.
                - Designed, implemented the following:
                    int main();
                    int is_variable(char *str);
                    int is_equal(char *str);
                    void error_number(int n, char *eq);
                    void error_classifier(FILE *input);
                    int brackets(node_t *head, char *str);
                -Modified the following functions:
                    void push(node_t **top, char c)

-------->TEST CASES:
-------->CASE 1: equations.txt
-------->Answer: PASSED
-------->Output:
***ERROR ID 0 on a = ((c+d)*a)/(b/(d-a))
***ERROR ID 0 on b = 4*[x + 3*(2*x + 1)]
***ERROR ID 0 on c = -5*{3 - 2*[1 - 4*(3 - 22)]}
***ERROR ID 0 on d = 5 + 2*{[3 + (2*x - 1) + x] - 2}
***ERROR ID 0 on e = 5 + 9 * 3
***ERROR ID 1 on (5 + 9)*3
***ERROR ID 2 on f (5 + 9)*3
***ERROR ID 3 on g = 5 + 2*{[3 + (2*x - 1) + x - 2}
***ERROR ID 3 on h = 5 + 9 * 3)
***ERROR ID 3 on i = 5 + (9 * 3
----------------------------------------------------------------------------------------------------------------
-------->CASE 2: equations1.txt
-------->Answer: PASSED
-------->Output:
***ERROR ID 0 on a = ((c+d)*a)/(b/(d-a))
***ERROR ID 0 on b = 4*[x + 3*(2*x + 1)]
***ERROR ID 0 on c = -5*{3 - 2*[1 - 4*(3 - 22)]}
***ERROR ID 0 on d = 5 + 2*{[3 + (2*x - 1) + x] - 2}
***ERROR ID 0 on e = 5 + 9 * 3
----------------------------------------------------------------------------------------------------------------
-------->CASE 3: equations2.txt
-------->Answer: PASSED
-------->Output:
***ERROR ID 0 on a = ((c+d)*a)/(b/(d-a))
***ERROR ID 0 on b = 4*[x + 3*(2*x + 1)]
***ERROR ID 0 on c = -5*{3 - 2*[1 - 4*(3 - 22)]}
***ERROR ID 0 on d = 5 + 2*{[3 + (2*x - 1) + x] - 2}
***ERROR ID 0 on e = 5 + 9 * 3
-----------------------------------------------------------------------------------------------------------------
-------->CASE 4: equations3.txt
-------->Answer: PASSED
-------->Output:
***ERROR ID 3 on g = 5 + 2*{[3 + (2*x - 1) + x - 2}
-----------------------------------------------------------------------------------------------------------------
-------->CASE 5: equations4.txt
-------->Answer: PASSED because file was empty making it no variable in the file giving error ID 1 and file empty
-------->Output:
***ERROR ID 1 and The file is empty.
-----------------------------------------------------------------------------------------------------------------------------------------------------------------
-------->Question 1: Example of a worst-case type of equation that would require many items to be placed on the stack?
-------->Answer: The worst-case type of equation is when the equation has n number of opening brackets which will be implemented in
                 stacks and will lead to use of push function as n number of opening brackets are there in the equation
                 making it O(N) since stacks is fully dependent on the n number of opening brackets available in the equation.

-------->Question 2: Big O for determining that n equations of max length m are valid?
-------->Answer: The Big O for determining that n equations of max length m are n*m since we have to read these equations one by one through the given
                input file, storing them into a string. We then traverse the string reading individual characters one by one (via for loop) to see if there
                exists any error. This makes the complexity to this situation to be n*m which Big O(N^2).

-------->Question 3: Big O of the storage requirements for a stack linked list of size n?
-------->Answer: A stack linked list of size n can be only accessed by the top for push, pop, and peek functions.
                 Since, only top has access to all the values in stacks it leads to storing and removing of values to be done by one variable
                 hence, the variable is counted as big O(1).
-------->Sources:
https://www.tutorialspoint.com/cprogramming/switch_statement_in_c.htm
https://stackoverflow.com/questions/26172043/sending-a-file-pointer-to-another-function-c-programming
https://www.geeksforgeeks.org/implement-a-stack-using-singly-linked-list/
*/
