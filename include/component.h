#ifndef _component_c_
#define _component_c_

#define COMPVALUESIZE 10

typedef enum booleanValues {FALSE, TRUE, ERROR} boolean;
typedef enum terminalValues {INPUT, OUTPUT} terminal;

typedef struct nodeInformation {
    int nodeID;
    boolean GNDstatus;
    float nodeVoltage;
} nodeInfo;

typedef struct componentInformation {
    int componentID;
    char componentType[10];
    float componentValue;
    nodeInfo *inputNodeID;
    nodeInfo *outputNodeID;
    boolean compShortStatus;
    boolean compOpenStatus;
    float voltageAcross;
    float currentThrough;
    boolean isHorizontal;
    struct componentInformation *nextComponent;
    int *parallel;
    int inputSerial;
    int outputSerial;
} compInfo;

typedef struct listOfUniqueNodeData {
    int *uniqueNodeList;
    int uniqueNodeCount;
} uniqueNodeData;

typedef struct componentsConnectedToNode {
    int *listOfComponentID;
    int numberOfComponents;
} nodeConnectionData;

typedef struct calculationInformation {
    float **conductanceMatrix;
    float *currentMatrix;
    int matrixSize;
} calcInfo;


int countComponentNumber(void);
int countTrivialNodeNumber(void);
void initializeResistor(compInfo *resistor);
void initializeCapacitor(compInfo *capacitor);
void initializeInductor(compInfo *inductor);
char addComponent(void);
void removeLastComponent();
int generateStaticNodeID(void);
void combineNode(int *componentSequence, boolean *terminalSequence, int componentNumber);
compInfo *createSearchComponent(void);
compInfo *findComponentByID(int compID);
void setNodeVoltage(int nodeID, float nodeVoltage);
void initializeGND(int compID, boolean terminal);
boolean skipVoltageToGND(int componentID);
void initializeNodeVoltages(void);
boolean uniqueNodeIdentifier(int *nodeIDptr, int nodeID, int currentNodeCount);
uniqueNodeData countUniqueNodeNumber(void);
nodeConnectionData listComponentsOfNode(int nodeID);
boolean checkSuperNode(int nodeID);
int *needMoreMemory(int *memPtr, int numberOfComponents);
int *extractNodeData(int nodeID);
nodeConnectionData *nodesOfUnknownVoltage(void);
float checkNodeVoltage(int nodeID);
calcInfo *getNodeEquation(void);

#endif // _component_c_
