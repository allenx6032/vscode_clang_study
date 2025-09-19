/*
 *	Platform Specification Selector
 *	Copyright(C) 2003-2012 Jinhao(cnjinhao@hotmail.com)
 *
 *	Distributed under the Nana Software License, Version 1.0.
 *	(See accompanying file LICENSE_1_0.txt or copy at
 *	http://nanapro.sourceforge.net/LICENSE_1_0.txt)
 *
 *	@file: nana/detail/platform_spec_selector.cpp
 *
 *  This file is used to support the Nana project of some cross-platform IDE,
 *	
 */

#include <nana/config.hpp>

#if defined(NANA_WINDOWS)
	#include "platform_spec_win32.cpp.h"
#elif defined(NANA_LINUX)
	#include "platform_spec_x11.cpp.h"
#endif

