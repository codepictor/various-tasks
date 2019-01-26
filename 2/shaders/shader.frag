layout(origin_upper_left) in vec4 gl_FragCoord;

uniform vec2 explosionPoint;
uniform float currTime;
uniform float waveSpeed;


float GetWaveFunc(float lengthFromExplosion, float wavePath)
{
	return exp(-(lengthFromExplosion - wavePath) * (lengthFromExplosion - wavePath) * 0.002f);
}


vec4 GetColor(vec2 coords)
{
	float step = 50.0f;
	bool hor = mod(coords.x, 2.0f * step) > step;
	bool ver = mod(coords.y, 2.0f * step) > step;

	if (hor ^^ ver)
	{
		return vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}
	else
	{
		return vec4(1.0f, 1.0f, 1.0f, 1.0f);
	}
}


float GetLength(vec2 coords)
{
	return sqrt(coords.x * coords.x + coords.y * coords.y);
}



void main()
{
	float offsetValue = GetWaveFunc(GetLength(gl_FragCoord.xy - explosionPoint), waveSpeed * currTime);
	vec2 offsetDir = gl_FragCoord.xy - explosionPoint;
	offsetDir = offsetDir * (1.0f / GetLength(offsetDir));
	gl_FragColor = GetColor(gl_FragCoord.xy + offsetDir * offsetValue);
	
	//gl_FragColor.rgba = vec4(vec3(offsetValue), 1.0f);
}


