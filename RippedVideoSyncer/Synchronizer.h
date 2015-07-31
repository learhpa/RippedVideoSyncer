#ifndef __SYNCHRONIZER_H__
#define __SYNCHRONIZER_H__

class Synchronizer {
public:
	virtual bool synchronize() = 0;
	virtual ~Synchronizer() {};
};


#endif