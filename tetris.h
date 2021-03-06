
extern int nSpace[24][12];
extern int nBlock[7][4][4][4];
extern int nX, nY;
extern int nBlockNo;
extern time_t tStart, tEnd;
extern int nFalling;
extern int nBlockRot;
extern int nGameOver;

extern void initSpace();
extern void drawAll();
extern void addBlock();
extern void delBlock();
extern int isLineFull();
extern void delFullLine();
extern int isCrushing();
extern void setNewBlock();
extern void moveToLeft();
extern void moveToRight();
extern void revertRot();
extern void avoidCrush();
extern void dropBlock();
extern void getInput();
