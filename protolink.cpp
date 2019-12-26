#include "protolink.h"

#include <Arduino.h>

#define LEN_N_BYTES 2 // The number of bytes describing the lenght of the rest of the message

ProtoLink::ProtoLink(uint8_t* fbp, uint fbs) { 
  fb = fbp;
  fb_size = fbs;
}

// Connects a stream to protolink instance
ProtoLink::State ProtoLink::init(Stream* s) {
  stream = s;
  state = INIT;
}

// Does a step in the state machine
ProtoLink::State ProtoLink::run() {
  switch(state) {
    case NO_CONN: break;
    case INIT:    run_INIT();     break;
    case RECV_FB: run_RECV_FB();  break;
  }
  return state;
}

// Receives and copies new framebuffer contents to the framebuffer
void ProtoLink::run_RECV_FB() {

  // First LEN_N_BYTES bytes are body length in bytes
  uint len = 0;
  while (!len) {
    if (stream->available() >= LEN_N_BYTES) {
      
      uint8_t lenbuf[LEN_N_BYTES];
      stream->readBytes(lenbuf, LEN_N_BYTES);
      
      for (int i = 0; i < LEN_N_BYTES; i++) {
        len |= (lenbuf[LEN_N_BYTES - 1 - i] << i * 8);
      }
    }
    yield();
  }

  Serial.print("Len: ");
  Serial.println(len);
  
  // Copy the rest of the message into the framebuffer
  while (true) {
    
    int available = stream->available();
    
    if (stream->available() >= len) {
      
      // No buffer overflow pls
      int copy_len = min(fb_size, len);
      
      stream->readBytes(fb, copy_len);

      // Go back to initial state to wait for next command
      state = INIT;
      return;
    }
    yield();
    
  }
}

// Initial state after being connected,
// The first incoming byte decides what the rest of the message will be
void ProtoLink::run_INIT() {
  while (true) {
    if (stream->available()) {
      int in = stream->read();

      switch(in) {
        case RECV_FB: state = RECV_FB; break;
        default: state = ERR; break;
      };

      return;
    }
    yield();
  }
}

#define to_str(p) case(p): return #p;
String ProtoLink::stateString() {
  switch(state) {
    to_str(NO_CONN);
    to_str(INIT);
    to_str(RECV_FB);
    to_str(ERR);
  }
}
