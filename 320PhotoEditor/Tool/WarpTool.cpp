#include "WarpTool.h"

WarpTool::WarpTool(sf::Texture* up, sf::Texture* down, sf::Texture* over) : Tool(up, down, over)
{
	warpCompute = new ComputeShader("../assets/warp_compute.comp");
	pointsBuf = ComputeShader::genBuffer();
}

void WarpTool::init()
{
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
	}

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

void WarpTool::calculateTransformMatrx(sf::Vector2i oa, sf::Vector2i ob, sf::Vector2i oc, sf::Vector2i od,
									   sf::Vector2i na, sf::Vector2i nb, sf::Vector2i nc, sf::Vector2i nd,
									   Matrix3x3& transform)
{
	Matrix3x3 T1 = {
		1,0,0,
		0,1,0,
		0,0,1
	};

	Matrix3x3 T2 = {
		1,0,0,
		0,1,0,
		0,0,1
	};

	//compute affine transform
	T1[0][0] = oa.x; T1[0][1] = ob.x; T1[0][2] = oc.x; T1[1][0] = oa.y; T1[1][1] = ob.y; T1[1][2] = oc.y;
	T2[0][0] = na.x; T2[0][1] = nb.x; T2[0][2] = nc.x; T2[1][0] = na.y; T2[1][1] = nb.y; T2[1][2] = nc.y;

	Matrix3x3 T;

	//matrix multiply
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			T[i][j] = 0.0f;
			for (int k = 0; k < 3; ++k)
			{
				T[i][j] += T1[i][k] * T2[k][j];
			}
		}
	}

	Matrix3x3 Tinverse;

	float det = 0.0f;
	det += T[0][0] * T[1][1] * T[2][2];
	det += T[0][1] * T[1][2] * T[2][0];
	det += T[0][2] * T[1][0] * T[2][1];
	det -= T[0][2] * T[1][1] * T[2][0];
	det -= T[0][0] * T[1][2] * T[2][1];
	det -= T[0][1] * T[1][0] * T[2][2];

	Tinverse[0][0] = (T[1][1] * T[2][2] - T[1][2] * T[2][1]) / det;
	Tinverse[0][1] = (T[0][2] * T[2][1] - T[0][1] * T[2][2]) / det;
	Tinverse[0][2] = (T[0][1] * T[1][2] - T[0][2] * T[1][1]) / det;
	Tinverse[1][0] = (T[1][2] * T[2][0] - T[1][0] * T[2][2]) / det;
	Tinverse[1][1] = (T[0][0] * T[2][2] - T[0][2] * T[2][0]) / det;
	Tinverse[1][2] = (T[1][0] * T[0][2] - T[0][0] * T[1][2]) / det;
	Tinverse[2][0] = (T[1][0] * T[2][1] - T[1][1] * T[2][0]) / det;
	Tinverse[2][1] = (T[0][1] * T[2][0] - T[0][0] * T[2][1]) / det;
	Tinverse[2][2] = (T[0][0] * T[1][1] - T[0][1] * T[1][0]) / det;

	Matrix3x3 T3 = {
		1,0,0,
		0,1,0,
		0,0,1
	};
	Matrix3x3 T4 = {
		1,0,0,
		0,1,0,
		0,0,1
	};
	T3[0][0] = na.x - oa.x;
	T3[0][1] = nb.x - ob.x;
	T3[0][2] = nc.x - oc.x;
	T3[1][0] = na.y - oa.y;
	T3[1][1] = nb.y - ob.y;
	T3[1][2] = nc.y - oc.y;
	T4[0][2] = oa.x;
	T4[1][2] = oa.y;

	Matrix3x3 Tp;

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			Tp[i][j] = 0.0f;
			for (int k = 0; k < 3; ++k)
			{
				Tp[i][j] += T3[i][k] * Tinverse[k][j];
			}
		}
	}

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			transform[i][j] = 0.0f;
			for (int k = 0; k < 3; ++k)
			{
				transform[i][j] += T4[i][k] * Tp[k][j];
			}
		}
	}
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
}
