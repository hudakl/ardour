/*
    Copyright (C) 2009 Paul Davis

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

*/

#ifndef __libpbd_debug_h__
#define __libpbd_debug_h__

#include <stdint.h>

#include <sstream>

#include "pbd/libpbd_visibility.h"
#include "pbd/timing.h"

namespace PBD {

	LIBPBD_API extern uint64_t debug_bits;
	LIBPBD_API uint64_t new_debug_bit (const char* name);
	LIBPBD_API void debug_print (const char* prefix, std::string str);
	LIBPBD_API void set_debug_bits (uint64_t bits);
	LIBPBD_API int parse_debug_options (const char* str);
	LIBPBD_API void list_debug_options ();

	namespace DEBUG {

		/* this namespace is so that we can write DEBUG::bit_name */
                
		LIBPBD_API extern uint64_t Stateful;
		LIBPBD_API extern uint64_t Properties;
		LIBPBD_API extern uint64_t FileManager;
		LIBPBD_API extern uint64_t Pool;
		LIBPBD_API extern uint64_t EventLoop;
		LIBPBD_API extern uint64_t AbstractUI;
		LIBPBD_API extern uint64_t Configuration;
		extern uint64_t FileUtils;
	}
}

#ifndef NDEBUG
#define DEBUG_TRACE(bits,str) if ((bits) & PBD::debug_bits) { PBD::debug_print (# bits, str); }
#define DEBUG_STR_DECL(id) std::stringstream __debug_str ## id;
#define DEBUG_STR(id) __debug_str ## id
#define DEBUG_STR_APPEND(id,s) __debug_str ## id << s;
#define DEBUG_ENABLED(bits) ((bits) & PBD::debug_bits)
#ifdef PTW32_VERSION
#define DEBUG_THREAD_SELF pthread_self().p
#else
#define DEBUG_THREAD_SELF pthread_self()
#endif

#define DEBUG_TIMING_START(bits,td) if ((bits) & PBD::debug_bits) { td.start_timing (); }
#define DEBUG_TIMING_ADD_ELAPSED(bits,td) if ((bits) & PBD::debug_bits) { td.add_elapsed (); }
#define DEBUG_TIMING_RESET(bits,td) if ((bits) & PBD::debug_bits) { td.reset (); }

#else
#define DEBUG_TRACE(bits,fmt,...) /*empty*/
#define DEBUG_STR(a) /* empty */
#define DEBUG_STR_APPEND(a,b) /* empty */
#define DEBUG_ENABLED(b) (0)
#define DEBUG_THREAD_SELF 0

#define DEBUG_TIMING_START(bits,td) /*empty*/
#define DEBUG_TIMING_ADD_ELAPSED(bits,td) /*empty*/
#define DEBUG_TIMING_RESET(bits,td) /*empty*/

#endif
#endif /* __libpbd_debug_h__ */

