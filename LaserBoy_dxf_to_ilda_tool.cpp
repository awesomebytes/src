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
// LaserBoy.cpp is part of LaserBoy.
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
#include "LaserBoy_SDL_GUI.hpp"
#include <iostream>
#include "LaserBoy_frame.hpp"
//############################################################################
int main(int argc, char *argv[])
{


      LaserBoy_SDL_GUI LaserBoy_App(1,1);
      LaserBoy_space space(&LaserBoy_App);
      LaserBoy_frame frame(&space);
      space.from_dxf_file(argv[1]);

      //changing ild file format
      space.dumb_file_format = !space.dumb_file_format;
      //if(space.dumb_file_format)
      //  space.TUI_clue = "ild 4,5";
      //else
      //  space.TUI_clue = "ild 0,1,2,(!3)";
      //
      space.current_frame().minimize(0); // get rid of useless segments
      space.current_frame().optimize(0); // interpolate points to correct projection
      space.current_frame().quarter_turn(0, 3); // rotate CCW 90 degrees
      // use the power of charmander to rotate over X Z plane
      char mander; // it's a cool pokemon
      //select all segments
      space.current_frame().egg = 0; // select first  vertex
      space.current_frame().spider = (space.current_frame().number_of_vertices() - 1); // select last vertex
      space.rotation_step = 45.0 * one_degree; // rotate 45 degree
      cout << "fulcrum is x: " << space.current_frame().p_space->fulcrum.x << " y: " << space.current_frame().p_space->fulcrum.y << " z: " << space.current_frame().p_space->fulcrum.z;
      // fulcrum, which is something like the rotation central point
      // by default is 0 0 0
      space.current_frame().p_space->fulcrum.x = -1.0;
      space.current_frame().p_space->fulcrum.y = 0.0;
      space.current_frame().p_space->fulcrum.z = 0.0;
      space.current_frame().rotate_selection(LaserBoy_3D_double(0, space.rotation_step, 0));
      space.current_frame().save_as_ild(argv[2]);


      return 0;
}

//############################################################################
//////////////////////////////////////////////////////////////////////////////
//############################################################################
