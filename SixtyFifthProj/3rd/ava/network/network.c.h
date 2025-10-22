#ifdef NETWORK_C
#pragma once
#define SOCKET_C
#define DISPATCH_C
#define PORT_C
#define WEBSERVER_C
#define OSCSEND_C
#define OSCRECV_C
#define OSCPACK_C
#define SENDBUF_C
#endif

#include "network_compat.c.h"
#include "network_socket.c.h"
#include "network_dispatch.c.h"
#include "network_port.c.h"
#include "network_webserver.c.h"
#include "network_oscsend.c.h"
#include "network_oscrecv.c.h"
#include "network_oscpack.c.h"
#include "network_sendbuf.c.h"
