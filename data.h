static const char *vertex_shader_src =
	"#version 330\n"
	"layout(location = 0) in  vec2 in_Center;\n"
	"layout(location = 1) in  vec3 inFG_Color;\n"
	"layout(location = 2) in  vec3 inBG_Color;\n"
	"layout(location = 3) in  float in_SpriteX;\n"
	"layout(location = 4) in  float in_SpriteY;\n"
	"layout(location = 5) in  vec2 in_Position;\n"

	"uniform mat4 MVP;\n"
	"uniform int texture_width;\n"
	"uniform int texture_height;\n"

	"vec2 find_uv() {\n"
	"    float x_pos = in_SpriteX + in_Position.x;\n"
	"    float y_pos = texture_height - in_SpriteY + in_Position.y - 1;\n"
	"    return vec2(x_pos/texture_width, y_pos/texture_height);\n"
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
