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
// LaserBoy_segment.hpp is part of LaserBoy.
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
#ifndef __LASERBOY_SEGMENT_DEFINITIONS__
#define __LASERBOY_SEGMENT_DEFINITIONS__

//############################################################################
#include "LaserBoy_bmp.hpp"
#include "LaserBoy_real_segment.hpp"

//############################################################################
class LaserBoy_segment : public LaserBoy_segment_base
{
public:
    LaserBoy_segment(LaserBoy_space* ps = NULL)
                     : p_space       (ps),
                       palette_index (LASERBOY_ILDA_DEFAULT),
                       error         (LASERBOY_OK)           {}
    //------------------------------------------------------------------------
    LaserBoy_segment(LaserBoy_space* ps,
                     const int& palette_index,
                     bool       add_origin
                    )
                     : p_space       (ps),
                       palette_index (palette_index),
                       error         (LASERBOY_OK)
                    {
                        if(add_origin)
                        {
                            reserve(2);
                            push_back(LaserBoy_vertex());
                            push_back(LaserBoy_vertex());
                        }
                    }
    //------------------------------------------------------------------------
    LaserBoy_segment(const LaserBoy_segment& segment)
                     : p_space       (segment.p_space),
                       palette_index (segment.palette_index),
                       error         (LASERBOY_OK)
                    {
                        clear();
                        reserve(segment.size());
                        insert(end(), segment.begin(), segment.end());
                    }
    //------------------------------------------------------------------------
    LaserBoy_segment(const LaserBoy_real_segment& real_segment)
                     : p_space       (real_segment.p_space),
                       palette_index (real_segment.palette_index),
                       error         (LASERBOY_OK)
                    {
                        clear();
                        reserve(real_segment.size());
                        for(int i = 0; i < (int)real_segment.size(); i++)
                            push_back((LaserBoy_vertex)real_segment[i]);
                    }
    //------------------------------------------------------------------------
    LaserBoy_segment(LaserBoy_space   *ps,
                     LaserBoy_3D_short from,
                     LaserBoy_vertex   to
                    ); // the line
    //------------------------------------------------------------------------
    LaserBoy_segment(LaserBoy_space   *ps,
                     double            factor,
                     LaserBoy_3D_short from,
                     LaserBoy_vertex   to
                    ); // the line
    //------------------------------------------------------------------------
    LaserBoy_segment(LaserBoy_space*   ps,
                     LaserBoy_vertex   p1,
                     LaserBoy_vertex   p2,
                     string            font,
                     string            text
                    );   // mono spaced font constructor
    //------------------------------------------------------------------------
    LaserBoy_segment(LaserBoy_space*   ps,
                     LaserBoy_vertex   p1,
                     LaserBoy_vertex   p2,
                     string            font,
                     string            text,
                     int               dud
                    );   // variable spaced font constructor
    //------------------------------------------------------------------------
    LaserBoy_segment(LaserBoy_space*   ps,
                     LaserBoy_3D_short center,
                     LaserBoy_3D_short arc_start,
                     double            arc_angle // OK degrees, whatever!
                    );   // circular arc constructor
    //------------------------------------------------------------------------
    LaserBoy_segment(LaserBoy_space*   ps,
                     LaserBoy_3D_short center,
                     LaserBoy_3D_short arc_start,
                     double            arc_angle,
                     double            radii_ratio
                    );   // elliptical arc constructor
    //------------------------------------------------------------------------
    LaserBoy_segment(LaserBoy_space*   ps,
                     LaserBoy_3D_short center,
                     LaserBoy_3D_short first_vertex,
                     int               number_of_sides
                    );   // polygon constructor
    //------------------------------------------------------------------------
    LaserBoy_segment(LaserBoy_space*   ps,
                     LaserBoy_3D_short center,
                     LaserBoy_3D_short first_vertex,
                     int               number_of_sides,
                     double            ratio
                    );   // polystar constructor
    //------------------------------------------------------------------------
    LaserBoy_segment(LaserBoy_space*   ps,
                     LaserBoy_3D_short center,
                     int               radius,
                     int               pedals_numerator,
                     int               pedals_denominator
                    );   // rhodonea
    //------------------------------------------------------------------------
    LaserBoy_segment(LaserBoy_space*   ps,
                     int               center_radius,
                     LaserBoy_3D_short center,
                     int               roller_radius,
                     int               roller_offset
                    );   // epitrochoid (and epicycloid)
    //------------------------------------------------------------------------
    LaserBoy_segment(LaserBoy_space*   ps,
                     int               center_radius,
                     int               roller_radius,
                     int               roller_offset,
                     LaserBoy_3D_short center
                    );   // hypotrochoid (and hypocycloid)
    //------------------------------------------------------------------------
    LaserBoy_segment(LaserBoy_space*   ps,
                     LaserBoy_3D_short center,
                     int               amplitude_x,
                     int               amplitude_y,
                     int               frequency_x,
                     int               frequency_y,
                     double            phase_x,
                     double            phase_y
                    );   // Lissajous curve
    //------------------------------------------------------------------------
   ~LaserBoy_segment()    {    clear();    }
    //------------------------------------------------------------------------
    bool operator == (const LaserBoy_segment& segment)
            {
                if(palette_index != segment.palette_index)
                    return false;
                if(size() != segment.size())
                    return false;
                for(int i = 0; i < (int)size(); i++)
                    if(at(i) != segment.at(i))
                        return false;
                return true;
            }
    //------------------------------------------------------------------------
    LaserBoy_segment&  operator += (const LaserBoy_segment& segment)
                        {
                            if(palette_index != segment.palette_index)
                                promote_to_true_color();
                            reserve(size() + segment.size());
                            insert(end(), segment.begin(), segment.end());
                            return *this;
                        }
    //------------------------------------------------------------------------
    LaserBoy_segment&  operator += (const LaserBoy_vertex& vertex)
                        {
                            push_back(vertex);
                            return *this;
                        }
    //------------------------------------------------------------------------
    LaserBoy_segment   operator + (const LaserBoy_segment& segment)
                        {
                            LaserBoy_segment sum(*this);
                            if(sum.palette_index != segment.palette_index)
                                sum.promote_to_true_color();
                            sum.reserve(sum.size() + segment.size());
                            sum.insert(end(), segment.begin(), segment.end());
                            return sum;
                        }
    //------------------------------------------------------------------------
    LaserBoy_segment   operator + (const LaserBoy_vertex& vertex)
                        {
                            LaserBoy_segment sum(*this);
                            sum.push_back(vertex);
                            return sum;
                        }
    //------------------------------------------------------------------------
    LaserBoy_segment&  operator =  (const LaserBoy_segment& segment)
                        {
                            clear();
//                            palette_index = segment.palette_index;
                            reserve(segment.size());
                            insert(begin(), segment.begin(), segment.end());
                            p_space = segment.p_space;
                            return *this;
                        }
    //------------------------------------------------------------------------
    bool is_2D() const
            {
                if((int)size() > 1)
                {
                    for(int i = 0; i < (int)size(); i++)
                        if(at(i).z != 0)
                            return false;
                }
                return true;
            }
    //------------------------------------------------------------------------
    bool at_index_has_magnitude(int vertex_index) const
            {
                if(    vertex_index
                    && vertex_index < (int)size()
                  )
                {
                    return (bool)(at(vertex_index - 1) | at(vertex_index));
                }
                else
                    return false;
            }
    //------------------------------------------------------------------------
    double total_magnitude() const
            {
                return (front() | back());
            }
    //------------------------------------------------------------------------
    LaserBoy_vertex first_lit_vector() const
                    {
                        for(int i = 1; i < (int)size(); i++)
                            if(at(i).is_lit())
                                return at(i);
                        return LaserBoy_vertex(0);
                    }
    //------------------------------------------------------------------------
    int number_of_vertices() const
            {
                return (int)size();
            }
    //------------------------------------------------------------------------
    int first_lit_vector_index() const
            {
                for(int i = 1; i < (int)size(); i++)
                    if(at(i).is_lit())
                        return i;
                return -1;
            }
    //------------------------------------------------------------------------
    LaserBoy_vertex first_lit_anchor() const
                    {
                        for(int i = 1; i < (int)size(); i++)
                            if(at(i).is_lit())
                                return at(i - 1);
                        return LaserBoy_vertex(0);
                    }
    //------------------------------------------------------------------------
    int first_lit_anchor_index() const
            {
                for(int i = 1; i < (int)size(); i++)
                    if(at(i).is_lit())
                        return (i - 1);
                return -1;
            }
    //------------------------------------------------------------------------
    int last_lit_anchor_index() const
            {
                for(int i = (int)size() - 1; i > 0; i--)
                    if(at(i).is_lit())
                        return i - 1;
                return -1;
            }
    //------------------------------------------------------------------------
    LaserBoy_vertex last_lit_anchor() const
                    {
                        for(int i = (int)size() - 1; i > 0; i--)
                            if(at(i).is_lit())
                                return at(i - 1);
                        return LaserBoy_vertex(0);
                    }
    //------------------------------------------------------------------------
    LaserBoy_vertex last_lit_vector() const
                    {
                        for(int i = (int)size() - 1; i > 0; i--)
                            if(at(i).is_lit())
                                return at(i);
                        return LaserBoy_vertex(0);
                    }
    //------------------------------------------------------------------------
    int last_lit_vector_index() const
            {
                for(int i = (int)size() - 1; i > 0; i--)
                    if(at(i).is_lit())
                        return i;
                return -1;
            }
    //------------------------------------------------------------------------
    int number_of_lit_vectors() const
            {
                int count = 0;
                for(int i = 1; i < (int)size(); i++)
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
                int count = 1; //first vertex is always an anchor
                for(int i = 1; i < (int)size(); i++)
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
    LaserBoy_segment& remove_vertex(int vertex_index)
            {
                if(size() <= 2) // takes 2 vertices to make a vector!
                    clear();
                else if(    vertex_index >= 0
                         && vertex_index <  (int)size()
                       )
                {
                    int              i;
                    LaserBoy_segment segment(p_space);
                    segment.reserve(size());
                    for(i = 0; i < vertex_index; i++)
                        segment += at(i);
                    for(i = vertex_index + 1; i < (int)size(); i++)
                        segment += at(i);
                    *this = segment;
                }
                return *this;
            }
    //------------------------------------------------------------------------
    LaserBoy_3D_short  segment_front               () const ;
    LaserBoy_3D_short  segment_back                () const ;
    LaserBoy_3D_short  segment_top                 () const ;
    LaserBoy_3D_short  segment_bottom              () const ;
    LaserBoy_3D_short  segment_right               () const ;
    LaserBoy_3D_short  segment_left                () const ;
    LaserBoy_3D_short  vertex_farthest_from_origin () const ;
    short              segment_height              () const ;
    short              segment_width               () const ;
    short              segment_depth               () const ;
    short              segment_size                () const ;
    bool               is_closed_polygon           () const ;
    LaserBoy_segment&  reverse                     ();
    LaserBoy_segment&  reverse_sub_segment         (int p1, int p2);
    LaserBoy_segment&  reorder_from                (int vertex_index);
    LaserBoy_segment&  randomize_segments          ();
    LaserBoy_segment   shortest_path_of_segments   (const LaserBoy_segment& previous_frame);
    void               blank_all_vertices          ();
    void               unblank_all_vertices        ();
    void               blacken_vertices            ();
    void               reduce_blank_vectors        ();
    void               remove_dots                 ();
    void               enhance_dots                ();
    void               remove_dwell_vertices       ();
    void               reduce_lit_vectors          ();
    void               accentuate_the_positive     ();
    void               eliminate_the_negative      ();
    void               impose_bit_resolution       ();
    LaserBoy_segment&  reorder_segments            (const LaserBoy_segment& previous_frame);
    LaserBoy_segment&  fracture_segments           ();
    LaserBoy_segment&  bond_segments               ();
    LaserBoy_segment&  add_new_vertex              (int  vertex_index);
    LaserBoy_segment&  break_segment               (int& vertex_index);
    LaserBoy_segment&  connect_the_dots            (int p1, int p2);
    double             vector_angle                (int vertex) const ;
    double             total_angle                 () const ;
    double             max_angle                   () const ;
    double             vector_magnitude            (int vertex) const ;
    double             total_distance              () const ;
    double             max_distance                () const ;
    double             max_color_distance          () const ;
    double             max_dark_distance           () const ;
    double             length_in_time              () const ;
    void               add_dwell                   ();
    void               add_lit_span_vertices       ();
    void               add_blank_span_vertices     ();
    void               flip                        (int plane);
    void               quarter_turn                (int plane, int turns);
    void               z_order_vertices            (unsigned short span);
    void               flatten_z                   ();
    int                rotate                      (LaserBoy_3D_double a);
    int                rotate_around_origin        (LaserBoy_3D_double a);
    //------------------------------------------------------------------------
    int                rotate_on_coordinates       (LaserBoy_3D_double p,
                                                    LaserBoy_3D_double a
                                                   );
    //------------------------------------------------------------------------
    int                rotate_on_coordinates_x     (LaserBoy_3D_double p, double a);
    int                rotate_on_coordinates_y     (LaserBoy_3D_double p, double a);
    int                rotate_on_coordinates_z     (LaserBoy_3D_double p, double a);
    int                rotate_around_origin        ();
    //------------------------------------------------------------------------
    void               ripple                      (int    direction,
                                                    double amplitude,
                                                    double freq     ,
                                                    double phase
                                                   );
    //------------------------------------------------------------------------
    LaserBoy_palette   as_color_table              () const ;
    void               strip_color                 ();
    void               strip_color_or              ();
    void               strip_color_avg             ();
    void               to_palette_by_index         (int index);
    void               to_target_palette_by_index  ();
    void               best_match_palette          (int index);
    void               best_match_target_palette   ();
    void               convert_black_to_blank      ();
    void               convert_blank_to_black      ();
    void               set_vertex_to_black         (int index);
    void               impose_black_level          ();
    void               rainbow_recolor             (int effect);
    LaserBoy_segment&  rotate_colors               (int steps );
    bool               find_rgb_in_palette         (const LaserBoy_palette& palette);
    void               set_rgb_from_palette        ();
    void               set_palette_to_332          ();
    void               sync_rgb_and_palette        ();
    void               bit_reduce_to_palette       ();
    void               best_reduce_to_palette      ();
    void               promote_to_true_color       ();
    void               shade                       (u_char shade);
    void               tint                        (u_char tint);
    bool               color_from_bmp              (string file);
    void               color_from_bmp              (struct LaserBoy_bmp* bmp);
    bool               subtract_bmp                (string file);
    void               subtract_bmp                (struct LaserBoy_bmp* bmp);
    //------------------------------------------------------------------------
    int                move                        (LaserBoy_3D_double d,
                                                    bool check_bounds = true
                                                   );
    //------------------------------------------------------------------------
    int                move                        ();
    //------------------------------------------------------------------------
    int                scale                       (LaserBoy_3D_double s);
    int                scale_on_coordinates        (LaserBoy_3D_double p,
                                                    LaserBoy_3D_double s
                                                   );
    //------------------------------------------------------------------------
    int                scale_around_origin         (LaserBoy_3D_double s);
    int                scale_around_origin         ();
    LaserBoy_3D_double find_center                 () const ;
    int                number_of_segments          () const ;
    //------------------------------------------------------------------------
    LaserBoy_segment   blend                       (const LaserBoy_segment& segment,
                                                    double ratio
                                                   );
    //------------------------------------------------------------------------
    bool               find_segment                (int index,
                                                    int& start,
                                                    int& end
                                                   ) const ;
    //------------------------------------------------------------------------
    bool               find_segment                (int vertex_index,
                                                    int& start,
                                                    int& end,
                                                    int& segment_index
                                                   ) const ;
    //------------------------------------------------------------------------
    LaserBoy_segment   find_segment                (int index) const ;
    LaserBoy_frame_set find_segments               () const ;
    LaserBoy_3D_double find_segment_center         (int index) const ;
    int                segment_index_of_vertex     (int index) const ;
    int                move_segment                (int index, LaserBoy_3D_double d);
    int                rotate_segment              (int index, LaserBoy_3D_double a);
    int                rotate_segment_around_origin(int index, LaserBoy_3D_double a);
    int                scale_segment               (int index, LaserBoy_3D_double m);
    int                scale_segment_around_origin (int index, LaserBoy_3D_double m);
    //------------------------------------------------------------------------
    void               to_fstream_wave             (fstream&  out,
                                                    LaserBoy_wave_header& header,
                                                    bool end_of_frame = false,
                                                    bool unique_frame = false
                                                   );
    //------------------------------------------------------------------------
    LaserBoy_space*    p_space;

    int                palette_index,
                       error        ;
    //------------------------------------------------------------------------
};

//############################################################################
LaserBoy_segment blank_segment(LaserBoy_space* ps);
LaserBoy_segment NULL_segment (LaserBoy_space* ps);

//############################################################################
#endif

//############################################################################
//////////////////////////////////////////////////////////////////////////////
//############################################################################
