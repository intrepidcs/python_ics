#include <cstring>
#include "icsnVC40.h"

#ifdef _WIN32
#define API extern "C" __declspec(dllexport) int __stdcall
#else
#define API extern "C" int
#endif

static unsigned char payload[300];
static int calls;

static void receive(icsSpyMessage* msg)
{
    memset(msg, 0, sizeof(*msg));
    for (int i = 0; i < 300; ++i)
        payload[i] = (unsigned char)i;
    msg->Protocol = SPY_PROTOCOL_ETHERNET;
    msg->NumberBytesHeader = 1;
    msg->NumberBytesData = 44;
    msg->ExtraDataPtr = payload;
}

API icsneoGetDLLVersion() { return 1; }
API icsneoWaitForRxMessagesWithTimeOut(void*, unsigned int) { return 1; }
API icsneoGetMessages(void*, icsSpyMessage* msg, int* count, int* errors)
{
    receive(msg);
    *count = 1;
    *errors = 0;
    return 1;
}
API icsneoScriptReadTxMessage(void*, unsigned int, icsSpyMessage* msg)
{
    receive(msg);
    return 1;
}
API icsneoScriptReadRxMessage(void*, unsigned int, icsSpyMessage* msg, icsSpyMessage* mask)
{
    receive(msg);
    receive(mask);
    return 1;
}
API icsneoTxMessages(void*, icsSpyMessage*, int, int) { ++calls; return 1; }
API capacity_mock_calls() { return calls; }
