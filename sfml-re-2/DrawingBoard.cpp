#include "DrawingBoard.h"
#include <cstdlib>


DrawingBoard::DrawingBoard(float width, float height) :
	m_width(width), m_height(height)
{
}


DrawingBoard::~DrawingBoard()
{
}

void DrawingBoard::newLine() {
	this->vertices.emplace_back(sf::VertexArray(sf::PrimitiveType::TriangleFan));
}

void DrawingBoard::append(sf::Vector2f v2)
{
	if (this->vertices.empty()) this->vertices.emplace_back();
	this->vertices.back().append(sf::Vertex(v2, sf::Color(std::rand() % 256, std::rand() % 256, std::rand() % 256, 200)));
}

void DrawingBoard::resize(float new_width, float new_height)
{
	float w_ratio = new_width / this->m_width;
	float h_ratio = new_height / this->m_height;
	for (auto& vertexArr : this->vertices) {
		for (size_t i = 0; i < vertexArr.getVertexCount(); ++i) {
			sf::Vector2f pos = vertexArr[i].position;
			vertexArr[i].position = { pos.x * w_ratio, pos.y * h_ratio };
		}
	}
	this->m_width = new_width;
	this->m_height = new_height;
}

void DrawingBoard::clear()
{
	this->vertices.clear();
}

void DrawingBoard::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (auto& vertexArr : this->vertices) {
		target.draw(vertexArr);
	}
}
