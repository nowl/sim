GLchar vertexsource[] = "\n\
#version 330\n                                                          \
in  vec2 in_Position;\n                                                 \
in  vec3 inFG_Color;\n                                                  \
in  vec3 inBG_Color;\n                                                  \
in  float in_Char;\n                                                    \
in  vec2 in_UVPosition;\n                                               \
\n                                                                      \
uniform mat4 MVP;\n                                                     \
\n                                                                      \
#define TEXTURE_WIDTH 304\n                                             \
#define TEXTURE_HEIGHT 144\n                                            \
\n                                                                      \
vec2 find_uv() {\n                                                      \
    int char_x = int(in_Char) % 32;\n                                   \
    int char_y = int(in_Char) / 32;\n                                   \
\n                                                                      \
    float x_pos = 8 + char_x*9 + in_UVPosition.x;\n                     \
    float y_pos = TEXTURE_HEIGHT - (8 + (7-char_y)*16 + in_UVPosition.y);\n \
    return vec2(x_pos/TEXTURE_WIDTH, y_pos/TEXTURE_HEIGHT);\n           \
}\n                                                                     \
\n                                                                      \
out vec3 fg_Color;\n                                                    \
out vec3 bg_Color;\n                                                    \
out vec2 UV;\n                                                          \
void main(void) {\n                                                     \
    gl_Position = MVP * vec4(in_Position.x, in_Position.y, 0.0, 1.0);\n \
 \n                                                                     \
    fg_Color = inFG_Color;\n                                            \
    bg_Color = inBG_Color;\n                                            \
    UV = find_uv();\n                                                   \
}\n                                                                     \
\n                                                                      \
";

GLchar fragmentsource[] = "\n\
#version 330\n                                                          \
precision highp float;\n                                                \
\n                                                                      \
uniform  sampler2D in_Texture;\n                                        \
\n                                                                     \
in  vec3 fg_Color;\n                                                    \
in  vec3 bg_Color;\n                                                    \
in  vec2 UV;\n                                                          \
//out vec4 gl_FragColor;\n                                                \
\n                                                                     \
void main(void) {\n                                                     \
    vec4 texel = texture(in_Texture, UV);\n                             \
    \n                                                                  \
    if(texel.r != 0)\n                                                  \
        gl_FragColor = vec4(fg_Color, 1);\n                             \
    else\n                                                              \
        gl_FragColor = vec4(bg_Color, 1);\n                             \
}\n                                                                     \
";
