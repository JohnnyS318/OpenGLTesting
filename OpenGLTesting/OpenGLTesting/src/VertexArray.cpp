﻿#include "VertexArray.h"
#include "Renderer.h"

#include "VertexBufferLayout.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &_rendererID));
	GLCall(glBindVertexArray(_rendererID));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &_rendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	vb.Bind();

    const std::vector<VertexBufferElement> elements = layout.GetElements();

	unsigned int offset = 0;
	
	for (unsigned int i = 0;i < elements.size(); i++)
	{
		const VertexBufferElement element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		// define the layout of the vertex attribute;
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
		offset += VertexBufferElement::GetSizeOfType(element.type);
	}
	
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(_rendererID));
}


void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}

