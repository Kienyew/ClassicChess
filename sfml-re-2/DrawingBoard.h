#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
class DrawingBoard : public sf::Drawable
{
public:
	DrawingBoard(float width, float height);
	~DrawingBoard();
	void newLine();
	void append(sf::Vector2f v2);
	void resize(float new_width, float new_height);
	void clear();
	
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

private:
	std::vector<sf::VertexArray> vertices;
	float m_width;
	float m_height;
};

