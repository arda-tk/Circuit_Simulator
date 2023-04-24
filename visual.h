#ifndef _visual_c_
#define _visual_c_

#include "component.h"

#define INPUTSTREAM 30
#define mapSizeRow 8
#define mapSizeCol 12
#define MAXNODESIZE (mapSizeRow * mapSizeCol)
#define upperLeft 201
#define upperRight 187
#define lowerLeft 200
#define lowerRight 188
#define vertical 186
#define horizontal 205
#define whiteSpace 32

void userManual();
void initializeMap();
boolean navigate();
void testResistive(void);
void testRLC(void);

#endif // _visual_c_
