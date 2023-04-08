#include "Common.h"

sf::Vector2f operator*(const sf::Vector2f& a, const sf::Vector2f& b)
{
	return sf::Vector2f(a.x * b.x, a.y * b.y);
}

sf::Vector2f operator*=(const sf::Vector2f& a, const sf::Vector2f& b)
{
	return sf::Vector2f(a * b);
}

sf::Vector2f operator*(const sf::Vector2f& a, const sf::Vector2u& b)
{
	return sf::Vector2f(a.x * b.x, a.y * b.y);
}

sf::Vector2f operator/(const sf::Vector2f& a, const sf::Vector2u& b)
{
	return sf::Vector2f(a.x / b.x, a.y / b.y);
}

sf::Vector2f operator/(const sf::Vector2i& a, const sf::Vector2u& b)
{
	return sf::Vector2f((float)a.x / (float)b.x, (float)a.y / (float)b.y);
}

sf::Vector2f operator/(const sf::Vector2u& a, const sf::Vector2u& b)
{
	return sf::Vector2f((float)a.x / b.x, (float)a.y / b.y);
}

sf::Vector2f operator-(const sf::Vector2i& a, const sf::Vector2f& b)
{
	return sf::Vector2f(a.x - b.x, a.y - b.y);
}

sf::Vector2f operator/(const sf::Vector2i& a, const float& b)
{
	return sf::Vector2f(a.x / b, a.y / b);
}

sf::Vector2u operator/(const sf::Vector2u& a, const int& b)
{
	return sf::Vector2u(a.x / b, a.y / b);
}

sf::Vector2i operator*(const sf::Vector2i a, const float& b)
{
	return sf::Vector2i(a.x * b, a.y * b);
}

float hue2rgb(float p, float q, float t)
{

	if (t < 0)
		t += 1;
	if (t > 1)
		t -= 1;
	if (t < 1. / 6)
		return p + (q - p) * 6 * t;
	if (t < 1. / 2)
		return q;
	if (t < 2. / 3)
		return p + (q - p) * (2. / 3 - t) * 6;

	return p;

}

sf::Color hsl2rgb(float h, float s, float l)
{
	sf::Color rgb;

	if (0 == s)
	{
		rgb.r = rgb.g = rgb.b = l;
	}
	else
	{
		float q = l < 0.5 ? l * (1 + s) : l + s - l * s;
		float p = 2 * l - q;
		rgb.r = hue2rgb(p, q, h + 1. / 3) * 255;
		rgb.g = hue2rgb(p, q, h) * 255;
		rgb.b = hue2rgb(p, q, h - 1. / 3) * 255;
	}

	return rgb;
}

float* rgb2hsl(sf::Color rgb)
{
	float r = rgb.r / 255.0;
	float g = rgb.g / 255.0;
	float b = rgb.b / 255.0;

	float cmax = fmax(r, fmax(g, b));
	float cmin = fmin(r, fmin(g, b));
	float delta = cmax - cmin;

	float lightness = (cmax + cmin) / 2.0;

	float hue, saturation;
	if (delta == 0)
	{
		hue = 0;
		saturation = 0;
	}
	else
	{
		if (lightness < 0.5)
		{
			saturation = delta / (cmax + cmin);
		}
		else
		{
			saturation = delta / (2.0 - cmax - cmin);
		}
		if (cmax == r)
		{
			hue = fmod((g - b) / delta, 6.0);
		}
		else if (cmax == g)
		{
			hue = ((b - r) / delta) + 2.0;
		}
		else
		{
			hue = ((r - g) / delta) + 4.0;
		}
		hue /= 6.0;
	}

	float* hsl = new float[3];
	hsl[0] = hue;
	hsl[1] = saturation;
	hsl[2] = lightness;

	return hsl;
}

#ifdef _WIN32
	#include <Windows.h>
	#include <tchar.h>
	#include <atlstr.h>
	std::string openFileDialog(sf::RenderWindow* parentWindow, bool selectMultiple)
	{
		OPENFILENAME ofn;
		TCHAR szFile[260] = { 0 };

		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = (HWND)parentWindow->getSystemHandle();
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = _T("All\0*.*\0");
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER | (selectMultiple ? OFN_ALLOWMULTISELECT : 0);

		if (GetOpenFileName(&ofn) == TRUE)
		{
			return std::string(CW2A(ofn.lpstrFile));
		}

		std::cerr << "Error: open file dialog fail" << std::endl;

		return "";
	}
#elif __APPLE__
	std::string openFileDialog(sf::RenderWindow* parentWindow, bool selectMultiple)
	{
		std::string path;
		std::cin >> path;
		return path;
	}
#else
	std::string openFileDialog(sf::RenderWindow* parentWindow, bool selectMultiple)
	{
		std::cerr << "Error: Unkown OS, unable to create open file dialog"
		return "";
	}
#endif
