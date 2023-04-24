#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "../include/component.h"
#include "../include/calculator.h"

enum OOM {
    p = -12,
    n = -9,
    u = -6,
    m = -3,
    N = 1,
    k = 3,
    M = 6,
    G = 9,
    T = 12
}; //ORDERS OF MAGNITUDES
enum source {
    AC, DC
}; //SOURCE TYPE
enum componentType {
    O, F, H, V
}; //OHM, FARAD, HENRY, VOLT

char *unit[4] = {"resistor", "capacitor", "inductor", "voltage"};

nodeInfo *headNode = NULL;
nodeInfo *currentNode = NULL;
compInfo *headComponent = NULL;
compInfo *currentComponent = NULL;

/*
 * input: void
 * output: number of components in the circuit
 *
 * initializes an empty search variable as head node,
 * and loops through the linked list to count the number
 * of components
 */
int countComponentNumber(void)
{
    int retVal; //return value

    if (headComponent == NULL) //if no component is available
        retVal = 0;
    else {
        retVal = 1; //set default return value to one if any component exists at all
        currentComponent = headComponent;
        while (currentComponent->nextComponent != NULL) //iterate until the last component
        {
            currentComponent = currentComponent->nextComponent;
            retVal++; //increase retVal if more components are found
        }
    }

    return retVal; //return the number of components
}

/*
 * input: void
 * output: number of trivial nodes
 *
 * number of trivial nodes is equal to two times the number
 * of components, because each component is assigned two
 * trivial node IDs to their terminals by default
 */
int countTrivialNodeNumber(void)
{
    return (2 * countComponentNumber()); //return two times the component number
}

/*
 * input: pointer to a circuit component
 * output: void
 *
 * initializes the short-circuit and open-circuit status
 * of resistor type components as FALSE
 */
void initializeResistor(compInfo *resistor)
{
    resistor->compOpenStatus = FALSE; //set open status FALSE for resistor
    resistor->compShortStatus = FALSE; //set short status FALSE for resistor
}

/*
 * input: pointer to a circuit component
 * output: void
 *
 * initializes the short-circuit status of capacitor type
 * components to FALSE and open-circuit status to TRUE
 */
void initializeCapacitor(compInfo *capacitor)
{
    capacitor->compOpenStatus = TRUE; //set open status TRUE for capacitor
    capacitor->compShortStatus = FALSE; //set short status FALSE for capacitor
    capacitor->componentValue = (float)calMag(T); //set value very close to INFINITY
}

/*
 * input: pointer to a circuit component
 * output: void
 *
 * initializes the short-circuit status of inductor type
 * components to TRUE and open-circuit status to FALSE
 */
void initializeInductor(compInfo *inductor)
{
    inductor->compOpenStatus = FALSE; //set open status FALSE for inductor
    inductor->compShortStatus = TRUE; //set short status TRUE for inductor
    inductor->componentValue = (float) calMag(p); //set value very close to zero
}

/*
 * input: void
 * output: component type in a single character such as
 * R, F, H or V
 *
 * takes user input such as "1000 pF" to add components
 * to the circuit. Parses the string into "1000", "p" and
 * "F", as in component value, order of magnitude, and
 * component type. appends the component to the linked list
 */
char addComponent(void)
{
    char componentValue[COMPVALUESIZE]; //holds input string such as "1000 pF"
    float value; //holds "1000"
    char order, type; //holds "p" and "F" respectively, as an example of pico-farads

    compInfo *returnComponent = (compInfo *) malloc(sizeof(compInfo)); //create new component
    returnComponent->nextComponent = headComponent; //point it to old head
    headComponent = returnComponent; //assign it as new head

    nodeInfo *returnNodeOne = (nodeInfo *) malloc(sizeof(nodeInfo)); //create input node for new component
    nodeInfo *returnNodeTwo = (nodeInfo *) malloc(sizeof(nodeInfo)); //create output node for new component

    returnNodeOne->nodeID = 2 * countComponentNumber() - 1; //trivial node number assigned to input node
    returnNodeTwo->nodeID = returnNodeOne->nodeID + 1; //(input node + 1) assigned to output node

    returnNodeOne->GNDstatus = FALSE; //both nodes are NOT grounded by default
    returnNodeTwo->GNDstatus = FALSE;

    returnNodeOne->nodeVoltage = (float)NAN; //both node voltages assigned "Not a Number" by default
    returnNodeTwo->nodeVoltage = (float)NAN;

    returnComponent->inputNodeID = returnNodeOne; //assign input node
    returnComponent->outputNodeID = returnNodeTwo; //assign output node

    returnComponent->componentID = countComponentNumber(); //assign component ID

    printf("Enter component value (ex: 1000 pF) >>> "); //get user input for component parameters
    fgets(componentValue, sizeof(componentValue) - 1, stdin);
    sscanf(componentValue, "%f %c%c", &value, &order, &type);

    switch (type) //initialize component information depending on their types
    {
        case 'O':
            strcpy(returnComponent->componentType, unit[O]);
            initializeResistor(returnComponent);

            switch (order)
            {
                case 'p':
                    returnComponent->componentValue = value * calMag(p);
                    break;
                case 'n':
                    returnComponent->componentValue = value * calMag(n);
                    break;
                case 'u':
                    returnComponent->componentValue = value * calMag(u);
                    break;
                case 'm':
                    returnComponent->componentValue = value * calMag(m);
                    break;
                case 'N':
                    returnComponent->componentValue = value * calMag(N);
                    break;
                case 'k':
                    returnComponent->componentValue = value * calMag(k);
                    break;
                case 'M':
                    returnComponent->componentValue = value * calMag(M);
                    break;
                case 'G':
                    returnComponent->componentValue = value * calMag(G);
                    break;
                case 'T':
                    returnComponent->componentValue = value * calMag(T);
                    break;
                default:
                    puts("component value failed to identify.");
                    exit(EXIT_FAILURE);
            }
            break;

        case 'F':
            strcpy(returnComponent->componentType, unit[F]);
            initializeCapacitor(returnComponent);
            break;

        case 'H':
            strcpy(returnComponent->componentType, unit[H]);
            initializeInductor(returnComponent);
            break;

        case 'V':
            strcpy(returnComponent->componentType, unit[V]);

            switch (order)
            {
                case 'p':
                    returnComponent->componentValue = value * calMag(p);
                    break;
                case 'n':
                    returnComponent->componentValue = value * calMag(n);
                    break;
                case 'u':
                    returnComponent->componentValue = value * calMag(u);
                    break;
                case 'm':
                    returnComponent->componentValue = value * calMag(m);
                    break;
                case 'N':
                    returnComponent->componentValue = value * calMag(N);
                    break;
                case 'k':
                    returnComponent->componentValue = value * calMag(k);
                    break;
                case 'M':
                    returnComponent->componentValue = value * calMag(M);
                    break;
                case 'G':
                    returnComponent->componentValue = value * calMag(G);
                    break;
                case 'T':
                    returnComponent->componentValue = value * calMag(T);
                    break;
                default:
                    puts("component value failed to identify.");
                    exit(EXIT_FAILURE);
            }
            break;

        default:
            puts("component type failed to identify."); //print error message if component failed to identify
            exit(EXIT_FAILURE);
    }

    return type; //return the type of component whether its a resistor, capacitor, ...
}

/*
 * input: void
 * output: void
 *
 * removes the last component added to the circuit
 */
void removeLastComponent(void)
{
    headComponent = headComponent->nextComponent; //remove last component
}

/*
 * input: void
 * output: unique node ID
 *
 * generates a new and unique ID to be assigned to
 * junction points as a unique node ID. uses a static
 * variable to keep track of the largest node ID, increments
 * it by one in every operation to make sure it is unique
 */
int generateStaticNodeID(void)
{
    int newNodeID = countTrivialNodeNumber(); //basis for new unique node ID is the largest trivial node ID
    static int staticCounter = 0; //static counter to make sure every new node ID generated is unique
    int retVal; //return value

    staticCounter++; //increase static variable to produce different and unique node IDs at every function call

    retVal = newNodeID + staticCounter; //newly created unique node ID

    return retVal; //return unique node ID
}

/*
 * input: an array of component IDs, array of terminal types,
 * and number of components to be connected
 * output: void
 *
 * takes the array of component IDs, as well as array of terminal
 * types, and depending on whether the terminals are input or
 * output, makes the connection.
 *
 * example: component IDs: 1,2 terminal types: INPUT, OUTPUT,
 * number of components: 2
 * --> connect input terminal of component 1 to output terminal
 * of component 2
 */
void combineNode(int *componentSequence, boolean *terminalSequence, int componentNumber)
{
    int staticNodeID = generateStaticNodeID(); //generate unique node ID to assign to junction point

    puts("trying to combine the nodes of components of IDs:");
    for(int i=0; i<componentNumber; i++) //list components to be connected, for debugging purposes, can be commented out
    {
        printf("%d, ", *(componentSequence + i));
    }
    puts(" "); //newline

    for(int i=0; i<componentNumber; i++) //for however many components that are to be connected
    {
        compInfo *comp = findComponentByID(*(componentSequence + i)); //locate components one by one

        if(*(terminalSequence + i) == INPUT) //if input terminal is to be connected
        {
            comp->inputNodeID->nodeID = staticNodeID; //assign unique node ID
        }
        else if(*(terminalSequence + i) == OUTPUT) //if output terminal is to be connected
        {
            comp->outputNodeID->nodeID = staticNodeID; //assign unique node ID
        }
    }
}

/*
 * input: void
 * output: pointer to head component
 *
 * creates pointer to component model, and initializes it as
 * the head component, helps ease the development of searching
 * through linked list that stores the components
 */
compInfo *createSearchComponent(void)
{
    compInfo *searchComponent = (compInfo *) malloc(sizeof(compInfo)); //allocate memory for dummy variable
    searchComponent = headComponent; //initialize as head of the linked list, that stores the components

    return searchComponent; //return the address
}

/*
 * input: component ID
 * output: pointer to the component of relevant ID
 *
 * loops through the linked list of available components
 * and checks the list to find which component matches input ID
 * returns the address of the component model
 */
compInfo *findComponentByID(int compID)
{
    compInfo *searchComponent = createSearchComponent(); //create search variable
    int check = 0; //loop-stop variable

    while (check == 0) //loop through available circuit components until component of ID "compID" is found
    {
        if (searchComponent->componentID != compID) //if not found
        {
            searchComponent = searchComponent->nextComponent; //keep searching through the list
        }
        else //if found
        {
            check = 1; //exit loop
        }
    }

    return (searchComponent); //return the address of the component found
}

/*
 * input: node ID of choice, voltage to be assigned
 * output: void
 *
 * loops through the linked list of components, checks their
 * input and output node IDs, it any nodes match the input
 * parameters, sets their nodeVoltage property to input parameter
 * of node voltage value
 */
void setNodeVoltage(int nodeID, float nodeVoltage)
{
    compInfo *comp = createSearchComponent(); //create search variable

    printf("setNodeVoltage: node of interest is of ID %d\n", nodeID);

    for(int i=0; i<countComponentNumber(); i++) //check all components in the circuit
    {
        printf("checking for component of ID %d\n", comp->componentID);
        if(comp->inputNodeID->nodeID == nodeID) //if "nodeID" is found at input terminal
        {
            puts("found at input node");
            comp->inputNodeID->nodeVoltage = nodeVoltage; //set the voltage to "nodeVoltage"
        }
        else if(comp->outputNodeID->nodeID == nodeID) //if "nodeID" is found at output terminal
        {
            puts("found at output node");
            comp->outputNodeID->nodeVoltage = nodeVoltage; //set the voltage to "nodeVoltage"
        }
        else //if function produces error, display error message
        {
            puts("F: component has no terminal connected to a voltage source");
        }

        comp = comp->nextComponent; //switch to next component at every cycle of the loop
    }
}

/*
 * input: component ID of choice, terminal type of choice
 * output: node ID that will be set as GND
 *
 * takes a component ID and either of INPUT or OUTPUT terminal,
 * then returns the node ID of that components specified terminal
 * so it can later be referred in the code as GND node
 */
int labelAsGround(int compID, boolean terminal)
{
    compInfo *comp = findComponentByID(compID); //locate the component to have one of its terminals labeled as GND
    int nodeID; //return value, which is the node ID that is labeled as GND

    if(terminal == INPUT) //if input terminal of the component is to be grounded
    {
        nodeID = comp->inputNodeID->nodeID; //store input node ID
    }
    else if(terminal == OUTPUT) //if output terminal of the component is to be grounded
    {
        nodeID = comp->outputNodeID->nodeID; //store output node ID
    }

    return nodeID; //return the node ID, in other words, "label" the node
}

/*
 * input: component ID of choice, terminal type of choice
 * output: void
 *
 * pulls the node ID that is labeled as GND in the function above
 * and initializes it as ground by setting GNDstatus to TRUE,
 * node ID to zero (which is reserved for GND nodes), and the
 * node voltage to zero
 */
void initializeGND(int compID, boolean terminal)
{
    int nodeToGround = labelAsGround(compID, terminal); //get the ID of the node labeled as GND

    compInfo *testComp = findComponentByID(compID); //locate the component

    //printf("node to be labeled as ground has node ID of %d\n", nodeToGround);
    //printf("comp ID = %d, inNode:%d, outNode:%d\n", compID, testComp->inputNodeID->nodeID, testComp->outputNodeID->nodeID);

    compInfo *comp = createSearchComponent(); //create search variable

    for(int i=0; i<countComponentNumber(); i++) //for every component in the circuit
    {
        if(comp->inputNodeID->nodeID == nodeToGround) //if their input node matches the labeled node ID, connect them to GND
        {
            comp->inputNodeID->nodeVoltage = (float)0; //set node voltage to zero
            comp->inputNodeID->GNDstatus = TRUE; //set GND status to TRUE
            comp->inputNodeID->nodeID = 0; //set node ID to zero, which is reserved for GND node
        }
        else if(comp->outputNodeID->nodeID == nodeToGround) //if their output node matches the labeled node ID, connect to GND
        {
            comp->outputNodeID->nodeVoltage = (float)0; //set node voltage to zero
            comp->outputNodeID->GNDstatus = TRUE; //set GND status to TRUE
            comp->outputNodeID->nodeID = 0; //set node ID to zero
        }
        else //in case of error, display error message
        {
            puts("F: could not find terminal to initialize as ground");
        }

        comp = comp->nextComponent; //cycle through components
    }
}

/*
 * input: component ID of choice
 * output boolean type return value indicating whether the
 * operation was successful or not
 *
 * during later functions in the code, for which one of them checks
 * if super node is present in the circuit, this function makes sure
 * to skip the voltage sources that are connected to ground to not
 * cause any algorithmic errors
 */
boolean skipVoltageToGND(int componentID)
{
    compInfo *comp = findComponentByID(componentID); //locate the component of interest
    boolean retVal = FALSE; //default return value is FALSE

    if(strcmp(comp->componentType, "voltage") == 0) //if component is voltage source
    {
        if((comp->inputNodeID->GNDstatus == TRUE) || (comp->outputNodeID->GNDstatus == TRUE)) //and if either of its terminals is connected to GND
        {
            retVal = TRUE; //return TRUE indicating that the component is a voltage source with one terminal connected to GND
        }
    }

    return retVal; //return whether it is TRUE or FALSE
}

/*
 * input: void
 * output: void
 *
 * loops through the linked list of available circuit components
 * and checks if it can do any voltage value initializations on nodes
 * if it can, it goes ahead and does
 *
 * example: if a voltage source has its negative end connected to GND
 * node and positive end connected to, lets say node ID of X, and the
 * voltage source is of value 10 Volts, it means that node X will have
 * a node voltage of 10 Volts. In such cases, this function does the
 * initializations wherever possible
 */
void initializeNodeVoltages(void)
{
    for(int i=0; i<countComponentNumber(); i++) //for every component in the circuit
    {
        compInfo *comp = findComponentByID(i+1); //locate them one by one

        if(skipVoltageToGND(comp->componentID)) //if component is a voltage source with one end connected to ground
        {
            if(comp->inputNodeID->GNDstatus == TRUE) //and if input terminal is grounded
            {
                setNodeVoltage(comp->outputNodeID->nodeID, comp->componentValue); //set voltage to all "node IDs"
            }
            else if(comp->outputNodeID->GNDstatus == TRUE) //and if output terminal is grounded
            {
                setNodeVoltage(comp->inputNodeID->nodeID, comp->componentValue); //set voltage to all "node IDs"
            }
        }
    }
}

/*
 * input: list of node IDs, a node ID of choice, and number of nodes
 * in the circuit
 * output: boolean value indicating whether uniqueness of the input node ID
 * is TRUE or FALSE. in case of any failure, returns ERROR
 *
 * loops through the list of node IDs provided, and checks the input node ID
 * to see if it matches any ID on the list. if a match is found, it means
 * that the ID of interest is not unique
 */
boolean uniqueNodeIdentifier(int *nodeIDptr, int nodeID, int currentNodeCount)
{
    boolean retVal = ERROR; // if default value returns, function is has produced an error
    int counter = 0; //count the number of nodes that do not match "nodeID"

    for (int i = 0; i < currentNodeCount; i++) //for all the elements in the list of node IDs
    {
        if (*(nodeIDptr + i) == nodeID) //if any ID in the list matches input "nodeID"
        {
            //puts("matching node found");
            retVal = FALSE; //input "nodeID" is not unique
            break;
        }
        else //if no match is found, keep looking
        {
            counter++; //keep count of non-matching cases
        }
    }

    if (counter == currentNodeCount) //if counter matches number of nodes present in the node ID list, input "nodeID" is unique
    {
        //puts("unique node found");
        retVal = TRUE; //input "nodeID" is unique
    }

    return retVal; //return uniqueness status
}

/*
 * input: node ID of choice
 * output: pointer to node model
 *
 * loops through the linked list of available components, and
 * checks their nodes to see if any of them match the input node ID
 * if match is found, returns a pointer to that specific node model
 * to allow for further operations on other properties of that node
 */
nodeInfo *findNodeInformation(int nodeID)
{
    nodeInfo *returnNode = (nodeInfo *) malloc(sizeof(nodeInfo)); //allocate memory for the node model to return
    compInfo *comp = createSearchComponent(); //create search variable

    for(int i=0; i<countComponentNumber(); i++) //for every component in the circuit
    {
        if(comp->inputNodeID->nodeID == nodeID) //if their input node matches "nodeID"
        {
            puts("F: findNodeInformation will pull input node data right now");
            returnNode = comp->inputNodeID; //store the entire "input node model" of the component
            break;
        }
        else if(comp->outputNodeID->nodeID == nodeID) //if their output node matches "nodeID"
        {
            puts("F: findNodeInformation will pull output node data right now");
            returnNode = comp->outputNodeID; //store the entire "output node model" of the component
            break;
        }

        comp = comp->nextComponent; //cycle through the components list
    }

    printf("F: pulled node data is of ID %d\n", returnNode->nodeID);

    return returnNode; //return the address of the node model of interest
}

/*
 * input: void
 * output: struct type variable called uniqueNodeData, see
 * the beginning of "component.h" for details of the struct
 *
 * loops through available circuit components and checks their
 * node IDs which may or may not be unique IDs. reviews the
 * node IDs of each component to check their "uniqueness" and if
 * any are found to be unique, stores them for later use. Also,
 * counts the number of unique nodes at the same time. Returns the
 * struct named uniqueNodeData which consists of two elements that
 * are: list of unique node IDs, number of unique nodes
 */
uniqueNodeData countUniqueNodeNumber(void)
{
    compInfo *comp = createSearchComponent(); //create search variable
    uniqueNodeData data; //struct that stores data of unique nodes, see component.h for details
    int *trivialNodes = (int *) calloc(countTrivialNodeNumber(), sizeof(int)); //allocate memory for trivial nodes
    int *uniqueNodes = (int *) malloc(countTrivialNodeNumber() * sizeof(int)); //allocate memory for unique nodes
    int uniqueCounter = 0; //count unique nodes

    for (int i = 0, j = 0; j < countComponentNumber(); j++, i = i + 2) //you need two variables in this for loop
        // "i" is for selecting terminals individually, "j" is for running the loop just enough times to check all components
    {
        //puts("F: looping through components");
        *(trivialNodes + i) = comp->inputNodeID->nodeID; //store all trivial node IDs in a pointer which has been allocated enough space
        *(trivialNodes + i + 1) = comp->outputNodeID->nodeID; //this is why "i = i+2" is essential, to take inputs at every loop, such
        //as --> (1,2), (3,4), (5,6).. etc.

        if (uniqueCounter == 0) //if first ever nodes are being checked, should default them as unique
        {
            //puts("F: first two nodes are set as unique by default");
            uniqueCounter += 2; //set number of unique nodes to two by default

            *uniqueNodes = *(trivialNodes + i); //initialize first 2 nodes as unique
            *(uniqueNodes + 1) = *(trivialNodes + i + 1);
        } else if (uniqueCounter > 0) //if unique nodes list is not empty
        {
            //puts("F: checking the rest of the nodes...");
            if (TRUE == uniqueNodeIdentifier(uniqueNodes, *(trivialNodes + i), uniqueCounter)) //is input node unique?
            {
                //puts("F: input node found to be unique");
                *(uniqueNodes + uniqueCounter) = *(trivialNodes + i); //if yes, store its node ID
                uniqueCounter++; //increase unique node count
            }

            if (TRUE ==
                uniqueNodeIdentifier(uniqueNodes, *(trivialNodes + i + 1), uniqueCounter)) //is output node unique?
            {
                //puts("F: output node found to be unique");
                *(uniqueNodes + uniqueCounter) = *(trivialNodes + i + 1); //if yes, store its node ID
                uniqueCounter++; //increase unique node count
            }
        }
        else //if an error occurs, display error message
        {
            puts("unique node identifier has failed");
        }

        comp = comp->nextComponent; //move to next component
        //puts("F: moving onto next components");
    }

    data.uniqueNodeList = (int *) malloc(uniqueCounter * sizeof(int)); //allocate just enough memory to store unique node IDs
    //puts("F: memory allocated for return struct");

    data.uniqueNodeList = uniqueNodes; //store unique node IDs
    //puts("F: assigned node list");
    data.uniqueNodeCount = uniqueCounter; //store unique node count
    //puts("F: assigned number of nodes");

    return data; //return unique node list and count
}

/*
 * input: node ID of choice
 * output: struct type variable called nodeConnectionData, see
 * the beginning of "component.h" for details of the struct
 *
 * for a specific node of interest, lists and returns all the
 * components' IDs that are connected to that node. Also returns
 * the total number of components connected to that node
 */
nodeConnectionData listComponentsOfNode(int nodeID)
{
    compInfo *comp = createSearchComponent(); //create search variable
    uniqueNodeData data; //store node data
    nodeConnectionData connectionData; //return value
    int componentCounter = 0; //count the number of components connected to "nodeID"

    data = countUniqueNodeNumber(); //pull node data

    int *componentIDlist = (int *) malloc(data.uniqueNodeCount * sizeof(int)); //allocate memory for component list

    for (int i = 0; i < countComponentNumber(); i++) //go through all components
    {
        if (comp->inputNodeID->nodeID == nodeID || comp->outputNodeID->nodeID == nodeID) //if node ID matches "nodeID"
        {
            *(componentIDlist + componentCounter) = comp->componentID; //store the components ID
            componentCounter++; //also keep count of the number of components
        }
        comp = comp->nextComponent; //loop through available components
    }

    connectionData.listOfComponentID = (int *) malloc(
            componentCounter * sizeof(int)); // allocate memory for component IDs

    connectionData.listOfComponentID = componentIDlist; //store list of component IDs
    connectionData.numberOfComponents = componentCounter; //store number of components connected to "nodeID"

    return connectionData; //return number of components connected to "node"ID" and their count
}

/*
 * input: node ID of choice
 * output: boolean value of TRUE or FALSE depending on
 * whether a super node is present in the circuit or not
 *
 * loops through the linked list of components, if a voltage
 * source is detected, checks whether it has one of its nodes
 * connected to ground. If voltage source does not have a
 * connection to GND, returns FALSE, otherwise (if supernode
 * is present) returns TRUE
 */
boolean checkSuperNode(int nodeID)
{
    compInfo *searchComponent = createSearchComponent(); //create search variable
    boolean retVal = FALSE; //return value is set to FALSE by default

    for (int i = 0; i < countComponentNumber(); i++) //for every component
    {
        if (searchComponent->inputNodeID->nodeID == nodeID ||
            searchComponent->outputNodeID->nodeID == nodeID) //check if component is connected to "nodeID"
        {

            if (strcmp(searchComponent->componentType, "voltage") == 0) //check if it is a voltage source
            {
                retVal = TRUE; //set the return value to TRUE
                break;
            }
        }
        else
        {
            searchComponent = searchComponent->nextComponent; //loop through components
        }
    }

    return retVal; //return the super node availability status of the circuit
}

/*
 * input: memory address where parallel components of a
 * given component are stored, number of parallel components
 * it has
 * output: same memory address as input, but larger
 *
 * in theory, there can exist infinitely many components,
 * that are connected in parallel to a given component. To
 * avoid allocating memory for a default upper limit of
 * maximum 10 parallel component IDs, per say, this function
 * changes the default size of the variable that stores
 * parallel component IDs, allocating adjacent memory blocks
 * in the memory to be able to store more parallel IDs
 */
int *needMoreMemory(int *memPtr, int numberOfComponents)
{
    memPtr = (int *) realloc(memPtr, (numberOfComponents - 1) * sizeof(int)); //reallocate the memory block to be larger

    return memPtr; //return the reallocated, larger, memory address
}

/*
 * input: node ID of choice
 * output: list of node IDs adjacent to input node
 *
 * the function pulls component IDs that are connected to
 * input node of interest, and returns a list of the other
 * nodes of each component
 */
int *extractNodeData(int nodeID) {
    compInfo *componentStorage; //variable to store individual components during some search algorithm
    nodeConnectionData nodeData; //store node data
    nodeData = listComponentsOfNode(nodeID); //pull component connection data to "node ID"

    int *nodeList = (int *) malloc(nodeData.numberOfComponents * sizeof(int)); //allocate memory for node list
    //int nodeCounter = 0;

    for(int i = 0; i<nodeData.numberOfComponents; i++) //for as many components as in the previously pulled node data
    {
        componentStorage = findComponentByID(*(nodeData.listOfComponentID+i)); //locate component of interest

        if(componentStorage->inputNodeID->nodeID == nodeID) //if node being checked is function parameter "nodeID"
        {
            *(nodeList+i) = componentStorage->outputNodeID->nodeID; //store the ID of its other terminal
        }
        else if(componentStorage->outputNodeID->nodeID == nodeID) //if node being checked is function parameter "nodeID"
        {
            *(nodeList+i) = componentStorage->inputNodeID->nodeID; //store the ID of its other terminal
        }
        else //display error message if function fails the operation
        {
            puts("unexpected error occurred during node data extraction");
        }
    }

    return nodeList; //return the list of components connected to "nodeID"
}

/*
 * input: void
 * output: struct type variable called nodeConnectionData, see
 * the beginning of "component.h" for details of the struct
 *
 * pulls node data in which all unique node IDs are listed, and
 * check each node to see if their voltage value is known. If any
 * are of unknown voltages, and needed to be found through analysis
 * it stores the node IDs of these nodes of unknown voltages. Returns
 * the list of node IDs, as well as the count of them
 */
nodeConnectionData *nodesOfUnknownVoltage(void)
{
    //float *listOfNodesToReturn = (float *) malloc(countTrivialNodeNumber() * sizeof(float));
    uniqueNodeData nodeData; //store node data
    int *nodeVoltageList = (int *) malloc(nodeData.uniqueNodeCount * sizeof(int)); //allocate memory to store node IDs of unknown node voltages
    int nodeCounter = 0; //count the unknown node voltages

    nodeData = countUniqueNodeNumber(); //pull node data

    puts("F: unknown voltage index of pulled node data will be displayed");

    for(int i=0; i<nodeData.uniqueNodeCount; i++) //this part displays unique node IDs for debugging purposes, can be commented out
    {
        printf("%d, ", *(nodeData.uniqueNodeList + i));
    }
    puts(" ");
    puts("pulled data should have been displayed now");

    for(int i=0; i<nodeData.uniqueNodeCount; i++) //for every one of however many unique nodes there are in the circuit
    {
        nodeInfo *pulledNodeInfo = findNodeInformation(*(nodeData.uniqueNodeList + i)); //pull their node information one by one at every loop cycle

        if(isnanf(pulledNodeInfo->nodeVoltage)) //is the value nanf ("Not a Number" of type "float"), in other words, is it of an unknown value?
        {
            puts("F: indexing an unknown voltage data *****");
            *(nodeVoltageList + nodeCounter) = *(nodeData.uniqueNodeList + i); //store in in the node ID list dedicated for indexing node IDs of unknown node voltages
            nodeCounter++; //keep count of how many unknown voltage nodes there are
        }
        else //if the node voltage is known, just proceed with the operation
        {
            puts("F: voltage is known, function will return safely");
        }
    }

    nodeConnectionData *returnData = (nodeConnectionData *) malloc(sizeof(nodeConnectionData)); //allocate enough memory to store

    returnData->listOfComponentID = nodeVoltageList; //pass unknown node voltage list to returning struct
    printf("F: UKVL: %d, %d\n", *returnData->listOfComponentID, *(returnData->listOfComponentID+1));
    returnData->numberOfComponents = nodeCounter; //pass the number of nodes to returning struct
    printf("F: UKVC: %d\n", returnData->numberOfComponents);

    return returnData; //return list of node IDs that are of unknown node voltages, and their count
}

/*
 * input: node ID of choice
 * output: node voltage
 *
 * for a given node ID, returns the node's voltage value
 */
float checkNodeVoltage(int nodeID)
{
    compInfo *comp = createSearchComponent(); //create search variable
    float retVal = (float)NAN; //return NAN by default

    for(int i=0; i<countComponentNumber(); i++) //for every circuit element
    {
        if(comp->inputNodeID->nodeID == nodeID) //if input node is of ID "nodeID"
        {
            retVal = comp->inputNodeID->nodeVoltage; //store input nodes voltage value
            break;
        }
        else if(comp->outputNodeID->nodeID == nodeID) //if output node is of ID "nodeID"
        {
            retVal = comp->outputNodeID->nodeVoltage; //store output nodes voltage value
            break;
        }
        else //if function fails operation, display error message
        {
            puts("error in function checkNodeVoltage()");
        }

        comp = comp->nextComponent; //switch to next circuit component
    }

    return retVal; //return the node voltage of "nodeID"
}

/*
 * input: array of integers, number of array elements, input
 * value of type integer of choice
 * output: index number of the input value, within the list
 *
 * for a given list of integers and a number of interest, searches
 * for the number within the list. returns the index of where the
 * number is within the list
 */
int extractIndexFromList(int *list, int listLength, int number)
{
    int count = 0; //initialize as zero, can also be changed with error codes of choice such as "-1" or which are "not expected" to be returned

    for(int i=0; i<listLength; i++) //for the number of elements in the list
    {
        if(*(list + i) == number) //if number is found within the list
        {break;} //stop counting

        count++; //keep counting until the number is found within the list
    }

    return count; //return the index value of the item in the list
}

/*
 * input: void
 * output: analysis results
 *
 * most complex function by far, pulls all required node and component
 * data to generate a conductance and a current matrix, performs matrix
 * operations on them to find the unknown node voltages. Refer to inline
 * comments in the function for more information
 */
calcInfo *getNodeEquation(void)
{
    uniqueNodeData nodeData; //store node data
    nodeData = countUniqueNodeNumber(); //pull node data
    sortNodeID(nodeData.uniqueNodeList, nodeData.uniqueNodeCount); //bubble sorting the node ID list is for easier development because this function is a bit longer
    //list of all unique nodes, and their count

    nodeConnectionData *unknownVoltageData; //store node IDs of unknown node voltage
    unknownVoltageData = nodesOfUnknownVoltage(); //pull unknown node voltage data
    sortNodeID(unknownVoltageData->listOfComponentID, unknownVoltageData->numberOfComponents); //sorting the list makes development easier
    //list of all unique nodes with unknown voltage values, and their count

    calcInfo *returnData = (calcInfo *) malloc(sizeof(calcInfo)); //return type, contains conductance and current matrices, see component.h for definition
    int matrixSize = unknownVoltageData->numberOfComponents; //pull the "arbitrary" matrix size, which is known by the program at this point of analysis

    //this is how to allocate memory for 2-Dimensional array manually
    returnData->conductanceMatrix = (float **) malloc(matrixSize * sizeof(float *)); //allocate "n" many pointers, which are the "rows" of the matrix
    for(int i=0; i<matrixSize; i++) //for every row allocated in the above line
        returnData->conductanceMatrix[i] = (float *) malloc(matrixSize * sizeof(float)); //allocate "n" many individual cells, which are "columns" of the individual rows
    returnData->currentMatrix = (float *) malloc(matrixSize * sizeof(float)); //current matrix is "n by 1" matrix so just allocate memory for "n" items
    returnData->matrixSize = matrixSize; //it is important to include matrix size in return value, so that matrix operation functions know the matrix size they are dealing with

    float equationCoefficients[unknownVoltageData->numberOfComponents][2]; //temporary space for storing rows of conductance data
    /*
     * the reason the array is 2 dimensional is because it indexes conductance values for individual node IDs separately, for example:
     *
     * node IDs: [ 1     2      3     4]
     * conduct.: [0.1   1.3   -0.67   0]
     *
     * same principle applies for the current matrix below
     */
    float currentMatrix[unknownVoltageData->numberOfComponents][2]; //temporary space for storing elements of current data

    for(int i=0; i<unknownVoltageData->numberOfComponents; i++) //initialize coefficient matrix
    {
        equationCoefficients[i][0] = (float)*(unknownVoltageData->listOfComponentID + i); //notice first row "[0]" is being assigned node IDs
        equationCoefficients[i][1] = (float)0; //and the second row "[1]" is being assigned default values of zero
        //equationCoefficients[i][1] = (float)checkNodeVoltage(*(nodeData.uniqueNodeList + i));
    }

    for(int i=0; i<unknownVoltageData->numberOfComponents; i++) //initialize current matrix
    {
        currentMatrix[i][0] = (float)*(unknownVoltageData->listOfComponentID + i); //notice first row is assigned node IDs
        currentMatrix[i][1] = (float)0; //and second row is initialized as zero as it was for "equationCoefficients"
        //currentMatrix[i][1] = (float)checkNodeVoltage(*(nodeData.uniqueNodeList + i));
    }

    float *coefMat = (float *) malloc(3 * sizeof(float)); //middle variable to transfer values from the two above matrices to return value
    float *curMat = (float *) malloc(3 * sizeof(float)); //above line is for conductance coefficients (matrix), this is for current matrix

    //up to here, it was the getting ready part, now the analysis takes place

    for(int i=0; i<unknownVoltageData->numberOfComponents; i++) //for however many nodes there are of unknown voltage values
    {
        nodeConnectionData componentsOfNode; //store node data
        componentsOfNode = listComponentsOfNode(*(unknownVoltageData->listOfComponentID + i)); //pull component IDs connected to current node
        sortNodeID(componentsOfNode.listOfComponentID, componentsOfNode.numberOfComponents); //sorting is good
        int countRowNumber = 0; //count the number of rows

        /*
         * display some info for debugging purposes, it is okay to leave these commented out
         *
         * printf("checking node ID of %d, with %d components connected to it\n", *(unknownVoltageData->listOfComponentID + i), componentsOfNode.numberOfComponents);
         * puts("F: inside the loop, pulled component connections of node data");
         * puts("F: will enter the inner loop of unknown voltages");
         */

        for(int j=0; j<componentsOfNode.numberOfComponents; j++) //this inner loop fills in values for one unknown node
        {
            compInfo *tempComp = findComponentByID(*(componentsOfNode.listOfComponentID + j)); //find each component connected to currently worked on node

            printf("analyzing component %d with nodes of in:%d, out:%d\n", tempComp->componentID, tempComp->inputNodeID->nodeID, tempComp->outputNodeID->nodeID);

            if(tempComp->inputNodeID->nodeID == *(unknownVoltageData->listOfComponentID + i)) //if input node of the component is in the unknown voltage list
            {
                //puts("just made it into the tempComp->inputNodeID->nodeID");
                if(!isnanf(tempComp->outputNodeID->nodeVoltage)) //is its other node assigned a voltage value?
                {
                    //get index in order to locate where to write in matrices
                    int index = extractIndexFromList(unknownVoltageData->listOfComponentID, unknownVoltageData->numberOfComponents, *(unknownVoltageData->listOfComponentID + i));

                    //write to current matrix because the voltage at components other end is known
                    currentMatrix[index][1] = currentMatrix[index][1] + (tempComp->outputNodeID->nodeVoltage / tempComp->componentValue);
                    //write to dedicated place in conductance matrix
                    equationCoefficients[index][1] = equationCoefficients[index][1] + (1 / tempComp->componentValue);
                }
                else if(isnanf(tempComp->outputNodeID->nodeVoltage)) //is its other node assigned an unknown voltage (NaN)?
                {
                    //get index..
                    int index = extractIndexFromList(unknownVoltageData->listOfComponentID, unknownVoltageData->numberOfComponents, tempComp->outputNodeID->nodeID);
                    //this time, write in conductance matrix instead of current matrix, because this is a node with unknown voltage value
                    equationCoefficients[index][1] = equationCoefficients[index][1] + ((-1) / tempComp->componentValue);

                    //get new index for the node being inspected in this cycle of the loop
                    index = extractIndexFromList(unknownVoltageData->listOfComponentID, unknownVoltageData->numberOfComponents, *(unknownVoltageData->listOfComponentID + i));
                    //write to dedicated place in conductance matrix
                    equationCoefficients[index][1] = equationCoefficients[index][1] + (1 / tempComp->componentValue);
                }
                else //display encouraging error message because this function is a bit tricky to put together
                {
                    puts("error occurred but keep up the good work");
                }
            }
            else if(tempComp->outputNodeID->nodeID == *(unknownVoltageData->listOfComponentID + i)) //if output node of the component is in the unknown voltage list
            {
                //puts("just made it into the tempComp->outputNodeID->nodeID");
                if(!isnanf(tempComp->inputNodeID->nodeVoltage)) //is its other node assigned a voltage value?
                {
                    //get index in order to locate where to write in matrices
                    int index = extractIndexFromList(unknownVoltageData->listOfComponentID, unknownVoltageData->numberOfComponents, *(unknownVoltageData->listOfComponentID + i));

                    //write to current matrix because the voltage at components other end is known
                    currentMatrix[index][1] = currentMatrix[index][1] + (tempComp->inputNodeID->nodeVoltage / tempComp->componentValue);
                    //write to dedicated place in conductance matrix
                    equationCoefficients[index][1] = equationCoefficients[index][1] + (1 / tempComp->componentValue);
                }
                else if(isnanf(tempComp->inputNodeID->nodeVoltage))
                {
                    //get index..
                    int index = extractIndexFromList(unknownVoltageData->listOfComponentID, unknownVoltageData->numberOfComponents, tempComp->inputNodeID->nodeID);
                    //this time, write in conductance matrix instead of current matrix, because this is a node with unknown voltage value
                    equationCoefficients[index][1] = equationCoefficients[index][1] + ((-1) / tempComp->componentValue);

                    //get new index for the node being inspected in this cycle of the loop
                    index = extractIndexFromList(unknownVoltageData->listOfComponentID, unknownVoltageData->numberOfComponents, *(unknownVoltageData->listOfComponentID + i));
                    //write to dedicated place in conductance matrix
                    equationCoefficients[index][1] = equationCoefficients[index][1] + (1 / tempComp->componentValue);
                }
                else //display another very encouraging error message
                {
                    puts("keep up the good work_2");
                }
            }
        }

        for(int runThrough=0; runThrough<unknownVoltageData->numberOfComponents; runThrough++) //runs through the arrays' elements
        {
            *(coefMat + runThrough) = equationCoefficients[runThrough][1]; //assign to conductance row pointer
            *(curMat + runThrough) = currentMatrix[runThrough][1]; //assign to current element pointer
        }
        for(int init=0; init<unknownVoltageData->numberOfComponents; init++) //clear the arrays for the next round of operation
        {
            equationCoefficients[init][1] = 0; //set all zero
            currentMatrix[init][1] = 0; //set all zero
        }

        for(int loop=0; loop<matrixSize; loop++) //pass conductance data to functions return element
        {
            returnData->conductanceMatrix[i][loop] = coefMat[loop]; //conductance data..
        }
        returnData->currentMatrix[i] = curMat[i]; //pass current data to functions return element

        //displaying for debugging purposes, can be commented out
        puts("coef matrix row is:");
        printf("%f\t%f\n", *(coefMat), *(coefMat+1));
        puts("current matrix element is:");
        printf("%f\n", *(curMat+i));
    }

    return returnData; //return conductance matrix and current matrix
}
