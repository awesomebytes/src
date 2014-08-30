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
// LaserBoy_frame_set.hpp is part of LaserBoy.
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
#ifndef __LASERBOY_FRAME_SET_DEFINITIONS__
#define __LASERBOY_FRAME_SET_DEFINITIONS__

//############################################################################
#include "LaserBoy_frame.hpp"

//############################################################################
class LaserBoy_frame_set : public LaserBoy_frame_set_base
{
public:
    //------------------------------------------------------------------------
    LaserBoy_frame_set(LaserBoy_space* ps = NULL)
                     : p_space            (ps)
                     , num_2D_frames      ( 0)
                     , num_3D_frames      ( 0)
                     , frame_index        ( 0)
                     , frame_select_start (-1)
                     , frame_select_end   (-1)
                     , error              (LASERBOY_OK)
                     , null_frame         (ps)
                        {
                            null_frame = NULL_frame(ps);
                        }
    //------------------------------------------------------------------------
    LaserBoy_frame_set(const LaserBoy_frame_set& f)
                     : p_space            (f.p_space)
                     , num_2D_frames      (f.num_2D_frames)
                     , num_3D_frames      (f.num_3D_frames)
                     , frame_index        (f.frame_index)
                     , frame_select_start (f.frame_select_start)
                     , frame_select_end   (f.frame_select_end)
                     , error              (f.error)
                     , null_frame         (f.p_space)
                        {
                            null_frame = NULL_frame(f.p_space);
                            reserve(f.size());
                            insert(begin(), f.begin(), f.end());
                        }
    //------------------------------------------------------------------------
    LaserBoy_frame_set(LaserBoy_space* ps,
                       LaserBoy_vertex(*F)(int, int),
                       int vertices_per_frame,
                       int num_frames
                      );
    //------------------------------------------------------------------------
virtual
   ~LaserBoy_frame_set()  {  clear();  }
    //------------------------------------------------------------------------
    void set_frame_index(int index) //sets frame_index
                    {
                        if(number_of_frames())
                        {
                            if(index >= number_of_frames())
                                index = 0;
                            if(index < 0)
                                index = number_of_frames() - 1;
                            frame_index = index;
                        }
                        else
                            frame_index = 0;
                    }
    //------------------------------------------------------------------------
    LaserBoy_frame& frame(int index) //sets frame_index
                    {
                        if(number_of_frames())
                        {
                            if(index >= number_of_frames())
                                index = 0;
                            if(index < 0)
                                index = number_of_frames() - 1;
                            frame_index = index;
                            return at(frame_index);
                        }
                        return null_frame;
                    }
    //------------------------------------------------------------------------
    LaserBoy_frame& next_frame() //sets frame_index
                    {
                        if(number_of_frames())
                        {
                            frame_index++;
                            if(frame_index >= number_of_frames())
                                frame_index = 0;
                            return at(frame_index);
                        }
                        return null_frame;
                    }
    //------------------------------------------------------------------------
    LaserBoy_frame& previous_frame() //sets frame_index
                    {
                        if(number_of_frames())
                        {
                            frame_index--;
                            if(frame_index < 0)
                                frame_index = number_of_frames() - 1;
                            return at(frame_index);
                        }
                        return null_frame;
                    }
    //------------------------------------------------------------------------
    LaserBoy_frame& frame_picker(int index)
                    {
                        if(number_of_frames())
                        {
                            if(index < 0)
                                index = number_of_frames() - 1;
                            else if(index >= number_of_frames())
                                index = 0;
                            return at(index);
                        }
                        return null_frame;
                    }
    //------------------------------------------------------------------------
    LaserBoy_frame  const_frame_picker(int index) const
                    {
                        if(number_of_frames())
                        {
                            if(index < 0)
                                index = number_of_frames() - 1;
                            else if(index >= number_of_frames())
                                index = 0;
                            return at(index);
                        }
                        return null_frame;
                    }
    //------------------------------------------------------------------------
    LaserBoy_frame& current_frame()
                    {
                        if(number_of_frames())
                            return at(frame_index);
                        return null_frame;
                    }
    //------------------------------------------------------------------------
    void  delete_current_frame()
            {
                if(number_of_frames() > 1)
                {
                    erase(begin() + frame_index);
                    frame_index--;
                    if(frame_index < 0)
                        frame_index = 0;
                }
                else
                {
                    clear();
                    push_back(null_frame);
                }
                validate();
                return;
            }
    //------------------------------------------------------------------------
    void  delete_frame(int index)
            {
                if(number_of_frames() > 1)
                {
                    if(index < number_of_frames())
                    {
                        erase(begin() + index);
                        if(frame_index >= index)
                        {
                            frame_index--;
                            if(frame_index < 0)
                                frame_index = number_of_frames() - 1;
                        }
                    }
                }
                else
                {
                    clear();
                    push_back(null_frame);
                }
                validate();
                return;
            }
    //------------------------------------------------------------------------
    void  copy_frame()
            {
                insert(begin() + frame_index, frame_picker(frame_index));
                frame_index++;
                return;
            }
    //------------------------------------------------------------------------
    void  push_back_frame(const LaserBoy_frame& frame)
            {
                push_back(frame);
                return;
            }
    //------------------------------------------------------------------------
    void  count_frames()
            {
                num_2D_frames = num_3D_frames = 0;
                for(int i = 0; i < number_of_frames(); i++)
                    at(i).is_2D() ? num_2D_frames++ : num_3D_frames++;
                return;
            }
    //------------------------------------------------------------------------
    int   total_vertices() const
            {
                int  i,
                     vertices = 0;
                for(i = 0; i < number_of_frames(); i++)
                    vertices += (at(i).number_of_vertices());
                return vertices;
            }
    //------------------------------------------------------------------------
    LaserBoy_frame& operator ++ () //pre
                    {
                        if(number_of_frames())
                        {
                            frame_index++;
                            if(frame_index >= number_of_frames())
                                frame_index = 0;
                            return at(frame_index);
                        }
                        return null_frame;
                    }
    //------------------------------------------------------------------------
    LaserBoy_frame& operator -- () // pre
                    {
                        if(number_of_frames())
                        {
                            frame_index--;
                            if(frame_index < 0)
                                frame_index = number_of_frames() - 1;
                            return at(frame_index);
                        }
                        return null_frame;
                    }
    //------------------------------------------------------------------------
    LaserBoy_frame& operator ++ (int = 0) //post
                    {
                        if(number_of_frames())
                        {
                            int frame_return = frame_index;
                            frame_index++;
                            if(frame_index >= number_of_frames())
                                frame_index = 0;
                            return at(frame_return);
                        }
                        return null_frame;
                    }
    //------------------------------------------------------------------------
    LaserBoy_frame& operator -- (int = 0) // post
                    {
                        if(number_of_frames())
                        {
                            int frame_return = frame_index;
                            frame_index--;
                            if(frame_index < 0)
                                frame_index = number_of_frames() - 1;
                            return at(frame_return);
                        }
                        return null_frame;
                    }
    //------------------------------------------------------------------------
    LaserBoy_frame_set& operator  = (const LaserBoy_frame_set& frames)
                        {
                            clear();
                            reserve(frames.size());
                            insert(begin(), frames.begin(), frames.end());
                            frame_select_start = frames.frame_select_start;
                            frame_select_end   = frames.frame_select_end;
                            num_2D_frames      = frames.num_2D_frames;
                            num_3D_frames      = frames.num_3D_frames;
                            return *this;
                        }
    //------------------------------------------------------------------------
    LaserBoy_frame_set& operator += (const LaserBoy_frame_set& frames)
                        {
                            reserve(size() + frames.size());
                            insert(end(), frames.begin(), frames.end());
                            return *this;
                        }
    //------------------------------------------------------------------------
    LaserBoy_frame_set& operator  = (const LaserBoy_frame& frame)
                        {
                            clear();
                            frame_select_start = -1;
                            frame_select_end   = -1;
                            push_back(frame);
                            return *this;
                        }
    //------------------------------------------------------------------------
    LaserBoy_frame_set& operator += (const LaserBoy_frame& frame);
    //------------------------------------------------------------------------
    LaserBoy_frame_set& operator += (LaserBoy_segment& segment)
                        {
                            LaserBoy_ild_header header;
                            header.format = segment.is_2D();
                            push_back(LaserBoy_frame(header, segment));
                            return *this;
                        }
    //------------------------------------------------------------------------
    LaserBoy_frame_set selected_frames()
                        {
                            int                 i;
                            LaserBoy_frame_set  selected(p_space);
                            for(i = 0; i < number_of_frames(); i++)
                                if(at(i).is_selected)
                                    selected.push_back(at(i));
                            return selected;
                        }
    //------------------------------------------------------------------------
    LaserBoy_frame_set  operator +  (const LaserBoy_frame_set& frames) const
                        {
                            LaserBoy_frame_set sum(*this);
                            sum += frames;
                            return sum;
                        }
    //------------------------------------------------------------------------
    LaserBoy_frame& operator [] (int index) // does not set frame_index
                    {
                        if(number_of_frames())
                        {
                            if(index >= number_of_frames())
                                index = 0;
                            if(index < 0)
                                index = number_of_frames() - 1;
                            return at(index);
                        }
                        return null_frame;
                    }
    //------------------------------------------------------------------------
    LaserBoy_frame selected_frame_index(int index)
                    {
                        if(number_of_frames())
                        {
                            int selected_count = 0,
                                i;
                            if(    index < number_of_frames()
                                && index >= 0
                              )
                            {
                                for(i = 0; i < number_of_frames(); i++)
                                {
                                    if(at(i).is_selected)
                                    {
                                        if(index == selected_count)
                                            return at(i);
                                        selected_count++;
                                    }
                                }
                            }
                        }
                        return null_frame;
                    }
    //------------------------------------------------------------------------
    LaserBoy_segment sum_of_frames()
                        {
                            bool              same_palettes = true;
                            int               i;
                            LaserBoy_segment  segment(p_space, front().palette_index, false);
                            for(i = 1; i < number_of_frames(); i++)
                                if(segment.palette_index != at(i).palette_index)
                                {
                                    same_palettes = false;
                                    break;
                                }
                            if(!same_palettes)
                            {
                                segment.promote_to_true_color();
                                promote_to_true_color();
                            }
                            for(i = 0; i < number_of_frames(); i++)
                                segment += at(i);
                            return segment;
                        }
    //------------------------------------------------------------------------
    int number_of_frames() const {   return (int)size();   }
    //------------------------------------------------------------------------
    int number_of_selected_frames() const
        {
            int selected_count = 0,
                i;
            for(i = 0; i < number_of_frames(); i++)
                if(at(i).is_selected)
                    selected_count++;
            return selected_count;
        }
    //------------------------------------------------------------------------
    void                 render_frame(const int& index) const;
    //------------------------------------------------------------------------
    LaserBoy_frame_set&  reverse            ();
    LaserBoy_frame_set&  make_current_first ();
    LaserBoy_frame_set&  reverse_selected   ();
    LaserBoy_frame_set&  random_order       ();
    LaserBoy_frame_set&  frame_reverse      ();
    //------------------------------------------------------------------------
    bool    from_nothing                    ();
    //------------------------------------------------------------------------
    bool    from_ild_file                   (string    file,
                                             bool      append = false)       ;
    //------------------------------------------------------------------------
    bool    from_txt_file                   (string    file,
                                             bool      append = false)       ;
    //------------------------------------------------------------------------
    bool    superimpose_from_ild_file       (string    file          )       ;
    //------------------------------------------------------------------------
    bool    superimpose_from_txt_file       (string    file          )       ;
    //------------------------------------------------------------------------
    bool    from_dxf_file                   (string    file,
                                             bool      append = false)       ;
    //------------------------------------------------------------------------
    bool    from_dxf_directory              (string    file,
                                             bool      append = false)       ;
    //------------------------------------------------------------------------
    int     from_ifstream_ild               (ifstream& in,
                                             bool      append = false)       ;
    //------------------------------------------------------------------------
    int     from_ifstream_txt               (ifstream& in,
                                             bool      append = false)       ;
    //------------------------------------------------------------------------
    int     from_LaserBoy_wave_file         (string    file,
                                             bool      append = false)       ;
    //------------------------------------------------------------------------
    bool    from_qm_wave_file               (string    file,
                                             bool      global_polarity,
                                             bool      append = false)       ;
    //------------------------------------------------------------------------
    bool    from_unformatted_wave_file      (string    file,
                                             bool      global_polarity,
                                             bool      append = false)       ;
    //------------------------------------------------------------------------
    int     from_fstream_LaserBoy_wave      (LaserBoy_wave_header header,
                                             fstream&             in,
                                             bool      append = false)       ;
    //------------------------------------------------------------------------
    int     from_fstream_unframed_wave      (LaserBoy_wave_header header,
                                             fstream&             in,
                                             bool      append = false)       ;
    //------------------------------------------------------------------------
    int     from_fstream_qm_wave            (LaserBoy_wave_header header,
                                             fstream&             in,
                                             bool      global_polarity,
                                             bool      append = false)       ;
    //------------------------------------------------------------------------
    int     from_fstream_unformatted_wave   (LaserBoy_wave_header header,
                                             fstream&             in,
                                             bool      global_polarity,
                                             bool      append = false)       ;
    //------------------------------------------------------------------------
    void validate()
            {
                if(frame_index >= (int)size())
                    frame_index = 0;
                if(frame_select_start >= (int)size())
                    frame_select_start = -1;
                if(frame_select_end >= (int)size())
                    frame_select_end = -1;
            }
    //------------------------------------------------------------------------
    bool    is_2D                           (                        )       ;
    void    flatten_z                       (                        )       ;
    void    z_order_vertices                (unsigned short span     )       ;
    void    unblank_all_vertices            (                        )       ;
    void    convert_black_to_blank          (                        )       ;
    void    convert_blank_to_black          (                        )       ;
    void    impose_black_level              (                        )       ;
    void    reduce_blank_vectors            (                        )       ;
    void    remove_dots                     (                        )       ;
    void    enhance_dots                    (                        )       ;
    void    remove_dwell_vertices           (                        )       ;
    void    reduce_lit_vectors              (                        )       ;
    void    minimize                        (                        )       ;
    void    to_dots                         (                        )       ;
    void    accentuate_the_positive         (                        )       ;
    void    eliminate_the_negative          (                        )       ;
    void    impose_bit_resolution           (                        )       ;
    void    explode_current_frame           (                        )       ;
    void    explode_all_frames              (                        )       ;
    void    collapse_selected_frames        (                        )       ;
    void    delete_every_nth_frame          (unsigned short n        )       ;
    void    keep_every_nth_frame            (unsigned short n        )       ;
    void    fracture_segments               (                        )       ;
    void    blank_equivalent_vectors        (                        )       ;
    void    bond_segments                   (                        )       ;
    void    reorder_segments                (                        )       ;
    void    randomize_segments              (                        )       ;
    void    add_dwell                       (                        )       ;
    void    add_lit_span_vertices           (                        )       ;
    void    add_blank_span_vertices         (                        )       ;
    void    delete_redundant_frames         (                        )       ;
    void    optimize                        (                        )       ;
    void    rainbow_recolor                 (int effect              )       ;
    void    quarter_turn                    (int plane, int turns    )       ;
    int     scale_around_origin             (LaserBoy_3D_double f    )       ;
    int     scale_around_origin             (                        )       ;
    int     rotate_around_origin            (LaserBoy_3D_double f    )       ;
    int     rotate_around_origin            (                        )       ;
    int     move                            (LaserBoy_3D_double f    )       ;
    int     move                            (                        )       ;
    void    toggle_frame_select_start       (                        )       ;
    void    toggle_frame_select_end         (                        )       ;
    void    delete_selected_frames          (                        )       ;
    void    trim_to_selected_frames         (                        )       ;
    void    bit_reduce_to_palette           (                        )       ;
    void    best_reduce_to_palette          (                        )       ;
    void    promote_to_true_color           (                        )       ;
    void    best_match_palette              (int index               )       ;
    void    best_match_target_palette       (                        )       ;
    void    strip_color                     (                        )       ;
    void    strip_color_or                  (                        )       ;
    void    strip_color_avg                 (                        )       ;
    void    to_palette_by_index             (int index               )       ;
    void    to_target_palette_by_index      (                        )       ;
    bool    color_from_bmp                  (string file             )       ;
    void    color_from_bmp                  (struct LaserBoy_bmp* bmp)       ;
    bool    subtract_bmp                    (string file             )       ;
    void    subtract_bmp                    (struct LaserBoy_bmp* bmp)       ;
    void    flip                            (int plane               )       ;
    void    renumber                        (                        )       ;
    bool    save_as_ild                     (string file             )       ;
    bool    save_as_txt                     (string file             )       ;
    void    to_ofstream_ild                 (ofstream& out           )       ;
    void    to_ofstream_txt                 (ofstream& out           )       ;
    bool    save_as_wave                    (string file,
                                             bool   optimized,
                                             bool   timed
                                            )                                ;
    void    to_fstream_wave                 (fstream& out,
                                             bool     optimized,
                                             bool     timed
                                            )                                ;
    bool    save_as_bmp_directory           (string dir              ) const ;
    bool    save_as_dxf_directory           (string dir              ) const ;
    //------------------------------------------------------------------------
    LaserBoy_space*  p_space           ;

    int              num_2D_frames     ,
                     num_3D_frames     ,
                     frame_index       ,
                     frame_select_start,
                     frame_select_end  ,
                     error             ;

    LaserBoy_frame   null_frame        ;
};

//############################################################################
typedef int(*LaserBoy_frame_effect    )(LaserBoy_frame*    );
typedef int(*LaserBoy_frame_set_effect)(LaserBoy_frame_set*);

//############################################################################
#endif

//############################################################################
//////////////////////////////////////////////////////////////////////////////
//############################################################################
