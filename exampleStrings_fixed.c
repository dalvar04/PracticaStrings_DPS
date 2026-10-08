#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
 
char array1[] = "Foo" "bar";
char array2[] = { 'F', 'o', 'o', 'b', 'a', 'r', '\0' };

#define MAX_SIZE 1024
 
const char* s1 = "\nHello\nWorld\n";
const char* s2 = "\nHello\nWorld\n";

void get_dirname(void) {

  char directory[MAX_SIZE];
  if(getcwd(directory, sizeof(directory)) != NULL) {
      printf("Current working directory: %s\n", directory);
  } else {
      fprintf(stderr,"getcwd() error - Directory too long\n");
  }
}
 
void get_y_or_n(void) {  
	
    char response[8];
    int counter=0;

	do {
        printf("Continue? [y] n: ");

        if (fgets(response, sizeof(response), stdin) == NULL) {
            fprintf(stderr, "fgets() error\n");
            return;
        }

        response[strlen(response)-1]='\0';

        if (response[0] != 'y' && response[0] != 'Y' &&
            response[0] != 'n' && response[0] != 'N') {
            printf("Invalid response. Please enter 'y' or 'n'.\n");
            counter++;
        }

    } while (response[0] != 'y' && response[0] != 'Y' &&
             response[0] != 'n' && response[0] != 'N' && counter < 5);

    if (response[0] == 'n' || response[0] == 'N' || counter >= 5) {
        printf("Exiting program.\n");
        exit(0);
    } 

}

void get_parameters(int params){
    
    if(params != 3) {
        printf("Usage: <executable> <param1> <param2>\n");
        exit (1);
    }
}

int main(int argc, char *argv[]){


    char key[MAX_SIZE];
    char array3[16];
    char array4[16];
    char array5 []  = "01234567890123456";
    char ptr_char [] = "new string literal";

    get_parameters(argc);
    get_dirname();
  
    if (snprintf(key, sizeof(key), "%s = %s", argv[1], argv[2]) >= (int)sizeof(key)) {
        fprintf(stderr,"snprintf() error - Key too long\n");
        return 1;
    }
    
    get_y_or_n();

    printf ("%s\n",array1);
    printf ("%s\n",array2);
 
    puts (s1);
    printf ("\n");
    puts (s2);
    printf ("\n");
    
    //strncpy(array3, array5, sizeof(array3));
    strncpy(array3, array5, sizeof(array3)-1);
    array3[sizeof(array3) - 1] = '\0';

    //strncpy(array4, array3, strlen(array3));
    strncpy(array4, array3, sizeof(array4) - 1);
    array4[sizeof(array4) - 1] = '\0';
    
    ptr_char [0] = 'N';
    printf ("%s\n",ptr_char);
    array5 [0] = 'M';

    return 0;
}
