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
// LaserBoy_palette_set.cpp is part of LaserBoy.
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
#include "LaserBoy_space.hpp"

//############################################################################
int LaserBoy_palette_set::new_palette_id       = 0;
int LaserBoy_palette_set::new_super_palette_id = 0;

//############################################################################
LaserBoy_palette& LaserBoy_palette_set::palette_picker(int index)
{
    if(index == LASERBOY_TRUE_COLOR)
        return at(target_palette_index);
    if(index < 0)
        index = number_of_palettes() - 1;
    else if(index >= number_of_palettes())
        index = 0;
    return at(index);
}

//############################################################################
LaserBoy_palette LaserBoy_palette_set::const_palette_picker(int index) const
{
    if(index == LASERBOY_TRUE_COLOR)
        return at(target_palette_index);

    if(index < 0)
        index = number_of_palettes() - 1;
    else if(index >= number_of_palettes())
        index = 0;

    return at(index);
}

//############################################################################
int LaserBoy_palette_set::palette_from_ifstream_txt(ifstream&     in,
                                                    const int&    format_1,
                                                    int&          line_number,
                                                    const string& name
                                                   )
{
    LaserBoy_palette palette(p_space);
    if(palette.from_ifstream_txt(in, format_1, line_number))
    {
        if(name.size())
            palette.name = name;
        else
        {
            char palette_name[8];
            sprintf(palette_name, "%07d", p_space->new_palette_id++);
            palette.name = string("P") + palette_name;
        }
        push_back(palette);
        palette_index = p_space->number_of_palettes() - 1;
    }
    return LASERBOY_OK;
}

//############################################################################
int LaserBoy_palette_set::palettes_from_ifstream_txt(ifstream& in)
{
    int               line_number = 1,
                      named_palette_index;

    string            word;
    //------------------------------------------------------------------------
    while(in.good())
    {
        clear_to_alpha(in, line_number);
        if(get_next_word(in, word, line_number))
        {
            if(word == "frame")
            {
            }
            else if(word == "table")
            {
            }
            else if(word == "palette")
            {
                // palette
                if(get_next_word(in, word, line_number))
                {
                    if(word == "named")
                    {
                        if(get_next_word(in, word, line_number))
                        {
                            // palette named name
                            named_palette_index = p_space->name_to_palette_index(word);
                            if(named_palette_index == LASERBOY_NOT_FOUND)
                                cout << "error on line: " << line_number << " \'" << word << "\' is not a valid LaserBoy palette name." << ENDL;
                            else
                                p_space->palette_index = named_palette_index;
                        }
                        else
                            // palette named [no-name]
                            cout << "error on line: " << line_number << " LaserBoy palette name is missing." << ENDL;
                    }
                    else if(word == "rgb")
                    {
                        if(get_next_word(in, word, line_number))
                        {
                            // palette rgb name
                            named_palette_index = p_space->name_to_palette_index(word);
                            if(named_palette_index == LASERBOY_NOT_FOUND)
                                p_space->palette_from_ifstream_txt(in, LASERBOY_RGB, line_number, word);
                            else
                                p_space->palette_index = named_palette_index;
                        }
                        else
                            // palette rgb [no-name]
                            p_space->palette_from_ifstream_txt(in, LASERBOY_RGB, line_number);
                    }
                    else if(word == "hex")
                    {
                        if(get_next_word(in, word, line_number))
                        {
                            // palette hex name
                            named_palette_index = p_space->name_to_palette_index(word);
                            if(named_palette_index == LASERBOY_NOT_FOUND)
                                p_space->palette_from_ifstream_txt(in, LASERBOY_HEX, line_number, word);
                            else
                                p_space->palette_index = named_palette_index;
                        }
                        else
                            // palette hex [no-name]
                            p_space->palette_from_ifstream_txt(in, LASERBOY_HEX, line_number);
                    }
                    else
                        // palette bad_word!
                        cout << "error on line: " << line_number << " \'" << word << "\' is not a LaserBoy text format token." << ENDL;
                }
                else
                    // palette rgb [no-name]
                    p_space->palette_from_ifstream_txt(in, LASERBOY_RGB, line_number);
            }
        } // end if(get_next_word(in, word, line_number))
    } // end while(in.good())
    //------------------------------------------------------------------------
    return LASERBOY_OK;
}

//############################################################################
void LaserBoy_palette_set::populate_palette_set()
{
    LaserBoy_palette  palette(p_space);
    u_char        r = 0,
                  g = 0,
                  b = 0,
                  shift;
    int           i,
                  hue;
    //------------------------------------------------------------------------
    reserve(LASERBOY_BUILT_IN_PALETTES);
    //------------------------------------------------------------------------
    palette.reserve(256);
    palette.name = "Default_";
    palette.first = 0;
    palette.push_back(LaserBoy_color(0xff, 0x00, 0x00));
    palette.push_back(LaserBoy_color(0xff, 0x10, 0x00));
    palette.push_back(LaserBoy_color(0xff, 0x20, 0x00));
    palette.push_back(LaserBoy_color(0xff, 0x30, 0x00));
    palette.push_back(LaserBoy_color(0xff, 0x40, 0x00));
    palette.push_back(LaserBoy_color(0xff, 0x50, 0x00));
    palette.push_back(LaserBoy_color(0xff, 0x60, 0x00));
    palette.push_back(LaserBoy_color(0xff, 0x70, 0x00));
    palette.push_back(LaserBoy_color(0xff, 0x80, 0x00));
    palette.push_back(LaserBoy_color(0xff, 0x90, 0x00));
    palette.push_back(LaserBoy_color(0xff, 0xa0, 0x00));
    palette.push_back(LaserBoy_color(0xff, 0xb0, 0x00));
    palette.push_back(LaserBoy_color(0xff, 0xc0, 0x00));
    palette.push_back(LaserBoy_color(0xff, 0xd0, 0x00));
    palette.push_back(LaserBoy_color(0xff, 0xe0, 0x00));
    palette.push_back(LaserBoy_color(0xff, 0xf0, 0x00));
    palette.push_back(LaserBoy_color(0xff, 0xff, 0x00));
    palette.push_back(LaserBoy_color(0xe0, 0xff, 0x00));
    palette.push_back(LaserBoy_color(0xc0, 0xff, 0x00));
    palette.push_back(LaserBoy_color(0xa0, 0xff, 0x00));
    palette.push_back(LaserBoy_color(0x80, 0xff, 0x00));
    palette.push_back(LaserBoy_color(0x60, 0xff, 0x00));
    palette.push_back(LaserBoy_color(0x40, 0xff, 0x00));
    palette.push_back(LaserBoy_color(0x20, 0xff, 0x00));
    palette.push_back(LaserBoy_color(0x00, 0xff, 0x00));
    palette.push_back(LaserBoy_color(0x00, 0xff, 0x20));
    palette.push_back(LaserBoy_color(0x00, 0xff, 0x40));
    palette.push_back(LaserBoy_color(0x00, 0xff, 0x60));
    palette.push_back(LaserBoy_color(0x00, 0xff, 0x80));
    palette.push_back(LaserBoy_color(0x00, 0xff, 0xa0));
    palette.push_back(LaserBoy_color(0x00, 0xff, 0xc0));
    palette.push_back(LaserBoy_color(0x00, 0xff, 0xe0));
    palette.push_back(LaserBoy_color(0x00, 0x82, 0xff));
    palette.push_back(LaserBoy_color(0x00, 0x72, 0xff));
    palette.push_back(LaserBoy_color(0x00, 0x68, 0xff));
    palette.push_back(LaserBoy_color(0x0a, 0x60, 0xff));
    palette.push_back(LaserBoy_color(0x00, 0x52, 0xff));
    palette.push_back(LaserBoy_color(0x00, 0x4a, 0xff));
    palette.push_back(LaserBoy_color(0x00, 0x40, 0xff));
    palette.push_back(LaserBoy_color(0x00, 0x20, 0xff));
    palette.push_back(LaserBoy_color(0x00, 0x00, 0xff));
    palette.push_back(LaserBoy_color(0x20, 0x00, 0xff));
    palette.push_back(LaserBoy_color(0x40, 0x00, 0xff));
    palette.push_back(LaserBoy_color(0x60, 0x00, 0xff));
    palette.push_back(LaserBoy_color(0x80, 0x00, 0xff));
    palette.push_back(LaserBoy_color(0xa0, 0x00, 0xff));
    palette.push_back(LaserBoy_color(0xe0, 0x00, 0xff));
    palette.push_back(LaserBoy_color(0xff, 0x00, 0xff));
    palette.push_back(LaserBoy_color(0xff, 0x20, 0xff));
    palette.push_back(LaserBoy_color(0xff, 0x40, 0xff));
    palette.push_back(LaserBoy_color(0xff, 0x60, 0xff));
    palette.push_back(LaserBoy_color(0xff, 0x80, 0xff));
    palette.push_back(LaserBoy_color(0xff, 0xa0, 0xff));
    palette.push_back(LaserBoy_color(0xff, 0xc0, 0xff));
    palette.push_back(LaserBoy_color(0xff, 0xe0, 0xff));
    palette.push_back(LaserBoy_color(0xff, 0xff, 0xff)); // white 55
    palette.white = palette.number_of_colors() - 1;
    palette.push_back(LaserBoy_color(0xff, 0xe0, 0xe0));
    palette.push_back(LaserBoy_color(0xff, 0xff, 0xff));
    palette.push_back(LaserBoy_color(0xff, 0xa0, 0xa0));
    palette.push_back(LaserBoy_color(0xff, 0x80, 0x80));
    palette.push_back(LaserBoy_color(0xff, 0x60, 0x60));
    palette.push_back(LaserBoy_color(0xff, 0x40, 0x40));
    palette.push_back(LaserBoy_color(0xff, 0x20, 0x20)); // last unique
    palette.last  = palette.number_of_colors() - 1;
    palette.push_back(LaserBoy_color(0x80, 0x80, 0x80)); // gray
    palette.push_back(LaserBoy_color(0x00, 0x00, 0x00)); // black
    palette.black = palette.number_of_colors() - 1;
    push_back(palette);
    palette.clear();
    //------------------------------------------------------------------------
    palette.reserve(256);
    palette.name = "X29_____";
    palette.push_back(LaserBoy_color(0x00, 0x00, 0x00)); // black
    palette.black = palette.number_of_colors() - 1;
    palette.push_back(LaserBoy_color(0x00, 0x00, 0x00));
    palette.push_back(LaserBoy_color(0xff, 0x00, 0x00));
    palette.first = palette.number_of_colors() - 1;
    palette.push_back(LaserBoy_color(0xff, 0x00, 0x00));
    palette.push_back(LaserBoy_color(0xff, 0xff, 0x00));
    palette.push_back(LaserBoy_color(0xff, 0xff, 0x00));
    palette.push_back(LaserBoy_color(0x00, 0xff, 0x00));
    palette.push_back(LaserBoy_color(0x00, 0xff, 0x00));
    palette.push_back(LaserBoy_color(0x80, 0x80, 0x00));
    palette.push_back(LaserBoy_color(0x80, 0x80, 0x00));
    palette.push_back(LaserBoy_color(0x00, 0x00, 0xff));
    palette.push_back(LaserBoy_color(0x00, 0x00, 0xff));
    palette.push_back(LaserBoy_color(0xff, 0x00, 0xff));
    palette.push_back(LaserBoy_color(0xff, 0x00, 0xff));
    palette.push_back(LaserBoy_color(0xff, 0xff, 0xff)); // white
    palette.white = palette.number_of_colors() - 1;
    palette.push_back(LaserBoy_color(0xff, 0xff, 0xff));
    palette.push_back(LaserBoy_color(0x00, 0xff, 0xff));
    palette.push_back(LaserBoy_color(0x00, 0xff, 0xff));
    palette.push_back(LaserBoy_color(0x00, 0xff, 0xff));
    palette.push_back(LaserBoy_color(0x00, 0xff, 0xff)); //last unique
    palette.last  = palette.number_of_colors() - 1;
    palette.push_back(LaserBoy_color(0x80, 0x80, 0x80)); // gray
    push_back(palette);
    palette.clear();
    //------------------------------------------------------------------------
    palette.reserve(256);
    palette.name = "ILDA_std";
    palette.push_back(LaserBoy_color(0x00, 0x00, 0x00)); // black
    palette.black = palette.number_of_colors() - 1;
    palette.push_back(LaserBoy_color(0xff, 0xff, 0xff)); // white
    palette.white = palette.number_of_colors() - 1;
    palette.first = palette.number_of_colors() - 1;  // first
    palette.push_back(LaserBoy_color(0xff, 0x00, 0x00));
    palette.first = palette.number_of_colors() - 1;
    palette.push_back(LaserBoy_color(0xff, 0xff, 0x00));
    palette.push_back(LaserBoy_color(0x00, 0xff, 0x00));
    palette.push_back(LaserBoy_color(0x00, 0xff, 0xff));
    palette.push_back(LaserBoy_color(0x00, 0x00, 0xff));
    palette.push_back(LaserBoy_color(0xff, 0x00, 0xff));
    palette.push_back(LaserBoy_color(0xff, 0x80, 0x80));
    palette.push_back(LaserBoy_color(0xff, 0x8c, 0x80));
    palette.push_back(LaserBoy_color(0xff, 0x97, 0x80));
    palette.push_back(LaserBoy_color(0xff, 0xa3, 0x80));
    palette.push_back(LaserBoy_color(0xff, 0xae, 0x80));
    palette.push_back(LaserBoy_color(0xff, 0xba, 0x80));
    palette.push_back(LaserBoy_color(0xff, 0xc5, 0x80));
    palette.push_back(LaserBoy_color(0xff, 0xd1, 0x80));
    palette.push_back(LaserBoy_color(0xff, 0xdc, 0x80));
    palette.push_back(LaserBoy_color(0xff, 0xe8, 0x80));
    palette.push_back(LaserBoy_color(0xff, 0xf3, 0x80));
    palette.push_back(LaserBoy_color(0xff, 0xff, 0x80));
    palette.push_back(LaserBoy_color(0xf3, 0xff, 0x80));
    palette.push_back(LaserBoy_color(0xe8, 0xff, 0x80));
    palette.push_back(LaserBoy_color(0xdc, 0xff, 0x80));
    palette.push_back(LaserBoy_color(0xd1, 0xff, 0x80));
    palette.push_back(LaserBoy_color(0xc5, 0xff, 0x80));
    palette.push_back(LaserBoy_color(0xba, 0xff, 0x80));
    palette.push_back(LaserBoy_color(0xae, 0xff, 0x80));
    palette.push_back(LaserBoy_color(0xa3, 0xff, 0x80));
    palette.push_back(LaserBoy_color(0x97, 0xff, 0x80));
    palette.push_back(LaserBoy_color(0x8c, 0xff, 0x80));
    palette.push_back(LaserBoy_color(0x80, 0xff, 0x80));
    palette.push_back(LaserBoy_color(0x80, 0xff, 0x8c));
    palette.push_back(LaserBoy_color(0x80, 0xff, 0x97));
    palette.push_back(LaserBoy_color(0x80, 0xff, 0xa3));
    palette.push_back(LaserBoy_color(0x80, 0xff, 0xae));
    palette.push_back(LaserBoy_color(0x80, 0xff, 0xba));
    palette.push_back(LaserBoy_color(0x80, 0xff, 0xc5));
    palette.push_back(LaserBoy_color(0x80, 0xff, 0xd1));
    palette.push_back(LaserBoy_color(0x80, 0xff, 0xdc));
    palette.push_back(LaserBoy_color(0x80, 0xff, 0xe8));
    palette.push_back(LaserBoy_color(0x80, 0xff, 0xf3));
    palette.push_back(LaserBoy_color(0x80, 0xff, 0xff));
    palette.push_back(LaserBoy_color(0x80, 0xf3, 0xff));
    palette.push_back(LaserBoy_color(0x80, 0xe8, 0xff));
    palette.push_back(LaserBoy_color(0x80, 0xdc, 0xff));
    palette.push_back(LaserBoy_color(0x80, 0xd1, 0xff));
    palette.push_back(LaserBoy_color(0x80, 0xc5, 0xff));
    palette.push_back(LaserBoy_color(0x80, 0xba, 0xff));
    palette.push_back(LaserBoy_color(0x80, 0xae, 0xff));
    palette.push_back(LaserBoy_color(0x80, 0xa3, 0xff));
    palette.push_back(LaserBoy_color(0x80, 0x97, 0xff));
    palette.push_back(LaserBoy_color(0x80, 0x8c, 0xff));
    palette.push_back(LaserBoy_color(0x80, 0x80, 0xff));
    palette.push_back(LaserBoy_color(0x8c, 0x80, 0xff));
    palette.push_back(LaserBoy_color(0x97, 0x80, 0xff));
    palette.push_back(LaserBoy_color(0xa3, 0x80, 0xff));
    palette.push_back(LaserBoy_color(0xae, 0x80, 0xff));
    palette.push_back(LaserBoy_color(0xba, 0x80, 0xff));
    palette.push_back(LaserBoy_color(0xc5, 0x80, 0xff));
    palette.push_back(LaserBoy_color(0xd1, 0x80, 0xff));
    palette.push_back(LaserBoy_color(0xdc, 0x80, 0xff));
    palette.push_back(LaserBoy_color(0xe8, 0x80, 0xff));
    palette.push_back(LaserBoy_color(0xf3, 0x80, 0xff));
    palette.push_back(LaserBoy_color(0xff, 0x80, 0xff));
    palette.push_back(LaserBoy_color(0xff, 0x80, 0xf3));
    palette.push_back(LaserBoy_color(0xff, 0x80, 0xe8));
    palette.push_back(LaserBoy_color(0xff, 0x80, 0xdc));
    palette.push_back(LaserBoy_color(0xff, 0x80, 0xd1));
    palette.push_back(LaserBoy_color(0xff, 0x80, 0xc5));
    palette.push_back(LaserBoy_color(0xff, 0x80, 0xba));
    palette.push_back(LaserBoy_color(0xff, 0x80, 0xae));
    palette.push_back(LaserBoy_color(0xff, 0x80, 0xa3));
    palette.push_back(LaserBoy_color(0xff, 0x80, 0x97));
    palette.push_back(LaserBoy_color(0xff, 0x80, 0x8c));
    palette.push_back(LaserBoy_color(0xff, 0x00, 0x00));
    palette.push_back(LaserBoy_color(0xff, 0x17, 0x00));
    palette.push_back(LaserBoy_color(0xff, 0x2e, 0x00));
    palette.push_back(LaserBoy_color(0xff, 0x46, 0x00));
    palette.push_back(LaserBoy_color(0xff, 0x5d, 0x00));
    palette.push_back(LaserBoy_color(0xff, 0x74, 0x00));
    palette.push_back(LaserBoy_color(0xff, 0x8b, 0x00));
    palette.push_back(LaserBoy_color(0xff, 0xa2, 0x00));
    palette.push_back(LaserBoy_color(0xff, 0xb9, 0x00));
    palette.push_back(LaserBoy_color(0xff, 0xd1, 0x00));
    palette.push_back(LaserBoy_color(0xff, 0xe8, 0x00));
    palette.push_back(LaserBoy_color(0xff, 0xff, 0x00));
    palette.push_back(LaserBoy_color(0xe8, 0xff, 0x00));
    palette.push_back(LaserBoy_color(0xd1, 0xff, 0x00));
    palette.push_back(LaserBoy_color(0xb9, 0xff, 0x00));
    palette.push_back(LaserBoy_color(0xa2, 0xff, 0x00));
    palette.push_back(LaserBoy_color(0x8b, 0xff, 0x00));
    palette.push_back(LaserBoy_color(0x74, 0xff, 0x00));
    palette.push_back(LaserBoy_color(0x5d, 0xff, 0x00));
    palette.push_back(LaserBoy_color(0x46, 0xff, 0x00));
    palette.push_back(LaserBoy_color(0x2e, 0xff, 0x00));
    palette.push_back(LaserBoy_color(0x17, 0xff, 0x00));
    palette.push_back(LaserBoy_color(0x00, 0xff, 0x00));
    palette.push_back(LaserBoy_color(0x00, 0xff, 0x17));
    palette.push_back(LaserBoy_color(0x00, 0xff, 0x2e));
    palette.push_back(LaserBoy_color(0x00, 0xff, 0x46));
    palette.push_back(LaserBoy_color(0x00, 0xff, 0x5d));
    palette.push_back(LaserBoy_color(0x00, 0xff, 0x74));
    palette.push_back(LaserBoy_color(0x00, 0xff, 0x8b));
    palette.push_back(LaserBoy_color(0x00, 0xff, 0xa2));
    palette.push_back(LaserBoy_color(0x00, 0xff, 0xb9));
    palette.push_back(LaserBoy_color(0x00, 0xff, 0xd1));
    palette.push_back(LaserBoy_color(0x00, 0xff, 0xe8));
    palette.push_back(LaserBoy_color(0x00, 0xff, 0xff));
    palette.push_back(LaserBoy_color(0x00, 0xe8, 0xff));
    palette.push_back(LaserBoy_color(0x00, 0xd1, 0xff));
    palette.push_back(LaserBoy_color(0x00, 0xb9, 0xff));
    palette.push_back(LaserBoy_color(0x00, 0xa2, 0xff));
    palette.push_back(LaserBoy_color(0x00, 0x8b, 0xff));
    palette.push_back(LaserBoy_color(0x00, 0x74, 0xff));
    palette.push_back(LaserBoy_color(0x00, 0x5d, 0xff));
    palette.push_back(LaserBoy_color(0x00, 0x46, 0xff));
    palette.push_back(LaserBoy_color(0x00, 0x2e, 0xff));
    palette.push_back(LaserBoy_color(0x00, 0x17, 0xff));
    palette.push_back(LaserBoy_color(0x00, 0x00, 0xff));
    palette.push_back(LaserBoy_color(0x17, 0x00, 0xff));
    palette.push_back(LaserBoy_color(0x2e, 0x00, 0xff));
    palette.push_back(LaserBoy_color(0x46, 0x00, 0xff));
    palette.push_back(LaserBoy_color(0x5d, 0x00, 0xff));
    palette.push_back(LaserBoy_color(0x74, 0x00, 0xff));
    palette.push_back(LaserBoy_color(0x8b, 0x00, 0xff));
    palette.push_back(LaserBoy_color(0xa2, 0x00, 0xff));
    palette.push_back(LaserBoy_color(0xb9, 0x00, 0xff));
    palette.push_back(LaserBoy_color(0xd1, 0x00, 0xff));
    palette.push_back(LaserBoy_color(0xe8, 0x00, 0xff));
    palette.push_back(LaserBoy_color(0xff, 0x00, 0xff));
    palette.push_back(LaserBoy_color(0xff, 0x00, 0xe8));
    palette.push_back(LaserBoy_color(0xff, 0x00, 0xd1));
    palette.push_back(LaserBoy_color(0xff, 0x00, 0xb9));
    palette.push_back(LaserBoy_color(0xff, 0x00, 0xa2));
    palette.push_back(LaserBoy_color(0xff, 0x00, 0x8b));
    palette.push_back(LaserBoy_color(0xff, 0x00, 0x74));
    palette.push_back(LaserBoy_color(0xff, 0x00, 0x5d));
    palette.push_back(LaserBoy_color(0xff, 0x00, 0x46));
    palette.push_back(LaserBoy_color(0xff, 0x00, 0x2e));
    palette.push_back(LaserBoy_color(0xff, 0x00, 0x17));
    palette.push_back(LaserBoy_color(0x80, 0x00, 0x00));
    palette.push_back(LaserBoy_color(0x80, 0x0c, 0x00));
    palette.push_back(LaserBoy_color(0x80, 0x17, 0x00));
    palette.push_back(LaserBoy_color(0x80, 0x23, 0x00));
    palette.push_back(LaserBoy_color(0x80, 0x2f, 0x00));
    palette.push_back(LaserBoy_color(0x80, 0x3a, 0x00));
    palette.push_back(LaserBoy_color(0x80, 0x46, 0x00));
    palette.push_back(LaserBoy_color(0x80, 0x51, 0x00));
    palette.push_back(LaserBoy_color(0x80, 0x5d, 0x00));
    palette.push_back(LaserBoy_color(0x80, 0x69, 0x00));
    palette.push_back(LaserBoy_color(0x80, 0x74, 0x00));
    palette.push_back(LaserBoy_color(0x80, 0x80, 0x00));
    palette.push_back(LaserBoy_color(0x74, 0x80, 0x00));
    palette.push_back(LaserBoy_color(0x69, 0x80, 0x00));
    palette.push_back(LaserBoy_color(0x5d, 0x80, 0x00));
    palette.push_back(LaserBoy_color(0x51, 0x80, 0x00));
    palette.push_back(LaserBoy_color(0x46, 0x80, 0x00));
    palette.push_back(LaserBoy_color(0x3a, 0x80, 0x00));
    palette.push_back(LaserBoy_color(0x2f, 0x80, 0x00));
    palette.push_back(LaserBoy_color(0x23, 0x80, 0x00));
    palette.push_back(LaserBoy_color(0x17, 0x80, 0x00));
    palette.push_back(LaserBoy_color(0x0c, 0x80, 0x00));
    palette.push_back(LaserBoy_color(0x00, 0x80, 0x00));
    palette.push_back(LaserBoy_color(0x00, 0x80, 0x0c));
    palette.push_back(LaserBoy_color(0x00, 0x80, 0x17));
    palette.push_back(LaserBoy_color(0x00, 0x80, 0x23));
    palette.push_back(LaserBoy_color(0x00, 0x80, 0x2f));
    palette.push_back(LaserBoy_color(0x00, 0x80, 0x3a));
    palette.push_back(LaserBoy_color(0x00, 0x80, 0x46));
    palette.push_back(LaserBoy_color(0x00, 0x80, 0x51));
    palette.push_back(LaserBoy_color(0x00, 0x80, 0x5d));
    palette.push_back(LaserBoy_color(0x00, 0x80, 0x69));
    palette.push_back(LaserBoy_color(0x00, 0x80, 0x74));
    palette.push_back(LaserBoy_color(0x00, 0x80, 0x80));
    palette.push_back(LaserBoy_color(0x00, 0x74, 0x80));
    palette.push_back(LaserBoy_color(0x00, 0x69, 0x80));
    palette.push_back(LaserBoy_color(0x00, 0x5d, 0x80));
    palette.push_back(LaserBoy_color(0x00, 0x51, 0x80));
    palette.push_back(LaserBoy_color(0x00, 0x46, 0x80));
    palette.push_back(LaserBoy_color(0x00, 0x3a, 0x80));
    palette.push_back(LaserBoy_color(0x00, 0x2f, 0x80));
    palette.push_back(LaserBoy_color(0x00, 0x23, 0x80));
    palette.push_back(LaserBoy_color(0x00, 0x17, 0x80));
    palette.push_back(LaserBoy_color(0x00, 0x0c, 0x80));
    palette.push_back(LaserBoy_color(0x00, 0x00, 0x80));
    palette.push_back(LaserBoy_color(0x0c, 0x00, 0x80));
    palette.push_back(LaserBoy_color(0x17, 0x00, 0x80));
    palette.push_back(LaserBoy_color(0x23, 0x00, 0x80));
    palette.push_back(LaserBoy_color(0x2f, 0x00, 0x80));
    palette.push_back(LaserBoy_color(0x3a, 0x00, 0x80));
    palette.push_back(LaserBoy_color(0x46, 0x00, 0x80));
    palette.push_back(LaserBoy_color(0x51, 0x00, 0x80));
    palette.push_back(LaserBoy_color(0x5d, 0x00, 0x80));
    palette.push_back(LaserBoy_color(0x69, 0x00, 0x80));
    palette.push_back(LaserBoy_color(0x74, 0x00, 0x80));
    palette.push_back(LaserBoy_color(0x80, 0x00, 0x80));
    palette.push_back(LaserBoy_color(0x80, 0x00, 0x74));
    palette.push_back(LaserBoy_color(0x80, 0x00, 0x69));
    palette.push_back(LaserBoy_color(0x80, 0x00, 0x5d));
    palette.push_back(LaserBoy_color(0x80, 0x00, 0x51));
    palette.push_back(LaserBoy_color(0x80, 0x00, 0x46));
    palette.push_back(LaserBoy_color(0x80, 0x00, 0x3a));
    palette.push_back(LaserBoy_color(0x80, 0x00, 0x2f));
    palette.push_back(LaserBoy_color(0x80, 0x00, 0x23));
    palette.push_back(LaserBoy_color(0x80, 0x00, 0x17));
    palette.push_back(LaserBoy_color(0x80, 0x00, 0x0c));
    palette.push_back(LaserBoy_color(0xff, 0xc0, 0xc0));
    palette.push_back(LaserBoy_color(0xff, 0x40, 0x40));
    palette.push_back(LaserBoy_color(0xc0, 0x00, 0x00));
    palette.push_back(LaserBoy_color(0x40, 0x00, 0x00));
    palette.push_back(LaserBoy_color(0xff, 0xff, 0xc0));
    palette.push_back(LaserBoy_color(0xff, 0xff, 0x40));
    palette.push_back(LaserBoy_color(0xc0, 0xc0, 0x00));
    palette.push_back(LaserBoy_color(0x40, 0x40, 0x00));
    palette.push_back(LaserBoy_color(0xc0, 0xff, 0xc0));
    palette.push_back(LaserBoy_color(0x40, 0xff, 0x40));
    palette.push_back(LaserBoy_color(0x00, 0xc0, 0x00));
    palette.push_back(LaserBoy_color(0x00, 0x40, 0x00));
    palette.push_back(LaserBoy_color(0xc0, 0xff, 0xff));
    palette.push_back(LaserBoy_color(0x40, 0xff, 0xff));
    palette.push_back(LaserBoy_color(0x00, 0xc0, 0xc0));
    palette.push_back(LaserBoy_color(0x00, 0x40, 0x40));
    palette.push_back(LaserBoy_color(0xc0, 0xc0, 0xff));
    palette.push_back(LaserBoy_color(0x40, 0x40, 0xff));
    palette.push_back(LaserBoy_color(0x00, 0x00, 0xc0));
    palette.push_back(LaserBoy_color(0x00, 0x00, 0x40));
    palette.push_back(LaserBoy_color(0xff, 0xc0, 0xff));
    palette.push_back(LaserBoy_color(0xff, 0x40, 0xff));
    palette.push_back(LaserBoy_color(0xc0, 0x00, 0xc0));
    palette.push_back(LaserBoy_color(0x40, 0x00, 0x40));
    palette.push_back(LaserBoy_color(0xff, 0x60, 0x60));
    palette.push_back(LaserBoy_color(0xff, 0xff, 0xff)); // white
    palette.push_back(LaserBoy_color(0xf5, 0xf5, 0xf5));
    palette.push_back(LaserBoy_color(0xeb, 0xeb, 0xeb));
    palette.push_back(LaserBoy_color(0xe0, 0xe0, 0xe0));
    palette.push_back(LaserBoy_color(0xd5, 0xd5, 0xd5));
    palette.push_back(LaserBoy_color(0xcb, 0xcb, 0xcb));
    palette.push_back(LaserBoy_color(0xc0, 0xc0, 0xc0));
    palette.push_back(LaserBoy_color(0xb5, 0xb5, 0xb5));
    palette.push_back(LaserBoy_color(0xab, 0xab, 0xab));
    palette.push_back(LaserBoy_color(0xa0, 0xa0, 0xa0));
    palette.push_back(LaserBoy_color(0x95, 0x95, 0x95));
    palette.push_back(LaserBoy_color(0x8b, 0x8b, 0x8b));
    palette.push_back(LaserBoy_color(0x80, 0x80, 0x80)); // gray
    palette.push_back(LaserBoy_color(0x75, 0x75, 0x75));
    palette.push_back(LaserBoy_color(0x6b, 0x6b, 0x6b));
    palette.push_back(LaserBoy_color(0x60, 0x60, 0x60));
    palette.push_back(LaserBoy_color(0x55, 0x55, 0x55));
    palette.push_back(LaserBoy_color(0x4b, 0x4b, 0x4b));
    palette.push_back(LaserBoy_color(0x40, 0x40, 0x40));
    palette.push_back(LaserBoy_color(0x35, 0x35, 0x35));
    palette.push_back(LaserBoy_color(0x2b, 0x2b, 0x2b));
    palette.push_back(LaserBoy_color(0x20, 0x20, 0x20));
    palette.push_back(LaserBoy_color(0x15, 0x15, 0x15));
    palette.push_back(LaserBoy_color(0x0b, 0x0b, 0x0b));
    palette.last  = palette.number_of_colors() - 1;  // last
    palette.push_back(LaserBoy_color(0x00, 0x00, 0x00)); // black
    push_back(palette);
    palette.clear();
    //------------------------------------------------------------------------
    palette.reserve(256);
    palette.name = "DXF_____";
    palette.push_back(LaserBoy_color(0x00, 0x00, 0x00));
    palette.black = palette.number_of_colors() - 1;  // black
    palette.push_back(LaserBoy_color(0xff, 0x00, 0x00));
    palette.first = palette.number_of_colors() - 1;  // first
    palette.push_back(LaserBoy_color(0xff, 0xff, 0x00));
    palette.push_back(LaserBoy_color(0x00, 0xff, 0x00));
    palette.push_back(LaserBoy_color(0x00, 0xff, 0xff));
    palette.push_back(LaserBoy_color(0x00, 0x00, 0xff));
    palette.push_back(LaserBoy_color(0xff, 0x00, 0xff));
    palette.push_back(LaserBoy_color(0xff, 0xff, 0xff));
    palette.push_back(LaserBoy_color(0x7f, 0x7f, 0x7f));
    palette.push_back(LaserBoy_color(0xbf, 0xbf, 0xbf));
    palette.push_back(LaserBoy_color(0xff, 0x00, 0x00));
    palette.push_back(LaserBoy_color(0xff, 0x7f, 0x7f));
    palette.push_back(LaserBoy_color(0xa5, 0x00, 0x00));
    palette.push_back(LaserBoy_color(0xa5, 0x52, 0x52));
    palette.push_back(LaserBoy_color(0x7f, 0x00, 0x00));
    palette.push_back(LaserBoy_color(0x7f, 0x3f, 0x3f));
    palette.push_back(LaserBoy_color(0x4c, 0x00, 0x00));
    palette.push_back(LaserBoy_color(0x4c, 0x26, 0x26));
    palette.push_back(LaserBoy_color(0x26, 0x00, 0x00));
    palette.push_back(LaserBoy_color(0x26, 0x13, 0x13));
    palette.push_back(LaserBoy_color(0xff, 0x3f, 0x00));
    palette.push_back(LaserBoy_color(0xff, 0x9f, 0x7f));
    palette.push_back(LaserBoy_color(0xa5, 0x29, 0x00));
    palette.push_back(LaserBoy_color(0xa5, 0x67, 0x52));
    palette.push_back(LaserBoy_color(0x7f, 0x1f, 0x00));
    palette.push_back(LaserBoy_color(0x7f, 0x4f, 0x3f));
    palette.push_back(LaserBoy_color(0x4c, 0x13, 0x00));
    palette.push_back(LaserBoy_color(0x4c, 0x2f, 0x26));
    palette.push_back(LaserBoy_color(0x26, 0x09, 0x00));
    palette.push_back(LaserBoy_color(0x26, 0x17, 0x13));
    palette.push_back(LaserBoy_color(0xff, 0x7f, 0x00));
    palette.push_back(LaserBoy_color(0xff, 0xbf, 0x7f));
    palette.push_back(LaserBoy_color(0xa5, 0x52, 0x00));
    palette.push_back(LaserBoy_color(0xa5, 0x7c, 0x52));
    palette.push_back(LaserBoy_color(0x7f, 0x3f, 0x00));
    palette.push_back(LaserBoy_color(0x7f, 0x5f, 0x3f));
    palette.push_back(LaserBoy_color(0x4c, 0x26, 0x00));
    palette.push_back(LaserBoy_color(0x4c, 0x39, 0x26));
    palette.push_back(LaserBoy_color(0x26, 0x13, 0x00));
    palette.push_back(LaserBoy_color(0x26, 0x1c, 0x13));
    palette.push_back(LaserBoy_color(0xff, 0xbf, 0x00));
    palette.push_back(LaserBoy_color(0xff, 0xdf, 0x7f));
    palette.push_back(LaserBoy_color(0xa5, 0x7c, 0x00));
    palette.push_back(LaserBoy_color(0xa5, 0x91, 0x52));
    palette.push_back(LaserBoy_color(0x7f, 0x5f, 0x00));
    palette.push_back(LaserBoy_color(0x7f, 0x6f, 0x3f));
    palette.push_back(LaserBoy_color(0x4c, 0x39, 0x00));
    palette.push_back(LaserBoy_color(0x4c, 0x42, 0x26));
    palette.push_back(LaserBoy_color(0x26, 0x1c, 0x00));
    palette.push_back(LaserBoy_color(0x26, 0x21, 0x13));
    palette.push_back(LaserBoy_color(0xff, 0xff, 0x00));
    palette.push_back(LaserBoy_color(0xff, 0xff, 0x7f));
    palette.push_back(LaserBoy_color(0xa5, 0xa5, 0x00));
    palette.push_back(LaserBoy_color(0xa5, 0xa5, 0x52));
    palette.push_back(LaserBoy_color(0x7f, 0x7f, 0x00));
    palette.push_back(LaserBoy_color(0x7f, 0x7f, 0x3f));
    palette.push_back(LaserBoy_color(0x4c, 0x4c, 0x00));
    palette.push_back(LaserBoy_color(0x4c, 0x4c, 0x26));
    palette.push_back(LaserBoy_color(0x26, 0x26, 0x00));
    palette.push_back(LaserBoy_color(0x26, 0x26, 0x13));
    palette.push_back(LaserBoy_color(0xbf, 0xff, 0x00));
    palette.push_back(LaserBoy_color(0xdf, 0xff, 0x7f));
    palette.push_back(LaserBoy_color(0x7c, 0xa5, 0x00));
    palette.push_back(LaserBoy_color(0x91, 0xa5, 0x52));
    palette.push_back(LaserBoy_color(0x5f, 0x7f, 0x00));
    palette.push_back(LaserBoy_color(0x6f, 0x7f, 0x3f));
    palette.push_back(LaserBoy_color(0x39, 0x4c, 0x00));
    palette.push_back(LaserBoy_color(0x42, 0x4c, 0x26));
    palette.push_back(LaserBoy_color(0x1c, 0x26, 0x00));
    palette.push_back(LaserBoy_color(0x21, 0x26, 0x13));
    palette.push_back(LaserBoy_color(0x7f, 0xff, 0x00));
    palette.push_back(LaserBoy_color(0xbf, 0xff, 0x7f));
    palette.push_back(LaserBoy_color(0x52, 0xa5, 0x00));
    palette.push_back(LaserBoy_color(0x7c, 0xa5, 0x52));
    palette.push_back(LaserBoy_color(0x3f, 0x7f, 0x00));
    palette.push_back(LaserBoy_color(0x5f, 0x7f, 0x3f));
    palette.push_back(LaserBoy_color(0x26, 0x4c, 0x00));
    palette.push_back(LaserBoy_color(0x39, 0x4c, 0x26));
    palette.push_back(LaserBoy_color(0x13, 0x26, 0x00));
    palette.push_back(LaserBoy_color(0x1c, 0x26, 0x13));
    palette.push_back(LaserBoy_color(0x3f, 0xff, 0x00));
    palette.push_back(LaserBoy_color(0x9f, 0xff, 0x7f));
    palette.push_back(LaserBoy_color(0x29, 0xa5, 0x00));
    palette.push_back(LaserBoy_color(0x67, 0xa5, 0x52));
    palette.push_back(LaserBoy_color(0x1f, 0x7f, 0x00));
    palette.push_back(LaserBoy_color(0x4f, 0x7f, 0x3f));
    palette.push_back(LaserBoy_color(0x13, 0x4c, 0x00));
    palette.push_back(LaserBoy_color(0x2f, 0x4c, 0x26));
    palette.push_back(LaserBoy_color(0x09, 0x26, 0x00));
    palette.push_back(LaserBoy_color(0x17, 0x26, 0x13));
    palette.push_back(LaserBoy_color(0x00, 0xff, 0x00));
    palette.push_back(LaserBoy_color(0x7f, 0xff, 0x7f));
    palette.push_back(LaserBoy_color(0x00, 0xa5, 0x00));
    palette.push_back(LaserBoy_color(0x52, 0xa5, 0x52));
    palette.push_back(LaserBoy_color(0x00, 0x7f, 0x00));
    palette.push_back(LaserBoy_color(0x3f, 0x7f, 0x3f));
    palette.push_back(LaserBoy_color(0x00, 0x4c, 0x00));
    palette.push_back(LaserBoy_color(0x26, 0x4c, 0x26));
    palette.push_back(LaserBoy_color(0x00, 0x26, 0x00));
    palette.push_back(LaserBoy_color(0x13, 0x26, 0x13));
    palette.push_back(LaserBoy_color(0x00, 0xff, 0x3f));
    palette.push_back(LaserBoy_color(0x7f, 0xff, 0x9f));
    palette.push_back(LaserBoy_color(0x00, 0xa5, 0x29));
    palette.push_back(LaserBoy_color(0x52, 0xa5, 0x67));
    palette.push_back(LaserBoy_color(0x00, 0x7f, 0x1f));
    palette.push_back(LaserBoy_color(0x3f, 0x7f, 0x4f));
    palette.push_back(LaserBoy_color(0x00, 0x4c, 0x13));
    palette.push_back(LaserBoy_color(0x26, 0x4c, 0x2f));
    palette.push_back(LaserBoy_color(0x00, 0x26, 0x09));
    palette.push_back(LaserBoy_color(0x13, 0x26, 0x17));
    palette.push_back(LaserBoy_color(0x00, 0xff, 0x7f));
    palette.push_back(LaserBoy_color(0x7f, 0xff, 0xbf));
    palette.push_back(LaserBoy_color(0x00, 0xa5, 0x52));
    palette.push_back(LaserBoy_color(0x52, 0xa5, 0x7c));
    palette.push_back(LaserBoy_color(0x00, 0x7f, 0x3f));
    palette.push_back(LaserBoy_color(0x3f, 0x7f, 0x5f));
    palette.push_back(LaserBoy_color(0x00, 0x4c, 0x26));
    palette.push_back(LaserBoy_color(0x26, 0x4c, 0x39));
    palette.push_back(LaserBoy_color(0x00, 0x26, 0x13));
    palette.push_back(LaserBoy_color(0x13, 0x26, 0x1c));
    palette.push_back(LaserBoy_color(0x00, 0xff, 0xbf));
    palette.push_back(LaserBoy_color(0x7f, 0xff, 0xdf));
    palette.push_back(LaserBoy_color(0x00, 0xa5, 0x7c));
    palette.push_back(LaserBoy_color(0x52, 0xa5, 0x91));
    palette.push_back(LaserBoy_color(0x00, 0x7f, 0x5f));
    palette.push_back(LaserBoy_color(0x3f, 0x7f, 0x6f));
    palette.push_back(LaserBoy_color(0x00, 0x4c, 0x39));
    palette.push_back(LaserBoy_color(0x26, 0x4c, 0x42));
    palette.push_back(LaserBoy_color(0x00, 0x26, 0x1c));
    palette.push_back(LaserBoy_color(0x13, 0x26, 0x21));
    palette.push_back(LaserBoy_color(0x00, 0xff, 0xff));
    palette.push_back(LaserBoy_color(0x7f, 0xff, 0xff));
    palette.push_back(LaserBoy_color(0x00, 0xa5, 0xa5));
    palette.push_back(LaserBoy_color(0x52, 0xa5, 0xa5));
    palette.push_back(LaserBoy_color(0x00, 0x7f, 0x7f));
    palette.push_back(LaserBoy_color(0x3f, 0x7f, 0x7f));
    palette.push_back(LaserBoy_color(0x00, 0x4c, 0x4c));
    palette.push_back(LaserBoy_color(0x26, 0x4c, 0x4c));
    palette.push_back(LaserBoy_color(0x00, 0x26, 0x26));
    palette.push_back(LaserBoy_color(0x13, 0x26, 0x26));
    palette.push_back(LaserBoy_color(0x00, 0xbf, 0xff));
    palette.push_back(LaserBoy_color(0x7f, 0xdf, 0xff));
    palette.push_back(LaserBoy_color(0x00, 0x7c, 0xa5));
    palette.push_back(LaserBoy_color(0x52, 0x91, 0xa5));
    palette.push_back(LaserBoy_color(0x00, 0x5f, 0x7f));
    palette.push_back(LaserBoy_color(0x3f, 0x6f, 0x7f));
    palette.push_back(LaserBoy_color(0x00, 0x39, 0x4c));
    palette.push_back(LaserBoy_color(0x26, 0x42, 0x4c));
    palette.push_back(LaserBoy_color(0x00, 0x1c, 0x26));
    palette.push_back(LaserBoy_color(0x13, 0x21, 0x26));
    palette.push_back(LaserBoy_color(0x00, 0x7f, 0xff));
    palette.push_back(LaserBoy_color(0x7f, 0xbf, 0xff));
    palette.push_back(LaserBoy_color(0x00, 0x52, 0xa5));
    palette.push_back(LaserBoy_color(0x52, 0x7c, 0xa5));
    palette.push_back(LaserBoy_color(0x00, 0x3f, 0x7f));
    palette.push_back(LaserBoy_color(0x3f, 0x5f, 0x7f));
    palette.push_back(LaserBoy_color(0x00, 0x26, 0x4c));
    palette.push_back(LaserBoy_color(0x26, 0x39, 0x4c));
    palette.push_back(LaserBoy_color(0x00, 0x13, 0x26));
    palette.push_back(LaserBoy_color(0x13, 0x1c, 0x26));
    palette.push_back(LaserBoy_color(0x00, 0x3f, 0xff));
    palette.push_back(LaserBoy_color(0x7f, 0x9f, 0xff));
    palette.push_back(LaserBoy_color(0x00, 0x29, 0xa5));
    palette.push_back(LaserBoy_color(0x52, 0x67, 0xa5));
    palette.push_back(LaserBoy_color(0x00, 0x1f, 0x7f));
    palette.push_back(LaserBoy_color(0x3f, 0x4f, 0x7f));
    palette.push_back(LaserBoy_color(0x00, 0x13, 0x4c));
    palette.push_back(LaserBoy_color(0x26, 0x2f, 0x4c));
    palette.push_back(LaserBoy_color(0x00, 0x09, 0x26));
    palette.push_back(LaserBoy_color(0x13, 0x17, 0x26));
    palette.push_back(LaserBoy_color(0x00, 0x00, 0xff));
    palette.push_back(LaserBoy_color(0x7f, 0x7f, 0xff));
    palette.push_back(LaserBoy_color(0x00, 0x00, 0xa5));
    palette.push_back(LaserBoy_color(0x52, 0x52, 0xa5));
    palette.push_back(LaserBoy_color(0x00, 0x00, 0x7f));
    palette.push_back(LaserBoy_color(0x3f, 0x3f, 0x7f));
    palette.push_back(LaserBoy_color(0x00, 0x00, 0x4c));
    palette.push_back(LaserBoy_color(0x26, 0x26, 0x4c));
    palette.push_back(LaserBoy_color(0x00, 0x00, 0x26));
    palette.push_back(LaserBoy_color(0x13, 0x13, 0x26));
    palette.push_back(LaserBoy_color(0x3f, 0x00, 0xff));
    palette.push_back(LaserBoy_color(0x9f, 0x7f, 0xff));
    palette.push_back(LaserBoy_color(0x29, 0x00, 0xa5));
    palette.push_back(LaserBoy_color(0x67, 0x52, 0xa5));
    palette.push_back(LaserBoy_color(0x1f, 0x00, 0x7f));
    palette.push_back(LaserBoy_color(0x4f, 0x3f, 0x7f));
    palette.push_back(LaserBoy_color(0x13, 0x00, 0x4c));
    palette.push_back(LaserBoy_color(0x2f, 0x26, 0x4c));
    palette.push_back(LaserBoy_color(0x09, 0x00, 0x26));
    palette.push_back(LaserBoy_color(0x17, 0x13, 0x26));
    palette.push_back(LaserBoy_color(0x7f, 0x00, 0xff));
    palette.push_back(LaserBoy_color(0xbf, 0x7f, 0xff));
    palette.push_back(LaserBoy_color(0x52, 0x00, 0xa5));
    palette.push_back(LaserBoy_color(0x7c, 0x52, 0xa5));
    palette.push_back(LaserBoy_color(0x3f, 0x00, 0x7f));
    palette.push_back(LaserBoy_color(0x5f, 0x3f, 0x7f));
    palette.push_back(LaserBoy_color(0x26, 0x00, 0x4c));
    palette.push_back(LaserBoy_color(0x39, 0x26, 0x4c));
    palette.push_back(LaserBoy_color(0x13, 0x00, 0x26));
    palette.push_back(LaserBoy_color(0x1c, 0x13, 0x26));
    palette.push_back(LaserBoy_color(0xbf, 0x00, 0xff));
    palette.push_back(LaserBoy_color(0xdf, 0x7f, 0xff));
    palette.push_back(LaserBoy_color(0x7c, 0x00, 0xa5));
    palette.push_back(LaserBoy_color(0x91, 0x52, 0xa5));
    palette.push_back(LaserBoy_color(0x5f, 0x00, 0x7f));
    palette.push_back(LaserBoy_color(0x6f, 0x3f, 0x7f));
    palette.push_back(LaserBoy_color(0x39, 0x00, 0x4c));
    palette.push_back(LaserBoy_color(0x42, 0x26, 0x4c));
    palette.push_back(LaserBoy_color(0x1c, 0x00, 0x26));
    palette.push_back(LaserBoy_color(0x21, 0x13, 0x26));
    palette.push_back(LaserBoy_color(0xff, 0x00, 0xff));
    palette.push_back(LaserBoy_color(0xff, 0x7f, 0xff));
    palette.push_back(LaserBoy_color(0xa5, 0x00, 0xa5));
    palette.push_back(LaserBoy_color(0xa5, 0x52, 0xa5));
    palette.push_back(LaserBoy_color(0x7f, 0x00, 0x7f));
    palette.push_back(LaserBoy_color(0x7f, 0x3f, 0x7f));
    palette.push_back(LaserBoy_color(0x4c, 0x00, 0x4c));
    palette.push_back(LaserBoy_color(0x4c, 0x26, 0x4c));
    palette.push_back(LaserBoy_color(0x26, 0x00, 0x26));
    palette.push_back(LaserBoy_color(0x26, 0x13, 0x26));
    palette.push_back(LaserBoy_color(0xff, 0x00, 0xbf));
    palette.push_back(LaserBoy_color(0xff, 0x7f, 0xdf));
    palette.push_back(LaserBoy_color(0xa5, 0x00, 0x7c));
    palette.push_back(LaserBoy_color(0xa5, 0x52, 0x91));
    palette.push_back(LaserBoy_color(0x7f, 0x00, 0x5f));
    palette.push_back(LaserBoy_color(0x7f, 0x3f, 0x6f));
    palette.push_back(LaserBoy_color(0x4c, 0x00, 0x39));
    palette.push_back(LaserBoy_color(0x4c, 0x26, 0x42));
    palette.push_back(LaserBoy_color(0x26, 0x00, 0x1c));
    palette.push_back(LaserBoy_color(0x26, 0x13, 0x21));
    palette.push_back(LaserBoy_color(0xff, 0x00, 0x7f));
    palette.push_back(LaserBoy_color(0xff, 0x7f, 0xbf));
    palette.push_back(LaserBoy_color(0xa5, 0x00, 0x52));
    palette.push_back(LaserBoy_color(0xa5, 0x52, 0x7c));
    palette.push_back(LaserBoy_color(0x7f, 0x00, 0x3f));
    palette.push_back(LaserBoy_color(0x7f, 0x3f, 0x5f));
    palette.push_back(LaserBoy_color(0x4c, 0x00, 0x26));
    palette.push_back(LaserBoy_color(0x4c, 0x26, 0x39));
    palette.push_back(LaserBoy_color(0x26, 0x00, 0x13));
    palette.push_back(LaserBoy_color(0x26, 0x13, 0x1c));
    palette.push_back(LaserBoy_color(0xff, 0x00, 0x3f));
    palette.push_back(LaserBoy_color(0xff, 0x7f, 0x9f));
    palette.push_back(LaserBoy_color(0xa5, 0x00, 0x29));
    palette.push_back(LaserBoy_color(0xa5, 0x52, 0x67));
    palette.push_back(LaserBoy_color(0x7f, 0x00, 0x1f));
    palette.push_back(LaserBoy_color(0x7f, 0x3f, 0x4f));
    palette.push_back(LaserBoy_color(0x4c, 0x00, 0x13));
    palette.push_back(LaserBoy_color(0x4c, 0x26, 0x2f));
    palette.push_back(LaserBoy_color(0x26, 0x00, 0x09));
    palette.push_back(LaserBoy_color(0x26, 0x13, 0x17));
    palette.push_back(LaserBoy_color(0x54, 0x54, 0x54));
    palette.push_back(LaserBoy_color(0x76, 0x76, 0x76));
    palette.push_back(LaserBoy_color(0x98, 0x98, 0x98));
    palette.push_back(LaserBoy_color(0xba, 0xba, 0xba));
    palette.push_back(LaserBoy_color(0xdc, 0xdc, 0xdc));
    palette.push_back(LaserBoy_color(0xff, 0xff, 0xff));
    palette.white = palette.number_of_colors() - 1;  //white
    palette.last  = palette.number_of_colors() - 1;  //last
    push_back(palette);
    palette.clear();
    //------------------------------------------------------------------------
    palette.reserve(256);
    palette.name = "ezfbHues";
    for(i = 0; i < LASERBOY_PALETTE_MAX - 1; i++)
    {
        hue = i * 1528 / LASERBOY_PALETTE_MAX;
        shift = hue % 255;
        if(hue < 255)
        {
            r = 255;
            g = shift;
        }
        else if(hue < 510)
        {
            r = 256 - shift;
            g = 255;
        }
        else if(hue < 765)
        {
            g = 255;
            b = shift;
        }
        else if(hue < 1020)
        {
            g = 256 - shift;
            b = 255;
        }
        else if(hue < 1275)
        {
            r = shift;
            b = 255;
        }
        else
        {
            r = 255;
            b = 256 - shift;
        }
        palette.push_back(LaserBoy_color(r, g, b));
    }
    palette.push_back(LaserBoy_color(0x00, 0x00, 0x00)); // black
    palette.first = 0;
    palette.black = 255;
    palette.white  = 254;
    palette.last  = 254;
    push_back(palette);
    palette.clear();
    //------------------------------------------------------------------------
    palette.reserve(256);
    palette.name = "RedGreen";
    palette.first = 0;
    for(i = 0; i < LASERBOY_PALETTE_MAX; i++)
    {
        hue = i * 510 / (LASERBOY_PALETTE_MAX - 1);
        shift = hue % 255;
        if(hue < 255)
        {
            r = 255;
            g = shift;
        }
        else if(hue < 510)
        {
            r = 253 - shift;
            g = 255;
        }
        palette.push_back(LaserBoy_color(r, g, 0));
    }
    palette.push_back(LaserBoy_color(0x00, 0x00, 0x00)); // black
    palette.last  = 254;
    palette.white = 254;
    palette.black = 255;
    push_back(palette);
    palette.clear();
    //------------------------------------------------------------------------
    palette.reserve(256);
    palette.name = "ezfb_332";
    for(i = 0; i < LASERBOY_PALETTE_MAX; i++)
        palette.push_back(LaserBoy_color(  i & 0xe0,
                                      (i & 0x1c) << 3,
                                      (i & 0x03) << 6
                                    )
                         );
    palette.first =   1;
    palette.last  = 255;
    palette.white = 255;
    palette.black =   0;
    push_back(palette);
    palette.clear();
    //------------------------------------------------------------------------
    palette.reserve(256);
    palette.name = "_Reds___";
    for(i = 0; i < LASERBOY_PALETTE_MAX; i++)
        palette.push_back(LaserBoy_color(i, 0, 0));
    palette.first =   0;
    palette.black =   0;
    palette.white = 255;
    palette.last  = 255;
    push_back(palette);
    palette.clear();
    //------------------------------------------------------------------------
    palette.reserve(256);
    palette.name = "_Greens_";
    for(i = 0; i < LASERBOY_PALETTE_MAX; i++)
        palette.push_back(LaserBoy_color(0, i, 0));
    palette.first =   0;
    palette.black =   0;
    palette.white = 255;
    palette.last  = 255;
    push_back(palette);
    palette.clear();
    //------------------------------------------------------------------------
    palette.reserve(256);
    palette.name = "_Blues__";
    for(i = 0; i < LASERBOY_PALETTE_MAX; i++)
        palette.push_back(LaserBoy_color(0, 0, i));
    palette.first =   0;
    palette.black =   0;
    palette.white = 255;
    palette.last  = 255;
    push_back(palette);
    palette.clear();
    //------------------------------------------------------------------------
    palette.name = "_Grays__";
    for(i = 0; i < LASERBOY_PALETTE_MAX; i++)
        palette.push_back(LaserBoy_color(i, i, i));
    palette.first =   0;
    palette.black =   0;
    palette.white = 255;
    palette.last  = 255;
    push_back(palette);
    //------------------------------------------------------------------------
    return;
}

//############################################################################
void LaserBoy_palette_set::add_palette()
{
    LaserBoy_palette palette(p_space);
    palette.reserve(256);
    char palette_name[8];
    sprintf(palette_name, "%07d", p_space->new_palette_id++);
    palette.name = string("P") + palette_name;
    palette.first = 0;
    palette.last  = 0;
    palette.push_back(LaserBoy_color(0x00, 0x00, 0x00));
    palette.white = 0;
    palette.black = 0;
    push_back(palette);
    target_palette_index = number_of_palettes() - 1;
}

//############################################################################
void LaserBoy_palette_set::copy_palette(int index)
{
    LaserBoy_palette palette(palette_picker(index));
    char palette_name[8];
    sprintf(palette_name, "%07d", p_space->new_palette_id++);
    palette.name = string("P") + palette_name;
    push_back(palette);
    target_palette_index = number_of_palettes() - 1;
}

//############################################################################
void LaserBoy_palette_set::set_selected_color_index(u_char c)
{
    if(c >= p_space->current_palette().number_of_colors())
        c = 0;
    selected_color_index = c;
    return;
}

//############################################################################
//////////////////////////////////////////////////////////////////////////////
//############################################################################
