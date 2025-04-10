#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;  // Canvas size (width,height)
uniform vec2 u_mouse;       // mouse position in screen pixels
uniform float u_time;       // Time in seconds since load


void main() 
{
	vec2 st = gl_FragCoord.xy/u_resolution;
	vec2 Mouse_st = u_mouse / u_resolution;

	
	// float a = smoothstep(0.0,1.0,st.y-0.6);


    gl_FragColor = vec4(0.0,0.0,st.y,1.0);
}