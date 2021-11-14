#pragma once
#ifndef H_SHADER
#define H_SHADER

#include <string>
#include <unordered_map>

struct vec4f
{
	float v0;
	float v1;
	float v2;
	float v3;
};


class Shader
{
private:
	unsigned int m_rendererID{ 0 };
	std::string m_filePath{ "" };
	std::unordered_map<std::string, int> m_uniformLocationCache;

	unsigned int
	createShader(const std::string &vertex_shader, const std::string &fragment_shader);

	unsigned int
	compileShader(unsigned int type, const std::string &source);

	int GetUniformLocation(const std::string &name);

public:
	Shader(const std::string &filepath);
	~Shader();


	void bind() const;
	void unbind() const;

	void setUniform4f(const std::string &name, vec4f floats);
	void setUniform1i(const std::string& name, int value);
};

#endif // H_SHADER