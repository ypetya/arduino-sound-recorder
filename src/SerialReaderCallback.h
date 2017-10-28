
#ifndef SERIALREADERCALLBACK_H
#define SERIALREADERCALLBACK_H

#include <cstdlib>


class SerialReaderCallback{
public:
    SerialReaderCallback();
    
    virtual void onDataRead(char * data, size_t length){};
};

#endif /* SERIALREADERCALLBACK_H */

