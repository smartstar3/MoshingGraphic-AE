#include "MoshingGraphic.h"

typedef struct flowBlock
{
	short xDisplace, yDisplace;
	unsigned short thres;
} FlowBlock;

typedef struct flowFrame {
	bool ready; //remember to initialize as false
	FlowBlock blocks[15000];
} FlowFrame;

typedef struct seqData {
	bool ready; //remember to initialize as false
	bool refreshLayer;
	int numOfFrame; //updates upon allocating new frames

	int frameWidth, frameHeight; //target's size
	int blockWidth;
	int numHBlock, numVBlock; //something to do with target's screan ratio
	FlowFrame frames[10]; //10 frames, allocate afterwards with handles
} SeqData;

typedef struct itData {
	PF_InData* in_data;
	SeqData* seq_data;
	PF_SampPB samp_pb;
	unsigned short threshold;
	int currentFrame;
	int loopData;
	float Xscale, Yscale;
	PF_SampPB composite;
} ItData;

typedef struct tempBlock { //store source block
	int width;
	PF_Pixel* pxs;
} tempBlock;

const int dir[9][2] = { { -1,-1 },{ 0,-1 },{ 1, -1 },{ -1, 0 },{ 0, 0 },{ 1, 0 },{ -1, 1 },{ 0, 1 },{ 1, 1 } }; //(-1,-1) to (1,1)

PF_Err calcOpticFlow(PF_InData* in_data, PF_LayerDef* source, PF_LayerDef* target, int frameNum, SeqData* seqData);

PF_Point getDIstort(PF_InData* in_data, SeqData* seqData, int x, int y, int frameNum, unsigned short threshold);