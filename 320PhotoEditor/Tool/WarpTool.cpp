#include "WarpTool.h"

WarpTool::WarpTool(sf::Texture* up, sf::Texture* down, sf::Texture* over) : Tool(up, down, over)
{
	warpCompute = new ComputeShader("../assets/warp_compute.comp");
	pointsBuf = ComputeShader::genBuffer();
}

void WarpTool::init()
{
}

void WarpTool::start(Layer* layer)
{
	sf::Vector2u layerSize = layer->getImage()->getSize();
	sf::Vector2i section = {(int)(layerSize.x / size), (int)(layerSize.y / size)};

	controlPoints.clear();

	for (int x = 0; x < size; x++)
	{
		std::vector<sf::Vector2i> point;
		for (int y = 0; y < size; y++)
		{
			point.push_back({ section.x * x, section.y * y });
		}
	}

	layer->reload();
	layerCopy.loadFromImage(*layer->getImage());
	this->layer = layer;
}

void WarpTool::mousePressed(sf::Mouse::Button button)
{
	if (button == sf::Mouse::Button::Left)
	{
		selectedPoint = selectControlPoint(cursorPos);
		down = true;
	}
}

void WarpTool::mouseReleased(sf::Mouse::Button button)
{
	if (button == sf::Mouse::Button::Left)
	{
		down = false;
	}
}

void WarpTool::mouseMoved(sf::Vector2i pos)
{
	cursorPos = pos;

	if (!down || selectedPoint.x == -1)
	{
		return;
	}

	controlPoints.at(selectedPoint.x).at(selectedPoint.y) = layer->cursorToPixel(cursorPos);
	int* pointsBuffer = new int[size * size * 2];

	int index = 0;
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			pointsBuffer[index] = controlPoints.at(x).at(y).x;
			index++;
			pointsBuffer[index] = controlPoints.at(x).at(y).y;
			index++;
		}
	}
	warpCompute->use();
		
	ComputeShader::setBuffer(pointsBuf, sizeof(int) * size * size * 2, pointsBuffer);
	delete[] pointsBuffer;
	ComputeShader::bindBuffer(pointsBuf, 2);


	warpCompute->bindTexture(layerCopy.getNativeHandle(), 0);
	warpCompute->bindTexture(layer->getSprite()->getTexture()->getNativeHandle(), 1);
	warpCompute->setBool("copyMode", false);
	warpCompute->setInt("px", size);
	warpCompute->setInt("py", size);
	sf::Vector2u layerSize = layer->getImage()->getSize();

	warpCompute->compute(layerSize.x / 10.0f, layerSize.y / 10.0f, 1);
}

//TODO:
sf::Vector2i WarpTool::selectControlPoint(sf::Vector2i cursorPos)
{
	sf::Vector2i pos = layer->cursorToPixel(cursorPos);

	sf::Vector2i i = {0,0};
	for (i.y = 0; i.y < size; i.y++)
	{
		for (i.x = 0; i.x < size; i.x++)
		{
			double dx = controlPoints.at(i.x).at(i.y).x - pos.x;
			double dy = controlPoints.at(i.x).at(i.y).y - pos.y;
			float distance = std::sqrt(dx * dx + dy * dy);
			if (distance < 10)
			{
				return i;
			}
		}
	}

	return sf::Vector2i(-1, -1);
}

int* WarpTool::calculateTransformMatrx(std::vector<std::vector<sf::Vector2i>> controlPoints)
{
	return nullptr;
}
