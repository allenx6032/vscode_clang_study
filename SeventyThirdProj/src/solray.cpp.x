
#include <raylib/raylib.h>
#include <sol/sol.hpp>

namespace solray {
    extern "C" {
        __attribute__((visibility("default"))) int luaopen_solray(lua_State *L) {
            sol::state lua(L);
            sol::table raylib = lua.create_table();

            raylib.new_usertype<Color>(
                "Color", sol::constructors<Color()>(),
                sol::constructors<Color(unsigned char, unsigned char, unsigned char)>(),
                "r", &Color::r, "g", &Color::g, "b", &Color::b, "a", &Color::a);

            raylib.new_usertype<Vector2>("Vector2", sol::constructors<Vector2()>(),
                                         sol::constructors<Vector2(float, float)>(),
                                         "x", &Vector2::x, "y", &Vector2::y);

            raylib.new_usertype<Vector3>(
                "Vector3", sol::constructors<Vector3()>(),
                sol::constructors<Vector3(float, float, float)>(), "x", &Vector3::x,
                "y", &Vector3::y, "z", &Vector3::z);

            raylib.new_usertype<Vector4>(
                "Vector4", sol::constructors<Vector4()>(),
                sol::constructors<Vector4(float, float, float, float)>(), "x",
                &Vector4::x, "y", &Vector4::y, "z", &Vector4::z, "w", &Vector4::w);

            raylib.new_usertype<Texture>("Texture", sol::constructors<Texture()>(),
                                         "id", &Texture::id, "width", &Texture::width,
                                         "height", &Texture::height, "mipmaps",
                                         &Texture::mipmaps, "format", &Texture::format);

            raylib.new_usertype<Matrix>(
                "Matrix", sol::constructors<Matrix()>(),
                sol::constructors<Matrix(float, float, float, float, float, float,
                                         float, float, float, float, float, float,
                                         float, float, float, float)>(),
                "m0", &Matrix::m0, "m1", &Matrix::m1, "m2", &Matrix::m2, "m3",
                &Matrix::m3, "m4", &Matrix::m4, "m5", &Matrix::m5, "m6", &Matrix::m6,
                "m7", &Matrix::m7, "m8", &Matrix::m8, "m9", &Matrix::m9, "m10",
                &Matrix::m10, "m11", &Matrix::m11, "m12", &Matrix::m12, "m13",
                &Matrix::m13, "m14", &Matrix::m14, "m15", &Matrix::m15);

            raylib.new_usertype<Texture2D>(
                "Texture2D", sol::constructors<Texture2D()>(), "id", &Texture2D::id,
                "width", &Texture2D::width, "height", &Texture2D::height, "mipmaps",
                &Texture2D::mipmaps, "format", &Texture2D::format);

            raylib.new_usertype<Rectangle>(
                "Rectangle", sol::constructors<Rectangle()>(),
                sol::constructors<Rectangle(float, float, float, float)>(), "x",
                &Rectangle::x, "y", &Rectangle::y, "width", &Rectangle::width, "height",
                &Rectangle::height);

            raylib.new_usertype<Image>("Image", sol::constructors<Image()>(),
                                       sol::constructors<Image(int, int, int, int)>(),
                                       "data", &Image::data, "width", &Image::width,
                                       "height", &Image::height, "mipmaps",
                                       &Image::mipmaps, "format", &Image::format);

            raylib.new_usertype<RenderTexture>(
                "RenderTexture", sol::constructors<RenderTexture()>(), "id",
                &RenderTexture::id, "texture", &RenderTexture::texture, "depth",
                &RenderTexture::depth);

            raylib.new_usertype<NPatchInfo>(
                "NPatchInfo", sol::constructors<NPatchInfo()>(),
                sol::constructors<NPatchInfo(Rectangle, int, int, int, int)>(),
                "source", &NPatchInfo::source, "left", &NPatchInfo::left, "top",
                &NPatchInfo::top, "right", &NPatchInfo::right, "bottom",
                &NPatchInfo::bottom, "layout", &NPatchInfo::layout);

            raylib.new_usertype<GlyphInfo>(
                "GlyphInfo", sol::constructors<GlyphInfo()>(),
                sol::constructors<GlyphInfo(int, int, int, int, int, int)>(), "value",
                &GlyphInfo::value, "offset_x", &GlyphInfo::offsetX, "offset_y",
                &GlyphInfo::offsetY, "advance_x", &GlyphInfo::advanceX, "image",
                &GlyphInfo::image);

            raylib.new_usertype<Font>("Font", sol::constructors<Font()>(),
                                      sol::constructors<Font(int, int, int, int)>(),
                                      "base_size", &Font::baseSize, "glyph_count",
                                      &Font::glyphCount, "glyphs", &Font::glyphs,
                                      "texture", &Font::texture, "recs", &Font::recs);

            raylib.new_usertype<Camera2D>(
                "Camera2D", sol::constructors<Camera2D()>(),
                sol::constructors<Camera2D(Vector2, Vector2, float, int)>(), "offset",
                &Camera2D::offset, "target", &Camera2D::target, "rotation",
                &Camera2D::rotation, "zoom", &Camera2D::zoom);

            raylib.new_usertype<Camera3D>(
                "Camera3D", sol::constructors<Camera3D()>(),
                sol::constructors<Camera3D(Vector3, Vector3, Vector3, float, int)>(),
                "position", &Camera3D::position, "target", &Camera3D::target, "up",
                &Camera3D::up, "fovy", &Camera3D::fovy);

            raylib.new_usertype<Shader>("Shader", sol::constructors<Shader()>(),
                                        sol::constructors<Shader(int, int)>(), "id",
                                        &Shader::id, "locs", &Shader::locs);

            raylib.new_usertype<MaterialMap>(
                "MaterialMap", sol::constructors<MaterialMap()>(),
                sol::constructors<MaterialMap(int, int)>(), "texture",
                &MaterialMap::texture, "color", &MaterialMap::color, "value",
                &MaterialMap::value);

            raylib.new_usertype<Material>(
                "Material", sol::constructors<Material()>(),
                sol::constructors<Material(Shader, MaterialMap)>(), "shader",
                &Material::shader, "maps", &Material::maps, "params",
                &Material::params);

            raylib.new_usertype<Camera2D>(
                "Mesh", sol::constructors<Camera2D()>(),
                sol::constructors<Camera2D(Vector3, Vector3, Vector3, float, int)>(),
                "vboId", &Mesh::vboId, "vaoId", &Mesh::vaoId, "vertexCount",
                &Mesh::vertexCount);

            raylib.new_usertype<Model>("Model", sol::constructors<Model()>(),
                                       sol::constructors<Model(Mesh, Material)>(),
                                       "transform", &Model::transform, "meshCount",
                                       &Model::meshCount, "meshes", &Model::meshes,
                                       "materials", &Model::materials);

            raylib["init_window"] = &InitWindow;
            raylib["close_window"] = &CloseWindow;
            raylib["window_should_close"] = &WindowShouldClose;
            raylib["is_window_ready"] = &IsWindowReady;
            raylib["is_window_minimized"] = &IsWindowMinimized;
            raylib["is_window_resized"] = &IsWindowResized;
            raylib["is_window_hidden"] = &IsWindowHidden;
            raylib["is_window_maximized"] = &IsWindowMaximized;
            raylib["is_window_focused"] = &IsWindowFocused;
            raylib["is_window_fullscreen"] = &IsWindowFullscreen;
            raylib["is_window_state"] = &IsWindowState;
            raylib["set_window_state"] = &SetWindowState;
            raylib["clear_window_state"] = &ClearWindowState;
            raylib["toggle_fullscreen"] = &ToggleFullscreen;
            raylib["toggle_borderless_windowed"] = &ToggleBorderlessWindowed;
            raylib["maximize_window"] = &MaximizeWindow;
            raylib["minimize_window"] = &MinimizeWindow;
            raylib["restore_window"] = &RestoreWindow;
            raylib["set_window_icon"] = &SetWindowIcon;
            raylib["set_window_icons"] = &SetWindowIcons;
            raylib["set_window_title"] = &SetWindowTitle;
            raylib["set_window_position"] = &SetWindowPosition;
            raylib["set_window_monitor"] = &SetWindowMonitor;
            raylib["set_window_min_size"] = &SetWindowMinSize;
            raylib["set_window_max_size"] = &SetWindowMaxSize;
            raylib["set_window_size"] = &SetWindowSize;
            raylib["set_window_opacity"] = &SetWindowOpacity;
            raylib["set_window_focused"] = &SetWindowFocused;
            raylib["get_window_handle"] = &GetWindowHandle;
            raylib["get_screen_width"] = &GetScreenWidth;
            raylib["get_screen_height"] = &GetScreenHeight;
            raylib["ger_render_width"] = &GetRenderWidth;
            raylib["get_render_height"] = &GetRenderHeight;
            raylib["get_monitor_count"] = &GetMonitorCount;
            raylib["get_current_monitor"] = &GetCurrentMonitor;
            raylib["get_monitor_position"] = &GetMonitorPosition;
            raylib["get_monitor_width"] = &GetMonitorWidth;
            raylib["get_monitor_height"] = &GetMonitorHeight;
            raylib["get_monitor_physical_width"] = &GetMonitorPhysicalWidth;
            raylib["get_monitor_physical_height"] = &GetMonitorPhysicalHeight;
            raylib["get_monitor_refresh_rate"] = &GetMonitorRefreshRate;
            raylib["get_window_position"] = &GetWindowPosition;
            raylib["get_window_scale_dpi"] = &GetWindowScaleDPI;
            raylib["get_monitor_name"] = &GetMonitorName;
            raylib["set_clipboard_text"] = &SetClipboardText;
            raylib["get_clipboard_text"] = &GetClipboardText;
            raylib["enable_event_waiting"] = &EnableEventWaiting;

            raylib["show_cursor"] = &ShowCursor;
            raylib["hide_cursor"] = &HideCursor;
            raylib["is_cursor_hidden"] = &IsCursorHidden;
            raylib["enable_cursor"] = &EnableCursor;
            raylib["disable_cursor"] = &DisableCursor;
            raylib["is_cursor_on_screen"] = &IsCursorOnScreen;

            raylib["clear_background"] = &ClearBackground;
            raylib["begin_drawing"] = &BeginDrawing;
            raylib["end_drawing"] = &EndDrawing;
            raylib["begin_mode2d"] = &BeginMode2D;
            raylib["end_mode2d"] = &EndMode2D;
            raylib["begin_mode3d"] = &BeginMode3D;
            raylib["end_mode3d"] = &EndMode3D;
            raylib["begin_texture_mode"] = &BeginTextureMode;
            raylib["end_texture_mode"] = &EndTextureMode;
            raylib["begin_scissor_mode"] = &BeginScissorMode;
            raylib["end_scissor_mode"] = &EndScissorMode;
            raylib["begin_shader_mode"] = &BeginShaderMode;
            raylib["end_shader_mode"] = &EndShaderMode;
            raylib["begin_blend_mode"] = &BeginBlendMode;
            raylib["end_blend_mode"] = &EndBlendMode;
            raylib["begin_vr_stereo_mode"] = &BeginVrStereoMode;
            raylib["end_vr_stereo_mode"] = &EndVrStereoMode;

            raylib["load_vr_stereo_config"] = &LoadVrStereoConfig;
            raylib["unload_vr_stereo_config"] = &UnloadVrStereoConfig;

            raylib["load_shader"] = &LoadShader;
            raylib["load_shader_from_memory"] = &LoadShaderFromMemory;
            raylib["unload_shader"] = &UnloadShader;
            raylib["is_shader_valid"] = &IsShaderValid;
            raylib["get_shader_location"] = &GetShaderLocation;
            raylib["get_shader_location_attrib"] = &GetShaderLocationAttrib;
            raylib["set_shader_value"] = &SetShaderValue;
            raylib["set_shader_value_v"] = &SetShaderValueV;
            raylib["set_shader_value_matrix"] = &SetShaderValueMatrix;
            raylib["set_shader_value_texture"] = &SetShaderValueTexture;

            raylib["get_screen_to_world_ray"] = &GetScreenToWorldRay;
            raylib["get_screen_to_world_ray_ex"] = &GetScreenToWorldRayEx;
            raylib["get_world_to_screen"] = &GetWorldToScreen;
            raylib["get_world_to_screen_ex"] = &GetWorldToScreenEx;
            raylib["get_world_to_screen2d"] = &GetWorldToScreen2D;
            raylib["get_screen_to_world2d"] = &GetScreenToWorld2D;
            raylib["get_camera_matrix"] = &GetCameraMatrix;
            raylib["get_camera_matrix2d"] = &GetCameraMatrix2D;

            raylib["set_target_fps"] = &SetTargetFPS;
            raylib["get_fps"] = &GetFPS;
            raylib["get_frame_time"] = &GetFrameTime;
            raylib["get_time"] = &GetTime;

            raylib["swap_screen_buffer"] = &SwapScreenBuffer;
            raylib["poll_input_events"] = &PollInputEvents;
            raylib["wait_time"] = &WaitTime;

            raylib["set_random_seed"] = &SetRandomSeed;
            raylib["get_random_value"] = &GetRandomValue;
            raylib["load_random_sequence"] = &LoadRandomSequence;
            raylib["unload_random_sequence"] = &UnloadRandomSequence;

            raylib["take_screenshot"] = &TakeScreenshot;
            raylib["set_config_flags"] = &SetConfigFlags;
            raylib["open_url"] = &OpenURL;

            raylib["trace_log"] = &TraceLog;
            raylib["set_trace_log_level"] = &SetTraceLogLevel;
            raylib["mem_alloc"] = &MemAlloc;
            raylib["mem_realloc"] = &MemRealloc;
            raylib["mem_free"] = &MemFree;

            raylib["set_trace_log_callback"] = &SetTraceLogCallback;
            raylib["set_load_file_data_callback"] = &SetLoadFileDataCallback;
            raylib["set_save_file_data_callback"] = &SetSaveFileDataCallback;
            raylib["set_load_file_text_callback"] = &SetLoadFileTextCallback;
            raylib["set_save_file_text_callback"] = &SetSaveFileTextCallback;

            raylib["load_file_data"] = &LoadFileData;
            raylib["unload_file_data"] = &UnloadFileData;
            raylib["save_file_data"] = &SaveFileData;
            raylib["export_data_as_code"] = &ExportDataAsCode;
            raylib["load_file_text"] = &LoadFileText;
            raylib["unload_file_text"] = &UnloadFileText;
            raylib["save_file_text"] = &SaveFileText;

            raylib["file_exists"] = &FileExists;
            raylib["directory_exists"] = &DirectoryExists;
            raylib["is_file_extension"] = &IsFileExtension;
            raylib["get_file_length"] = &GetFileLength;
            raylib["get_file_extension"] = &GetFileExtension;
            raylib["get_file_name"] = &GetFileName;
            raylib["get_file_name_without_ext"] = &GetFileNameWithoutExt;
            raylib["get_directory_path"] = &GetDirectoryPath;
            raylib["get_prev_directory_path"] = &GetPrevDirectoryPath;
            raylib["get_working_directory"] = &GetWorkingDirectory;
            raylib["get_application_directory"] = &GetApplicationDirectory;
            raylib["make_directory"] = &MakeDirectory;
            raylib["change_directory"] = &ChangeDirectory;
            raylib["is_path_file"] = &IsPathFile;
            raylib["is_file_name_valid"] = &IsFileNameValid;
            raylib["load_directory_files"] = &LoadDirectoryFiles;
            raylib["load_directory_files_ex"] = &LoadDirectoryFilesEx;
            raylib["unload_directory_files"] = &UnloadDirectoryFiles;
            raylib["is_file_dropped"] = &IsFileDropped;
            raylib["load_dropped_files"] = &LoadDroppedFiles;
            raylib["unload_dropped_files"] = &UnloadDroppedFiles;
            raylib["get_file_mod_time"] = &GetFileModTime;

            raylib["compress_data"] = &CompressData;
            raylib["decompress_data"] = &DecompressData;
            raylib["encode_data_base64"] = &EncodeDataBase64;
            raylib["decode_data_base64"] = &DecodeDataBase64;
            raylib["compute_crc32"] = &ComputeCRC32;
            raylib["compute_md5"] = &ComputeMD5;
            raylib["compute_sha1"] = &ComputeSHA1;

            raylib["load_automation_event_list"] = &LoadAutomationEventList;
            raylib["unload_automation_event_list"] = &UnloadAutomationEventList;
            raylib["export_automation_event_list"] = &ExportAutomationEventList;
            raylib["set_automation_event_list"] = &SetAutomationEventList;
            raylib["set_automation_event_base_frame"] = &SetAutomationEventBaseFrame;
            raylib["start_automation_event_recording"] = &StartAutomationEventRecording;
            raylib["stop_automation_event_recording"] = &StopAutomationEventRecording;
            raylib["play_automation_event"] = &PlayAutomationEvent;

            raylib["is_key_pressed"] = &IsKeyPressed;
            raylib["is_key_down"] = &IsKeyDown;
            raylib["is_key_released"] = &IsKeyReleased;
            raylib["is_key_up"] = &IsKeyUp;
            raylib["get_key_pressed"] = &GetKeyPressed;
            raylib["get_char_pressed"] = &GetCharPressed;
            raylib["set_exit_key"] = &SetExitKey;
            raylib["is_key_pressed_repeat"] = &IsKeyPressedRepeat;

            raylib["is_gamepad_available"] = &IsGamepadAvailable;
            raylib["get_gamepad_name"] = &GetGamepadName;
            raylib["is_gamepad_button_pressed"] = &IsGamepadButtonPressed;
            raylib["is_gamepad_button_down"] = &IsGamepadButtonDown;
            raylib["is_gamepad_button_released"] = &IsGamepadButtonReleased;
            raylib["is_gamepad_button_up"] = &IsGamepadButtonUp;
            raylib["get_gamepad_button_pressed"] = &GetGamepadButtonPressed;
            raylib["get_gamepad_axis_count"] = &GetGamepadAxisCount;
            raylib["get_gamepad_axis_movement"] = &GetGamepadAxisMovement;
            raylib["set_gamepad_mappings"] = &SetGamepadMappings;
            raylib["set_gamepad_vibration"] = &SetGamepadVibration;

            raylib["is_mouse_button_pressed"] = &IsMouseButtonPressed;
            raylib["is_mouse_button_down"] = &IsMouseButtonDown;
            raylib["is_mouse_button_released"] = &IsMouseButtonReleased;
            raylib["is_mouse_button_up"] = &IsMouseButtonUp;
            raylib["get_mouse_x"] = &GetMouseX;
            raylib["get_mouse_y"] = &GetMouseY;
            raylib["get_mouse_position"] = &GetMousePosition;
            raylib["get_mouse_delta"] = &GetMouseDelta;
            raylib["set_mouse_position"] = &SetMousePosition;
            raylib["set_mouse_offset"] = &SetMouseOffset;
            raylib["set_mouse_scale"] = &SetMouseScale;
            raylib["get_mouse_wheel_move"] = &GetMouseWheelMove;
            raylib["get_mouse_wheel_move_v"] = &GetMouseWheelMoveV;
            raylib["set_mouse_cursor"] = &SetMouseCursor;

            raylib["get_touch_x"] = &GetTouchX;
            raylib["get_touch_y"] = &GetTouchY;
            raylib["get_touch_position"] = &GetTouchPosition;
            raylib["get_touch_point_id"] = &GetTouchPointId;
            raylib["get_touch_point_count"] = &GetTouchPointCount;

            raylib["set_gestures_enabled"] = &SetGesturesEnabled;
            raylib["is_gesture_detected"] = &IsGestureDetected;
            raylib["get_gesture_detected"] = &GetGestureDetected;
            raylib["get_gesture_hold_duration"] = &GetGestureHoldDuration;
            raylib["get_gesture_drag_vector"] = &GetGestureDragVector;
            raylib["get_gesture_drag_angle"] = &GetGestureDragAngle;
            raylib["get_gesture_pinch_vector"] = &GetGesturePinchVector;
            raylib["get_gesture_pinch_angle"] = &GetGesturePinchAngle;

            raylib["update_camera"] = &UpdateCamera;
            raylib["update_camera_pro"] = &UpdateCameraPro;

            raylib["set_shapes_texture"] = &SetShapesTexture;
            raylib["get_shapes_texture"] = &GetShapesTexture;
            raylib["get_shapes_texture_rectangle"] = &GetShapesTextureRectangle;

            raylib["draw_pixel"] = &DrawPixel;
            raylib["draw_pixel_v"] = &DrawPixelV;
            raylib["draw_line"] = &DrawLine;
            raylib["draw_line_v"] = &DrawLineV;
            raylib["draw_line_ex"] = &DrawLineEx;
            raylib["draw_line_strip"] = &DrawLineStrip;
            raylib["draw_line_bezier"] = &DrawLineBezier;
            raylib["draw_circle"] = &DrawCircle;
            raylib["draw_circle_sector"] = &DrawCircleSector;
            raylib["draw_circle_sector_lines"] = &DrawCircleSectorLines;
            raylib["draw_circle_gradient"] = &DrawCircleGradient;
            raylib["draw_circle_v"] = &DrawCircleV;

            return raylib.push();
        }
    }
} // namespace solray