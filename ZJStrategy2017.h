
//	2017  IT工作室-智能系统组 吴永康 

//	GitHub仓库 	https://github.com/TianMaXingKong2003/FIRA-5V5

//	ZJStrategy2017.h	

//	由于平台的头文件经过多届学长修改，建议学弟们在此基础上试着重写，便于熟悉变量与常数的定义 	 


//----------------------原平台的Strategy.h备注
 
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the STRATEGY_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// STRATEGY_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.

//----------------------翻译如下

// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 ZJSTRATEGY_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// ZJSTRATEGY_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的



#pragma once			//仅编译一次 

#ifdef ZJSTRATEGY_EXPORTS

	#define ZJSTRATEGY_API __declspec(dllexport)

#else

	#define ZJSTRATEGY_API __declspec(dllimport)

#endif


// -------------------------------所有添加的头文件（自定义）-------------------------------



#include <stdio.h>
#include <math.h>
#include <windows.h>
#include<fstream>



// -------------------------------全局参数（平台自带）-------------------------------

const long PLAYERS_PER_SIDE = 5;						// 每队球员个数

// 比赛状态
const long FREE_BALL = 1;								// 争球
const long PLACE_KICK = 2;								// 开球
const long PENALTY_KICK = 3;							// 点球
const long FREE_KICK = 4;								// 任意球
const long GOAL_KICK = 5;								// 门球

// 发球方
const long ANYONES_BALL = 0;							// 没有发球方
const long BLUE_BALL = 1;								// 蓝队发球
const long YELLOW_BALL = 2;								// 黄队发球

// 场地信息
const double FTOP = 77.2392;							// 场地上边界
const double FBOT = 6.3730;								// 场地下边界
const double FRIGHTX = 93.4259;							// 场地右边界
const double FLEFTX = 6.8118;							// 场地左边界

const double GTOPY = 49.6801;							// 球门上边界
const double GBOTY = 33.9320;							// 球门下边界
const double GRIGHT = 97.3632;							// 球门右边界
const double GLEFT = 2.8748;							// 球门左边界

#define ON_YELLOW 0										// 黄方
#define ON_BLUE	1										// 蓝方
	
#define OPPONENT_BALL 0
#define OUR_BALL 1

// 位置向量定义
typedef struct
{
	
	double x, y, z;										// x坐标，y坐标，z方向
} Vector3D;


// 区域范围定义
typedef struct
{
	long left, right, top, bottom;						// 左，右，上，下
} Bounds;


// 机器人的信息定义
typedef struct
{
	Vector3D pos;										// 机器人坐标
	double rotation;										// 机器人方向角
	double velocityLeft, velocityRight;					// 机器人左右轮速度
} Robot;

// 对方机器人的信息定义
typedef struct
{
	Vector3D pos;										// 机器人坐标
	double rotation;									// 机器人方向角
} OpponentRobot;

// 小球的位置定义
typedef struct
{
	Vector3D pos;										// 小球的坐标位置
} Ball;

// 主要的定义，包含所有运行时的的信息，由系统刷新
typedef struct
{
	Robot home[PLAYERS_PER_SIDE];						// 我方机器人数组
	OpponentRobot opponent[PLAYERS_PER_SIDE];			// 敌方机器人数组
	Ball currentBall,									// 当前小球的位置
		lastBall,										// 上一次小球的位置
		predictedBall;									// 预计的小球的位置
	Bounds fieldBounds,									// 场地范围
		goalBounds;										// 球门的位置与范围
	long gameState;										// 当前比赛状态
	long whoseBall;										// 发球方
	void *userData;										// 用户自定义信息（见自定义Mydata结构体）
} Environment;







// -------------------------------全局参数（自定义）-------------------------------

const double PI = 3.14159265359;

// 自定义
typedef struct
{
	//我方机器人相关
	Robot myRobot[PLAYERS_PER_SIDE];						// 我方机器人数组
	Vector3D myLastPos[PLAYERS_PER_SIDE];					// 我方机器人的旧坐标,方向
	Vector3D mySpeed[PLAYERS_PER_SIDE];					// 我方机器人的速度，跑位的方向
	Vector3D myLastSpeed[PLAYERS_PER_SIDE];				// 我方机器人上次的速度，跑位的方向
	//Vector3D myLeftSpeed[PLAYERS_PER_SIDE];				// 我方机器人的左轮速度
	//Vector3D myLastLeftSpeed[PLAYERS_PER_SIDE];			// 我方机器人上次的左轮速度
	//Vector3D myRightSpeed[PLAYERS_PER_SIDE];				// 我方机器人的右轮速度
	//Vector3D myLastRightSpeed[PLAYERS_PER_SIDE];			// 我方机器人上次的右轮速度

	//敌方机器人相关
	OpponentRobot oppRobot[PLAYERS_PER_SIDE];				// 敌方机器人数组
	Vector3D oppLastPos[PLAYERS_PER_SIDE];					// 敌方机器人的旧坐标,方向
	Vector3D oppSpeed[PLAYERS_PER_SIDE];					// 敌方机器人的速度，跑位的方向
	//Vector3D oppLastSpeed[PLAYERS_PER_SIDE];				// 敌方机器人上次的速度，跑位的方向

	//球相关
	Ball lastBall,										// 上一次小球的位置
		curBall,											// 当前小球的位置
		preBall;											// 预计的小球的位置
	Vector3D ballSpeed;									// 球速

	//其他
	long gameState;										// 当前比赛状态
	//int freeBall;										// 争球，0代表不是，1代表是
	//int placeKick;										// 开球，0代表不是，1代表是
	int penaltyKick;									// 点球，0代表不是，1代表是
	//int freeKick;										// 任意球，0代表不是，1代表是
	//int goalKick;										// 门球，0代表不是，1代表是

	bool locked;											// 是否已经判断了场地，true是，false未
	bool myArea;											// 我方是哪方，true黄方，false蓝方

	long whoseBall;										// 发球方

	int ballArea;										// 分区，专用函数int checkball();

	int chooseRobot;										//是否已选择点球队员

	int mainRobot;										// 主发
	int cutRobot;										// 包抄
	int slowRobot;										// 轻踢
	int defendRobot;										// 防守
	int goalie;											// 守门

	long time[2];										// time[1]取样周期 & time[0]取样次数
}Mydata;

// 我方机器人x,y,z初始值
const double InitializeMyPosition_X[5] = {
	10.6663,
	19.9199,
	19.7433,
	39.4618,
	39.8876
};
const double InitializeMyPosition_Y[5] = {
	42.3077,
	60.3647,
	22.9943,
	60.3031,
	23.1065
};
const double InitializeMyPosition_Z[5] = {
	90,
	0,
	0,
	0,
	0
};

// 对方机器人x,y,z初始值
const double InitializeOppPosition_X[5] = {
	90.4616,
	82.0921,
	81.2890,
	61.8525,
	61.4469
};
const double InitializeOppPosition_Y[5] = {
	42.2002,
	22.9046,
	60.4876,
	23.1527,
	60.3599
};
const double InitializeOppPosition_Z[5] = {
	-90,
	180,
	180,
	180,
	180
};

//修正  坐标转换时的  偏差
const double CORRECTX = 0;//-2.942073;
const double CORRECTY = 0;//-6.283795;

const double SPEED_NORMAL = 0.27;
const double SPEED_TANGENT = 0.81;

const double CORNER = 5;

const double ANGLE_A = 0.273575;
const double ANGLE_B = 0.534262;

const double ANGLE_K = 0.000294678;

const double SPEED_A = 0.060;
const double SPEED_B = 0.015222305;
const double SPEED_ZERO = 0.1896;	//0 减速度 和 125减速度的临界值
const double SPEED_ODD = 0.662;	//0.338;左右轮速为0时的减速参数

const Vector3D CONSTGATE = { FRIGHTX,(FTOP + FBOT) / 2,0 };

const Vector3D TOPGATE = { 93,72,0 };
const Vector3D BOTGATE = { 93,9,0 };

extern "C" ZJSTRATEGY_API void Create(Environment *env);		// Create    程序的初始化
extern "C" ZJSTRATEGY_API void Strategy(Environment *env);		// Strategy  程序的主要执行逻辑
extern "C" ZJSTRATEGY_API void Destroy(Environment *env);		// Destroy   程序的销毁

/* 创建新dll项目时自动生成的
// 此类是从 ZJStrategy.dll 导出的
class ZJSTRATEGY_API CZJStrategy {
public:
	CZJStrategy(void);
	// TODO:  在此添加您的方法。
};

extern ZJSTRATEGY_API int nZJStrategy;

ZJSTRATEGY_API int fnZJStrategy(void);
*/
