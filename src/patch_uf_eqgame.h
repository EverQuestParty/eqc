#ifndef EQC_SRC_PATCH_UF_EQGAME_H
#define EQC_SRC_PATCH_UF_EQGAME_H

#include "eqgame_functions.h"

#define EQAddr(n, addr) const size_t UF_a##n = ((addr - 0x400000) + UF_base_address)

#ifdef EQC_EXTERN
#define EQVar(n, type, value) extern type UF_##n;
#define EQFunc(n) extern p##n UF##n
#else
#define EQVar(n, type, value) type UF_##n = (type)value
#define EQFunc(n) p##n UF##n = (p##n)(UF_a##n)
#endif

EQVar(base_address, DWORD, GetModuleHandle(NULL));

EQAddr(Game__RegisterZone, 0x6C40F0);
EQFunc(Game__RegisterZone);

EQAddr(Game__RegisterModel, 0x4CAF50);
EQFunc(Game__RegisterModel);

EQAddr(Game__DisplayChat, 0x4E0310);
EQFunc(Game__DisplayChat);

EQAddr(Game__OnMsgRecv, 0x446DC0);
EQFunc(Game__OnMsgRecv);

EQAddr(Game__TradeStackCheck1, 0x5EB55B);
EQAddr(Game__TradeStackCheck2, 0x679ABA);

EQAddr(Game__DisplayLoadingMessage, 0x47C720);
EQFunc(Game__DisplayLoadingMessage);
EQAddr(Game__LoadingMessageArray, 0x8A9D78); // size = 69

//Player
EQAddr(Player__EnterZone, 0x4F1DB0);
EQFunc(Player__EnterZone);

EQVar(Player__UDPConnection, void**, 0xA983C8);
EQAddr(Player__SendReliableMessage, 0x695BA0);
EQFunc(Player__SendReliableMessage);

EQAddr(Player__CommandHandler, 0x4E0E70);
EQFunc(Player__CommandHandler);

#endif
