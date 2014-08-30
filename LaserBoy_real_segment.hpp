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
// LaserBoy_real_segment.hpp is part of LaserBoy.
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
#ifndef __LASERBOY_REAL_SEGMENT_DEFINITIONS__
#define __LASERBOY_REAL_SEGMENT_DEFINITIONS__

//############################################################################
#include "LaserBoy_palette.hpp"
#include "LaserBoy_vertex.hpp"
#include "LaserBoy_utility.hpp"

//############################################################################
class LaserBoy_frame_set;
class LaserBoy_space;

//############################################################################
class LaserBoy_real_segment : public LaserBoy_real_segment_base
{
public:
    LaserBoy_real_segment(LaserBoy_space* ps = NULL)
                 : p_space       (ps),
                   palette_index (LASERBOY_ILDA_DEFAULT),
                   error         (LASERBOY_OK)
                                                        {}
    //------------------------------------------------------------------------
    LaserBoy_real_segment(LaserBoy_space* ps,
                          const int& palette_index,
                          bool       add_origin
                         )
                 : p_space       (ps),
                   palette_index (palette_index),
                   error         (LASERBOY_OK)
                    {
                        if(add_origin)
                        {
                            push_back(LaserBoy_real_vertex());
                            push_back(LaserBoy_real_vertex());
                        }
                    }
    //------------------------------------------------------------------------
    LaserBoy_real_segment(const LaserBoy_real_segment& segment)
                 : p_space       (segment.p_space),
                   palette_index (segment.palette_index),
                   error         (LASERBOY_OK)
                    {
                        clear();
                        reserve(segment.size());
                        insert(end(), segment.begin(), segment.end());
                    }
    //------------------------------------------------------------------------
    LaserBoy_real_segment(LaserBoy_space*      ps,
                          LaserBoy_real_vertex from,
                          LaserBoy_real_vertex to
                         ); // 3D line function
    //------------------------------------------------------------------------
   ~LaserBoy_real_segment()    {    clear();    }
    //------------------------------------------------------------------------
    bool is_2D() const
            {
                if(number_of_vertices() > 1)
                {
                    for(int i = 0; i < number_of_vertices(); i++)
                        if(at(i).z != 0.0)
                            return false;
                }
                return true;
            }
    //------------------------------------------------------------------------
    bool operator == (const LaserBoy_real_segment& segment)
            {
                if(palette_index != segment.palette_index)
                    return false;
                if(size() != segment.size())
                    return false;
                for(int i = 0; i < number_of_vertices(); i++)
                    if(at(i) != segment.at(i))
                        return false;
                return true;
            }
    //------------------------------------------------------------------------
    LaserBoy_real_segment&  operator += (const LaserBoy_real_segment& segment)
                        {
                            insert(end(), segment.begin(), segment.end());
                            return *this;
                        }
    //------------------------------------------------------------------------
    LaserBoy_real_segment&  operator += (const LaserBoy_real_vertex& vertex)
                        {
                            push_back(vertex);
                            return *this;
                        }
    //------------------------------------------------------------------------
    LaserBoy_real_segment&  operator += (const LaserBoy_3D_double& float_3D)
                        {
                            for(int i = 0; i < (int)size(); i++)
                                at(i) += float_3D;
                            return *this;
                        }
    //------------------------------------------------------------------------
    LaserBoy_real_segment&  operator *= (const LaserBoy_3D_double& float_3D)
                        {
                            for(int i = 0; i < (int)size(); i++)
                                at(i) *= float_3D;
                            return *this;
                        }
    //------------------------------------------------------------------------
    LaserBoy_real_segment   operator + (const LaserBoy_3D_double& float_3D)
                        {
                            LaserBoy_real_segment real_segment(p_space);
                            for(int i = 0; i < (int)size(); i++)
                                real_segment.push_back(at(i) + float_3D);
                            return real_segment;
                        }
    //------------------------------------------------------------------------
    LaserBoy_real_segment   operator * (const LaserBoy_3D_double& float_3D)
                        {
                            LaserBoy_real_segment real_segment(p_space);
                            for(int i = 0; i < (int)size(); i++)
                                real_segment.push_back(at(i) * float_3D);
                            return real_segment;
                        }
    //------------------------------------------------------------------------
    LaserBoy_real_segment&  operator =  (const LaserBoy_real_segment& segment)
                        {
                            clear();
//                            palette_index = segment.palette_index;
                            reserve(segment.size());
                            insert(begin(), segment.begin(), segment.end());
                            p_space = segment.p_space;
                            return *this;
                        }
    //------------------------------------------------------------------------
    LaserBoy_real_vertex  first_lit_vector() const
                        {
                            for(int i = 1; i < number_of_vertices(); i++)
                                if(at(i).is_lit())
                                    return at(i);
                            return LaserBoy_real_vertex(0);
                        }
    //------------------------------------------------------------------------
    int number_of_vertices    () const {   return (int)size();   }
    //------------------------------------------------------------------------
    int first_lit_vector_index() const
                    {
                        for(int i = 1; i < number_of_vertices(); i++)
                            if(at(i).is_lit())
                                return i;
                        return -1;
                    }
    //------------------------------------------------------------------------
    LaserBoy_real_vertex first_lit_anchor() const
                    {
                        for(int i = 1; i < number_of_vertices(); i++)
                            if(at(i).is_lit())
                                return at(i - 1);
                        return LaserBoy_real_vertex(0);
                    }
    //------------------------------------------------------------------------
    int first_lit_anchor_index() const
                    {
                        for(int i = 1; i < number_of_vertices(); i++)
                            if(at(i).is_lit())
                                return (i - 1);
                        return -1;
                    }
    //------------------------------------------------------------------------
    LaserBoy_real_vertex last_lit_anchor() const
                    {
                        for(int i = number_of_vertices() - 1; i > 0; i--)
                            if(at(i).is_lit())
                                return at(i - 1);
                        return LaserBoy_real_vertex(0);
                    }
    //------------------------------------------------------------------------
    LaserBoy_real_vertex last_lit_vector() const
                    {
                        for(int i = number_of_vertices() - 1; i > 0; i--)
                            if(at(i).is_lit())
                                return at(i);
                        return LaserBoy_real_vertex(0);
                    }
    //------------------------------------------------------------------------
    int last_lit_vector_index() const
                    {
                        for(int i = number_of_vertices() - 1; i > 0; i--)
                            if(at(i).is_lit())
                                return i;
                        return -1;
                    }
    //------------------------------------------------------------------------
    int number_of_lit_vectors() const
                    {
                        int count = 0;
                        for(int i = 1; i < number_of_vertices(); i++)
                            if(at(i).is_lit())
                                count++;
                        return count;
                    }
    //------------------------------------------------------------------------
    int number_of_color_vectors() const;
    int number_of_dark_vectors () const;
    //------------------------------------------------------------------------
    int number_of_blank_vectors() const
                    {
                        int count = 0;
                        for(int i = 1; i < number_of_vertices(); i++)
                            if(at(i).is_blank())
                                count++;
                        return count;
                    }
    //------------------------------------------------------------------------
    int number_of_unique_colors() const
        {
            if(number_of_vertices() > 1)
            {
                int               i,
                                  j;
                LaserBoy_palette  palette(p_space);
                palette.push_back((LaserBoy_color)first_lit_vector());
                for(i = first_lit_vector_index() + 1; i < (int)size(); i++)
                {
                    for(j = 0; j < palette.number_of_colors(); j++)
                    {
                        if(palette[j] == (LaserBoy_color)at(i))
                            break;
                    }
                    if(j == palette.number_of_colors())
                        palette.push_back(at(i));
                }
                return palette.number_of_colors();
            }
        }
    //------------------------------------------------------------------------
    LaserBoy_3D_double      segment_front                () const ;
    LaserBoy_3D_double      segment_back                 () const ;
    LaserBoy_3D_double      segment_top                  () const ;
    LaserBoy_3D_double      segment_bottom               () const ;
    LaserBoy_3D_double      segment_right                () const ;
    LaserBoy_3D_double      segment_left                 () const ;
    double                  segment_height               () const ;
    double                  segment_width                () const ;
    double                  segment_depth                () const ;
    double                  segment_size                 () const ;
    LaserBoy_real_segment&  reverse                      ();
    void                    blank_all_vertices           ();
    void                    unblank_all_vertices         ();
    void                    flip                         (int plane);
    void                    quarter_turn                 (int plane, int turns);
    void                    z_order_vertices             (short span);
    void                    flatten_z                    ();
    int                     rotate                       (LaserBoy_3D_double a);
    int                     rotate_around_origin         (LaserBoy_3D_double a);
    //------------------------------------------------------------------------
    int                     rotate_on_coordinates        (LaserBoy_3D_double p,
                                                          LaserBoy_3D_double a
                                                         );
    //------------------------------------------------------------------------
    bool                    find_rgb_in_palette          (const LaserBoy_palette& palette);
    void                    set_rgb_from_palette         ();
    void                    set_palette_to_332           ();
    void                    sync_rgb_and_palette         ();
    void                    best_match_palette           (int index);
    void                    bit_reduce_to_palette        ();
    void                    best_reduce_to_palette       ();
    void                    convert_black_to_blank       ();
    void                    convert_blank_to_black       ();
    void                    impose_black_level           ();
    int                     move                         (LaserBoy_3D_double d);
    int                     scale                        (LaserBoy_3D_double s);
    //------------------------------------------------------------------------
    int                     scale_on_coordinates         (LaserBoy_3D_double p,
                                                          LaserBoy_3D_double s
                                                         );
    //------------------------------------------------------------------------
    int                     scale_around_origin          (LaserBoy_3D_double s);
    LaserBoy_3D_double      find_center                  () const ;
    int                     number_of_segments           () const ;
    //------------------------------------------------------------------------
    bool                    find_segment                 (int  index,
                                                          int& start,
                                                          int& end
                                                         )           const ;
    //------------------------------------------------------------------------
    LaserBoy_real_segment   find_segment                 (int index) const ;
    LaserBoy_3D_double      find_segment_center          (int index) const ;
    int                     move_segment                 (int index, LaserBoy_3D_double f);
    int                     rotate_segment               (int index, LaserBoy_3D_double a);
    int                     rotate_segment_around_origin (int index, LaserBoy_3D_double a);
    int                     scale_segment                (int index, LaserBoy_3D_double m);
    int                     scale_segment_around_origin  (int index, LaserBoy_3D_double m);
    int                     from_ifstream_dxf            (ifstream& in);
    //------------------------------------------------------------------------
    int                     from_ifstream_txt            (ifstream&  in,
                                                          const int& format_1,
                                                          int&       line_number
                                                         );
    //------------------------------------------------------------------------
    void                    normalize                    ();
    //------------------------------------------------------------------------
    int  palette_index,
         error        ;

    LaserBoy_space*   p_space;
    //------------------------------------------------------------------------
};

//############################################################################
//////////////////////////////////////////////////////////////////////////////
//############################################################################
class LaserBoy_real_segment_set : public vector<LaserBoy_real_segment>
{
public:
    //------------------------------------------------------------------------
    LaserBoy_real_segment_set(LaserBoy_space* ps = NULL)
        : p_space(ps)              {}
    //------------------------------------------------------------------------
   ~LaserBoy_real_segment_set()    {  clear();  }
    //------------------------------------------------------------------------
    void normalize();
    //------------------------------------------------------------------------
    LaserBoy_space*   p_space;
    //------------------------------------------------------------------------
};

//############################################################################
#endif

//############################################################################
//////////////////////////////////////////////////////////////////////////////
//############################################################################
