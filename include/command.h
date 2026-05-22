/**
 * Creating Command Headers here
 * for Implementing COmmand Table for shell
 */

 struct SimpleCommand {

    private: 
        int numberOfAvailableArgs;      //How much memory we have allocated   
        int numberOfArgs;               //Number of Arguments                 

    public:
        SimpleCommand();                //Constructor
        ~SimpleCommand();               //Destructure
        void insertArgument( char * argument);      //Will use it for insertion, one by one
        char ** arguments;             //Array of arguments
 };

 struct Command {
    private:
        int numberofAvailableSimpleCommands;        //Number of Space Allocated for Simple Commands
        int numberOfSimpleCommands;                 //How many Simple commands do we have?
        SimpleCommand ** simpleCommands;            //Convert our simpleCommands into a complete list
        char * outFile;                             //outfile redirection
        char * inputFile;                            //in file redirection
        char * errFile;                              //err file redirection
        int background;                              //background
        static Command currentCommand;                //what command is being built for now
        static SimpleCommand * currentSimpleCommand;   //what command is being built for now                                                              

    public:
        void prompt();
        void print();
        void execute();
        void clear();

        Command();
        void insertSimpleCommand( SimpleCommand * simpleCommand );
 };