/*
 * Graph search
 * 
 * Data Structures
 * 
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

/* 최대 vertex 10, 번호 0~9 */
/* 탐색시 여러 Edge 있을 경우 번호 작은 vertex 먼저 탐색 */
#include <stdio.h>
#include <stdlib.h>

int main(){
    char command;
    printf("[----- [한민우] [2018038047] -----]\n");
    do{
        printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                         Graph Searches                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Graph     = z                                       \n");
		printf(" Insert Vertes        = v       Insert Edge                 = e \n");
		printf(" Depth First Search   = d       Breath First Search         = b \n");
		printf(" Print Graph          = p       Quit                        = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

        switch(command){
            /* Initialize graph */
            case 'z': case 'Z':

            break;
            /* Quit */
            case 'q': case 'Q':

            break;
            /* Insert Vertes */
            case 'v': case 'V':

            break;
            /* Insert Edge */
            case 'e': case 'E':

            break;
            /* Depth first search */
            case 'd': case 'D':

            break;
            /* Breath first search */
            case 'b': case 'B':

            break;
            /* print graph */
            case 'p': case 'P':

            break;

        }
    }while(command != 'q' && command != 'Q');
    return 1;
}