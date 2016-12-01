#include "Mason/SREDebugDraw.h"
#include "SRE/Shader.hpp"

SREDebugDraw::SREDebugDraw() {

}

void SREDebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
	SRE::Shader::getUnlit()->setDepthTest(false);
	SRE::Debug::setColor(glm::vec4(color.r, color.g, color.b, color.a));
	for (int i = 0; i < vertexCount; i++) {
		auto p1 = vertices[i];
		auto p2 = vertices[(i + 1) % vertexCount];
		SRE::Debug::drawLine(glm::vec3(p1.x, p1.y, 0), glm::vec3(p2.x, p2.y, 0));
	}
	SRE::Shader::getUnlit()->setDepthTest(true);
}
void SREDebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
	SRE::Shader::getUnlit()->setDepthTest(false);
	SRE::Debug::setColor(glm::vec4(color.r, color.g, color.b, color.a));
	for (int i = 0; i < vertexCount; i++) {
		auto p1 = vertices[i];
		auto p2 = vertices[(i + 1) % vertexCount];
		SRE::Debug::drawLine(glm::vec3(p1.x, p1.y, 0), glm::vec3(p2.x, p2.y, 0));
	}
	SRE::Shader::getUnlit()->setDepthTest(true);
}
void SREDebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) {
	SRE::Debug::setColor(glm::vec4(color.r, color.g, color.b, color.a));

	int segments = 180;
	for (int i = 0; i < segments; i++) {
		float angle1 = i * ((float)360 / (float)segments);
		float angle2 = (i + 1) * ((float)360 / (float)segments);
		auto p1 = glm::vec3(center.x + cos(angle1)*radius, center.y + sin(angle1)*radius, 0);
		auto p2 = glm::vec3(center.x + cos(angle2)*radius, center.y + sin(angle2)*radius, 0);
		SRE::Debug::drawLine(p1, p2);
	}
}
void SREDebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) {
	
	SRE::Debug::setColor(glm::vec4(color.r, color.g, color.b, color.a));

	int segments = radius*M_PI;
	for (int i = 0; i < segments; i++) {
		float angle1 = i * (2 * M_PI / (float)segments);
		float angle2 = (i + 1) * (2 * M_PI / (float)segments);
		auto p1 = glm::vec3(center.x + cos(angle1)*radius, center.y + sin(angle1)*radius, 0);
		auto p2 = glm::vec3(center.x + cos(angle2)*radius, center.y + sin(angle2)*radius, 0);
		SRE::Debug::drawLine(p1, p2);
	}
	SRE::Debug::drawLine(glm::vec3(center.x, center.y, 0), glm::vec3(center.x + axis.x * radius, center.y + axis.y * radius, 0));
}
void SREDebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {
	SRE::Debug::setColor(glm::vec4(color.r, color.g, color.b, color.a));
	SRE::Debug::drawLine(glm::vec3(p1.x, p1.y, 0), glm::vec3(p2.x, p2.y, 0));
}
void SREDebugDraw::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color) {

}
void SREDebugDraw::DrawTransform(const b2Transform& xf) {
}