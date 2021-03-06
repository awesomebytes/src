//############################################################################
//
// LaserBoy !!!
//
// by James Lehman
// Extra Stimulus Inc.
// james@akrobiz.com
//
// began: October 2003
//
// Copyright 2003, 04, 05, 06, 07, 08, 09, 10, 11, 12, 2013 James Lehman.
// This source is distributed under the terms of the GNU General Public License.
//
// LaserBoy_GUI_base.hpp is part of LaserBoy.
//
// LaserBoy is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// LaserBoy is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with LaserBoy. If not, see <http://www.gnu.org/licenses/>.
//
//############################################################################
#ifndef __LASERBOY_GUI_BASE_DEFINITIONS__
#define __LASERBOY_GUI_BASE_DEFINITIONS__

#include "LaserBoy_TUI.hpp"

//############################################################################
class LaserBoy_GUI_base
{
public:
    LaserBoy_GUI_base(int x, int y)
        : running            (false)
        , prompt_escaped     (false)
        , teminate_requested (false)
        , xres               (x    )
        , yres               (y    )
        , space              (this )
                          {}
    //------------------------------------------------------------------------
virtual
   ~LaserBoy_GUI_base()   {}
    //------------------------------------------------------------------------
virtual void               display_space                              (             ) = 0;
virtual LaserBoy_color     display_prompt_and_echo_color              (string prompt) = 0;
virtual LaserBoy_3D_short  display_prompt_and_echo_3D_short           (string prompt) = 0;
virtual LaserBoy_3D_double display_prompt_and_echo_3D_double          (string prompt) = 0;
virtual string             display_prompt_file_with_auto_complete     (string prompt, string part) = 0;
virtual string             display_prompt_dir_with_auto_complete      (string prompt) = 0;
virtual string             display_prompt_f_effect_with_auto_complete (string prompt) = 0;
virtual string             display_prompt_fs_effect_with_auto_complete(string prompt) = 0;
virtual string             display_prompt_and_echo_name               (string prompt) = 0;
virtual string             display_prompt_and_echo_string             (string prompt) = 0;
virtual double             display_prompt_and_echo_double             (string prompt, double value) = 0;
virtual int                display_prompt_and_echo_int                (string prompt, int    value) = 0;
virtual int                display_prompt_and_echo_nibble             (string prompt) = 0;
virtual bool               display_prompt_and_echo_bool               (string prompt) = 0;
virtual void               display_error                              (string err   ) = 0;
virtual void               display_state                              (string state ) = 0;
virtual void               display_progress                           (int countdown) = 0;
    //------------------------------------------------------------------------
    bool   running,
           prompt_escaped,
           teminate_requested;

    int    xres,
           yres;

    string file_name;

    LaserBoy_TUI space;
};

//############################################################################
#endif

//############################################################################
//////////////////////////////////////////////////////////////////////////////
//############################################################################
