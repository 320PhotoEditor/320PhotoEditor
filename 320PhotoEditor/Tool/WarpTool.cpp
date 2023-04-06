#include "WarpTool.h"

WarpTool::WarpTool(sf::Texture* up, sf::Texture* down, sf::Texture* over) : Tool(up, down, over)
{
	warpCompute = new ComputeShader("../assets/warp_compute.comp");
	pointsBuf = ComputeShader::genBuffer();
}

void WarpTool::init()
{
	sf::Texture* upTexture = AssetManager::getInstance().getTexture("../assets/button_up.png");
	sf::Texture* downTexture = AssetManager::getInstance().getTexture("../assets/button_down.png");
	sf::Texture* overTexture = AssetManager::getInstance().getTexture("../assets/button_over.png");
	sf::Texture* incrupTexture = AssetManager::getInstance().getTexture("../assets/incr_button_up.png");
	sf::Texture* incrdownTexture = AssetManager::getInstance().getTexture("../assets/incr_button_down.png");
	sf::Texture* incroverTexture = AssetManager::getInstance().getTexture("../assets/incr_button_over.png");
	sf::Texture* decrupTexture = AssetManager::getInstance().getTexture("../assets/decr_button_up.png");
	sf::Texture* decrdownTexture = AssetManager::getInstance().getTexture("../assets/decr_button_down.png");
	sf::Texture* decroverTexture = AssetManager::getInstance().getTexture("../assets/decr_button_over.png");

	increaseControlPointsX = new ButtonElement(incrupTexture, incrdownTexture, incroverTexture);
	increaseControlPointsX->setUpdateFunction([this](GUIElement* element, int status) { this->buttonPressed(element, status); });
	container->addElement(increaseControlPointsX);
	increaseControlPointsX->setSize({ .25, .25 });
	increaseControlPointsX->setPosition({ 0.25, 0 });

	decreaseControlPointsX = new ButtonElement(decrupTexture, decrdownTexture, decroverTexture);
	decreaseControlPointsX->setUpdateFunction([this](GUIElement* element, int status) { this->buttonPressed(element, status); });
	container->addElement(decreaseControlPointsX);
	decreaseControlPointsX->setSize({ .25, .25 });
	decreaseControlPointsX->setPosition({ 0, 0 });

	increaseControlPointsY = new ButtonElement(incrupTexture, incrdownTexture, incroverTexture);
	increaseControlPointsY->setUpdateFunction([this](GUIElement* element, int status) { this->buttonPressed(element, status); });
	container->addElement(increaseControlPointsY);
	increaseControlPointsY->setSize({ .25, .25 });
	increaseControlPointsY->setPosition({ 0.25, 0.25 });

	decreaseControlPointsY = new ButtonElement(decrupTexture, decrdownTexture, decroverTexture);
	decreaseControlPointsY->setUpdateFunction([this](GUIElement* element, int status) { this->buttonPressed(element, status); });
	container->addElement(decreaseControlPointsY);
	decreaseControlPointsY->setSize({ .25, .25 });
	decreaseControlPointsY->setPosition({ 0, 0.25 });

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
	sf::Vector2i section = {(int)(layerSize.x / defaultSize), (int)(layerSize.y / defaultSize)};

	controlPoints.clear();

	controlPoints.resize(defaultSize, std::vector<sf::Vector2i>(defaultSize));
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

	if (!down || selectedPoint.x == -1)
	{
		return;
	}

	controlPoints.at(selectedPoint.y).at(selectedPoint.x) = layer->cursorToPixel(cursorPos);
	int* pointsBuffer = new int[controlPoints.size() * controlPoints[0].size() * 2];

	int index = 0;
	for (auto& y : controlPoints)
	{
		for (auto& x : y)
		{
			pointsBuffer[index] = x.x;
			index++;
			pointsBuffer[index] = x.y;
			index++;
		}
	}
	warpCompute->use();
		
	ComputeShader::setBuffer(pointsBuf, sizeof(int) * controlPoints.size() * controlPoints[0].size() * 2, pointsBuffer);
	delete[] pointsBuffer;
	ComputeShader::bindBuffer(pointsBuf, 2);


	warpCompute->bindTexture(layerCopy.getNativeHandle(), 0);
	warpCompute->bindTexture(layer->getSprite()->getTexture()->getNativeHandle(), 1);
	warpCompute->setBool("copyMode", false);
	warpCompute->setInt("px", controlPoints[0].size());
	warpCompute->setInt("py", controlPoints.size());
	sf::Vector2u layerSize = layer->getImage()->getSize();

	warpCompute->compute(layerSize.x / 10.0f, layerSize.y / 10.0f, 1);
}


sf::Vector2i WarpTool::selectControlPoint(sf::Vector2i cursorPos)
{
	sf::Vector2i pos = layer->cursorToPixel(cursorPos);

	sf::Vector2i i = {0,0};

	for (auto& y : controlPoints)
	{
		for (auto& x : y)
		{
			double dx = x.x - pos.x;
			double dy = x.y - pos.y;
			float distance = std::sqrt(dx * dx + dy * dy);
			if (distance < 10)
			{
				return i;
			}
			i.x++;
		}
		i.x = 0;
		i.y++;
	}

	return sf::Vector2i(-1, -1);
}

int* WarpTool::calculateTransformMatrx(std::vector<std::vector<sf::Vector2i>> controlPoints)
{
	return nullptr;
}

void WarpTool::initControlPoints()
{
	sf::Vector2u layerSize = layer->getImage()->getSize();

	int ix = 0, iy = 0;
	for (auto& y : controlPoints)
	{
		for (auto& x : y)
		{
			x = { (int)(layerSize.x / (y.size()-1) * ix), (int)(layerSize.y / (controlPoints.size()-1) * iy) };
			ix++;
		}
		ix = 0;
		iy++;
	}
}

void WarpTool::buttonPressed(GUIElement* button, int status)
{
	if (status != ButtonElement::ButtonState::DOWN)
	{
		return;
	}

	if (button == increaseControlPointsX)
	{
		for (auto& row : controlPoints)
		{
			row.resize(row.size() + 1);
		}
		initControlPoints();
	}
	else if(button == decreaseControlPointsX)
	{
		for (auto& row : controlPoints)
		{
			row.resize(row.size() - 1);
		}
		initControlPoints();
	}
	else if(button == increaseControlPointsY)
	{
		controlPoints.resize(controlPoints.size() + 1, std::vector<sf::Vector2i>(controlPoints[0].size()));
		initControlPoints();
	}
	else if(button == decreaseControlPointsY)
	{
		controlPoints.resize(controlPoints.size() - 1, std::vector<sf::Vector2i>(controlPoints[0].size()));
		initControlPoints();
	}
	else if(button == startWarp)
	{

	}

	for (auto& y : controlPoints)
	{
		for (auto& x : y)
		{
			std::cout << x.x << ":" << x.y << " , ";
		}
		std::cout << std::endl;
	}
	std::cout << controlPoints[0].size() << " : " << controlPoints.size() << std::endl;
	std::cout << std::endl;
}
