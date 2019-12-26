#ifndef Protolink_h
#define Protolink_h

#include <ESP8266WiFi.h>
#include <Stream.h>

class ProtoLink {
  public:
    enum State {
      NO_CONN,
      INIT,
      RECV_FB,
      ERR
    };
 
  private:
    Stream* stream;
    uint8_t* fb;
    uint fb_size;

    // Initial state
    State state = NO_CONN;

    // State methods
    void run_INIT();
    void run_RECV_FB();
    
  public:
    ProtoLink(uint8_t*, uint);
    
    State run();

    State init(Stream*);

    String stateString();
    
};

#endif
