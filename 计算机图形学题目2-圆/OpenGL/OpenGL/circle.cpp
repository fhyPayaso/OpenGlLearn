
#include <math.h>
#include "common.h"

#include "circle.h"

void draw8(int x, int y, int x0, int y0, void (*setPixel)(int x, int y))
{
	int dx = x - x0;
	int dy = y - y0;

	setPixel(x0 + dx, y0 + dy);
	setPixel(x0 + dy, y0 + dx);
	
	setPixel(x0 - dx, y0 + dy);
	setPixel(x0 - dy, y0 + dx);
	
	setPixel(x0 - dx, y0 - dy);
	setPixel(x0 - dy, y0 - dx);
	
	setPixel(x0 + dx, y0 - dy);
	setPixel(x0 + dy, y0 - dx);
}


void Bres(int xa, int ya, int xb, int yb, void (*setPixel)(int x, int y))
{
	int dx = abs(xb - xa);
	int dy = abs(yb - ya);
	int R = int(sqrt(dx * dx * 1.0 + dy * dy * 1.0));

	int x, y, p;

	x = 0;
	y = R;
	
	p = 3 - 2 * R;
	while (x <= y)
	{
		draw8(x + xa, y + ya, xa, ya, setPixel);
		x++;
		if (p >= 0)
		{
			
			p += 4 * (x - y) + 10;
			y--;
		}
		else
		{
			p += 4 * x + 6;
		}
	}
}
