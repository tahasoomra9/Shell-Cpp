%{
    #include <stdio.h>
    #include <string.h>
    #include "shell.tab.h"
%}

/* Token declarations */

%token NOTOKEN
%token NEWLINE
%token GREAT GREATGREAT
%token LESS LESSLESS
%token AMPERSAND
%token GREATAMPERSAND
%token GREATGREATAMPERSAND
%token PIPE
%token SEMICOLON
%token WORD

%%

/* EXPLANATION FOR THE CODE BELOW!!!!!!!!!! */
/* I AM ADDING THESE COMMENTS INCASE I GET FAMOUS AND SOMEONE LOOKS UP MY PROJECTS */
/* I NEED TO LARP AS MUCH AS POSSIBLE*/


/* An argument is considered a WORD after the first command WORD */
/* It can also be empty */
/* Example: 'ls' only contains a command and no arguments */

arg_list:
        arg_list WORD
      | /* Can be empty */
;


/* Command and arguments follow this sequence */
/* First WORD is considered the command */
/* Remaining WORDs become arguments */

cmd_and_args:
        WORD arg_list
;


/* A pipe list starts with one command */
/* If a PIPE appears connect the existing pipe list */
/* with another cmd_and_args */

pipe_list:
        pipe_list PIPE cmd_and_args
      | cmd_and_args
;


/* Input/output modifiers */

io_modifier:
        GREATGREAT WORD
      | GREAT WORD
      | GREATAMPERSAND WORD
      | GREATGREATAMPERSAND WORD
      | LESS WORD
;


/* Multiple modifiers can exist */
/* Or the list can be empty */

io_modifier_list:
        io_modifier_list io_modifier
      | /* Can be empty */
;


/* Optional background process */

background_optional:
        AMPERSAND
      | /* Can be empty */
;

/* A command line, consists of a pipe_list, an optional io_modifier_list also an background_optional*/
/*  Then NEWLINE to tell shell we are done and get on next line  */
/*  an edge case is, if a user types some utter bullshit such as ls |||||  */
/*it needs to throw error*/

command_line:
            pipe_list io_modifier background_optional NEWLINE
            | NEWLINE // Can accept a new line e.g user pressing enter simoutanously
            | error NEWLINE {ykeror;} //for error
            ;

command_list:
            command_line command_list //Self Explainatory
            ;
%%