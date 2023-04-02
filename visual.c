#include <stdio.h>
#include <stdlib.h>
#include "../include/visual.h"

/*
 * input: void
 * output: void
 *
 * prints user manual which contains instructions
 * on how to use the terminal-based simulator
 */
void userManual()
{
    puts("The letters O, F, H, and V are for ohm, farad, henry, and volt respectively.\n\n"
         "Enter component values by leaving a space between the component value\n"
         "and its unit, such as: 220 pF, 20 mH, 100 kO, or 5 NV.");
}

/*
 * input: void
 * output: void
 *
 * prints an example layout of 8 by 12 board of 96
 * rectangles, this is supposed to give a sense of
 * "component slots" to viewer
 */
void initializeMap()
{
    for(int row=0; row<mapSizeRow; row++)
    {
        for(int mode=0; mode<3; mode++)
        {
            for(int draw=0; draw<mapSizeCol; draw++)
            {
                if(mode == 0)
                {
                    putchar(upperLeft);
                    putchar(horizontal);
                    putchar(horizontal);
                    putchar(horizontal);
                    putchar(upperRight);
                }
                else if(mode == 1)
                {
                    putchar(vertical);
                    putchar(whiteSpace);
                    putchar(whiteSpace);
                    putchar(whiteSpace);
                    putchar(vertical);
                }
                else if(mode == 2)
                {
                    putchar(lowerLeft);
                    putchar(horizontal);
                    putchar(horizontal);
                    putchar(horizontal);
                    putchar(lowerRight);
                }
            }
            printf("\n");
        }
    }
}

/*
 * input: void
 * output: boolean value depending on whether the program
 * has exited successfully or not
 *
 * displays main menu, sub-menus, and the switching between
 * them. Normally, this should be the only function called
 * inside "main.c"
 */
boolean navigate()
{
    char buffer[2], showUserManual;

    printf("Do you want to read the user manual? (y/n): ");
    fgets(buffer, sizeof(buffer), stdin); //get user input into buffer
    sscanf(buffer, "%c", &showUserManual); //assign buffer content to variable

    if(showUserManual == 'y')
        userManual(); //show user manual if "yes"
    fflush(stdin); //flush input stream
    puts("\n\n\n");


    char bufferSecond[2];
    int operation;
    boolean keepCodeRunning = TRUE;

    while(keepCodeRunning)
    {
        printf("Choose operation: \n\n"
               "1. add component\n2. un-add last component\n"
               "3. draw net between components\n4. start simulation\n"
               "5. exit simulator\n\n>>>");
        fgets(bufferSecond, sizeof(bufferSecond), stdin);
        sscanf(bufferSecond, "%d", &operation);
        fflush(stdin);
        system("cls");

        switch(operation)
        {
            case 1:
                {
                    char compType;
                    compType = addComponent();
                    switch(compType)
                    {
                        case 'O':
                            puts("Success!\nResistor was added");
                            break;
                        case 'F':
                            puts("Success!\nCapacitor was added");
                            break;
                        case 'H':
                            puts("Success!\nInductor was added");
                            break;
                        case 'V':
                            puts("Success!\nVoltage source was added");
                            break;
                        default:
                            puts("If this shows up on screen, there is a bug in component adding");
                            exit(EXIT_FAILURE);
                    }
                    break;
                }
            case 2:
                if(countComponentNumber() == 0)
                {
                    puts("Error!\nThere are no components to be removed");
                    break;
                }
                else
                {
                    removeLastComponent();
                    puts("Success!\nLast component added was removed");
                    break;
                }
            case 3:
                //drawNet();
                break;
            case 4:
                //run();
                break;
            case 5:
                puts("Simulator has successfully stopped");
                exit(EXIT_SUCCESS);
            default:
                printf("Error!\nOperation failed to identify, please choose again\n");
        }
    }
    return TRUE;
}

