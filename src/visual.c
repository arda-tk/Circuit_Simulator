#include <stdio.h>
#include <stdlib.h>
#include "../include/visual.h"
#include "../include/calculator.h"
#include <string.h>

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

void testResistive(void)
{
    puts("adding components");
    for(int i=0; i<7; i++)
    {
        addComponent();
    }

    puts("components have been added");

    puts("initializing component sequence");
    int *ptrOne = (int *) malloc(3 * sizeof(int));
    *ptrOne = 1;
    *(ptrOne + 1) = 2;

    int *ptrTwo = (int *) malloc(4 * sizeof(int));
    *ptrTwo = 2;
    *(ptrTwo + 1) = 3;
    *(ptrTwo + 2) = 4;

    int *ptrThree = (int *) malloc(4 * sizeof(int));
    *ptrThree = 4;
    *(ptrThree + 1) = 5;
    *(ptrThree + 2) = 6;

    int *ptrFour = (int *) malloc(3 * sizeof(int));
    *ptrFour = 6;
    *(ptrFour + 1) = 7;

    int *ptrFive = (int *) malloc(5 * sizeof(int));
    *ptrFive = 1;
    *(ptrFive + 1) = 3;
    *(ptrFive + 2) = 5;
    *(ptrFive + 3) = 7;
    puts("component sequence has been initialized");

    puts("initializing terminal sequence");
    boolean *BptrOne = (boolean *) malloc(2 * sizeof(int));
    *BptrOne = INPUT;
    *(BptrOne + 1) = INPUT;

    boolean *BptrTwo = (boolean *) malloc(3 * sizeof(int));
    *BptrTwo = OUTPUT;
    *(BptrTwo + 1) = INPUT;
    *(BptrTwo + 2) = INPUT;

    boolean *BptrThree = (boolean *) malloc(3 * sizeof(int));
    *BptrThree = OUTPUT;
    *(BptrThree + 1) = INPUT;
    *(BptrThree + 2) = INPUT;

    boolean *BptrFour = (boolean *) malloc(2 * sizeof(int));
    *BptrFour = OUTPUT;
    *(BptrFour + 1) = INPUT;

    boolean *BptrFive = (boolean *) malloc(4 * sizeof(int));
    *BptrFive = OUTPUT;
    *(BptrFive + 1) = OUTPUT;
    *(BptrFive + 2) = OUTPUT;
    *(BptrFive + 3) = OUTPUT;
    puts("terminal sequence has been initialized");

    puts("combining nodes");
    combineNode(ptrOne, BptrOne, 2);
    combineNode(ptrTwo, BptrTwo, 3);
    combineNode(ptrThree, BptrThree, 3);
    combineNode(ptrFour, BptrFour, 2);
    combineNode(ptrFive, BptrFive, 4);
    puts("nodes have been combined");

    puts("initializing ground node");
    initializeGND(1, OUTPUT);
    puts("ground node has been initialized");

    puts("Here comes the node information on the circuit...\n");
    compInfo *comp = createSearchComponent();

    for(int i=0; i<countComponentNumber(); i++)
    {
        printf("node IDs for component %d are--> in:%d - out:%d\n", comp->componentID,
               comp->inputNodeID->nodeID, comp->outputNodeID->nodeID);

        comp = comp->nextComponent;
    }

    uniqueNodeData nodeData = countUniqueNodeNumber();

    printf("number of unique nodes are %d\n", nodeData.uniqueNodeCount);
    for(int i=0; i<nodeData.uniqueNodeCount; i++)
    {
        printf("%d ,", *(nodeData.uniqueNodeList + i));
    }
    puts (" ");

    puts("will not try to initialize known voltage values");
    initializeNodeVoltages();

    nodeConnectionData *pullUnknownVoltages;
    pullUnknownVoltages = nodesOfUnknownVoltage(); //request data of nodes with unknown voltages
    sortNodeID(pullUnknownVoltages->listOfComponentID, pullUnknownVoltages->numberOfComponents); //sort

    compInfo *comp2 = createSearchComponent();

    for(int i=0; i<countComponentNumber(); i++)
    {
        printf("voltages for component %d are--> in:%f - out:%f\n", comp2->componentID,
               comp2->inputNodeID->nodeVoltage, comp2->outputNodeID->nodeVoltage);

        comp2 = comp2->nextComponent;
    }

    calcInfo *res;
    res = getNodeEquation();

    puts("conductance matrix");
    for(int i=0; i<res->matrixSize; i++)
    {
        printf("%f and %f\n", res->conductanceMatrix[i][0], res->conductanceMatrix[i][1]);
    }
    printf("current matrix\n%f and %f\n", res->currentMatrix[0], res->currentMatrix[1]);

    float **inverseMatrix = (float **) malloc(res->matrixSize * sizeof(float *));
    for (int i = 0; i < res->matrixSize; i++) {
        inverseMatrix[i] = (float *) malloc(res->matrixSize * sizeof(float));
    }
    float *voltageVector = (float *) malloc(res->matrixSize * sizeof(float));

    inverse_matrix(res->conductanceMatrix, inverseMatrix, res->matrixSize);
    matrix_vector_multiply(inverseMatrix, res->currentMatrix, voltageVector, res->matrixSize);

    printf("\n\n\n\nnode voltages test: %f, %f\n\n", *voltageVector, *(voltageVector + 1));
    for(int i=0; i<pullUnknownVoltages->numberOfComponents; i++)
    {

        setNodeVoltage(*(pullUnknownVoltages->listOfComponentID + i), *(voltageVector + i));
    }

    puts("\n\n\n\n\nHere are the analysis results:");
    compInfo *analysisResults = createSearchComponent();

    for(int i=0; i<countComponentNumber(); i++)
    {
        if(!strcmp(analysisResults->componentType, "resistor"))
        {
            printf("For the %s component of ID %d, current through it is %f\n"
                   "and potential difference between its terminals is %f\n"
                   "inVoltage: %f, outVoltage: %f\n\n",
                   analysisResults->componentType, analysisResults->componentID,
                   ((analysisResults->inputNodeID->nodeVoltage - analysisResults->outputNodeID->nodeVoltage) / analysisResults->componentValue),
                   (analysisResults->inputNodeID->nodeVoltage - analysisResults->outputNodeID->nodeVoltage),
                   analysisResults->inputNodeID->nodeVoltage, analysisResults->outputNodeID->nodeVoltage);
        }

        else if(!strcmp(analysisResults->componentType, "voltage"))
        {
            printf("For the %s component of ID %d\n"
                   "potential difference between its terminals is %f\n"
                   "inVoltage: %f, outVoltage: %f\n\n",
                   analysisResults->componentType, analysisResults->componentID,
                   (analysisResults->inputNodeID->nodeVoltage - analysisResults->outputNodeID->nodeVoltage),
                   analysisResults->inputNodeID->nodeVoltage, analysisResults->outputNodeID->nodeVoltage);
        }
        else if(!strcmp(analysisResults->componentType, "capacitor"))
        {
            printf("For the %s component of ID %d, current through it is 0\n"
                   "and potential difference between its terminals is %f\n"
                   "inVoltage: %f, outVoltage: %f\n\n",
                   analysisResults->componentType, analysisResults->componentID,
                   (analysisResults->inputNodeID->nodeVoltage - analysisResults->outputNodeID->nodeVoltage),
                   analysisResults->inputNodeID->nodeVoltage, analysisResults->outputNodeID->nodeVoltage);
        }
        else if(!strcmp(analysisResults->componentType, "inductor"))
        {
            printf("For the %s component of ID %d, current through it is INFINITE\n"
                   "and potential difference between its terminals is %f\n"
                   "inVoltage: %f, outVoltage: %f\n\n",
                   analysisResults->componentType, analysisResults->componentID,
                   (analysisResults->inputNodeID->nodeVoltage - analysisResults->outputNodeID->nodeVoltage),
                   analysisResults->inputNodeID->nodeVoltage, analysisResults->outputNodeID->nodeVoltage);
        }
        else
        {
            puts("error during displaying the results");
        }

        analysisResults = analysisResults->nextComponent;
    }

    puts(" ");
}

void testRLC(void)
{
    puts("adding components");
    for(int i=0; i<5; i++)
    {
        addComponent();
    }
    puts("components have been added");

    puts("initializing component sequence");

    int *ptrOne = (int *) malloc(3 * sizeof(int));
    *ptrOne = 1;
    *(ptrOne + 1) = 2;

    int *ptrTwo = (int *) malloc(4 * sizeof(int));
    *ptrTwo = 2;
    *(ptrTwo + 1) = 3;
    *(ptrTwo + 2) = 4;

    int *ptrThree = (int *) malloc(4 * sizeof(int));
    *ptrThree = 4;
    *(ptrThree + 1) = 5;

    int *ptrFour = (int *) malloc(4 * sizeof(int));
    *ptrFour = 1;
    *(ptrFour + 1) = 3;
    *(ptrFour + 2) = 5;
    puts("component sequence has been initialized");

    puts("initializing terminal sequence");
    boolean *BptrOne = (boolean *) malloc(2 * sizeof(int));
    *BptrOne = INPUT;
    *(BptrOne + 1) = INPUT;

    boolean *BptrTwo = (boolean *) malloc(3 * sizeof(int));
    *BptrTwo = OUTPUT;
    *(BptrTwo + 1) = INPUT;
    *(BptrTwo + 2) = INPUT;

    boolean *BptrThree = (boolean *) malloc(3 * sizeof(int));
    *BptrThree = OUTPUT;
    *(BptrThree + 1) = INPUT;

    boolean *BptrFour = (boolean *) malloc(2 * sizeof(int));
    *BptrFour = OUTPUT;
    *(BptrFour + 1) = OUTPUT;
    *(BptrFour + 2) = OUTPUT;
    puts("terminal sequence has been initialized");

    puts("combining nodes");
    combineNode(ptrOne, BptrOne, 2);
    combineNode(ptrTwo, BptrTwo, 3);
    combineNode(ptrThree, BptrThree, 2);
    combineNode(ptrFour, BptrFour, 3);
    puts("nodes have been combined");

    puts("initializing ground node");
    initializeGND(1, OUTPUT);
    puts("ground node has been initialized");

    puts("Here comes the node information on the circuit...\n");
    compInfo *comp = createSearchComponent();

    for(int i=0; i<countComponentNumber(); i++)
    {
        printf("node IDs for component %d are--> in:%d - out:%d\n", comp->componentID,
               comp->inputNodeID->nodeID, comp->outputNodeID->nodeID);

        comp = comp->nextComponent;
    }

    uniqueNodeData nodeData = countUniqueNodeNumber();

    printf("number of unique nodes are %d\n", nodeData.uniqueNodeCount);
    for(int i=0; i<nodeData.uniqueNodeCount; i++)
    {
        printf("%d ,", *(nodeData.uniqueNodeList + i));
    }
    puts (" ");

    puts("will not try to initialize known voltage values");

    initializeNodeVoltages();

    nodeConnectionData *pullUnknownVoltages;
    pullUnknownVoltages = nodesOfUnknownVoltage(); //request data of nodes with unknown voltages
    sortNodeID(pullUnknownVoltages->listOfComponentID, pullUnknownVoltages->numberOfComponents); //sort

    compInfo *comp2 = createSearchComponent();

    for(int i=0; i<countComponentNumber(); i++)
    {
        printf("voltages for component %d are--> in:%f - out:%f\n", comp2->componentID,
               comp2->inputNodeID->nodeVoltage, comp2->outputNodeID->nodeVoltage);

        comp2 = comp2->nextComponent;
    }

    calcInfo *res;
    res = getNodeEquation();

    puts("conductance matrix");
    for(int i=0; i<res->matrixSize; i++)
    {
        printf("%f and %f\n", res->conductanceMatrix[i][0], res->conductanceMatrix[i][1]);
    }
    printf("current matrix\n%f and %f\n", res->currentMatrix[0], res->currentMatrix[1]);

    float **inverseMatrix = (float **) malloc(res->matrixSize * sizeof(float *));
    for (int i = 0; i < res->matrixSize; i++) {
        inverseMatrix[i] = (float *) malloc(res->matrixSize * sizeof(float));
    }
    float *voltageVector = (float *) malloc(res->matrixSize * sizeof(float));

    inverse_matrix(res->conductanceMatrix, inverseMatrix, res->matrixSize);
    matrix_vector_multiply(inverseMatrix, res->currentMatrix, voltageVector, res->matrixSize);

    printf("\n\n\n\nnode voltages test: %f, %f\n\n", *voltageVector, *(voltageVector + 1));

    for(int i=0; i<pullUnknownVoltages->numberOfComponents; i++)
    {
        //printf("unknown voltage at node %d\n", *(pullUnknownVoltages->listOfComponentID + i));
        //printf("voltage vector value %f\n", *(voltageVector + i));
        setNodeVoltage(*(pullUnknownVoltages->listOfComponentID + i), *(voltageVector + i));
    }

    puts("\n\n\n\n\nHere are the analysis results:");
    compInfo *analysisResults = createSearchComponent();

    for(int i=0; i<countComponentNumber(); i++)
    {
        if(!strcmp(analysisResults->componentType, "resistor"))
        {
            printf("For the %s component of ID %d, current through it is %f\n"
                   "and potential difference between its terminals is %f\n"
                   "inVoltage: %f, outVoltage: %f\n\n",
                   analysisResults->componentType, analysisResults->componentID,
                   ((analysisResults->inputNodeID->nodeVoltage - analysisResults->outputNodeID->nodeVoltage) / analysisResults->componentValue),
                   (analysisResults->inputNodeID->nodeVoltage - analysisResults->outputNodeID->nodeVoltage),
                   analysisResults->inputNodeID->nodeVoltage, analysisResults->outputNodeID->nodeVoltage);
        }

        else if(!strcmp(analysisResults->componentType, "voltage"))
        {
            printf("For the %s component of ID %d\n"
                   "potential difference between its terminals is %f\n"
                   "inVoltage: %f, outVoltage: %f\n\n",
                   analysisResults->componentType, analysisResults->componentID,
                   (analysisResults->inputNodeID->nodeVoltage - analysisResults->outputNodeID->nodeVoltage),
                   analysisResults->inputNodeID->nodeVoltage, analysisResults->outputNodeID->nodeVoltage);
        }
        else if(!strcmp(analysisResults->componentType, "capacitor"))
        {
            printf("For the %s component of ID %d, current through it is 0\n"
                   "and potential difference between its terminals is %f\n"
                   "inVoltage: %f, outVoltage: %f\n\n",
                   analysisResults->componentType, analysisResults->componentID,
                   (analysisResults->inputNodeID->nodeVoltage - analysisResults->outputNodeID->nodeVoltage),
                   analysisResults->inputNodeID->nodeVoltage, analysisResults->outputNodeID->nodeVoltage);
        }
        else if(!strcmp(analysisResults->componentType, "inductor"))
        {
            printf("For the %s component of ID %d, current through it is INFINITE\n"
                   "and potential difference between its terminals is %f\n"
                   "inVoltage: %f, outVoltage: %f\n\n",
                   analysisResults->componentType, analysisResults->componentID,
                   (analysisResults->inputNodeID->nodeVoltage - analysisResults->outputNodeID->nodeVoltage),
                   analysisResults->inputNodeID->nodeVoltage, analysisResults->outputNodeID->nodeVoltage);
        }
        else
        {
            puts("error during displaying the results");
        }

        analysisResults = analysisResults->nextComponent;
    }

    puts(" ");

}