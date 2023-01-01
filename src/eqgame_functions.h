#ifndef EQC_SRC_EQGAME_FUNCTIONS_H
#define EQC_SRC_EQGAME_FUNCTIONS_H

//Game
typedef int(__thiscall *pGame__RegisterZone)(void*, int, int, const char*, const char*, int, int, int, int, int);
typedef int(__thiscall *pGame__RegisterZone2)(void*, int, int, const char*, const char*, int, int, int, int, int);
typedef int(__thiscall *pGame__RegisterModel)(void*, int, int, const char*, int, int);
typedef void(__stdcall *pGame__DisplayChat)(const char *, int, bool, bool);
typedef int(__stdcall *pGame__OnMsgRecv)(void*, const char*, int);
typedef int(__thiscall *pGame__DisplayLoadingMessage)(void*, int, char const*);

//Player
typedef void(__thiscall *pPlayer__EnterZone)(void*, void*);
typedef char(__thiscall *pPlayer__SendReliableMessage)(void*, int, char*, int); //connection, priority?, data, data_len
typedef char(__thiscall *pPlayer__SendReliableMessageTitanium)(void*, int, char*, int, int); //connection, opcode, data, data_len, priority?
typedef int(__thiscall *pPlayer__CommandHandler)(void*, DWORD pp, const char *command);

#endif