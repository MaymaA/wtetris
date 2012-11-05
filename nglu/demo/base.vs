uniform mat4 world;
uniform mat4 view;
uniform mat4 proj;

in vec3 vertex;

void main(void){
	
	vec4 pos = vec4(vertex, 1);	

	gl_Position = proj * view * world * pos;
}
