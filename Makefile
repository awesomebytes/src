# Project: LaserBoy
# by James Lehman.

RM       = rm -f
STRIP    = strip -s -v
CPP      = g++
CPPFLAGS = -O3 -fexpensive-optimizations -static
OBJ      = ../src/LaserBoy_dxf_to_ilda_tool.obj ../src/LaserBoy_common.obj ../src/LaserBoy_frame.obj ../src/LaserBoy_frame_effects.obj ../src/LaserBoy_frame_set.obj ../src/LaserBoy_frame_set_effects.obj ../src/LaserBoy_ild_header.obj ../src/LaserBoy_segment.obj ../src/LaserBoy_palette.obj ../src/LaserBoy_palette_set.obj ../src/LaserBoy_real_segment.obj ../src/LaserBoy_wave.obj ../src/LaserBoy_space.obj ../src/LaserBoy_TUI.obj ../src/LaserBoy_SDL_GUI.obj ../src/LaserBoy_bmp.obj ../src/LaserBoy_font.obj
LIBS     = -lSDL -lboost_system -lboost_filesystem
BIN      = ../LaserBoy_dxf_to_ilda_tool
HEADERS  = LaserBoy_3D_double.hpp LaserBoy_3D_short.hpp LaserBoy_bmp.hpp LaserBoy_color.hpp LaserBoy_common.hpp LaserBoy_font.hpp LaserBoy_frame.hpp LaserBoy_frame_set.hpp LaserBoy_GUI_base.hpp LaserBoy_ild_header.hpp LaserBoy_includes.hpp LaserBoy_macros.hpp LaserBoy_palette.hpp LaserBoy_palette_set.hpp LaserBoy_real_segment.hpp LaserBoy_real_vertex.hpp LaserBoy_SDL_GUI.hpp LaserBoy_segment.hpp LaserBoy_space.hpp LaserBoy_TUI.hpp LaserBoy_utility.hpp LaserBoy_vertex.hpp LaserBoy_wave.hpp

all: $(BIN) strip

strip:
	$(STRIP) $(BIN)

clean:
	$(RM) $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(OBJ) -o $(BIN) $(LIBS)

../src/LaserBoy_dxf_to_ilda_tool.obj: LaserBoy_dxf_to_ilda_tool.cpp $(HEADERS)
	$(CPP) -c LaserBoy_dxf_to_ilda_tool.cpp -o ../src/LaserBoy_dxf_to_ilda_tool.obj $(CPPFLAGS)

../src/LaserBoy_SDL_GUI.obj: LaserBoy_SDL_GUI.cpp $(HEADERS)
	$(CPP) -c LaserBoy_SDL_GUI.cpp -o ../src/LaserBoy_SDL_GUI.obj $(CPPFLAGS)

../src/LaserBoy_TUI.obj: LaserBoy_TUI.cpp $(HEADERS)
	$(CPP) -c LaserBoy_TUI.cpp -o ../src/LaserBoy_TUI.obj $(CPPFLAGS)

../src/LaserBoy_space.obj: LaserBoy_space.cpp $(SPACE_HEADERS)
	$(CPP) -c LaserBoy_space.cpp -o ../src/LaserBoy_space.obj $(CPPFLAGS)

../src/LaserBoy_frame_set_effects.obj: LaserBoy_frame_set_effects.cpp $(HEADERS)
	$(CPP) -c LaserBoy_frame_set_effects.cpp -o ../src/LaserBoy_frame_set_effects.obj $(CPPFLAGS)

../src/LaserBoy_frame_effects.obj: LaserBoy_frame_effects.cpp $(HEADERS)
	$(CPP) -c LaserBoy_frame_effects.cpp -o ../src/LaserBoy_frame_effects.obj $(CPPFLAGS)

../src/LaserBoy_palette_set.obj: LaserBoy_palette_set.cpp $(HEADERS)
	$(CPP) -c LaserBoy_palette_set.cpp -o ../src/LaserBoy_palette_set.obj $(CPPFLAGS)

../src/LaserBoy_palette.obj: LaserBoy_palette.cpp $(HEADERS)
	$(CPP) -c LaserBoy_palette.cpp -o ../src/LaserBoy_palette.obj $(CPPFLAGS)

../src/LaserBoy_frame_set.obj: LaserBoy_frame_set.cpp $(HEADERS)
	$(CPP) -c LaserBoy_frame_set.cpp -o ../src/LaserBoy_frame_set.obj $(CPPFLAGS)

../src/LaserBoy_frame.obj: LaserBoy_frame.cpp $(HEADERS)
	$(CPP) -c LaserBoy_frame.cpp -o ../src/LaserBoy_frame.obj $(CPPFLAGS)

../src/LaserBoy_ild_header.obj: LaserBoy_ild_header.cpp LaserBoy_ild_header.hpp LaserBoy_common.hpp LaserBoy_macros.hpp LaserBoy_includes.hpp
	$(CPP) -c LaserBoy_ild_header.cpp -o ../src/LaserBoy_ild_header.obj $(CPPFLAGS)

../src/LaserBoy_bmp.obj: LaserBoy_bmp.cpp LaserBoy_bmp.hpp LaserBoy_font.hpp LaserBoy_color.hpp LaserBoy_common.hpp LaserBoy_macros.hpp LaserBoy_includes.hpp
	$(CPP) -c LaserBoy_bmp.cpp -o ../src/LaserBoy_bmp.obj $(CPPFLAGS)

../src/LaserBoy_font.obj: LaserBoy_font.cpp LaserBoy_font.hpp
	$(CPP) -c LaserBoy_font.cpp -o ../src/LaserBoy_font.obj $(CPPFLAGS)

../src/LaserBoy_segment.obj: LaserBoy_segment.cpp $(HEADERS)
	$(CPP) -c LaserBoy_segment.cpp -o ../src/LaserBoy_segment.obj $(CPPFLAGS)

../src/LaserBoy_real_segment.obj: LaserBoy_real_segment.cpp $(HEADERS)
	$(CPP) -c LaserBoy_real_segment.cpp -o ../src/LaserBoy_real_segment.obj $(CPPFLAGS)

../src/LaserBoy_wave.obj: LaserBoy_wave.cpp LaserBoy_wave.hpp LaserBoy_common.hpp LaserBoy_macros.hpp LaserBoy_includes.hpp
	$(CPP) -c LaserBoy_wave.cpp -o ../src/LaserBoy_wave.obj $(CPPFLAGS)

../src/LaserBoy_common.obj: LaserBoy_common.cpp LaserBoy_common.hpp LaserBoy_macros.hpp LaserBoy_includes.hpp
	$(CPP) -c LaserBoy_common.cpp -o ../src/LaserBoy_common.obj $(CPPFLAGS)
