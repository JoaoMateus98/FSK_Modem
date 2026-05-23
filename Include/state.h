#ifndef STATE_H
#define STATE_H

class Transmitter;

class State {
   public:
    virtual void handle(Transmitter& ctx) = 0;
    virtual ~State() = default;
};

#endif