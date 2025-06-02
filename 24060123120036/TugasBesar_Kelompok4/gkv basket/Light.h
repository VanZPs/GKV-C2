#ifndef LIGHT_H
#define LIGHT_H

#include "platform.h"

class Light {
public:
    Light() = default;
    ~Light() = default;
    
    // Setup the default lighting
    void setup(bool headlightMode) const;
    
    // Turn on headlight
    void enableHeadlight() const;
};

#endif 
