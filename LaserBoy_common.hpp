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
// LaserBoy_common.hpp is part of LaserBoy.
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
#ifndef __LASERBOY_COMMON_DEFINITIONS__
#define __LASERBOY_COMMON_DEFINITIONS__

//############################################################################
#include "LaserBoy_macros.hpp"

//############################################################################
typedef unsigned long  u_long ;
typedef unsigned int   u_int  ;
typedef unsigned short u_short;
typedef unsigned char  u_char ;

//############################################################################
extern const double quarter_pi;
extern const double half_pi;
extern const double three_quarters_pi;
extern const double pi;
extern const double two_pi;

extern const double one_degree; // in radians
extern const double one_radian; // in degrees

extern const u_char byte_primes   [55];
extern const short  short_bit_mask[16];

//############################################################################
//                        delta_02, delta_01, delta_12,
inline double delta_angle(double a, double b, double c) // sss triangle
{                       // returns the simple angle in the three vertices 0, 1, 2
    double angle;
    //------------------------------------------------------------------------
    if(    b == 0.0
        || c == 0.0
      )
        angle = 0;
    //------------------------------------------------------------------------
    else if(a == 0)
        angle = pi;
    //------------------------------------------------------------------------
    else if(a >= b + c)
        angle = 0;
    //------------------------------------------------------------------------
    else
        angle = pi - acos((b*b + c*c - a*a)/(2*b*c));
    //------------------------------------------------------------------------
    return angle;
}

//############################################################################
inline double simple_2D_angle(double x1, double y1, double x2, double y2)
{
    return atan2(y2 - y1, x2 - x1);
}

//############################################################################
inline u_char rescale_to_index(short* rescale, short value)
{
    int i;
    value &= 0xfffe; // remove possible LSB tag
    for(i = 0; i < 256; i++)
        if(rescale[i] == value)
            return (u_char)i;
    return 0x00;
}

//############################################################################
int    greatest_common_devisor  (int x, int y);
int    lowest_common_denominator(int x, int y);

//############################################################################
bool   file_exists     (string file);
bool   directory_exists(string dir );

//############################################################################
string time_as_string(double seconds);

//############################################################################
double random_01          ();
double random_neg_to_pos_1();

//############################################################################
bool   get_dxf_pair   (ifstream& in, int& group_code, string& entity_string);

//############################################################################
void   txt_tag        (ofstream& out);

bool   clear_to_alpha (ifstream& in, int& line_number);
bool   clear_to_digit (ifstream& in, int& line_number);
bool   clear_to_token (ifstream& in, int& next_char, int& line_number);

bool   get_next_word  (ifstream& in, string& word  , int& line_number);
bool   get_next_number(ifstream& in, double& number, int& line_number);
bool   get_next_hex   (ifstream& in, double& number, int& line_number);

//############################################################################
#endif

//############################################################################
//////////////////////////////////////////////////////////////////////////////
//############################################################################
