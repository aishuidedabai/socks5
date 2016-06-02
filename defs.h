#ifndef DEFS_H_
#define DEFS_H_
#include <uv.h>

#define SESSION_TCP_BUFSIZ 1024
#define SESSION_UDP_BUFSIZ 4096

struct Socks5Ctx;

typedef enum {
  S5_METHOD_IDENTIFICATION,
  S5_REQUEST,
  S5_START_PROXY,
  S5_STREAMING,
  S5_STREAMING_END,
  S5_CLOSING,
} SessionState;

typedef enum {
  SESSION_TYPE_UNKNOWN,
  SESSION_TYPE_TCP,
  SESSION_TYPE_UDP
} SessionType;

#define SESSION_FIELDS \
  uv_tcp_t *client_tcp; \
  uv_write_t *client_write_req; \
  char client_buf[SESSION_TCP_BUFSIZ]; \
  SessionState state; \
  Socks5Ctx s5_ctx; \
  SessionType type;

typedef struct {
  SESSION_FIELDS
} Session;

typedef struct {
  SESSION_FIELDS

  uv_tcp_t *upstream_tcp;
  uv_write_t *upstream_write_req;
  uv_getaddrinfo_t upstream_addrinfo_req;
  uv_connect_t upstream_connect_req;
  char upstream_buf[SESSION_TCP_BUFSIZ]; 
} TCPSession;

typedef struct {
  SESSION_FIELDS

  uv_udp_t *client_udp_recv;
  char clinet_udp_recv_buf[SESSION_UDP_BUFSIZ]; 

  uv_udp_t *upstream_udp;
  uv_udp_send_t *upstream_udp_send_req;
  uv_getaddrinfo_t upstream_udp_addrinfo_req;
  char upstream_udp_buf[SESSION_UDP_BUFSIZ]; 

  uv_udp_t *client_udp_send;
  uv_udp_send_t *client_udp_send_req;
  uv_getaddrinfo_t client_udp_addrinfo_req;
} UDPSession;

#endif /* end of include guard: DEFS_H_ */
