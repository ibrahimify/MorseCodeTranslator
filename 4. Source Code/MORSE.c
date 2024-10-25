// C Program to implement Morse Code Translator

/*



            some info:
            1. ASCII OF a=97, A=65, 0=48

            BUGS in code:
            1. while loop in main function, should iterate until (i<53)
            2. i forgot to convert special character so it will not show in the menu
            3. in text_to_morse function, use putc to put a space character to separate properly
            4. in counts_text function, for digits, it should be c-48 not c-22 or c-'0'.
            5. in latin_statistics function, 48+(i-26) when for loop starts from 26.


*/

//including libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

FILE *history; //This is a pointer to a file. It's used to store the history of commands that have been entered into the shell.

// the struct that defines a tree node. It contains the value of the node, and pointers to its left and right children. 
typedef struct tnode{
    char value;
    struct tnode *left;
    struct tnode *right;
} tnode;

// the struct we use in array containing the text and morse
typedef struct alphabets{
    char text, code[10];
} alphabets;

//function definations

//greetings
void greet(void); //funtion to print the greeting

//creating nodes
tnode* new(char c); //function that creates a new node for the tree. 

//text
void text_to_morse(char c, char *text_convert[], char *num_convert[]); // function that converts text to morse code
void counts_text(int* counts_text_arr, char c); // Count occurrences of characters in text and increment corresponding array elements
void latin_statistics (int *counts_text_arr); //function that takes in an array of integers and returns the number of times each letter appears in the text.

//morse
int test_valid_morse(char *insert); //function that tests if the input string is valid morse code. It returns 0 if it is, and 1 if it isn't.
void morse_to_text (char *insert, tnode *start, int *counts_text_arr, int *counts_morse_arr); //function that takes in a morse code string and converts it to text. It uses the tree structure to find the correct letter for each morse code character.
void counts_morse(char *arr, int *counts_morse_arr); //function counts the number of times a morse code character appears in an array.
void morse_statistics (int *counts_morse_arr); //function to counts the dash and dots

//releasing memory
void freemem(tnode* start); //function that frees the memory of a binary tree
// there


// main funtion
int main(){

    
    history = fopen("history.txt", "a"); //to open the file

    if (history == NULL) {
        // Handle file opening failure
        printf("Error opening history file!");
        return 1; // Indicate error
    }

    int option;
    int counts_text_arr[36]={0}, counts_morse_arr[2]={0};
    int i = 0, j = 0; 
    char insert[500] = {'\0'};
    tnode *start = new('\0'); //start/ root node for tree
    tnode *hold;
    
    //holds an array of strings of morse
        char *text_convert[] = { 

        ".-",   //-->A
        "-...", //-->B
        "-.-.", //-->C
        "-..",  //-->D          
        ".",    //-->E
        "..-.", //-->F
        "--.",  //-->G
        "....", //-->H
        "..",   //-->I
        ".---", //-->J
        "-.-",  //-->K
        ".-..", //-->L
        "--",   //-->M
        "-.",   //-->N
        "---",  //-->O
        ".--.", //-->P
        "--.-", //-->Q
        ".-.",  //-->R
        "...",  //-->S
        "-",    //-->T
        "..-",  //-->U
        "...-", //-->V
        ".--",  //-->W
        "-..-", //-->X
        "-.--", //-->Y
        "--..", //-->Z
    };

//This is an array of char pointers. It's used to translate the numbers 0-9 into their corresponding strings.
    char *num_convert[] = { 

        "-----", //-->0
        ".----", //-->1
        "..---", //-->2
        "...--", //-->3
        "....-", //-->4
        ".....", //-->5
        "-....", //-->6
        "--...", //-->7
        "---..", //-->8
        "----.", //-->9

    };


    greet(); //To print the greeting


    alphabets alphabet[53] = { //list of letters and their corresponding morse code characters. 
    
    {'a', ".-"},
    {'b', "-..."},
    {'c', "-.-."},
    {'d', "-.."},
    {'e', "."},
    {'f', "..-."},
    {'g', "--."},
    {'h', "...."},
    {'i', ".."},
    {'j', ".---"},
    {'k', "-.-"},
    {'l', ".-.."},
    {'m', "--"},
    {'n', "-."},
    {'o', "---"},
    {'p', ".--."},
    {'q', "--.-"},
    {'r', ".-."},
    {'s', "..."},
    {'t', "-"},
    {'u', "..-"},
    {'v', "...-"},
    {'w', ".--"},
    {'x', "-..-"},
    {'y', "-.--"},
    {'z', "--.."},

    {'0', "-----"},
    {'1', ".----"},
    {'2', "..---"},
    {'3', "...--"},
    {'4', "....-"},
    {'5', "....."},
    {'6', "-...."},
    {'7', "--..."},
    {'8', "---.."},
    {'9', "----."},

    {'/', "-..-."},
    {'\n', ".-.-"},
    {'.', ".-.-.-"},
    {'-', "-....-"},
    {'&', ".-..."},
    {'\'', ".----."},
    {'@', ".--.-."},
    {')', "-.--.-"},
    {'(', "-.--."},
    {':', "---..."},
    {',', "--..--"},
    {'=', "-...-"},
    {'!', "-.-.--"},
    {'+', ".-.-."},
    {'\"', ".-..-."},
    {'?', "..--.."},
    {' ', "/"}
    
    };
    

//loop that runs on every element of alphabet array
while(i < 53){ 

        hold = start;
        
        //loop for every element, except the last morse element
        for(j=0; alphabet[i].code[j+1] != '\0' ; j++){ 
            
            // to check if it is a (.) or (-)
            switch(alphabet[i].code[j]){
            case '.':
                if(hold->left != NULL)
                {
                    hold=hold->left; //move pointer if there is any node
                } 
                else //else, create one if there is no node
                {
                    hold->left = new('#'); 
                    hold = hold->left;
                } 
                break;

            case '-':
                if(hold->right != NULL)
                {
                    hold=hold->right;
                }
                else
                {
                    hold->right = new('#');
                    hold = hold->right;
                }
                break;
            }
        }

        //to save the character in tree using last morse element
        // (for int i = 0; )
        switch(alphabet[i].code[j]){ 
        case '.':
            if(hold->left != NULL)
            {
                hold->left->value = alphabet[i].text;   //if node exist, save the value
            } 
            else  //else, create node with letter
            {
                hold->left = new(alphabet[i].text);
            }
            break;

        case '-':
            if(hold->right != NULL)
            {
                hold->right->value = alphabet[i].text;
            }
            else
            {
                hold->right = new(alphabet[i].text);
            }
            break;
        }

        i++;
    }


// creating a menu for user
while( option != 3){  //continue to run until user select option 3
    
    printf("\n\n\n\n\n\nSELECT YOUR CHOICE FROM THE BELOW MENU");
    printf("\n-----------------------------------------\n\n");
    printf("\t<1> TEXT TO MORSE\n\t<2> MORSE TO TEXT\n\t<3> EXIT MENU");
    printf("\n\n-----------------------------------------\n");
    printf("Select your choice: ");
    scanf("%d", &option);
    fflush(stdin);

    switch(option){

        
            case 1: //text to morse
                
                int c;
                printf("\n\n--> Attaboy! You chose option (1)\n\nTranslate your Text to Morse Equivalent: ");
                
                fflush(stdin);
                
                while( (c = tolower(getchar())) != '\n' ) { //loop that will continue to run until the user enters a newline character. It takes in input from the user and converts it to lowercase.
                text_to_morse(c, text_convert, num_convert); //function converts a character to morse code.
                }
                break;

            case 2: //morse to text

                printf("\n\n--> You chose option (2)\n\nWrite a Morse to convert into Text Equivalent\n(RULE: Separate letters by whitespaces (' ') and separate words by front slashes ('/'))\n\nYOUR MORSE INPUT: ");
                fflush(stdin);
                fgets(insert, sizeof(insert), stdin);
                printf("YOUR TRANSLATED MORSE IS: ");
                morse_to_text(insert, start, counts_text_arr, counts_morse_arr);
                break;
                
            case 3: //exit menu and closing the file
                fclose(history);
                exit(1);
                break;

            default: //incase of wrong menu option selection
                printf("--------->  WORNG INPUT DETECTED!  <---------\nChoose options only from the given menu below\n");
                break;
        }
}

    freemem(start); //function to free tree memory
    fclose(history);
    return 0;
} 
//end of main funtion


//functions 
void greet(){ //greeting
     printf("\n\n\n\n\n           __  __                             ____            _        \n");
            printf("          |  \\/  |  ___   _ __  ___   ___    / ___| ___    __| |  ___  \n");
            printf("          | |\\/| | / _ \\ | '__|/ __| / _ \\  | |    / _ \\  / _` | / _ \\ \n");
            printf("          | |  | || (_) || |   \\__ \\|  __/  | |___| (_) || (_| ||  __/ \n");
            printf("          |_|__|_| \\___/ |_|   |___/ \\___|   \\____|\\___/  \\__,_| \\___| \n");
            printf("          |_   _|__ _  _ __   ___ | |  __ _ | |_  ___   _ __           \n");
            printf("            | | / _` || '_ \\ / __|| | / _` || __|/ _ \\ | '__|          \n");
            printf("            | || (_| || | | |\\__ \\| || (_| || |_| (_) || |             \n");
            printf("            |_| \\__,_||_| |_||___/|_| \\__,_| \\__|\\___/ |_|             \n");
            printf("                                                                    \n\n\n");
            printf("-----------------------------------------------------------------------------------\n");
            printf("-----------------------------------------------------------------------------------");
}

tnode* new(char c){ //node creation
    tnode *t = (tnode*)malloc(sizeof(tnode));
    t->value = c;
    t->right = t->left = NULL;
    return(t);
    
}

void text_to_morse(char c, char *text_convert[], char *num_convert[]) //text to morse
{
        if( islower(c) ) {
                fputs(text_convert[c - 'a'], stdout);
                fputc(' ', stdout); 
        } //checking if the character is lowercase, then printing out the corresponding morse code for that letter.
        
        else if ( isupper(c) ){
                fputs(text_convert[c -'A'], stdout);

        }
        else if( isdigit(c) ) {
                fputs(num_convert[c - '0'], stdout);
                fputc(' ', stdout);
        } //checks if the character is a digit. If it is, then it prints out the corresponding string in num_convert[c - '0']. It also adds a space after the string.
        
        else if( isspace(c) ) {
                fputc('/', stdout);
        } // checks if the character c is a space. If it is, then it prints out a slash (/)
        
        
        else {
                fputc(' ', stdout);
        }
}

void counts_text(int* counts_text_arr, char c){ //counts charcter
    
    if(isdigit(c))
    {
        counts_text_arr[c-22]++;
    }   //to check if it is digit, them increment its ASCII index 
    
    else if (islower(c))
    {
        counts_text_arr[c-97]++;
    } //to check if it is lowercase, them increment its ASCII index 
}

/*

*/

void latin_statistics (int *counts_text_arr){ //for latin (text) statistics
    

    for(int i=0; i<26; i++) //loops through the letter elements of the counter array and print
    {
        if(counts_text_arr[i]!=0) //in case this letter never appeared
        {
           
                printf("Letter %c is %d time(s)\n", 97+i, counts_text_arr[i]);
                history = fopen("history.txt", "a");
                fprintf(history, "Letter %c is %d time(s)\n", 97+i, counts_text_arr[i]);
            
        }
    }

    for(int i=26; i<36; i++) //loops through the digit elements of the counter array and print
    {
        if(counts_text_arr[i]!=0) //in case this letter never appeared
        {
           
                printf("Letter %c is %d time(s)\n", 22+i, counts_text_arr[i]);
                history = fopen("history.txt", "a");
                fprintf(history, "Letter %c is %d time(s)\n", 97+i, counts_text_arr[i]);
        }
    }

    for(int i=0; i<36; i++){
        counts_text_arr[i] = 0;
    }
}
 
int test_valid_morse(char *insert){ //checking if it is morse or not
    int i = 0;
    while(i<strlen(insert)) //as long as i is less than the length of insert, then we will continue to execute the code inside of our while loop
    {
        if (insert[i]!=' ' && insert[i]!='\n' && insert[i]!='-' && insert[i]!='/' && insert[i]!='.')
        {
            return 1; //returns 1 if it is not valid
        }
        i++;
    }
    return 0; //returns 0 if it is valid
}

void morse_to_text (char *insert, tnode *start, int *counts_text_arr, int *counts_morse_arr) //morse to text
{
    if(test_valid_morse(insert))
    {

        printf("\n\n---------------------------->  WORNG INPUT DETECTED!  <----------------------------\nYou are writing a wrong input, please write the correct MORSE value for conversion");
        return;
        
    } //check validity
    //the counting index 
    int count=0; //counting the indexes the array
    while(count < strlen(insert)) 
    {
        tnode *temporary = start; //It declares a temporary pointer to a tnode, and initializes it with the value of start.
        int i = count;
        while (insert[i]!= '\0' && insert[i]!= '/' &&  insert[i]!= ' ') //In Morse, letters and words are separated by spaces and slashes
        {
            switch(insert[i])
            {
                case '.': 
                
                temporary=temporary->left; //if (.) appears, we move left
                break;
                
                case '-': 
                
                temporary=temporary->right; //if (/) appears, we move right
                break;
            }
            count++;

            i++;
        }

        // it will print character into the screen and also save it into the file
        counts_text(counts_text_arr, temporary->value); 

                printf(temporary->value? "%c" : "", temporary->value);
                history = fopen("history.txt", "a");
                fprintf(history, temporary->value? "%c" : "", temporary->value);
        

        //if ('/') appears, print white space (' ')
        if(insert[count]=='/'){  
           
                    printf(" ");
                    history = fopen("history.txt", "a");
                    fprintf(history, " ");
                
        }
        count++; 
    }
    
    //to print the stats of morse and latin 

    counts_morse(insert, counts_morse_arr);
    morse_statistics(counts_morse_arr);
    latin_statistics(counts_text_arr);
}

void counts_morse(char *arr, int *counts_morse_arr){ //counts morse
    int i = 0;

    //initializing arrays
    counts_morse_arr[0] = 0; 
    counts_morse_arr[1] = 0;

    while(i<strlen(arr)){
        if(arr[i]=='-')
        {
            counts_morse_arr[0]++;
        }

        else if(arr[i]=='.')
        {
            counts_morse_arr[1]++;
        }
        i++;
    }
}

void morse_statistics (int *counts_morse_arr){ //for morse statistics

        printf("\n\nDOT COUNT(s) : %d\nDASH COUNT(s) : %d\n\n", counts_morse_arr[1], counts_morse_arr[0]);
        history = fopen("history.txt", "a");
        fprintf(history, "\n\nDOT COUNT(s) : %d\nDASH COUNT(s) : %d\n\n", counts_morse_arr[1], counts_morse_arr[0]);

}



void freemem(tnode* start) //release memory
{
    if ( start != NULL )
        {
            freemem (start -> right);
            freemem (start -> left);
            free(start);
        }
    
    return;
}