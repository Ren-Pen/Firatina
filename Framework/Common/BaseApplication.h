#pragma once
#ifndef __FRAMEWORK_BASE_APPLICATION_H
#define __FRAMEWORK_BASE_APPLICATION_H

#include "IApplication.h"

namespace slimenano
{
	class BaseApplication : public IApplication
	{
	public:
		virtual int Initialize() override;
		virtual void Finalize() override;
		virtual void Tick() override;
		virtual bool IsQuit() override;

	protected:
		bool m_bQuit;
	};

}

#endif //!__FRAMEWORK_BASE_APPLICATION_H