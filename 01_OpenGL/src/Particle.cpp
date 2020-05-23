#include "Particle.h"

Particle::Particle(float xPos, float yPos, float width, float height, glm::vec4 startingColor, glm::vec4 dyingColor, float life, std::string shader, bool allowRotation, bool allowScale)
	: m_xPos(xPos), m_yPos(yPos), m_Width(width), m_Height(height), m_startingColor(startingColor), m_dyingColor(dyingColor), m_life(life), m_currLife(life), m_Color(startingColor), m_Shader(shader),
		m_AllowRotation(allowRotation), m_AllowScale(allowScale)
{
	m_Sprite = new Sprite(m_xPos, m_yPos, m_Width, m_Height, m_Color, shader);
	m_Sprite->SetRotation(Random::Float() * 360);
	m_Velocity = glm::vec2(Random::Float() * 100 - 50, Random::Float() * 100 - 50);
}

Particle::Particle(float xPos, float yPos, float width, float height, glm::vec4 startingColor, glm::vec4 dyingColor, float life)
{
	Particle(xPos, yPos, width, height, startingColor, dyingColor, life, "src/res/shaders/Sphere.shader", 1, 1);
}

Particle::Particle(float xPos, float yPos, float width, float height, glm::vec4 startingColor, glm::vec4 dyingColor)
{
	Particle(xPos, yPos, width, height, startingColor, dyingColor, 100.0f, "src/res/shaders/Sphere.shader", 1, 1);
}

Particle::~Particle()
{
	//delete m_Sprite;
}

void Particle::OnUpdate()
{
	float _life = m_currLife / m_life;
	m_Color = glm::lerp(m_dyingColor, m_startingColor, _life);
	m_Color.a = m_Color.a * _life;
	m_currLife -= 1;
	float scaleSpeed = (m_life - m_currLife);
	//"bug" -> but it seems pretty fun, lol	
	//m_Sprite->SetSize({ m_Sprite->GetWidth() - scaleSpeed, m_Sprite->GetHeight() - scaleSpeed });
	if(m_AllowRotation)
		m_Sprite->RotateSprite(m_Sprite->GetRotation() + (m_RotationSpeed * m_Color.a));
	if(m_AllowScale)
		m_Sprite->SetSize({ m_Sprite->GetOriginalSize().width * m_Color.a + m_minimalSize, m_Sprite->GetOriginalSize().height * m_Color.a + m_minimalSize });
	m_Sprite->MoveSpriteBy(m_Velocity.x * m_Speed / 100, m_Velocity.y * m_Speed / 100);
	m_Sprite->SetColor(m_Color);
	
}