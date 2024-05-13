#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

// Вариант3
//
// y'' + y = 1 , y(0) = 0 , y(π/2) = 0
//
// Аналитическое решение: y(x) = 1-sin(x)-cos(x)
//
// Для преобразования дифференциального уравнения второго порядка(y'' + y = 1)
// в систему уравнений первого порядка необходимо ввести новые переменные :
//Hi people!
//
// получаем систему уравнений первого порядка :
// y' = z //f1
// z' = 1 - y //f2

float f1(float x, float y, float z)//функция
{
  return(z);// значение зет
}
float f2(float x, float y, float z)
{
  return(1 - y);
}
float shoot(float x0, float y0, float z0, float xn, float h, int p) // метод Рунге-Кутта
{
  ofstream output_rk4xy("rk4xy.txt");

  float x, y, z, k1, k2, k3, k4, l1, l2, l3, l4, k, l, x1, y1, z1;
  x = x0;
  y = y0;
  z = z0;
  do
  {
    k1 = h * f1(x, y, z);
    l1 = h * f2(x, y, z);
    k2 = h * f1(x + h / 2.0, y + k1 / 2.0, z + l1 / 2.0);
    l2 = h * f2(x + h / 2.0, y + k1 / 2.0, z + l1 / 2.0);
    k3 = h * f1(x + h / 2.0, y + k2 / 2.0, z + l2 / 2.0);
    l3 = h * f2(x + h / 2.0, y + k2 / 2.0, z + l2 / 2.0);
    k4 = h * f1(x + h, y + k3, z + l3);
    l4 = h * f2(x + h, y + k3, z + l3);
    l = 1 / 6.0 * (l1 + 2 * l2 + 2 * l3 + l4);
    k = 1 / 6.0 * (k1 + 2 * k2 + 2 * k3 + k4);
    y1 = y + k;
    x1 = x + h;
    z1 = z + l;
    x = x1;
    y = y1;
    z = z1;
    cout << x << " " << y << endl;
    if (p == 1)
    {
      output_rk4xy << x << " " << y << endl;
    }
  } while (x < xn);
  cout << endl;

  output_rk4xy.close();

  return(y);
}
int main()
{
  //поиск подходящего y' осуществляется методом Ньютона

  float x0, y0, h, xn, yn, z0, m1, m2, m3, b, b1, b2, b3, e;
  int p = 0;

  x0 = 0; // из условия y(0) = 0
  y0 = 0; // из условия y(0) = 0
  xn = 3.14 / 2; // из условия y(pi/2) = 0
  yn = 0; // из условия y(pi/2) = 0
  h = 0.1; // шаг для метода RK
  m1 = -10.0; // рандомное первое приближение производной

  b = yn;
  z0 = m1;
  b1 = shoot(x0, y0, z0, xn, h, p = 0);
  if (fabs(b1 - b) < 0.00005) //метод ньютона
  {
    e = shoot(x0, y0, z0, xn, h, p = 1);
    return(0);
  }
  else
  {
    m2 = 10.0; // рандомное второе приближение производной
    z0 = m2;
    b2 = shoot(x0, y0, z0, xn, h, p = 0);
  }
  if (fabs(b2 - b) < 0.00005)
  {
    e = shoot(x0, y0, z0, xn, h, p = 1);
    return(0);
  }
  else
  {
    m3 = m2 + (((m2 - m1) * (b - b2)) / (b2 - b1)); //пояснение в файле
    if (b1 - b2 == 0)
      exit(0);

    z0 = m3;
    b3 = shoot(x0, y0, z0, xn, h, p = 0);
  }
  if (fabs(b3 - b) < 0.000005)
  {
    e = shoot(x0, y0, z0, xn, h, p = 1);
    exit(0);
  }
  do
  {
    m1 = m2;
    m2 = m3;
    b1 = b2;
    b2 = b3;
    m3 = m2 + (((m2 - m1) * (b - b2)) / (1.0 * (b2 - b1)));
    z0 = m3;
    b3 = shoot(x0, y0, z0, xn, h, p = 0);

  } while (fabs(b3 - b) < 0.0005);
  z0 = m3;
  e = shoot(x0, y0, z0, xn, h, p = 1);

  return 0;
}