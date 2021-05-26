#ifndef __SBUS_H__
#define __SBUS_H__
#include "main.h"
uint8_t update_sbus(uint8_t *buf);
typedef struct
{
	uint16_t CH1;//1通道
	uint16_t CH2;//2通道
	uint16_t CH3;//3通道
	uint16_t CH4;//4通道
	uint16_t CH5;//5通道
	uint16_t CH6;//6通道
    uint16_t CH7;//7通道
    uint16_t CH8;//8通道
    uint16_t CH9;//9通道
    uint16_t CH10;//10通道
    uint16_t CH11;//11通道
    uint16_t CH12;//12通道
    uint16_t CH13;//13通道
    uint16_t CH14;//14通道
    uint16_t CH15;//15通道
    uint16_t CH16;//16通道
	uint8_t ConnectState;//有新数据的标志
}SBUS_CH_Struct;
extern SBUS_CH_Struct SBUS_CH;
#endif

