#ifndef EQC_SRC_PATCH_SOD_EQGAME_H
#define EQC_SRC_PATCH_SOD_EQGAME_H

#include "eqgame_functions.h"

#define EQAddr(n, addr) const size_t SoD_a##n = ((addr - 0x400000) + SoD_base_address)

#ifdef EQC_EXTERN
#define EQVar(n, type, value) extern type SoD_##n;
#define EQFunc(n) extern p##n SoD##n
#else
#define EQVar(n, type, value) type SoD_##n = (type)value
#define EQFunc(n) p##n SoD##n = (p##n)(SoD_a##n)
#endif

EQVar(base_address, DWORD, GetModuleHandle(NULL));

EQAddr(Game__RegisterZone, 0x6939D0);
EQFunc(Game__RegisterZone);

EQAddr(Game__RegisterModel, 0x4CAF50);
EQFunc(Game__RegisterModel);

EQAddr(Game__DisplayChat, 0x4DCD60);
EQFunc(Game__DisplayChat);

EQAddr(Game__OnMsgRecv, 0x44ABB0);
EQFunc(Game__OnMsgRecv);

EQAddr(Game__TradeStackCheck1, 0x5CFB72);
EQAddr(Game__TradeStackCheck2, 0x651F3A);

EQAddr(Game__DisplayLoadingMessage, 0x47F6E0);
EQFunc(Game__DisplayLoadingMessage);
EQAddr(Game__LoadingMessageArray, 0x854930); // size = 69

//Player
EQAddr(Player__EnterZone, 0x4F2420);
EQFunc(Player__EnterZone);

EQVar(Player__UDPConnection, void**, 0xA42580);
EQAddr(Player__SendReliableMessage, 0x66D250);
EQFunc(Player__SendReliableMessage);

EQAddr(Player__CommandHandler, 0x4DD7C0);
EQFunc(Player__CommandHandler);

#endif
