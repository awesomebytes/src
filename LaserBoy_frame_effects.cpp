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
// LaserBoy_frame_effects.cpp is part of LaserBoy.
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
int tranz(LaserBoy_frame* p_frame)
{
    int                i;
    double             amplitude = 0,
                       phase = half_pi;
    LaserBoy_frame     frame(*p_frame);
    LaserBoy_frame_set out(frame.p_space);
    //------------------------------------------------------------------------
    out += frame;
    for(i = 0; i < 60; i++)
    {
        frame.ripple(3, amplitude, 2, phase);
        out += frame;
        frame.rotate_colors(1);
        phase += (two_pi / 61.0);
        amplitude += (.66 / 61.0);
    }
    for(i = 0; i < 60; i++)
    {
        frame.ripple(3, amplitude, 2, phase);
        out += frame;
        frame.rotate_colors(1);
        phase += (two_pi / 61.0);
    }
    for(i = 0; i < 60; i++)
    {
        frame.ripple(3, amplitude, 2, phase);
        out += frame;
        frame.rotate_colors(1);
        phase += (two_pi / 61.0);
        amplitude -= (.66 / 61.0);
    }
    for(i = 0; i < 60; i++)
    {
        frame.ripple(0, amplitude, 2, phase);
        out += frame;
        frame.rotate_colors(1);
        phase += (two_pi / 61.0);
        amplitude += (.66 / 61.0);
    }
    for(i = 0; i < 60; i++)
    {
        frame.ripple(0, amplitude, 2, phase);
        out += frame;
        frame.rotate_colors(1);
        phase += (two_pi / 61.0);

    }
    for(i = 0; i < 60; i++)
    {
        frame.ripple(0, amplitude, 2, phase);
        out += frame;
        frame.rotate_colors(1);
        phase += (two_pi / 61.0);
        amplitude -= (.66 / 61.0);
    }
    for(i = 0; i < 60; i++)
    {
        frame.ripple(1, amplitude, 2, phase);
        out += frame;
        frame.rotate_colors(1);
        phase += (two_pi / 61.0);
        amplitude += (.66 / 61.0);
    }
    for(i = 0; i < 60; i++)
    {
        frame.ripple(1, amplitude, 2, phase);
        out += frame;
        frame.rotate_colors(1);
        phase += (two_pi / 61.0);
    }
    for(i = 0; i < 60; i++)
    {
        frame.ripple(1, amplitude, 2, phase);
        out += frame;
        frame.rotate_colors(1);
        phase += (two_pi / 61.0);
        amplitude -= (.66 / 61.0);
    }
    for(i = 0; i < 60; i++)
    {
        frame.ripple(2, amplitude, 4, phase);
        out += frame;
        frame.rotate_colors(1);
        phase += (two_pi / 61.0);
        amplitude += (.66 / 61.0);
    }
    for(i = 0; i < 60; i++)
    {
        frame.ripple(2, amplitude, 4, phase);
        out += frame;
        frame.rotate_colors(1);
        phase += (two_pi / 61.0);
    }
    for(i = 0; i < 60; i++)
    {
        frame.ripple(2, amplitude, 4, phase);
        out += frame;
        frame.rotate_colors(1);
        phase += (two_pi / 61.0);
        amplitude -= (.66 / 61.0);
    }
    out.save_as_ild(LASERBOY_ILD_SHARE + "tranz.ild");
    return LASERBOY_OK;
}

//############################################################################
int train(LaserBoy_frame* p_frame)
{
    int                 frame_count,
                        vertex_count;
    LaserBoy_3D_short   temp_position;
    LaserBoy_frame      frame(*p_frame);
    LaserBoy_frame_set  out(frame.p_space);
    //------------------------------------------------------------------------
    out += frame;
    for(frame_count = 0; frame_count < frame.number_of_vertices(); frame_count++)
    {
        temp_position = frame.front();
        for(vertex_count = 0; vertex_count < frame.number_of_vertices() - 1; vertex_count++)
            frame.at(vertex_count) = frame.at(vertex_count + 1).position();
        frame.back() = temp_position;
        out += frame;
    }
    out.save_as_ild(LASERBOY_ILD_SHARE + "train.ild");
    return LASERBOY_OK;
}

//############################################################################
int gleam(LaserBoy_frame* p_frame)
{
    int                 frame_count,
                        vertex_count,
                        counter;
    LaserBoy_frame      frame_1(*p_frame),
                        frame_2(*p_frame);
    LaserBoy_frame_set  out(frame_1.p_space);
    //------------------------------------------------------------------------
    frame_1.promote_to_true_color();
    frame_2.promote_to_true_color();
    for(frame_count = 0; frame_count < 10; frame_count++)
    {
        frame_2.clear();
        counter = frame_count;
        for(vertex_count = 0; vertex_count < frame_1.number_of_vertices(); vertex_count++)
        {
            frame_2.push_back(frame_1.at(vertex_count));
            if(    frame_1.at(vertex_count).is_color(0)
                && !(counter++ % 10)
              )
            {
                frame_2.push_back(frame_1.at(vertex_count));
                frame_2.back().r =
                frame_2.back().g =
                frame_2.back().b = 255;
                frame_2.push_back(frame_1.at(vertex_count));
                frame_2.back().blank();
            }
        }
        out += frame_2;
    }
    out.save_as_ild(LASERBOY_ILD_SHARE + "gleam.ild");
    return LASERBOY_OK;
}

//############################################################################
int stars(LaserBoy_frame* p_frame) // individual segments must have no size (dots!)
{
    int                frame_count,
                       segment_index;
    LaserBoy_3D_short  d,
                       center;
    LaserBoy_3D_double s(1.1, 1.1, 1.1);
    LaserBoy_frame     frame(*p_frame);
    LaserBoy_frame_set out(frame.p_space);
    //------------------------------------------------------------------------
    out += frame;
    for(frame_count = 0; frame_count < 199; frame_count++)
    {
        for(segment_index = 0; segment_index < frame.number_of_segments(); segment_index++)
        {
            if(frame.scale_segment_around_origin(segment_index, s)) // out of bounds
            {
                center = frame.find_segment_center(segment_index);
                while(!(d.x = rand() % 5000 - 2500)); //  -2500 to +2500, not zero
                while(!(d.y = rand() % 5000 - 2500));
                while(!(d.z = rand() % 5000 - 2500));
                d -= center;
                frame.move_segment(segment_index, d); // somewhere near the origin
            }
        }
        out += frame;
    }
    out.save_as_ild(LASERBOY_ILD_SHARE + "stars.ild");
    return LASERBOY_OK;
}

//############################################################################
int shrink(LaserBoy_frame* p_frame)
{
    int                frame_count;
    LaserBoy_3D_double s(0.96, 0.96, 0.96);
    LaserBoy_frame     frame(*p_frame);
    LaserBoy_frame_set out(frame.p_space);
    //------------------------------------------------------------------------
    out += frame;
    for(frame_count = 0; frame_count < 149; frame_count++)
    {
        frame.scale_around_origin(s);
        out += frame;
    }
    out.save_as_ild(LASERBOY_ILD_SHARE + "shrink.ild");
    return LASERBOY_OK;
}

//############################################################################
int fill(LaserBoy_frame* p_frame)
{
    int                i,
                       segment_index;
    LaserBoy_3D_double s;
    LaserBoy_frame     frame(*p_frame);
    LaserBoy_frame_set out(frame.p_space);
    //------------------------------------------------------------------------
    for(segment_index = 0; segment_index < (*p_frame).number_of_segments(); segment_index++)
    {
        frame = (*p_frame).find_segment(segment_index);
        out += frame;
        s = 0.95;
        for(i = 0; i < 20; i++)
        {
            frame = (*p_frame).find_segment(segment_index);
            frame.scale_segment(0, s);
            out[out.number_of_frames() - 1] += frame;
            s -= 0.05;
        }
    }
    out.convert_blank_to_black();
    out.save_as_ild(LASERBOY_ILD_SHARE + "fill.ild");
    return LASERBOY_OK;
}

//############################################################################
int squeez(LaserBoy_frame* p_frame)
{
    int                frame_count;
    LaserBoy_3D_double s;
    LaserBoy_frame     frame(*p_frame);
    LaserBoy_frame_set temp(frame.p_space),
                       out(frame.p_space);
    //------------------------------------------------------------------------
    s.x = 0.94;
    s.y = 1.00;
    s.z = 1.00;
    temp += frame;
    for(frame_count = 0; frame_count < 49; frame_count++)
    {
        frame.scale_around_origin(s);
        temp += frame;
    }
    out += temp;
    temp.reverse();
    temp.delete_frame(0);
    out += temp;
    temp.clear();
    //------------------------------------------------------------------------
    s.x = 1.00;
    s.y = 0.94;
    s.z = 1.00;
    frame = *(p_frame);
    temp += frame;
    for(frame_count = 0; frame_count < 49; frame_count++)
    {
        frame.scale_around_origin(s);
        temp += frame;
    }
    out += temp;
    temp.reverse();
    temp.delete_frame(0);
    out += temp;
    temp.clear();
    //------------------------------------------------------------------------
    s.x = 1.00;
    s.y = 1.00;
    s.z = 0.94;
    frame = *(p_frame);
    temp += frame;
    for(frame_count = 0; frame_count < 49; frame_count++)
    {
        frame.scale_around_origin(s);
        temp += frame;
    }
    out += temp;
    temp.reverse();
    temp.delete_frame(0);
    out += temp;
    temp.clear();
    //------------------------------------------------------------------------
    s.x = 0.94;
    s.y = 0.94;
    s.z = 0.94;
    frame = *(p_frame);
    temp += frame;
    for(frame_count = 0; frame_count < 49; frame_count++)
    {
        frame.scale_around_origin(s);
        temp += frame;
    }
    out += temp;
    temp.reverse();
    temp.delete_frame(0);
    out += temp;
    //------------------------------------------------------------------------
    out.save_as_ild(LASERBOY_ILD_SHARE + "squeez.ild");
    return LASERBOY_OK;
}

//############################################################################
int around(LaserBoy_frame* p_frame)
{
    int                frame_count,
                       segment_index,
                       total_segments;
    LaserBoy_3D_double a(0, 0, pi/20);
    LaserBoy_frame     frame(*p_frame);
    LaserBoy_frame_set out(frame.p_space);
    //------------------------------------------------------------------------
    out += frame;
    total_segments = frame.number_of_segments();

    for(segment_index = 0; segment_index < total_segments; segment_index++)
    {
        for(frame_count = 0; frame_count < 10; frame_count++)
        {
            frame.rotate_segment(segment_index, a);
            out += frame;
        }
    }
    for(segment_index = 0; segment_index < total_segments; segment_index++)
    {
        for(frame_count = 0; frame_count < 10; frame_count++)
        {
            frame.rotate_segment(segment_index, a);
            out += frame;
        }
    }
    for(frame_count = 0; frame_count < 20; frame_count++)
    {
        for(segment_index = 0; segment_index < total_segments; segment_index++)
            frame.rotate_segment(segment_index, a);
        out += frame;
    }
    for(frame_count = 0; frame_count < 20; frame_count++)
    {
        for(segment_index = 0; segment_index < total_segments; segment_index++)
            frame.rotate_segment(segment_index, a);
        out += frame;
    }
    for(frame_count = 0; frame_count < 20; frame_count++)
    {
        for(segment_index = 0; segment_index < total_segments; segment_index++)
            frame.rotate_segment(segment_index, a);
        out += frame;
    }
    out.save_as_ild(LASERBOY_ILD_SHARE + "around.ild");
    return LASERBOY_OK;
}

//############################################################################
int rotate(LaserBoy_frame* p_frame)
{
    int                frame_count;
    LaserBoy_3D_double a;
    LaserBoy_frame     frame(*p_frame);
    LaserBoy_frame_set out(frame.p_space);
    //------------------------------------------------------------------------
    a.x = -pi/100;
    a.y = 0;
    a.z = 0;
    for(frame_count = 0; frame_count < 200; frame_count++)
    {
        frame.rotate_colors(1);
        out += frame;
        frame.rotate_around_origin(a);
    }
    a.x = 0;
    a.y = pi/100;
    a.z = 0;
    for(frame_count = 0; frame_count < 200; frame_count++)
    {
        frame.rotate_colors(1);
        out += frame;
        frame.rotate_around_origin(a);
    }
    a.x = 0;
    a.y = 0;
    a.z = pi/100;
    for(frame_count = 0; frame_count < 200; frame_count++)
    {
        frame.rotate_colors(1);
        out += frame;
        frame.rotate_around_origin(a);
    }
    a.x = pi/100;
    a.y = pi/100;
    a.z = pi/100;
    for(frame_count = 0; frame_count < 233; frame_count++)
    {
        frame.rotate_colors(1);
        out += frame;
        frame.rotate_around_origin(a);
    }
    out.save_as_ild(LASERBOY_ILD_SHARE + "rotate.ild");
    return LASERBOY_OK;
}

//############################################################################
int rock(LaserBoy_frame* p_frame)
{
    int                i;
    LaserBoy_3D_double a(0, 0, one_degree);
    LaserBoy_frame     frame(*p_frame);
    LaserBoy_frame_set out(frame.p_space);
    //------------------------------------------------------------------------
    for(i = 0; i < 45; i++)
    {
        frame = *p_frame;
        frame.rotate_around_origin(a * i);
        out += frame;
    }
    for(i = 45; i > -45; i--)
    {
        frame = *p_frame;
        frame.rotate_around_origin(a * i);
        out += frame;
    }
    for(i = -45; i < 0; i++)
    {
        frame = *p_frame;
        frame.rotate_around_origin(a * i);
        out += frame;
    }
    out.save_as_ild(LASERBOY_ILD_SHARE + "rock.ild");
    return LASERBOY_OK;
}

//############################################################################
int bounce(LaserBoy_frame* p_frame)
{
    int                frame_count,
                       out_of_bounds;
    LaserBoy_3D_double r;
    LaserBoy_3D_short  d;
    LaserBoy_frame     frame(*p_frame);
    LaserBoy_frame_set out(frame.p_space);
    //------------------------------------------------------------------------
    d.x = short(random_neg_to_pos_1() * 3000);
    d.y = short(random_neg_to_pos_1() * 3000);
    d.z = short(random_neg_to_pos_1() * 3000);
    r.x = random_neg_to_pos_1() * pi/8.0;
    r.y = random_neg_to_pos_1() * pi/8.0;
    r.z = random_neg_to_pos_1() * pi/8.0;
    //------------------------------------------------------------------------
    out += frame;
    for(frame_count = 0; frame_count < 499; frame_count++)
    {
        frame.rotate(r);
        while((out_of_bounds = frame.move(d)))
        {
            switch(out_of_bounds)
            {
                //--------------------------------------------
                case LASERBOY_OUT_POS_X:
                case LASERBOY_OUT_NEG_X:
                      d.x = -d.x;
                      r.x = -r.x;
                      break;
                //--------------------------------------------
                case LASERBOY_OUT_POS_Y:
                case LASERBOY_OUT_NEG_Y:
                      d.y = -d.y;
                      r.y = -r.y;
                      break;
                //--------------------------------------------
                case LASERBOY_OUT_POS_Z:
                case LASERBOY_OUT_NEG_Z:
                      d.z = -d.z;
                      r.z = -r.z;
                      break;
                //--------------------------------------------
            }
        }
        out += frame;
        frame.rotate_colors(1);
    }
    out.save_as_ild(LASERBOY_ILD_SHARE + "bounce.ild");
    return LASERBOY_OK;
}

//############################################################################
int spin(LaserBoy_frame* p_frame)
{
    LaserBoy_frame      frame(*p_frame);
    LaserBoy_frame_set  out(frame.p_space);
    int                 frame_count,
                        segment_index,
                        out_of_bounds,
                        total_segments = frame.number_of_segments();
    LaserBoy_3D_double* r = new LaserBoy_3D_double[total_segments];
    LaserBoy_3D_short*  d = new LaserBoy_3D_short[total_segments];
    //------------------------------------------------------------------------
    for(segment_index = 0; segment_index < total_segments; segment_index++)
    {
        d[segment_index].x = short(random_neg_to_pos_1() * 1000);
        d[segment_index].y = short(random_neg_to_pos_1() * 1000);
        d[segment_index].z = short(random_neg_to_pos_1() * 1000);
        r[segment_index].x = random_neg_to_pos_1() * pi/20.0;
        r[segment_index].y = random_neg_to_pos_1() * pi/20.0;
        r[segment_index].z = random_neg_to_pos_1() * pi/20.0;
    }
    //------------------------------------------------------------------------
    out += frame;
    for(frame_count = 0; frame_count < 199; frame_count++)
    {
        for(segment_index = 0; segment_index < total_segments; segment_index++)
        {
            frame.rotate_segment(segment_index, r[segment_index]);
            while((out_of_bounds = frame.move_segment(segment_index, d[segment_index])))
            {
                switch(out_of_bounds)
                {
                    case LASERBOY_OUT_POS_X:
                    case LASERBOY_OUT_NEG_X:
                            d[segment_index].x = -d[segment_index].x;
                            r[segment_index].x = -r[segment_index].x;
                            break;
                    //--------------------------------------------
                    case LASERBOY_OUT_POS_Y:
                    case LASERBOY_OUT_NEG_Y:
                            d[segment_index].y = -d[segment_index].y;
                            r[segment_index].y = -r[segment_index].y;
                            break;
                    //--------------------------------------------
                    case LASERBOY_OUT_POS_Z:
                    case LASERBOY_OUT_NEG_Z:
                            d[segment_index].z = -d[segment_index].z;
                            r[segment_index].z = -r[segment_index].z;
                            break;
                    //--------------------------------------------
                }
            }
        }
        out += frame;
        frame.rotate_colors(1);
    }
    delete d;
    delete r;
    out.save_as_ild(LASERBOY_ILD_SHARE + "spin.ild");
    return LASERBOY_OK;
}

//############################################################################
int _break(LaserBoy_frame* p_frame)
{
    LaserBoy_frame      frame(*p_frame);
    LaserBoy_frame_set  out(frame.p_space);
    int                 frame_count,
                        segment_index,
                        out_of_bounds;
    LaserBoy_3D_short*  d = new LaserBoy_3D_short[frame.number_of_segments()];
    //------------------------------------------------------------------------
    for(segment_index = 0; segment_index < frame.number_of_segments(); segment_index++)
    {
        d[segment_index].x = short((random_01() - 0.5) * 3000);
        d[segment_index].y = short((random_01() - 0.5) * 3000);
        d[segment_index].z = short((random_01() - 0.5) * 3000);
    }
    //------------------------------------------------------------------------
    out += frame;
    for(frame_count = 1; frame_count < 199; frame_count++)
    {
        for(segment_index = 0; segment_index < frame.number_of_segments(); segment_index++)
            while((out_of_bounds = frame.move_segment(segment_index, d[segment_index])))
            {
                switch(out_of_bounds)
                {
                    case LASERBOY_OUT_POS_X:
                    case LASERBOY_OUT_NEG_X:
                            d[segment_index].x = -(d[segment_index].x);
                            break;
                    //--------------------------------------------
                    case LASERBOY_OUT_POS_Y:
                    case LASERBOY_OUT_NEG_Y:
                            d[segment_index].y = -(d[segment_index].y);
                            break;
                    //--------------------------------------------
                    case LASERBOY_OUT_POS_Z:
                    case LASERBOY_OUT_NEG_Z:
                            d[segment_index].z = -(d[segment_index].z);
                            break;
                    //--------------------------------------------
                }
            }
        out += frame;
        frame.rotate_colors(1);
    }
    delete d;
    out.save_as_ild(LASERBOY_ILD_SHARE + "break.ild");
    return LASERBOY_OK;
}

//############################################################################
int rainbow(LaserBoy_frame* p_frame)
{
    int                 i,
                        span =   p_frame->p_space->current_palette().last
                               - p_frame->p_space->current_palette().first;
    LaserBoy_frame_set  out(p_frame->p_space);
    //------------------------------------------------------------------------
    out += *p_frame;
    for(i = 1; i <= span; i++)
    {
        out[i - 1].rotate_colors(1);
        out += out[i - 1];
    }
    out.save_as_ild(LASERBOY_ILD_SHARE + "rainbow.ild");
    return LASERBOY_OK;
}

//############################################################################
int fade(LaserBoy_frame* p_frame)
{
    int                 i,
                        j;
    LaserBoy_frame      frame(p_frame->p_space);
    LaserBoy_frame_set  out(p_frame->p_space);
    //------------------------------------------------------------------------
    frame = *p_frame;
    out += frame;
    for(i = 1; i < 256; i++)
    {
        frame = *p_frame;
        frame.shade(i);
        out += frame;
    }
    out.save_as_ild(LASERBOY_ILD_SHARE + "fade.ild");
    return LASERBOY_OK;
}

//############################################################################
int bleach(LaserBoy_frame* p_frame)
{
    int                 i;
    LaserBoy_frame      frame(p_frame->p_space);
    LaserBoy_frame_set  out(p_frame->p_space);
    //------------------------------------------------------------------------
    frame = *p_frame;
    out += frame;
    for(i = 1; i < 256; i++)
    {
        frame = *p_frame;
        frame.tint(i);
        out += frame;
    }
    out.save_as_ild(LASERBOY_ILD_SHARE + "bleach.ild");
    return LASERBOY_OK;
}

//############################################################################
int move_l2r(LaserBoy_frame* p_frame)
{
    int                 i,
                        j;
    LaserBoy_3D_short   d;
    LaserBoy_frame      frame(p_frame->p_space);
    LaserBoy_frame_set  out(p_frame->p_space);
    //------------------------------------------------------------------------
    frame = *p_frame;
    d.x = -662;
    out += frame;
    for(i = 0; i < 100; i++)
    {
        for(j = 0; j < frame.number_of_vertices(); j++)
            if(frame.at(j).x <= LASERBOY_MIN_SHORT)
                frame.set_vertex_to_black(j);

        frame.move(d, false);
        out += frame;
    }
    out.reverse();
    //------------------------------------------------------------------------
    frame = *p_frame;
    d.x = 662;
    for(i = 0; i < 100; i++)
    {
        for(j = 0; j < frame.number_of_vertices(); j++)
            if(frame.at(j).x >= LASERBOY_MAX_SHORT)
                frame.set_vertex_to_black(j);
        frame.move(d, false);
        out += frame;
    }
    //------------------------------------------------------------------------
    out.save_as_ild(LASERBOY_ILD_SHARE + "move_l2r.ild");
    return LASERBOY_OK;
}

//############################################################################
int move_t2b(LaserBoy_frame* p_frame)
{
    int                 i,
                        j;
    LaserBoy_3D_short   d;
    LaserBoy_frame      frame(p_frame->p_space);
    LaserBoy_frame_set  out(p_frame->p_space);
    //------------------------------------------------------------------------
    frame = *p_frame;
    d.y = 662;
    out += frame;
    for(i = 0; i < 100; i++)
    {
        for(j = 0; j < frame.number_of_vertices(); j++)
            if(frame.at(j).y >= LASERBOY_MAX_SHORT)
                frame.set_vertex_to_black(j);
        frame.move(d, false);
        out += frame;
    }
    out.reverse();
    //------------------------------------------------------------------------
    frame = *p_frame;
    d.y = -662;
    for(i = 0; i < 100; i++)
    {
        for(j = 0; j < frame.number_of_vertices(); j++)
            if(frame.at(j).y <= LASERBOY_MIN_SHORT)
                frame.set_vertex_to_black(j);

        frame.move(d, false);
        out += frame;
    }
    //------------------------------------------------------------------------
    out.save_as_ild(LASERBOY_ILD_SHARE + "move_t2b.ild");
    return LASERBOY_OK;
}

//############################################################################
int wipe(LaserBoy_frame* p_frame)
{
    int                 i,
                        j;
    LaserBoy_frame      frame(p_frame->p_space);
    LaserBoy_frame_set  out(p_frame->p_space);
    //------------------------------------------------------------------------
    frame = *p_frame;
    out += frame;
    for(i = 0; i < 100; i++)
    {
        for(j = 0; j < frame.number_of_vertices(); j++)
            if(frame.at(j).x <= (short)((i * 661.98) - 32767.0))
                frame.set_vertex_to_black(j);
        out += frame;
    }
    out.save_as_ild(LASERBOY_ILD_SHARE + "wipe.ild");
    return LASERBOY_OK;
}

//############################################################################
int radial_wipe(LaserBoy_frame* p_frame)
{
    int                 i,
                        j;
    LaserBoy_frame      frame(p_frame->p_space);
    LaserBoy_frame_set  out(p_frame->p_space);
    //------------------------------------------------------------------------
    frame = *p_frame;
    out += frame;
    for(i = 99; i >= 0; i--)
    {
        for(j = 0; j < frame.number_of_vertices(); j++)
            if(frame.at(j).magnitude() >= (i * 468.09))
                frame.set_vertex_to_black(j);
        out += frame;
    }
    out.save_as_ild(LASERBOY_ILD_SHARE + "radial_wipe.ild");
    return LASERBOY_OK;
}

//############################################################################
int angle_wipe(LaserBoy_frame* p_frame)
{
    int                 i,
                        j;
    LaserBoy_frame      frame(p_frame->p_space);
    LaserBoy_frame_set  out(p_frame->p_space);
    //------------------------------------------------------------------------
    frame = *p_frame;
    frame.flip(0);
    out += frame;
    for(i = 99; i >= 0; i--)
    {
        for(j = 0; j < frame.number_of_vertices(); j++)
            if(((atan2(frame.at(j).y, frame.at(j).x) / two_pi) + 0.5) >= (i / 99.0))
                frame.set_vertex_to_black(j);
        out += frame;
    }
    out.flip(0);
    out.save_as_ild(LASERBOY_ILD_SHARE + "angle_wipe.ild");
    return LASERBOY_OK;
}

//############################################################################
int draw(LaserBoy_frame* p_frame)
{
    int                 i;
    LaserBoy_frame      frame(p_frame->p_space);
    LaserBoy_frame_set  out(p_frame->p_space);
    //------------------------------------------------------------------------
    frame += p_frame->front();
    frame += p_frame->front();
    out += frame;
    //------------------------------------------------------------------------
    for(i = 1; i < p_frame->number_of_vertices(); i++)
    {
        frame += p_frame->at(i);
        out += frame;
    }
    out.save_as_ild(LASERBOY_ILD_SHARE + "draw.ild");
    return LASERBOY_OK;
}

//############################################################################
int wobble(LaserBoy_frame* p_frame)
{
    LaserBoy_frame      frame(*p_frame);
    LaserBoy_frame_set  out(frame.p_space);
    int                 frame_count,
                        segment_index,
                        out_of_bounds;
    LaserBoy_3D_double* a = new LaserBoy_3D_double[frame.number_of_segments()];
    //------------------------------------------------------------------------
    for(segment_index = 0; segment_index < frame.number_of_segments(); segment_index++)
    {
        a[segment_index].x = (random_01() - 0.5) * pi/20;
        a[segment_index].y = (random_01() - 0.5) * pi/20;
        a[segment_index].z = (random_01() - 0.5) * pi/20;
    }

    out += frame;
    for(frame_count = 1; frame_count < 300; frame_count++)
    {
        for(segment_index = 0; segment_index < frame.number_of_segments(); segment_index++)
            while((out_of_bounds = frame.rotate_segment(segment_index, a[segment_index])))
            {
                switch(out_of_bounds)
                {
                    case LASERBOY_OUT_POS_X:
                    case LASERBOY_OUT_NEG_X:
                            a[segment_index].x = -a[segment_index].x;
                            break;
                    //--------------------------------------------
                    case LASERBOY_OUT_POS_Y:
                    case LASERBOY_OUT_NEG_Y:
                            a[segment_index].y = -a[segment_index].y;
                            break;
                    //--------------------------------------------
                    case LASERBOY_OUT_POS_Z:
                    case LASERBOY_OUT_NEG_Z:
                            a[segment_index].z = -a[segment_index].z;
                            break;
                    //--------------------------------------------
                }
            }
        out += frame;
        frame.rotate_colors(1);
    }
    delete a;
    out.save_as_ild(LASERBOY_ILD_SHARE + "wobble.ild");
    return LASERBOY_OK;
}

//############################################################################
int wiggle(LaserBoy_frame* p_frame)
{
    int                 frame_count,
                        segment_index;
    LaserBoy_3D_double  d;
    LaserBoy_frame      frame(*p_frame);
    LaserBoy_frame_set  out(frame.p_space);
    //------------------------------------------------------------------------
    out += frame;
    for(frame_count = 1; frame_count < 199; frame_count++)
    {
        for(segment_index = 0; segment_index < frame.number_of_segments(); segment_index++)
        {
            do
            {
                d.x = (random_01() - 0.5) * 1000;
                d.y = (random_01() - 0.5) * 1000;
                d.z = (random_01() - 0.5) * 1000;
            } while(frame.move_segment(segment_index, d));
        }
        out += frame;
    }
    out.save_as_ild(LASERBOY_ILD_SHARE + "wiggle.ild");
    return LASERBOY_OK;
}

//############################################################################
int throb(LaserBoy_frame* p_frame)
{
    bool                flip_flop = false;
    int                 frame_count,
                        segment_index;
    double              s;
    LaserBoy_frame      frame(*p_frame);
    LaserBoy_frame_set  out(frame.p_space);
    //------------------------------------------------------------------------
    out += frame;
    for(frame_count = 1; frame_count < 199; frame_count++)
    {
        for(segment_index = 0; segment_index < frame.number_of_segments(); segment_index++)
        {
            do
            {
                if(flip_flop)
                    s = (random_01() / 10 + 0.9); // 0.9 to 1.0
                else
                    s = (random_01() / 10 + 1.0); // 1.0 to 1.1
                flip_flop = !flip_flop;
            } while(frame.scale_segment(segment_index, s));
        }
        out += frame;
    }
    out.save_as_ild(LASERBOY_ILD_SHARE + "throb.ild");
    return LASERBOY_OK;
}

//############################################################################
int pop(LaserBoy_frame* p_frame)
{
    bool                flip_flop = false;
    int                 frame_count,
                        segment_index;
    double              s;
    LaserBoy_frame      frame(*p_frame);
    LaserBoy_frame_set  out(frame.p_space);
    //------------------------------------------------------------------------
    out += frame;
    for(frame_count = 1; frame_count < 199; frame_count++)
    {
        for(segment_index = 0; segment_index < frame.number_of_segments(); segment_index++)
        {
            do
            {
                if(flip_flop)
                    s = 0.8;
                else
                    s = 1.2;
                flip_flop = !flip_flop;
            } while(frame.scale_segment(segment_index, s));
        }
        out += frame;
    }
    out.save_as_ild(LASERBOY_ILD_SHARE + "pop.ild");
    return LASERBOY_OK;
}

//############################################################################
int jazz(LaserBoy_frame* p_frame)
{
    bool                flip_flop = false;
    int                 frame_count,
                        segment_index;
    double              s;
    LaserBoy_frame      frame(*p_frame);
    LaserBoy_frame_set  out(frame.p_space);
    //------------------------------------------------------------------------
    out += frame;
    for(frame_count = 1; frame_count < 199; frame_count++)
    {
        for(segment_index = 0; segment_index < frame.number_of_segments(); segment_index++)
        {
            do
            {
                if(flip_flop)
                    s = (random_01() / 10 + 0.9); // 0.9 to 1.0
                else
                    s = (random_01() / 10 + 1.0); // 1.0 to 1.1
                flip_flop = !flip_flop;
            } while(frame.scale_segment_around_origin(segment_index, s));
        }
        out += frame;
    }
    out.save_as_ild(LASERBOY_ILD_SHARE + "jazz.ild");
    return LASERBOY_OK;
}

//############################################################################
int bump(LaserBoy_frame* p_frame)
{
    bool                flip_flop = false;
    int                 frame_count,
                        segment_index;
    double              s;
    LaserBoy_frame      frame(*p_frame);
    LaserBoy_frame_set  out(frame.p_space);
    //------------------------------------------------------------------------
    out += frame;
    for(frame_count = 1; frame_count < 199; frame_count++)
    {
        for(segment_index = 0; segment_index < frame.number_of_segments(); segment_index++)
        {
            do
            {
                if(flip_flop)
                    s = 0.8;
                else
                    s = 1.2;
                flip_flop = !flip_flop;
            } while(frame.scale_segment_around_origin(segment_index, s));
        }
        out += frame;
    }
    out.save_as_ild(LASERBOY_ILD_SHARE + "bump.ild");
    return LASERBOY_OK;
}

//############################################################################
int scan(LaserBoy_frame* p_frame)
{
    int                 frame_count,
                        segment_index,
                        out_of_bounds;
    LaserBoy_3D_short   d(1200,  666,     0);
    LaserBoy_3D_double  a(   0,    0, pi/30);
    LaserBoy_frame      frame(*p_frame);
    LaserBoy_frame_set  out(frame.p_space);
    //------------------------------------------------------------------------
    out += frame;
    for(frame_count = 0; frame_count < 199; frame_count++)
    {
        for(segment_index = 0; segment_index < frame.number_of_segments(); segment_index++)
        {
            frame.rotate_segment(segment_index, a);
            while((out_of_bounds = frame.move_segment(segment_index, d)))
            {
                switch(out_of_bounds)
                {
                    //--------------------------------------------
                    case LASERBOY_OUT_POS_X:
                    case LASERBOY_OUT_NEG_X:
                        d.x = -d.x;
                        break;
                    //--------------------------------------------
                    case LASERBOY_OUT_POS_Y:
                    case LASERBOY_OUT_NEG_Y:
                        d.y = -d.y;
                        break;
                    //--------------------------------------------
                }
            }
        }
        out += frame;
    }
    out.save_as_ild(LASERBOY_ILD_SHARE + "scan.ild");
    return LASERBOY_OK;
}

//############################################################################
int fall(LaserBoy_frame* p_frame)
{
    int                  frame_count,
                         segment_index,
                         out_of_bounds;
    LaserBoy_3D_double   d;
    LaserBoy_frame       frame(*p_frame);
    LaserBoy_frame_set   segments = frame.find_segments(),
                         out(frame.p_space);
    //------------------------------------------------------------------------
    out += frame;
    for(frame_count = 1; frame_count < 199; frame_count++)
    {
        for(segment_index = 0; segment_index < segments.number_of_frames(); segment_index++)
        {
            d.x = (random_01() - 0.5) * 1000; // -500 to +500
            d.y = (random_01() - 1  ) * 1000; // always negative. DOWN!
            d.z = (random_01() - 0.5) * 1000; // -500 to +500
            out_of_bounds = segments[segment_index].move(d);
            if(out_of_bounds)
            {
                switch(out_of_bounds)
                {
                    case LASERBOY_OUT_POS_X:
                    case LASERBOY_OUT_NEG_X:
                        d.x = -d.x;
                        break;
                    //--------------------------------------------
                    case LASERBOY_OUT_NEG_Y:
                        d.y = 60000 - segments[segment_index].segment_height();
                        cout << segments[segment_index].segment_top().y << ENDL;
                        break;
                    //--------------------------------------------
                    case LASERBOY_OUT_POS_Z:
                    case LASERBOY_OUT_NEG_Z:
                        d.z = -d.z;
                        break;
                    //--------------------------------------------
                }
                segments[segment_index].move(d);
            }
        }
        frame = segments.sum_of_frames();
        out += frame;
    }
    out.save_as_ild(LASERBOY_ILD_SHARE + "fall.ild");
    return LASERBOY_OK;
}

//############################################################################
int melt(LaserBoy_frame* p_frame)
{
    int                 frame_count,
                        i;
    LaserBoy_frame      frame(*p_frame);
    LaserBoy_frame_set  out(frame.p_space);
    //------------------------------------------------------------------------
    out += frame;
    for(frame_count = 1; frame_count < 199; frame_count++)
    {
        frame.at(0).x = (short)((   frame.back().x  / 10.0
                                  + frame.at(0).x
                                  + frame.at(1).x  / 10.0
                                )
                                / 1.2
                                + 0.5
                               );
        frame.at(0).y = (short)((   frame.back().y  / 10.0
                                  + frame.at(0).y
                                  + frame.at(1).y  / 10.0
                                )
                                / 1.2
                                + 0.5
                               );
        frame.at(0).z = (short)((   frame.back().z  / 10.0
                                  + frame.at(0).z
                                  + frame.at(1).z  / 10.0
                                )
                                / 1.2
                                + 0.5
                               );
        for(i = 1; i < (int)frame.size() - 1; i++)
        {
            frame.at(i).x = (short)((   frame.at(i - 1).x  / 10.0
                                      + frame.at(i).x
                                      + frame.at(i + 1).x  / 10.0
                                    )
                                    / 1.2
                                    + 0.5
                                   );
            frame.at(i).y = (short)((   frame.at(i - 1).y  / 10.0
                                      + frame.at(i).y
                                      + frame.at(i + 1).y  / 10.0
                                    )
                                    / 1.2
                                    + 0.5
                                   );
            frame.at(i).z = (short)((   frame.at(i - 1).z  / 10.0
                                      + frame.at(i).z
                                      + frame.at(i + 1).z  / 10.0
                                    )
                                    / 1.2
                                    + 0.5
                                   );
        }
        frame.back().x = (short)((  frame.at(frame.size() - 2).x  / 10.0
                                  + frame.back().x
                                  + frame.at(0).x  / 10.0
                                )
                                / 1.2
                                + 0.5
                               );
        frame.back().y = (short)((  frame.at(frame.size() - 2).y  / 10.0
                                  + frame.back().y
                                  + frame.at(0).y  / 10.0
                                )
                                / 1.2
                                + 0.5
                               );
        frame.back().z = (short)((  frame.at(frame.size() - 2).z  / 10.0
                                  + frame.back().z
                                  + frame.at(0).z  / 10.0
                                )
                                / 1.2
                                + 0.5
                               );
        out += frame;
    }
    out.save_as_ild(LASERBOY_ILD_SHARE + "melt.ild");
    return LASERBOY_OK;
}

//############################################################################
int squirm(LaserBoy_frame* p_frame)
{
    int                 frame_count,
                        i;
    LaserBoy_frame      frame(*p_frame);
    LaserBoy_frame_set  out(frame.p_space);
    //------------------------------------------------------------------------
    out += frame;
    for(frame_count = 1; frame_count < 199; frame_count++)
    {
        frame.at(0).x = (short)((   frame.back().x  / 10.0
                                  + frame.at(0).x
                                  - frame.at(1).x  / 10.0
                                )
                                + 0.5
                               );
        frame.at(0).y = (short)((   frame.back().y  / 10.0
                                  + frame.at(0).y
                                  - frame.at(1).y  / 10.0
                                )
                                + 0.5
                               );
        frame.at(0).z = (short)((   frame.back().z  / 10.0
                                  + frame.at(0).z
                                  - frame.at(1).z  / 10.0
                                )
                                + 0.5
                               );
        for(i = 1; i < (int)frame.size() - 1; i++)
        {
            frame.at(i).x = (short)((   frame.at(i - 1).x  / 10.0
                                      + frame.at(i).x
                                      - frame.at(i + 1).x  / 10.0
                                    )
                                    + 0.5
                                   );
            frame.at(i).y = (short)((   frame.at(i - 1).y  / 10.0
                                      + frame.at(i).y
                                      - frame.at(i + 1).y  / 10.0
                                    )
                                    + 0.5
                                   );
            frame.at(i).z = (short)((   frame.at(i - 1).z  / 10.0
                                      + frame.at(i).z
                                      - frame.at(i + 1).z  / 10.0
                                    )
                                    + 0.5
                                   );
        }
        frame.back().x = (short)((  frame.at(frame.size() - 2).x  / 10.0
                                  + frame.back().x
                                  - frame.at(0).x  / 10.0
                                )
                                + 0.5
                               );
        frame.back().y = (short)((  frame.at(frame.size() - 2).y  / 10.0
                                  + frame.back().y
                                  - frame.at(0).y  / 10.0
                                )
                                + 0.5
                               );
        frame.back().z = (short)((  frame.at(frame.size() - 2).z  / 10.0
                                  + frame.back().z
                                  - frame.at(0).z  / 10.0
                                )
                                + 0.5
                               );
        out += frame;
    }
    out.save_as_ild(LASERBOY_ILD_SHARE + "squirm.ild");
    return LASERBOY_OK;
}

//############################################################################








//############################################################################
void LaserBoy_space::load_frame_effects()
{
    //------------------------------------------------------------------------
    frame_effects.push_back(around);
    frame_effect_names.push_back(string("around"));
    //------------------------------------------------------------------------
    frame_effects.push_back(angle_wipe);
    frame_effect_names.push_back(string("angle_wipe"));
    //------------------------------------------------------------------------
    frame_effects.push_back(bleach);
    frame_effect_names.push_back(string("bleach"));
    //------------------------------------------------------------------------
    frame_effects.push_back(bounce);
    frame_effect_names.push_back(string("bounce"));
    //------------------------------------------------------------------------
    frame_effects.push_back(_break);
    frame_effect_names.push_back(string("break"));
    //------------------------------------------------------------------------
    frame_effects.push_back(bump);
    frame_effect_names.push_back(string("bump"));
    //------------------------------------------------------------------------
    frame_effects.push_back(draw);
    frame_effect_names.push_back(string("draw"));
    //------------------------------------------------------------------------
    frame_effects.push_back(fade);
    frame_effect_names.push_back(string("fade"));
    //------------------------------------------------------------------------
    frame_effects.push_back(fill);
    frame_effect_names.push_back(string("fill"));
    //------------------------------------------------------------------------
    frame_effects.push_back(fall);
    frame_effect_names.push_back(string("fall"));
    //------------------------------------------------------------------------
    frame_effects.push_back(gleam);
    frame_effect_names.push_back(string("gleam"));
    //------------------------------------------------------------------------
    frame_effects.push_back(jazz);
    frame_effect_names.push_back(string("jazz"));
    //------------------------------------------------------------------------
    frame_effects.push_back(melt);
    frame_effect_names.push_back(string("melt"));
    //------------------------------------------------------------------------
    frame_effects.push_back(move_l2r);
    frame_effect_names.push_back(string("move_l2r"));
    //------------------------------------------------------------------------
    frame_effects.push_back(move_t2b);
    frame_effect_names.push_back(string("move_t2b"));
    //------------------------------------------------------------------------
    frame_effects.push_back(pop);
    frame_effect_names.push_back(string("pop"));
    //------------------------------------------------------------------------
    frame_effects.push_back(radial_wipe);
    frame_effect_names.push_back(string("radial_wipe"));
    //------------------------------------------------------------------------
    frame_effects.push_back(rainbow);
    frame_effect_names.push_back(string("rainbow"));
    //------------------------------------------------------------------------
    frame_effects.push_back(rotate);
    frame_effect_names.push_back(string("rotate"));
    //------------------------------------------------------------------------
    frame_effects.push_back(rock);
    frame_effect_names.push_back(string("rock"));
    //------------------------------------------------------------------------
    frame_effects.push_back(scan);
    frame_effect_names.push_back(string("scan"));
    //------------------------------------------------------------------------
    frame_effects.push_back(shrink);
    frame_effect_names.push_back(string("shrink"));
    //------------------------------------------------------------------------
    frame_effects.push_back(spin);
    frame_effect_names.push_back(string("spin"));
    //------------------------------------------------------------------------
    frame_effects.push_back(squeez);
    frame_effect_names.push_back(string("squeez"));
    //------------------------------------------------------------------------
    frame_effects.push_back(squirm);
    frame_effect_names.push_back(string("squirm"));
    //------------------------------------------------------------------------
    frame_effects.push_back(stars);
    frame_effect_names.push_back(string("stars"));
    //------------------------------------------------------------------------
    frame_effects.push_back(throb);
    frame_effect_names.push_back(string("throb"));
    //------------------------------------------------------------------------
    frame_effects.push_back(train);
    frame_effect_names.push_back(string("train"));
    //------------------------------------------------------------------------
    frame_effects.push_back(tranz);
    frame_effect_names.push_back(string("tranz"));
    //------------------------------------------------------------------------
    frame_effects.push_back(wiggle);
    frame_effect_names.push_back(string("wiggle"));
    //------------------------------------------------------------------------
    frame_effects.push_back(wipe);
    frame_effect_names.push_back(string("wipe"));
    //------------------------------------------------------------------------
    frame_effects.push_back(wobble);
    frame_effect_names.push_back(string("wobble"));
    //------------------------------------------------------------------------
    return;
}

//############################################################################
//////////////////////////////////////////////////////////////////////////////
//############################################################################
