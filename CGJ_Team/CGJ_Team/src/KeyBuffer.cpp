#include "KeyBuffer.h"

KeyBuffer* KeyBuffer::m_instance;

KeyBuffer::KeyBuffer()
{
}

KeyBuffer::~KeyBuffer()
{
}

KeyBuffer * KeyBuffer::instance()
{
	if (!m_instance) {
		m_instance = new KeyBuffer();
	}
	return m_instance;
}

void KeyBuffer::pressKey(unsigned char key)
{
	key_states[key] = true;
}

void KeyBuffer::releaseKey(unsigned char key)
{
	key_states[key] = false;
}

bool KeyBuffer::isKeyDown(unsigned char key)
{
	return key_states[key];
}
