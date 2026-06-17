/***********************************************************************
 Bachelor of Software Engineering
 Media Design School
 Auckland
 New Zealand
 (c) 2026 Media Design School
 File Name   :   Mesh.cpp
 Description :   Defines the Mesh Class functions and properties
 Author      :   Angelo Joseph Arawiran Bohol
 Mail        :   angelo.bohol@mds.ac.nz
 ***********************************************************************/

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>
#include <cstddef>

#include "Mesh.h"

Mesh::Mesh() {
	// -- Render Properties -- //
	this->m_vao = 0;
	this->m_vbo = 0;
	this->m_drawCount = 0;
	this->m_drawType = 0;
	// -- //
}

Mesh::Mesh(const std::string& filePath) : Mesh() {
	tinyobj::ObjReaderConfig readerConfig;
	tinyobj::ObjReader reader;

	// Load the .obj file using ObjReader
	if (!reader.ParseFromFile(filePath, readerConfig)) {
		// An Error has Occurred
		if (!reader.Error().empty()) {
			std::cerr << "TinyObjReader: " << reader.Error();
		}

		exit(1);
	}

	// Warnings
	if (!reader.Warning().empty()) {
		// Log Warnings
		std::cout << "TinyObjReader: " << reader.Warning();
	}

	auto& attrib = reader.GetAttrib();
	auto& shapes = reader.GetShapes();

	// Loop through the Shapes of the Object
	for (size_t shapeIndex = 0; shapeIndex < shapes.size(); shapeIndex++) {
		// Loop through the Faces of the Shape
		size_t readIndexOffset = 0;
		for (size_t faceIndex = 0; faceIndex < shapes[shapeIndex].mesh.num_face_vertices.size(); faceIndex++) {
			size_t faceVertexCount = size_t(shapes[shapeIndex].mesh.num_face_vertices[faceIndex]);

			// Loop through the Vertices of the Face
			for (size_t vertexIndex = 0; vertexIndex < faceVertexCount; vertexIndex++) {
				// Concstruct the Vertex
				Vertex vertex{};
				tinyobj::index_t tinyObjVertex = shapes[shapeIndex].mesh.indices[readIndexOffset + vertexIndex];

				// Vertex Position
				vertex.position = {
					attrib.vertices[3 * size_t(tinyObjVertex.vertex_index) + 0],
					attrib.vertices[3 * size_t(tinyObjVertex.vertex_index) + 1],
					attrib.vertices[3 * size_t(tinyObjVertex.vertex_index) + 2]
				};

				// Ensure a Positive State (Negative States have no Texture-Coordinate Data)
				if (tinyObjVertex.texcoord_index >= 0) {
					// Vertex Texture Coordinates
					vertex.texCoord = {
						attrib.texcoords[2 * size_t(tinyObjVertex.texcoord_index) + 0],
						attrib.texcoords[2 * size_t(tinyObjVertex.texcoord_index) + 1]
					};
				}

				// Vertex Normal
				if (tinyObjVertex.normal_index >= 0) {
					vertex.normal = {
						attrib.normals[3 * size_t(tinyObjVertex.normal_index) + 0],
						attrib.normals[3 * size_t(tinyObjVertex.normal_index) + 1],
						attrib.normals[3 * size_t(tinyObjVertex.normal_index) + 2]
					};
				}

				this->m_vertices.push_back(vertex);
			}

			readIndexOffset += faceVertexCount;
		}
	}

	// Store for Use in Render
	this->m_drawType = GL_TRIANGLES;
	this->m_drawCount = static_cast<GLuint>(this->m_vertices.size());

	// Generate the VAO
	glGenVertexArrays(1, &this->m_vao);
	glBindVertexArray(this->m_vao);

	// Generate the VBO 
	glGenBuffers(1, &this->m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->m_vbo);
	glBufferData(GL_ARRAY_BUFFER, this->m_vertices.size() * sizeof(Vertex), this->m_vertices.data(), GL_STATIC_DRAW);
	
	// Set the Vertex Attribute information (how the Vertex Data is Interpreted)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(offsetof(Vertex, Vertex::position)));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(offsetof(Vertex, Vertex::texCoord)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(offsetof(Vertex, Vertex::normal)));
	glEnableVertexAttribArray(2);
	
	// Unbind the VAO
	glBindVertexArray(0);
}

Mesh::~Mesh() {
}

void Mesh::update(float deltaTime) {
}

void Mesh::draw() {
	glBindVertexArray(this->m_vao);
	glDrawArrays(this->m_drawType, 0, this->m_drawCount);
	glBindVertexArray(0);
}
