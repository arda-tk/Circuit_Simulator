//
// Created by Arda on 14/3/2023.
//

#include "../include/component.h"
#include <stdlib.h>
#include <stdio.h>

/*
 * input: void
 * output: void
 *
 * loops through the linked list of circuit components, checks
 * each component if they have other components connected to
 * them in parallel, if finds any, stores their IDs in the dedicated
 * variable of component model. Notice how it makes use of
 * "needMoreMemory"
 */
void checkParallelConnections(void)
{
    compInfo *comp = createSearchComponent();
    int *parallelComponentList = (int *) malloc(10 * sizeof(int)); //store possible parallel component IDs
    int counter = 0;

    for(int i=0; i<countComponentNumber(); i++) //for every component
    {
        for(int j=0; j<countComponentNumber(); j++) //go through list to compare
        {
            compInfo *compareComp = findComponentByID((j)); //dummy var for comparison
            if(comp->componentID == compareComp->componentID) //if component is compared to itself
            {
                continue;
            }
            else if((comp->inputNodeID->nodeID == compareComp->inputNodeID->nodeID)
                    && (comp->outputNodeID->nodeID == compareComp->outputNodeID->nodeID)) //if parallel
            {
                parallelComponentList[counter] = compareComp->componentID; //store parallel component ID
                counter++;
            }
            else if((comp->outputNodeID->nodeID == compareComp->inputNodeID->nodeID)
                    && (comp->inputNodeID->nodeID == compareComp->outputNodeID->nodeID)) //if reverse parallel
            {
                parallelComponentList[counter] = compareComp->componentID; //store parallel component ID
                counter++;
            }
            else
            {
                printf("--> An error occurred during parallel check\n");
            }

            needMoreMemory(comp->parallel, counter); //allocate memory

            for(int k=0; k<counter; k++) //copy parallel elements to struct member
            {
                comp->parallel[k] = parallelComponentList[k];
            }

            //free memory and reset counter
            counter = 0;
            free(compareComp);
        }
    }
    free(parallelComponentList);
}

/*
 * loops through the linked list of circuit components, checks
 * each component if they have other components connected to
 * them in series, if finds any, stores their IDs in dedicated
 * variables of component model
 */
void checkSerialConnections(void)
{
    compInfo *comp = createSearchComponent();

    for(int i=0; i<countComponentNumber(); i++) //for every component
    {
        for(int j=0; j<countComponentNumber(); j++) //go through list to compare
        {
            compInfo *compareComp = findComponentByID((j));

            if(comp->componentID == compareComp->componentID) //if component is compared to itself
            {
                continue;
            }
            else if(comp->inputNodeID->nodeID == compareComp->outputNodeID->nodeID) //if serial to input terminal
            {
                comp->inputSerial = compareComp->componentID;
            }
            else if(comp->outputNodeID->nodeID == compareComp->inputNodeID->nodeID) //if serial to output terminal
            {
                comp->outputSerial = compareComp->componentID;
            }
            else
            {
                printf("--> An error occurred during serial check\n");
            }

            free(compareComp); //free dummy variable
        }
    }
}