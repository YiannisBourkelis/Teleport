#ifndef CLIENTSTATE_H
#define CLIENTSTATE_H


enum class ClientState
{
    disconnected,
    connected,
    connectionRestorationTimerActive
};


#endif // CLIENTSTATE_H
