uniform mat4 world;
uniform mat4 view;
uniform mat4 proj;

struct Wave{
	vec3 src;
	float amp;
	float wlen;
	float time;
};

uniform Wave wave;

in vec3 vertex;

void main(void){
	
	vec4 pos_w = world * vec4(vertex, 1);
	vec3 pos = vec3(pos_w);

	vec3 wave_dir = normalize(pos - wave.src);
	vec3 wave_pos = wave.src + wave_dir * wave.time;

	vec3 delta = pos - wave_pos;

	float len_delta = length(delta);
	if (len_delta < wave.wlen){
		pos += normalize(wave_dir) * (len_delta * -wave.amp/wave.wlen + wave.amp);
	}
	
	gl_Position = proj * view * vec4(pos, 1);
}
