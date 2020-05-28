#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <string>

#include "defines.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "GLcall.h"

struct OriginalSize
{
	float width, height;
};

class Sprite	
{
private:
	float m_xPos;
	float m_yPos;
	float m_SpriteWidth;
	float m_SpriteHeight;
	unsigned int m_VAO;
	VertexBuffer* m_VB;
	VertexBufferLayout m_Layout;
	std::string m_TexturePath;
	float m_Rotation;
	glm::vec4 m_colorElement;
	glm::vec4 m_Color;
	float m_Size;
	OriginalSize m_originalSize;
	
public:
	VertexArray m_VA;		
	IndexBuffer *m_IB;		
	Shader *m_Shader;		
	Texture *m_Texture;

public:
	Sprite(float xPos, float yPos, float m_SpriteWidth, float SpriteHeight, const std::string TexturePath, glm::vec4 color, const std::string shaderPath);
	~Sprite();

	void MoveSpriteBy(float xPos, float yPos);
	void MoveSprite(float xPos, float yPos);
	//angle in degrees
	void RotateSprite(float angle);
	void SetColorElement(glm::vec4 color);
	inline float GetXPos() const { return m_xPos; }
	inline float GetYPos() const { return m_yPos; }
	inline float GetWidth() const { return m_SpriteWidth; }
	inline float GetHeight() const { return m_SpriteHeight; }
	inline glm::vec3 GetPosition() const { return glm::vec3(m_xPos, m_yPos, 1.0f); }
	inline float GetRotation() const { return m_Rotation; }
	inline glm::vec4 GetColorElement() const { return m_colorElement; }
	OriginalSize GetOriginalSize() { return m_originalSize; }
	void SetColor(glm::vec4 color) { m_Color = color; }
	void SetSize(glm::vec2 size) { m_SpriteWidth = size.x; m_SpriteHeight = size.y; }
	void SetPivot(unsigned int type);
	void SetRotation(float rotation) { m_Rotation = rotation; }

	void OnRender();
	

};
