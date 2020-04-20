#ifndef payload_types
#define payload_types


namespace payload_types {

const unsigned int HEADER_SIZE = 4;
const unsigned int PAYLOAD_TP_IDX = HEADER_SIZE - 1;
const unsigned int PAYLOAD_START_IDX = HEADER_SIZE;
const unsigned int PAYLOAD_SIZE_CONNECT_C = 2;
//const unsigned int PAYLOAD_SIZE_CONNECT_REPLY_c = 1;
const unsigned int MSG_SERVER_W_PAYLOAD_SIZE = 0;

const char *CONNECT_C = "C";
const char *CONNECT_REPLY_c = "c";
const char *MSG_SERVER_W = "W";
}

#endif // payload_types
