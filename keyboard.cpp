#include "keyboard.h"
#include "logger.h"

Keyboard::Keyboard()
{
	// Nothing to do here
}

void Keyboard::Update()
{
	
}

void Keyboard::OnKeyDown(int key)
{

	// Check to see if the key is defined
	if (key > KEY_LAST)
	{
		TBV_ERROR("[" + std::to_string(key) + "] - is not defined.");
		return;
	}
	m_Keys[key].Update(true);
}

void Keyboard::OnKeyUp(int key)
{

	// Check to see if the key is defined
	if (key > KEY_LAST)
	{
		TBV_ERROR("[" + std::to_string(key) + "] - is not defined.");
		return;
	}
	m_Keys[key].Update(false);
}

bool Keyboard::IsKeyHeld(int key) const
{

	// Check to see if the key is defined
	if (key > KEY_LAST)
	{
		TBV_ERROR("[" + std::to_string(key) + "] - is not defined.");
		return false;
	}
	return m_Keys[key].m_bIsDown;
}

bool Keyboard::IsKeyJustPressed(int key) const
{

	// Check to see if the key is defined
	if (key > KEY_LAST)
	{
		TBV_ERROR("[" + std::to_string(key) + "] - is not defined.");
		return false;
	}
	return m_Keys[key].m_bIsJustPressed;
}

bool Keyboard::IsKeyJustReleased(int key) const
{

	// Check to see if the key is defined
	if (key > KEY_LAST)
	{
		TBV_ERROR("[" + std::to_string(key) + "] - is not defined.");
		return false;
	}
	return m_Keys[key].m_bIsJustReleased;
}
