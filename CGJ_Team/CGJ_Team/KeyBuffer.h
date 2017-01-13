#ifndef _KEYBUFFER_
#define _KEYBUFFER_

#include "engine.h"

class KeyBuffer
{
private:
	static KeyBuffer* m_instance;

	bool key_states[256] = { false };
	bool special_states[128] = { false };

	KeyBuffer();
	~KeyBuffer();

public:
	static KeyBuffer* instance();

	void pressKey(unsigned char key);
	void releaseKey(unsigned char key);
	void pressSpecialKey(int key);
	void releaseSpecialKey(int key);

	bool isKeyDown(unsigned char key);
	bool isSpecialKeyDown(int key);
};

#endif