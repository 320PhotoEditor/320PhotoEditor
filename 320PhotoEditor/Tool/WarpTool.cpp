#include "WarpTool.h"

WarpTool::WarpTool(sf::Texture* up, sf::Texture* down, sf::Texture* over) : Tool(up, down, over)
{
	warpCompute = new ComputeShader("../assets/warp_compute.comp");
	pointsBuf = ComputeShader::genBuffer();
}

void WarpTool::init()
{
	/*
	Matrix3x3 transform;
	calculateTransformMatrx({ 1,1 }, { 2,1 }, { 2,2 }, { 1,2 }, { 2,2 }, { 3,2 }, { 3,3 }, { 2,3 }, transform);

	float x = 1.5, y = 1.5;
	x = transform[0][0] * x + transform[0][1] * y + transform[0][2];
	y = transform[1][0] * x + transform[1][1] * y + transform[1][2];

	std::cout << "x: " << x << " y: " << y << std::endl;

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			std::cout << transform[i][j] << " ";
		}
		std::cout << std::endl;
	}*/

	sf::Texture* upTexture = AssetManager::getInstance().getTexture("../assets/button_up.png");
	sf::Texture* downTexture = AssetManager::getInstance().getTexture("../assets/button_down.png");
	sf::Texture* overTexture = AssetManager::getInstance().getTexture("../assets/button_over.png");

	startWarp = new ButtonElement(upTexture, downTexture, overTexture);
	startWarp->setUpdateFunction([this](GUIElement* element, int status) { this->buttonPressed(element, status); });
	container->addElement(startWarp);
	startWarp->setSize({ .25, .25 });
	startWarp->setPosition({ 0.5, 0.125 });
}

void WarpTool::start(Layer* layer)
{
	this->layer = layer;
	sf::Vector2u layerSize = layer->getImage()->getSize();
	sf::Vector2i section = {(int)(layerSize.x / 4), (int)(layerSize.y / 4)};

	initControlPoints();

	layer->reload();
	layerCopy.loadFromImage(*layer->getImage());
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

	if (!down || selectedPoint == -1)
	{
		return;
	}

	controlPoints[selectedPoint] = layer->cursorToPixel(cursorPos);
	int pointsBuffer[4 * 2];

	int index = 0;
	for (auto& c : controlPoints)
	{
		pointsBuffer[index] = c.x;
		index++;
		pointsBuffer[index] = c.y;
		index++;
	}
	warpCompute->use();
		
	ComputeShader::setBuffer(pointsBuf, sizeof(int) * 4 * 2, pointsBuffer);
	ComputeShader::bindBuffer(pointsBuf, 2);


	warpCompute->bindTexture(layerCopy.getNativeHandle(), 0);
	warpCompute->bindTexture(layer->getSprite()->getTexture()->getNativeHandle(), 1);
	warpCompute->setBool("copyMode", false);
	sf::Vector2u layerSize = layer->getImage()->getSize();

	warpCompute->compute(layerSize.x / 10.0f, layerSize.y / 10.0f, 1);
}


int WarpTool::selectControlPoint(sf::Vector2i cursorPos)
{
	sf::Vector2i pos = layer->cursorToPixel(cursorPos);

	for (int i = 0; i < 4; i++)
	{
		double dx = controlPoints[i].x - pos.x;
		double dy = controlPoints[i].y - pos.y;
		float distance = std::sqrt(dx * dx + dy * dy);
		if (distance < 10)
		{
			return i;
		}
	}

	return -1;
}

void WarpTool::calculateTransformMatrx(sf::Vector2i originalControlPoints[4], sf::Vector2i controlPoints[4], Matrix3x3& transform)
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			for (int k = 0; k < 3; ++k)
			{
				transform[i][j] = 0;
			}
		}
	}
}

void WarpTool::initControlPoints()
{
	sf::Vector2u layerSize = layer->getImage()->getSize();

	controlPoints[0] = { 0, 0 };
	controlPoints[1] = { (int)layerSize.x, 0 };
	controlPoints[2] = { 0, (int)layerSize.y };
	controlPoints[3] = { (int)layerSize.x, (int)layerSize.y };
}

void WarpTool::buttonPressed(GUIElement* button, int status)
{
	if (status != ButtonElement::ButtonState::DOWN)
	{
		return;
	}
	
	if(button == startWarp)
	{

	}
}
