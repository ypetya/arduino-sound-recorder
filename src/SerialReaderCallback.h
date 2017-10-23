
#ifndef SERIALREADERCALLBACK_H
#define SERIALREADERCALLBACK_H

class SerialReaderCallback {
public:
    SerialReaderCallback();
    
    virtual void onDataRead(int data);
};

#endif /* SERIALREADERCALLBACK_H */

