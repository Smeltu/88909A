// This class is similar to CSingleLock in MFC
#ifndef __SINGLE_LOCK__
#define __SINGLE_LOCK__

#include "vex.h"

class SingleLock {
  private: vex::mutex & m_Lock;
  public: SingleLock(vex::mutex & Lock): m_Lock(Lock) {
      m_Lock.lock();
    }
    ~SingleLock() {
      m_Lock.unlock();
    }
};

#endif