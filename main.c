// FIXME set default character set to UTF-8

/**
* Simple Analog Circuit Simulator Coded in C
*
* Group Members:
*               Arda Tanil Kersu
*               Zehra Deniz Salman
*               Can Rollas
*
* Advisor:
*         Abdurrahman Gumus
*         Md Salam
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/component.h"
#include "../include/calculator.h"
#include "../include/topology.h"
#include "../include/visual.h"

int main()
{
    //navigate();

    //Topology test
    puts("adding components");
    for(int i=0; i<7; i++)
    {
        addComponent();
    }
    /*for(int i=0; i<5; i++)
    {
        addComponent();
    }*/
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
    /*int *ptrOne = (int *) malloc(3 * sizeof(int));
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
    *(ptrFour + 2) = 5;*/
    puts("component sequence has been initialized");

    printf("ptrOne is %d and %d\n", *ptrOne, *(ptrOne+1));
    printf("ptrThree is %d and %d and %d\n", *ptrThree, *(ptrThree+1), *(ptrThree+2));
    //

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
    /*boolean *BptrOne = (boolean *) malloc(2 * sizeof(int));
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
    *(BptrFour + 2) = OUTPUT;*/
    puts("terminal sequence has been initialized");

    puts("combining nodes");
    combineNode(ptrOne, BptrOne, 2);
    combineNode(ptrTwo, BptrTwo, 3);
    combineNode(ptrThree, BptrThree, 3);
    combineNode(ptrFour, BptrFour, 2);
    combineNode(ptrFive, BptrFive, 4);
    /*combineNode(ptrOne, BptrOne, 2);
    combineNode(ptrTwo, BptrTwo, 3);
    combineNode(ptrThree, BptrThree, 2);
    combineNode(ptrFour, BptrFour, 3);*/
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

    //transform_matrix(res->conductanceMatrix, res->matrixSize);
    //print_matrix(res->conductanceMatrix, res->matrixSize);

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

        /*printf("For the %s component of ID %d, current through it is %f\n"
               "and potential difference between its terminals is %f\n"
               "inVoltage: %f, outVoltage: %f\n\n",
               analysisResults->componentType, analysisResults->componentID,
               ((analysisResults->inputNodeID->nodeVoltage - analysisResults->outputNodeID->nodeVoltage) / analysisResults->componentValue),
               (analysisResults->inputNodeID->nodeVoltage - analysisResults->outputNodeID->nodeVoltage),
               analysisResults->inputNodeID->nodeVoltage, analysisResults->outputNodeID->nodeVoltage);*/

        analysisResults = analysisResults->nextComponent;
    }

    puts(" ");

    exit(EXIT_SUCCESS);
}
