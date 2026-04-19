#ifndef CONTROLCAN_H
#define CONTROLCAN_H

//接口卡类型定义
#define VCI_PCI5121		1      //PCI5121型号CAN卡
#define VCI_PCI9810		2
#define VCI_USBCAN1		3
#define VCI_USBCAN2		4     //USBCAN2型号CAN卡
#define VCI_PCI9820		5
#define VCI_CAN232		6
#define VCI_PCI5110		7
#define VCI_CANLite		8
#define VCI_ISA9620		9
#define VCI_ISA5420		10

//CAN错误码
#define	ERR_CAN_OVERFLOW			0x0001	//CAN控制器内部FIFO溢出
#define	ERR_CAN_ERRALARM			0x0002	//CAN控制器错误报警
#define	ERR_CAN_PASSIVE				0x0004	//CAN控制器消极错误
#define	ERR_CAN_LOSE				0x0008	//CAN控制器仲裁丢失
#define	ERR_CAN_BUSERR				0x0010	//CAN控制器总线错误

//通用错误码
#define	ERR_DEVICEOPENED			0x0100	//设备已经打开
#define	ERR_DEVICEOPEN				0x0200	//打开设备错误
#define	ERR_DEVICENOTOPEN			0x0400	//设备没有打开
#define	ERR_BUFFEROVERFLOW			0x0800	//缓冲区溢出
#define	ERR_DEVICENOTEXIST			0x1000	//此设备不存在
#define	ERR_LOADKERNELDLL			0x2000	//装载动态库失败
#define ERR_CMDFAILED				0x4000	//执行命令失败错误码
#define	ERR_BUFFERCREATE			0x8000	//内存不足


//函数调用返回状态值
#define	STATUS_OK					1      //成功
#define STATUS_ERR					0      // 失败
	
#define USHORT unsigned short int
#define BYTE unsigned char
#define CHAR char
#define UCHAR unsigned char
#define UINT unsigned int
#define DWORD unsigned int
#define PVOID void*
#define ULONG unsigned int
#define INT int
#define UINT32 UINT
#define LPVOID void*
#define BOOL BYTE
#define TRUE 1
#define FALSE 0


#if 1
//1.ZLGCAN系列接口卡信息的数据类型。
typedef  struct  _VCI_BOARD_INFO{
		USHORT	hw_Version;     //硬件版本号
		USHORT	fw_Version;      //固件版本号
		USHORT	dr_Version;      //驱动程序版本号
		USHORT	in_Version;      //接口库版本号
		USHORT	irq_Num;         //板卡所使用的中断号
		BYTE	can_Num;             //表示有几路CAN通道
		CHAR	str_Serial_Num[20];  //此板卡的序列号
		CHAR	str_hw_Type[40];      // 硬件类型，比如"USBCAN V1.00" (注意包括字符串结束符 '\n' )
		USHORT	Reserved[4];        //系统保留
} VCI_BOARD_INFO,*PVCI_BOARD_INFO; 

//2.定义CAN信息帧的数据类型。
typedef  struct  _VCI_CAN_OBJ{
	UINT	ID;                       //CAN帧ID
	UINT	TimeStamp;   //设备接收到某一帧的时间标识(从上电开始计时)
	BYTE	TimeFlag;       //是否使用时间标识
	BYTE	SendType;      //发送类型 
	BYTE	RemoteFlag;  //是否是远程帧
	BYTE	ExternFlag;    //是否是扩展帧
	BYTE	DataLen;         //数据长度 <=8
	BYTE	Data[8];           //数据内容
	BYTE	Reserved[3];
}VCI_CAN_OBJ,*PVCI_CAN_OBJ;

//3.定义CAN控制器状态的数据类型。
typedef struct _VCI_CAN_STATUS{
	UCHAR	ErrInterrupt;        //中断记录
	UCHAR	regMode;              //CAN控制器模式寄存器值
	UCHAR	regStatus;            //CAN控制器状态寄存器值
	UCHAR	regALCapture;    //CAN控制器仲裁丢失寄存器值
	UCHAR	regECCapture;    //CAN控制器错误寄存器值
	UCHAR	regEWLimit;         //CAN控制器错误警告限制寄存器值，默认96
	UCHAR	regRECounter;    //CAN 控制器接收错误寄存器值。为 0-127 时，为错误主动状态，
	                                                      // 为 128-254 为错误被动状态，为 255 时为总线关闭状态
	UCHAR	regTECounter;     //CAN 控制器发送错误寄存器值。为 0-127 时，为错误主动状态，
	                                                     //为 128-254 为错误被动状态，为 255 时为总线关闭状态
	DWORD	Reserved;            //系统保留
}VCI_CAN_STATUS,*PVCI_CAN_STATUS;

//4.定义错误信息的数据类型。
typedef struct _ERR_INFO{
		UINT	ErrCode;                          //错误码(对应着上述错误码定义)
		BYTE	Passive_ErrData[3];    //当产生的错误中有消极错误时表示为消极错误的错误标识数据
		BYTE	ArLost_ErrData;           //当产生的错误中有仲裁丢失错误时表示为仲裁丢失错误的错误标识数据
} VCI_ERR_INFO,*PVCI_ERR_INFO;

//5.定义初始化CAN的数据类型
typedef struct _INIT_CONFIG{
	DWORD	AccCode;      //验收码
	DWORD	AccMask;      //屏蔽码
	DWORD	Reserved;     //保留参数
	UCHAR	Filter;               //滤波方式  单滤波1  双滤波 0
	UCHAR	Timing0;	     //波特率定时器0
	UCHAR	Timing1;	     //波特率定时器1
	UCHAR	Mode;             //工作模式
}VCI_INIT_CONFIG,*PVCI_INIT_CONFIG;

#ifdef __cplusplus //这部分确保在C++环境中使用C语言链接规范，使得这些函数可以被C++程序调用
extern "C" {
#endif

DWORD VCI_OpenDevice(DWORD DeviceType,DWORD DeviceInd,DWORD Reserved);  //参数:设备类型、设备索引、保留参数
DWORD VCI_CloseDevice(DWORD DeviceType,DWORD DeviceInd);
DWORD VCI_InitCAN(DWORD DeviceType, DWORD DeviceInd, DWORD CANInd, PVCI_INIT_CONFIG pInitConfig); 
//初始化指定CAN通道   参数:设备类型、设备索引、CAN通道索引、初始化配置结构体指针

DWORD VCI_ReadBoardInfo(DWORD DeviceType,DWORD DeviceInd,PVCI_BOARD_INFO pInfo);//读取CAN接口卡的硬件信息  参数3：存储信息的结构体指针
DWORD VCI_ReadErrInfo(DWORD DeviceType,DWORD DeviceInd,DWORD CANInd,PVCI_ERR_INFO pErrInfo);//读取CAN错误信息  参数4：存储错误信息的结构体指针
DWORD VCI_ReadCANStatus(DWORD DeviceType,DWORD DeviceInd,DWORD CANInd,PVCI_CAN_STATUS pCANStatus);//读取CAN控制器状态  参数4：存储状态信息的结构体指针

DWORD VCI_GetReference(DWORD DeviceType,DWORD DeviceInd,DWORD CANInd,DWORD RefType,PVOID pData);//获取CAN控制器参数  参数3：参数类型，参数4：参数值指针
DWORD VCI_SetReference(DWORD DeviceType,DWORD DeviceInd,DWORD CANInd,DWORD RefType,PVOID pData);//设置CAN控制器参数 

ULONG VCI_GetReceiveNum(DWORD DeviceType,DWORD DeviceInd,DWORD CANInd); //获取接受区中的CAN帧数量
DWORD VCI_ClearBuffer(DWORD DeviceType,DWORD DeviceInd,DWORD CANInd);//清空CAN控制器的缓冲区

DWORD VCI_StartCAN(DWORD DeviceType,DWORD DeviceInd,DWORD CANInd); //启动指定的CAN通道
DWORD VCI_ResetCAN(DWORD DeviceType,DWORD DeviceInd,DWORD CANInd);//复位指定的CAM通道

ULONG VCI_Transmit(DWORD DeviceType,DWORD DeviceInd,DWORD CANInd,PVCI_CAN_OBJ pSend,UINT Len);//发送CAN帧  参数4：CAN帧数组指针   参数5：发送帧数
ULONG VCI_Receive(DWORD DeviceType,DWORD DeviceInd,DWORD CANInd,PVCI_CAN_OBJ pReceive,UINT Len,INT WaitTime);
//接收CAN帧  参数4：接收缓冲区指针   参数5：最大接受帧数   参数6：等待时间

#ifdef __cplusplus
}
#endif
#endif

#endif
