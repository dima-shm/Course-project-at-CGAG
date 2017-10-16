#include <math.h>
const double pi = 3.14159;


struct CSizeD
{
	double cx;
	double cy;
};

struct CRectD
{
	double left;
	double top;
	double right;
	double bottom;
	CRectD(){ left = top = right = bottom = 0; };
	CRectD(double l, double t, double r, double b);
	void SetRectD(double l, double t, double r, double b);
	CSizeD SizeD();	// Возвращает размеры(ширина, высота) прямоугольника 
};

CRectD::CRectD(double l, double t, double r, double b)
{
	left = l;
	top = t;
	right = r;
	bottom = b;
}
void CRectD::SetRectD(double l, double t, double r, double b)
{
	left = l;
	top = t;
	right = r;
	bottom = b;
}
CSizeD CRectD::SizeD()
{
	CSizeD cz;
	cz.cx = fabs(right - left);	// Ширина прямоугольной области
	cz.cy = fabs(top - bottom);	// Высота прямоугольной области
	return cz;
}



CMatrix SphereToCart(CMatrix& PView)
// Преобразование сферических координат в декартовы
{
	CMatrix R(3);

	double r = PView(0);
	double fi = PView(1);						// Градусы
	double q = PView(2);						// Градусы
	double fi_rad = (270.0 - fi) * pi / 180.0;	// Перевод fi в радианы
	double q_rad = q * pi / 180.0;				// Перевод q в радианы

	R(0) = r*sin(q_rad)*sin(fi_rad);			// x- координата точки наблюдения
	R(1) = r*sin(q_rad)*cos(fi_rad);			// y- координата точки наблюдения
	R(2) = r*cos(q_rad);						// z- координата точки наблюдения

	return R;
}
CMatrix Rotate3Dx(double fi)
// Поворот объекта вокруг оси OX
{
	double fi_rad = fi * pi / 180.0;
	CMatrix M(4, 4);

	M(0, 0) = 1; M(0, 1) = 0;			M(0, 2) = 0;			M(0, 3) = 0;
	M(1, 0) = 0; M(1, 1) = cos(fi_rad); M(1, 2) = -sin(fi_rad); M(1, 3) = 0;
	M(2, 0) = 0; M(2, 1) = sin(fi_rad); M(2, 2) = cos(fi_rad);  M(2, 3) = 0;
	M(3, 0) = 0; M(3, 1) = 0;           M(3, 2) = 0;			M(3, 3) = 1;

	return M;
}
CMatrix Rotate3Dy(double fi) 
// Поворот объекта вокруг оси OY
{
	double fi_rad = fi * pi / 180.0;
	CMatrix M(4, 4);

	M(0, 0) = cos(fi_rad); M(0, 1) = 0; M(0, 2) = -sin(fi_rad); M(0, 3) = 0;
	M(1, 0) = 0;		   M(1, 1) = 1; M(1, 2) = 0;			M(1, 3) = 0;
	M(2, 0) = sin(fi_rad); M(2, 1) = 0; M(2, 2) = cos(fi_rad);  M(2, 3) = 0;
	M(3, 0) = 0;		   M(3, 1) = 0; M(3, 2) = 0;		    M(3, 3) = 1;

	return M;
}
CMatrix Rotate3Dz(double fi)
// Поворот объекта вокруг оси OZ
{
	double fi_rad = fi * pi / 180.0;
	CMatrix M(4, 4);

	M(0, 0) = cos(fi_rad); M(0, 1) = -sin(fi_rad); M(0, 2) = 0; M(0, 3) = 0;
	M(1, 0) = sin(fi_rad); M(1, 1) = cos(fi_rad);  M(1, 2) = 0; M(1, 3) = 0;
	M(2, 0) = 0;		   M(2, 1) = 0;            M(2, 2) = 1; M(2, 3) = 0;
	M(3, 0) = 0;		   M(3, 1) = 0;            M(3, 2) = 1; M(3, 3) = 1;

	return M;
}
CMatrix CreateViewCoord(double r, double fi, double q)
// Создание матрицы пересчета из МСК в ВСК
{
	double fi_r = fi * pi / 180;
	double theta_r = q * pi / 180;

	CMatrix V(4, 4), M(4, 4);

	M(0, 0) = -1; 
	M(1, 1) = 1; M(2, 2) = 1; M(3, 3) = 1;

	V = M*Rotate3Dx(180 - q)*Rotate3Dz(90 - fi);
	return V;
}
CMatrix SpaceToWindow(CRectD& RS, CRect& RW)
{
	CMatrix M(3, 3);

	double kx = (RW.right - RW.left) / (RS.right - RS.left); // Масштаб по x
	double ky = (RW.bottom - RW.top) / (RS.top - RS.bottom); // масштаб по y

	M(0, 0) = kx; M(0, 1) = 0;   M(0, 2) = (double)RW.left - kx*RS.left;
	M(1, 0) = 0;  M(1, 1) = -ky; M(1, 2) = (double)RW.bottom + ky*RS.bottom;
	M(2, 0) = 0;  M(2, 1) = 0;   M(2, 2) = 1;

	return M;
}
CMatrix VectorMult(CMatrix& V1, CMatrix& V2)
// Векторное произведение векторов
{
	CMatrix M(3), A(3, 3);

	A(0, 0) = 0;	  A(0, 1) = -V1(2); A(0, 2) =  V1(1);
	A(1, 0) =  V1(2); A(1, 1) = 0;      A(1, 2) = -V1(0);
	A(2, 0) = -V1(1); A(2, 1) =  V1(0); A(2, 2) = 0;

	M = A*V2;
	return M;
}
double ScalarMult(CMatrix& V1, CMatrix& V2)
// Скалярное произведение векторов
{
	return sqrt(V1(0)*V1(0) + V1(1)*V1(1) + V1(2)*V1(2))*sqrt(V2(0)*V2(0) + V2(1)*V2(1) + V2(2)*V2(2))*(V1(0)*V2(0) + V1(1)*V2(1) + V1(2)*V2(2)) / sqrt((V1(0)*V1(0) + V1(1)*V1(1) + V1(2)*V1(2))*(V2(0)*V2(0) + V2(1)*V2(1) + V2(2)*V2(2)));
}

double ModVec(CMatrix& V)
// Модуль вектора V
{
	return sqrt(V(0)*V(0) + V(1)*V(1) + V(2)*V(2));
}
double CosV1V2(CMatrix& V1, CMatrix& V2)
// Косинус угла между векторами
{
	return ScalarMult(V1, V2)/(ModVec(V1)*ModVec(V2));
}