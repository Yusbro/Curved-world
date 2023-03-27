#version 330

in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec2 vertexNormal;
in vec4 vertexColor;

uniform mat4 mvp;
uniform vec3 camera = vec3(0.0,1.0,0.0);
uniform float offset=0;

out vec2 fragTexCoord;
out vec4 fragColor;


mat2 rotate(float angle){
	return mat2(cos(angle), -sin(angle), sin(angle), cos(angle));
}



void main(){
	fragTexCoord = vertexTexCoord;
	fragColor = vertexColor;
	
	vec4 world_pos = mvp * vec4(vertexPosition, 1.0);


	vec3 diff = world_pos.xyz - camera;
	float dist = length(diff);
	
	vec2 off = world_pos.xy;
	off = (rotate(dist) * off);
	
	float val = (dist*dist)*0.01;
	
	world_pos.y -= val;
	world_pos.x -= val*0.5;
	gl_Position = world_pos;
}
