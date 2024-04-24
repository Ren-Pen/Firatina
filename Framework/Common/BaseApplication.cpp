#include "BaseApplication.h"

namespace slimenano
{

	int BaseApplication::Initialize()
	{

		this->m_bQuit = false;

		return 0;
	}

	void BaseApplication::Finalize()
	{
	}

	void BaseApplication::Tick()
	{
	}

	bool slimenano::BaseApplication::IsQuit()
	{
		return this->m_bQuit;
	}

}