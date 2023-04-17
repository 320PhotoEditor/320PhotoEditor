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

	startWarp = new ButtonElement(upTexture, downTexture, overTexture);
	startWarp->setUpdateFunction([this](GUIElement* element, int status) { this->buttonPressed(element, status); });
	container->addElement(startWarp);
	startWarp->setSize({ .25, .25 });
	startWarp->setPosition({ 0, 0 });

	fillTransparent = new ButtonElement(upTexture, downTexture, overTexture, true);
	fillTransparent->setUpdateFunction([this](GUIElement* element, int status) { this->buttonPressed(element, status); });
	container->addElement(fillTransparent);
	fillTransparent->setSize({ .25, .25 });
	fillTransparent->setPosition({ 0.5, 0 });
}

void WarpTool::start(Layer* layer)
{
	this->layer = layer;
	sf::Vector2u layerSize = layer->getImage()->getSize();
	sf::Vector2i section = {(int)(layerSize.x / 4), (int)(layerSize.y / 4)};

	initControlPoints();
	originalControlPoints[0] = controlPoints[0];
	originalControlPoints[1] = controlPoints[1];
	originalControlPoints[2] = controlPoints[2];
	originalControlPoints[3] = controlPoints[3];

	layer->reload();
	layerCopy.loadFromImage(*layer->getImage());

	compute();
}

void WarpTool::stop()
{
	warpCompute->bindTexture(layerCopy.getNativeHandle(), 0);
	warpCompute->bindTexture(layer->getSprite()->getTexture()->getNativeHandle(), 1);
	warpCompute->setBool("doLines", false);
	sf::Vector2u layerSize = layer->getImage()->getSize();

	warpCompute->compute(layerSize.x / 10.0f, layerSize.y / 10.0f, 1);
	layer->loadImageFromTexture();
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

	compute();
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
	float A[8][8] = { 0	};
	float B[8] = { 0 }, x[8] = { 0 };

	for (int i = 0; i < 4; ++i)
	{
		A[i][0] = A[i + 4][3] = originalControlPoints[i].x;
		A[i][1] = A[i + 4][4] = originalControlPoints[i].y;
		A[i][2] = A[i + 4][5] = 1;
		A[i][3] = A[i][4] = A[i][5] =
		A[i + 4][0] = A[i + 4][1] = A[i + 4][2] = 0;
		A[i][6] = -originalControlPoints[i].x * controlPoints[i].x;
		A[i][7] = -originalControlPoints[i].y * controlPoints[i].x;
		A[i + 4][6] = -originalControlPoints[i].x * controlPoints[i].y;
		A[i + 4][7] = -originalControlPoints[i].y * controlPoints[i].y;
		B[i] = controlPoints[i].x;
		B[i + 4] = controlPoints[i].y;
	}

	//partial pivot
	for (int i = 0; i < 8; i++)
	{
		int maxRow = i;
		for (int j = i + 1; j < 8; j++)
		{
			if (abs(A[j][i]) > abs(A[maxRow][i]))
			{
				maxRow = j;
			}
		}

		if (maxRow != i)
		{
			for (int k = 0; k < 8; k++)
			{
				float temp = A[i][k];
				A[i][k] = A[maxRow][k];
				A[maxRow][k] = temp;
			}
			float temp = B[i];
			B[i] = B[maxRow];
			B[maxRow] = temp;
		}

		for (int j = i + 1; j < 8; j++)
		{
			float factor = A[j][i] / A[i][i];
			for (int k = i + 1; k < 8; k++)
			{
				A[j][k] -= factor * A[i][k];
			}
			B[j] -= factor * B[i];
		}
	}
	//back substitution
	for (int i = 8 - 1; i >= 0; i--)
	{
		x[i] = B[i];
		for (int j = i + 1; j < 8; j++)
		{
			x[i] -= A[i][j] * x[j];
		}
		x[i] /= A[i][i];
	}

	transform[0][0] = x[0];
	transform[0][1] = x[1];
	transform[0][2] = x[2];
	transform[1][0] = x[3];
	transform[1][1] = x[4];
	transform[1][2] = x[5];
	transform[2][0] = x[6];
	transform[2][1] = x[7];
	transform[2][2] = 1;
}

void WarpTool::initControlPoints()
{
	sf::Vector2u layerSize = layer->getImage()->getSize();

	controlPoints[0] = { 0, 0 };
	controlPoints[1] = { (int)layerSize.x-1, 0 };
	controlPoints[2] = { (int)layerSize.x - 1, (int)layerSize.y - 1 };
	controlPoints[3] = { 0, (int)layerSize.y-1 };
}

void WarpTool::buttonPressed(GUIElement* button, int status)
{
	if (button == fillTransparent && status != ButtonElement::ButtonState::OVER)
	{
		doFillTransparent = !doFillTransparent;
		compute();
	}

	if (status != ButtonElement::ButtonState::DOWN)
	{
		return;
	}
	
	if(button == startWarp)
	{
		doWarp = true;
		originalControlPoints[0] = controlPoints[0];
		originalControlPoints[1] = controlPoints[1];
		originalControlPoints[2] = controlPoints[2];
		originalControlPoints[3] = controlPoints[3];
	}
}

void WarpTool::compute()
{
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

	if (doWarp)
	{
		Matrix3x3 transform;
		calculateTransformMatrx(controlPoints, originalControlPoints, transform);
		warpCompute->setMat3("warp", transform);
	}
	warpCompute->setBool("doWarp", doWarp);

	warpCompute->bindTexture(layerCopy.getNativeHandle(), 0);
	warpCompute->bindTexture(layer->getSprite()->getTexture()->getNativeHandle(), 1);
	warpCompute->setBool("doLines", true);
	warpCompute->setInt("dashSize", layer->getImage()->getSize().x / 150);
	warpCompute->setBool("fillTransparent", doFillTransparent);
	sf::Vector2u layerSize = layer->getImage()->getSize();

	warpCompute->compute(layerSize.x / 10.0f, layerSize.y / 10.0f, 1);
}
