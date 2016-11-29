#ifndef _KEYBUFFER_
#define _KEYBUFFER_

#include "engine.h"

class KeyBuffer
{
private:
	static KeyBuffer* m_instance;

	bool key_states[256] = { false };

	KeyBuffer();
	~KeyBuffer();

public:
	static KeyBuffer* instance();

	void pressKey(unsigned char key);
	void releaseKey(unsigned char key);

	bool isKeyDown(unsigned char key);
};

#endif