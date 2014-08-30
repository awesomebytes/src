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
// LaserBoy_palette_set.hpp is part of LaserBoy.
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
#ifndef __LASERBOY_PALETTE_SET_DEFINITIONS__
#define __LASERBOY_PALETTE_SET_DEFINITIONS__

//############################################################################
#include "LaserBoy_palette.hpp"

//############################################################################
class LaserBoy_palette_set : public LaserBoy_palette_set_base
{
public:
    LaserBoy_palette_set(LaserBoy_space* ps = NULL)
                  : p_space                (ps),
                    palette_index          (LASERBOY_ILDA_DEFAULT),
                    target_palette_index   (0),
                    selected_color_index   (0)
                    {
                        populate_palette_set();
                    }
    //------------------------------------------------------------------------
virtual
   ~LaserBoy_palette_set()
                    {
                        clear();
                    }
    //------------------------------------------------------------------------
    LaserBoy_palette_set& replace_palette_set(const LaserBoy_palette_set& palette_set)
                    {
                        clear();
                        insert(begin(), palette_set.begin(), palette_set.end());
                        return *this;
                    }
    //------------------------------------------------------------------------
    LaserBoy_palette_set& operator = (const LaserBoy_palette_set& palette_set)
                    {
                        clear();
                        reserve(palette_set.size());
                        insert(begin(), palette_set.begin(), palette_set.end());
                        p_space = palette_set.p_space;
                        return *this;
                    }
    //------------------------------------------------------------------------
    LaserBoy_palette_set& operator += (const LaserBoy_palette_set& palette_set)
                    {
                        reserve(size() + palette_set.size());
                        insert(end(), palette_set.begin(), palette_set.end());
                        return *this;
                    }
    //------------------------------------------------------------------------
    LaserBoy_palette_set& operator += (const LaserBoy_palette& palette)
                    {
                        push_back(palette);
                        return *this;
                    }
    //------------------------------------------------------------------------
    LaserBoy_palette_set& push_back_palette(const LaserBoy_palette& palette)
                    {
                        push_back(palette);
                        return *this;
                    }
    //------------------------------------------------------------------------
    void  set_palette_index(int index) //sets palette_index
            {
                if(number_of_palettes())
                {
                    if(index >= number_of_palettes())
                        index = 0;
                    if(index < 0)
                        index = number_of_palettes() - 1;
                    palette_index = index;
                }
                else
                    palette_index = 0;
            }
    //------------------------------------------------------------------------
    void  set_target_palette_index(int index) //sets target_palette_index
            {
                if(number_of_palettes())
                {
                    if(index >= number_of_palettes())
                        index = 0;
                    if(index < 0)
                        index = number_of_palettes() - 1;
                    target_palette_index = index;
                }
                else
                    target_palette_index = 0;
            }
    //------------------------------------------------------------------------
    LaserBoy_palette&  palette(int index) //sets palette_index
                    {
                        if(number_of_palettes())
                        {
                            if(index >= number_of_palettes())
                                index = 0;
                            if(index < 0)
                                index = number_of_palettes() - 1;
                            palette_index = index;
                            return at(palette_index);
                        }
                        return front();
                    }
    //------------------------------------------------------------------------
    LaserBoy_palette&  target_palette(int index) //sets target_palette_index
                    {
                        if(number_of_palettes())
                        {
                            if(index >= number_of_palettes())
                                index = 0;
                            if(index < 0)
                                index = number_of_palettes() - 1;
                            target_palette_index = index;
                            return at(target_palette_index);
                        }
                        return front();
                    }
    //------------------------------------------------------------------------
    LaserBoy_palette& current_palette()
                    {
                        if(palette_index != LASERBOY_TRUE_COLOR)
                            return at(palette_index);
                        return at(target_palette_index);
                    }
    //------------------------------------------------------------------------
    LaserBoy_palette& target_palette()
                    {
                        return at(target_palette_index);
                    }
    //------------------------------------------------------------------------
    void delete_current_palette()
                    {
                        if(number_of_palettes())
                            erase(begin() + palette_index);
                        return;
                    }
    //------------------------------------------------------------------------
    bool palettes_from_txt_file(string file)
                    {
                        ifstream in;
                        in.open(file.c_str(), ios::in);
                        if(in.is_open())
                        {
                            palettes_from_ifstream_txt(in);
                            in.close();
                            return true;
                        }
                        return false;
                    }
    //------------------------------------------------------------------------
    int  name_to_palette_index(string name)
                    {
                        for(int i = 0; i < number_of_palettes(); i++)
                            if(at(i).name == name)
                                return i;
                        return LASERBOY_NOT_FOUND;
                    }
    //------------------------------------------------------------------------
    int               number_of_palettes          () const { return (int)size(); }
    LaserBoy_palette& palette_picker              (int index);
    LaserBoy_palette  const_palette_picker        (int index) const;
    //------------------------------------------------------------------------
    int               palette_from_ifstream_txt   (   ifstream&     in
                                                    , const int&    format_1
                                                    , int&          line_number
                                                    , const string& name = ""
                                                  );
    //------------------------------------------------------------------------
    int               palettes_from_ifstream_txt  (ifstream& in);
    //------------------------------------------------------------------------
    void              populate_palette_set        ()        ;
    void              add_palette                 ();
    void              copy_palette                (int index);
    void              set_selected_color_index    (u_char c );
    //------------------------------------------------------------------------
    LaserBoy_space*   p_space;

    int               palette_index,
                      target_palette_index,
                      selected_color_index;

    static int        new_palette_id;
    static int        new_super_palette_id;
    //------------------------------------------------------------------------
};

//############################################################################
#endif

//############################################################################
//////////////////////////////////////////////////////////////////////////////
//############################################################################
