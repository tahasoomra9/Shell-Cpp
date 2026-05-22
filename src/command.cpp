/**I will be a great programmer
 * i am Good,  i will be great
 * i am enough to achieve my dreams
 * it will be hard, it will burn me
 * but it will change me 
 */

 /**I FEEL MENTALLY TORN TODAY (5 days after starting this project) */

#include <stdio.h>
#include <string.h>
#include "command.h"
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

void Command::execute() 
{
    /**Execute Works by Taking Simple Commands and for every simple command it will
     * if return value for fork in greater than 1 it will keep going
     * else for child if value be given 0 and it will execture it and it will keep on exceuting
     * and for signed value it will thorow error
     */

     //-----------------------------//

     int ret;
     for (int i = 0; i < numberOfSimpleCommands; ++i) 
     {
        ret = fork(); //whatever return value is it will be given to fork

        if (ret == 0) 
        {
          //child
        //If return is 0 after fork() creation (e.g fork() craetes two process one child  and oothger parent)
        //take the simple command and inside it take arguments, get the first argument which will be its name, 
        //and the rest would be its command
        execvp(simpleCommands[i]->arguments[0], simpleCommands[i]->arguments);
        perror("execvp");
        _exit(1);
          
        }

        //for error thorwing
        else if (ret < 0) 
        {
            perror("fork");
            return;
        }

        /**
         * If a task is in foreground meaning wait for it to finish
         * if a task is in background contiue nomrally (like user can do other shit
         */

         if (!background) //if running in foreground
         {
            //wait for Child procress to finish
            waitpid(ret, NULL, 0); //give childs PID, ignore status, stop here utill the execution
         }


         //-----------------------------//
         /**Pipe and input out redirection 
          * Supports 3 pipes
          * A | B | C | D
          * 
          * Send output of A to B -> B output to C -> C output to D
          * Input comes from infile output comes from outfile
         */

         //INPUT REDIRECITON

         //To save in and out we need dup(0 to read 1 for input)
         int tempIn = dup(0);
         int tempOut = dup(1);

         //We need a file Descriptor for in/out redirection
         int fdin;
         int fdout;

         //if file is given, read it, update the fdin 
         if (inputFile) 
         {
            //updating File Desc
            fdin = open(inputFile, O_RDONLY);
         }

         //else take input from keyboard

         else {
            fdin = dup(tempIn);
         }

         /**PIPING System and OUTPUT REDIRECTION
          * Basic Idea, Output of one pipe, becomes input of next 
          * Another Case
          * Lets say we have cat hello.txt | grep hello
          * without piping it will read input from keyboard
          *but we want to make it read the previous pipe output
          the output of cat (our example) but mainly previous pipe output
         */

         //for every simplecommand
         for (int i = 0; i < numberOfSimpleCommands; i++) 
         {
            //make standard input (stdin) read from the descriptor instead of keyboartd
            dup2(fdin, 0); // 0 is stdin and it is being replaced by what fdin has read
            close(fdin); // close it, because we dont need the old descriptor anymore
         }


        }
}
