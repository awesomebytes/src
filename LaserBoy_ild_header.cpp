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
// LaserBoy_ild_header.cpp is part of LaserBoy.
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
#include "LaserBoy_ild_header.hpp"

//############################################################################
int LaserBoy_ild_header::from_ifstream_ild(ifstream&  in)
{
    char a, b, c, d, e, f, g, h;
    int  i;
    //------------------------------------------------------------------------
    name.erase    ();
    owner.erase   ();
    //------------------------------------------------------------------------
    while(in.good())
    {
        d = ' ';
        while(d != 'A' && in.good())
        {
            c = ' ';
            while(c != 'D' && in.good())
            {
                b = ' ';
                while(b != 'L' && in.good())
                {
                    a = ' ';
                    while(a != 'I' && in.good())
                        in.get(a);
                    in.get(b);
                }
                in.get(c);
            }
            in.get(d);
        }
        //--------------------------------------------------------------------
        in.get(e); in.get(f); in.get(g); in.get(h);
        i = (   (e & 0x000000ff) << 24
              | (f & 0x000000ff) << 16
              | (g & 0x000000ff) << 8
              | (h & 0x000000ff)
            );
        //--------------------------------------------------------------------
        if(    i == LASERBOY_3D_FRAME
            || i == LASERBOY_2D_FRAME
            || i == LASERBOY_PALETTE
            || i == LASERBOY_TABLE
            || i == LASERBOY_3D_FRAME_RGB
            || i == LASERBOY_2D_FRAME_RGB
          )
        {
            format = i;
            for(i = 0; i < 8; i++)
            {
                in.get(a);
                name += a;
            }
            for(i = 0; i < 8; i++)
            {
                in.get(a);
                owner += a;
            }
            in.get(a);    in.get(b);
            quantity = ((a & 0x00ff) << 8 | (b & 0x00ff));
            in.get(a);    in.get(b);
            identity = ((a & 0x00ff) << 8 | (b & 0x00ff));
            in.get(a);    in.get(b);
            total    = ((a & 0x00ff) << 8 | (b & 0x00ff));
            in.get(scanner);
            in.get(future) ;
            if(in.good())
                return LASERBOY_OK;
        }
        //--------------------------------------------------------------------
    }
    //------------------------------------------------------------------------
    if(in.good())
        return LASERBOY_OK;
    //------------------------------------------------------------------------
    return LASERBOY_FILE_OPEN_FAILED;
}

//############################################################################
void LaserBoy_ild_header::to_ofstream_ild(ofstream& out, bool dumb_file_format)
{
    int i;
    //------------------------------------------------------------------------
    out.put('I');
    out.put('L');
    out.put('D');
    out.put('A');
    out.put( 0 );
    out.put( 0 );
    out.put( 0 );
    //------------------------------------------------------------------------
    if(dumb_file_format)
    {
        if(format == LASERBOY_3D_FRAME)
            format = LASERBOY_3D_FRAME_RGB;

        else if(format == LASERBOY_2D_FRAME)
            format = LASERBOY_2D_FRAME_RGB;
    }
    out.put(format);
    //------------------------------------------------------------------------
    for(i = 0; i < 8; i++)
        out.put(name[i]);

    for(i = 0; i < 8; i++)
        out.put(owner[i]);

    out.put((char)((quantity & 0xff00) >> 8));
    out.put((char) (quantity & 0x00ff)      );

    out.put((char)((identity & 0xff00) >> 8));
    out.put((char) (identity & 0x00ff)      );

    out.put((char)((total    & 0xff00) >> 8));
    out.put((char) (total    & 0x00ff)      );

    out.put(scanner);
    out.put(future) ;
    //------------------------------------------------------------------------
    return;
}

//############################################################################
//////////////////////////////////////////////////////////////////////////////
//############################################################################
