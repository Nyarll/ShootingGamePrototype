
#include "Collision.h"

//â~ìØémÇÃè’ìÀ
//(â~1ÇÃîºåa, â~2ÇÃîºåa, â~1ÇÃxç¿ïW, â~2ÇÃxç¿ïW, â~1ÇÃyç¿ïW, â~2ÇÃyç¿ïW)
BOOL CircleCollision(double c1, double c2, double cx1, double cx2,
	double cy1, double cy2)
{
	double hlength = c1 + c2;
	double xlength = cx1 - cx2;
	double ylength = cy1 - cy2;

	if (hlength * hlength >= xlength * xlength + ylength * ylength)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

//éläpìØémÇÃè’ìÀ
//(box1_pos_x, box1_pos_y, box1_size_x, box1_size_y, box2_pos_x, box2_pos_y, box2_size_x, box2_size_y)
BOOL BoxCollision(double x1, double y1, double size_x1, double size_y1,
	double x2, double y2, double size_x2, double size_y2)
{
	double ax1 = x1 - size_x1, ax2 = x1 + size_x1;
	double ay1 = y1 - size_y1, ay2 = y1 + size_y1;

	double bx1 = x2 - size_x2, bx2 = x2 + size_x2;
	double by1 = y2 - size_y2, by2 = y2 + size_y2;

	if ((bx1 < ax2) && (by1 > ay1) && (by2 < ay2) && (ax1 < bx2))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


// ê¸ï™ÇÃè’ìÀ
// a1	b1
// |	
// |	|
// |	|
// |
// a2	b2
BOOL LineCollision(double line_a1, double line_a2, double line_b1, double line_b2)
{
	if ((line_a1 < line_b1) && (line_a2 > line_b2))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}