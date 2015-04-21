static const char *vertex_shader_src =
	"#version 330\n"
	"layout(location = 0) in  vec2 in_Center;\n"
	"layout(location = 1) in  vec3 inFG_Color;\n"
	"layout(location = 2) in  vec3 inBG_Color;\n"
	"layout(location = 3) in  float in_Char;\n"
	"layout(location = 4) in  vec2 in_Position;\n"

	"uniform mat4 MVP;\n"
	
	"#define TEXTURE_WIDTH 304\n"
	"#define TEXTURE_HEIGHT 144\n"

	"vec2 find_uv() {\n"
	"    int char_x = int(in_Char) % 32;\n"
	"    int char_y = int(in_Char) / 32;\n"
	"    float x_pos = 8 + char_x*9 + in_Position.x;\n"
	"    float y_pos = TEXTURE_HEIGHT - (8 + (7-char_y)*16 + in_Position.y);\n"
	"    return vec2(x_pos/TEXTURE_WIDTH, y_pos/TEXTURE_HEIGHT);\n"
	"}\n"

	"out vec3 fg_Color;\n"
	"out vec3 bg_Color;\n"
	"out vec2 UV;\n"

	"void main(void) {\n"
	"    gl_Position = MVP * vec4(in_Center.x+in_Position.x-4.5, in_Center.y+in_Position.y-8, 0.0, 1.0);\n"
	
	"    fg_Color = inFG_Color;\n"
	"    bg_Color = inBG_Color;\n"
	"    UV = find_uv();\n"
	"}\n";


const char *fragment_shader_src =
	"#version 330\n"
	"precision highp float;\n"

	"uniform  sampler2D in_Texture;\n"

	"in  vec3 fg_Color;\n"
	"in  vec3 bg_Color;\n"
	"in  vec2 UV;\n"

	"out vec4 fragcolor;\n"

	"void main(void) {\n"
	"    vec4 texel = texture(in_Texture, UV);\n"
	"    fragcolor = texel;\n"
	"    //if(texel.a != 0)\n"
	"    //    fragcolor = vec4(fg_Color, 1);\n"
	"    //else\n"
	"    //    fragcolor = vec4(bg_Color, 0);\n"
	"}\n";
