#ifndef HOOP_H
#define HOOP_H

#include "platform.h"

class Hoop {
public:
    Hoop() = default;
    ~Hoop() = default;
    
    // gamabr basketball hoop
    void draw() const;
    
private:
    
    void setupMaterial(const std::string& partName) const;
};

#endif // HOOP_H
