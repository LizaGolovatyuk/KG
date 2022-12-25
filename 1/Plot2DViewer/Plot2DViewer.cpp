#include <windows.h>
#include <windowsx.h>
#include "Data.h"
#include "Scene3D.h"
#include "Scene2D.h"

LRESULT _stdcall WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);						// прототип оконной процедуры
int _stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)		// основная процедура
{
	// Первая составляющая часть основной процедуры - создание окна: сначала описывается оконный класс wc, затем создаётся окно hWnd
	WNDCLASS wc;
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;						// имя оконной процедуры, закрепленной за данным классом
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;						// идентификатор приложения, содержащий адрес начала выделенной ему области памяти
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(6);
	wc.lpszMenuName = 0;							// меню в оконном классе отсутствует
	wc.lpszClassName = (LPCSTR)"MainWindowClass";	// имя оконного класса, используемое при создании экземпляров окна
	RegisterClass(&wc);								// регистрация класса wc

	HWND hWnd = CreateWindow(						// hWnd - дескриптор, идентифицирующий окно; функция создания окна заполняет дескриптор hWnd ненулевым значением
		(LPCSTR)"MainWindowClass",					// имя оконного класса
		(LPCSTR)"Plot2D Viewer",					// заголовок окна
		WS_OVERLAPPEDWINDOW,						// стиль окна
		200, 200, 400, 400,							// координаты на экране левого верхнего угла окна, его ширина и высота
		nullptr, nullptr, hInstance, nullptr);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// Вторая составляющая часть основной процедуры - основной цикл обработки системных сообщений, который ожидает сообщения и рассылает их соответствующим окнам
	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0))				// функция GetMessage выбирает из очереди сообщение и заносит его в структуру msg
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);						// функция DispatchMessage оповещает систему о необходимости вызова оконной процедуры
	}

	return 0;
}

// В основном модуле объявляется только одна глобальная переменная - создаётся объект класса Scene2D
// Все дальнейшие действия осуществляются посредством обращения к методам, реализованным в этом классе

Scene3D scene3D(X0, Y0, px, py, W, H);
int i = -1;


LRESULT _stdcall WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{

	case WM_PAINT:
	{
		HDC dc = GetDC(hWnd);
		scene3D.Clear3D(dc);			
		scene3D.Render3D(dc);		
		ReleaseDC(hWnd, dc);
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_F1:
		{
			int n_point = 2;
			Triad* v = new Triad[n_point];
			v[0] = Triad(-1000, 0, 0);
			v[1] = Triad(1000, 0, 0);

			int n_edges = 1;
			pair<double, double>* Edges = new pair<double, double>[n_edges];
			Edges[0].first = 0;
			Edges[0].second = 1;

			int count_facet = 1;
			Triad* f = new Triad[count_facet];
			f[0] = Triad(1, 0, 0);

			scene3D.CreateModel3D(n_point, v, Edges, n_edges, count_facet, f);
			InvalidateRect(hWnd, nullptr, false);
			return 0;
		}
		case VK_F2:
		{
			int n_point = 2;
			Triad* v = new Triad[n_point];
			v[0] = Triad(0, -1000, 0);
			v[1] = Triad(0, 1000, 0);

			int n_edges = 1;
			pair<double, double>* Edges = new pair<double, double>[n_edges];
			Edges[0].first = 0;
			Edges[0].second = 1;

			int count_facet = 1;
			Triad* f = new Triad[count_facet];
			f[0] = Triad(1, 0, 0);

			scene3D.CreateModel3D(n_point, v, Edges, n_edges, count_facet, f);
			InvalidateRect(hWnd, nullptr, false);
			return 0;
		}
		case VK_F3:
		{
			int n_point = 2;
			Triad* v = new Triad[n_point];
			v[0] = Triad(0, 0, -1000);
			v[1] = Triad(0, 0, 1000);

			int n_edges = 1;
			pair<double, double>* Edges = new pair<double, double>[n_edges];
			Edges[0].first = 0;
			Edges[0].second = 1;

			int count_facet = 1;
			Triad* f = new Triad[count_facet];
			f[0] = Triad(1, 0, 0);

			scene3D.CreateModel3D(n_point, v, Edges, n_edges, count_facet, f);
			InvalidateRect(hWnd, nullptr, false);
			return 0;
		}

		case VK_F4:
		{
			int n_point = 4;
			Triad* v = new Triad[n_point];
			v[0] = Triad(0, 0, 0);
			v[1] = Triad(0, 3, 0);
			v[2] = Triad(3, 0, 0);
			v[3] = Triad(0, 0, 3);

			int n_edges = 6;
			pair<double, double>* Edges = new pair<double, double>[n_edges];
			Edges[0].first = 0;
			Edges[0].second = 1;
			Edges[1].first = 1;
			Edges[1].second = 2;
			Edges[2].first = 2;
			Edges[2].second = 0;
			Edges[3].first = 0;
			Edges[3].second = 3;
			Edges[4].first = 3;
			Edges[4].second = 1;
			Edges[5].first = 3;
			Edges[5].second = 2;

			int count_facet = 4;
			Triad* facet = new Triad[4];
			facet[0] = Triad(0, 1, 2);
			facet[1] = Triad(0, 2, 3);
			facet[2] = Triad(0, 1, 3);
			facet[3] = Triad(1, 2, 3);

			scene3D.CreateModel3D(n_point, v, Edges, n_edges, count_facet, facet);
			InvalidateRect(hWnd, nullptr, false);
			return 0;
		}

		case VK_F5:
		{
			int n_point = 8;
			Triad* v = new Triad[n_point];
			v[0] = Triad(2, 2, 0);
			v[1] = Triad(2, -2, 0);
			v[2] = Triad(6, -2, 0);
			v[3] = Triad(6, 2, 0);
			v[4] = Triad(2, 2, 4);
			v[5] = Triad(2, -2, 4);
			v[6] = Triad(6, -2, 4);
			v[7] = Triad(6, 2, 4);

			int n_edges = 12;
			pair<double, double>* edges = new pair<double, double>[n_edges];
			edges[0].first = 0;
			edges[0].second = 1;
			edges[1].first = 0;
			edges[1].second = 4;
			edges[2].first = 0;
			edges[2].second = 3;
			edges[3].first = 1;
			edges[3].second = 2;
			edges[4].first = 1;
			edges[4].second = 5;
			edges[5].first = 2;
			edges[5].second = 3;
			edges[6].first = 2;
			edges[6].second = 6;
			edges[7].first = 3;
			edges[7].second = 7;
			edges[8].first = 4;
			edges[8].second = 5;
			edges[9].first = 4;
			edges[9].second = 7;
			edges[10].first = 5;
			edges[10].second = 6;
			edges[11].first = 6;
			edges[11].second = 7;

			int count_facet = 9;
			Triad* facet = new Triad[count_facet];
			facet[0] = Triad(0, 1, 2);
			facet[1] = Triad(0, 2, 3);
			facet[2] = Triad(0, 4, 7);
			facet[3] = Triad(0, 7, 3);
			facet[4] = Triad(3, 6, 2);
			facet[5] = Triad(1, 6, 2);
			facet[6] = Triad(1, 5, 6);
			facet[7] = Triad(0, 1, 5);
			facet[8] = Triad(0, 4, 5);
			facet[7] = Triad(4, 5, 6);
			facet[8] = Triad(4, 6, 7);

			scene3D.CreateModel3D(n_point, v, edges, n_edges, count_facet, facet);
			InvalidateRect(hWnd, nullptr, false);
			return 0;
		}

		case VK_F6:
		{
			
				Model3D m = scene3D.getModel3D(3);

				double x = m.get0().getX();
				double y = m.get0().getY();
				double z = m.get0().getZ();

				m.Apply(Translation(-x, -y, -z), true);

				Triad v(m.get3().getX() - m.get0().getX(), m.get3().getY() - m.get0().getY(), m.get3().getZ() - m.get0().getZ());
				double cosB = v.getY()/sqrt(v.getY()*v.getY()+v.getZ()*v.getZ());
				double sinB= v.getZ() / sqrt(v.getY() * v.getY() + v.getZ() * v.getZ());
				m.Apply(RotationX(cosB, -sinB), true);

				Triad v1(m.get3().getX() - m.get0().getX(), m.get3().getY() - m.get0().getY(), m.get3().getZ() - m.get0().getZ());
				double cosL = v1.getX() / sqrt(v1.getX() * v1.getX()+v1.getY() * v1.getY() + v1.getZ() * v1.getZ());
				double sinL = sqrt(v1.getY() * v1.getY() + v1.getZ() * v1.getZ())/ sqrt(v1.getX() * v1.getX()+v1.getY() * v1.getY() + v1.getZ() * v1.getZ());
				m.Apply(RotationZ(cosL, -sinL), true);

				m.Apply(MapingYZ(), true);

				/*Triad v2(m.get3().getX() - m.get0().getX(), m.get3().getY() - m.get0().getY(), m.get3().getZ() - m.get0().getZ());*/
				/* cosL = v2.getX() / sqrt(v2.getX() * v2.getX() + v2.getY() * v2.getY() + v2.getZ() * v2.getZ());
				 sinL = sqrt(v2.getY() * v2.getY() + v2.getZ() * v2.getZ()) / sqrt(v2.getX() * v2.getX() + v2.getY() * v2.getY() + v2.getZ() * v2.getZ());*/
				m.Apply(RotationZ(cosL, sinL), true);

				/*Triad v3(m.get3().getX() - m.get0().getX(), m.get3().getY() - m.get0().getY(), m.get3().getZ() - m.get0().getZ());*/
				/* cosB = v3.getY() / sqrt(v3.getY() * v3.getY() + v3.getZ() * v3.getZ());
				 sinB = v3.getZ() / sqrt(v3.getY() * v3.getY() + v3.getZ() * v3.getZ());*/
				m.Apply(RotationX(cosB, sinB), true);
				
				m.Apply(Translation(x,y,z), true);

				scene3D.Change3D(3, m);

				InvalidateRect(hWnd, nullptr, false);
				return 0;
		}
			
		case VK_TAB:
		{
			if (i == -1 || i<3) i = 3;
			else
			{
				if (i < scene3D.GetSize() - 1) i++;
				else i = 3;
			}
			break;
		}
			
		case VK_LEFT://сдвиг влево по х
		{
			if (i != -1 && i>2)
			{
				Model3D m = scene3D.getModel3D(i);
				m.Apply(Translation(-0.5, 0, 0),true);	
				scene3D.Change3D(i,m);
			}
			InvalidateRect(hWnd, nullptr, false);
			return 0;
		}
		case VK_RIGHT://сдвиг вправо по х
		{
			if (i != -1 && i > 2)
			{
				Model3D m = scene3D.getModel3D(i);
				m.Apply(Translation(0.5, 0, 0), true);
				scene3D.Change3D(i, m);
			}
			InvalidateRect(hWnd, nullptr, false);
			return 0;
		}
		case VK_DOWN://сдвиг вверх по у
		{
			if (i != -1 && i > 2)
			{
				Model3D m = scene3D.getModel3D(i);
				m.Apply(Translation(0, -0.5, 0), true);
				scene3D.Change3D(i, m);
			}
			InvalidateRect(hWnd, nullptr, false);
			return 0;
		}
		case VK_UP://сдвиг вниз по у
		{
			if (i != -1 && i > 2)
			{
				Model3D m = scene3D.getModel3D(i);
				m.Apply(Translation(0, 0.5, 0), true);
				scene3D.Change3D(i, m);
			}
			InvalidateRect(hWnd, nullptr, false);
			return 0;
		}
		case VK_BACK://сдвиг вперед по z
		{
			if (i != -1 && i > 2)
			{
				Model3D m = scene3D.getModel3D(i);
				m.Apply(Translation(0, 0, 0.5), true);
				scene3D.Change3D(i, m);
			}
			InvalidateRect(hWnd, nullptr, false);
			return 0;
		}
		case VK_RETURN://сдвиг назад по z
		{
			if (i != -1 && i > 2)
			{
				Model3D m = scene3D.getModel3D(i);
				m.Apply(Translation(0, 0, -0.5), true);
				scene3D.Change3D(i, m);
			}
			InvalidateRect(hWnd, nullptr, false);
			return 0;
		}





		case 0X41://поворот вокруг z против часовой
		{
			if (i != -1 && i > 2)
			{
				Model3D m = scene3D.getModel3D(i);
				m.Apply(RotationZ(M_PI/6), true);
				scene3D.Change3D(i, m);
			}
			InvalidateRect(hWnd, nullptr, false);
			return 0;
		}
		case 0X42://поворот вокруг z по часовой
		{
			if (i != -1 && i > 2)
			{
				Model3D m = scene3D.getModel3D(i);
				m.Apply(RotationZ(-M_PI / 6), true);
				scene3D.Change3D(i, m);
			}
			InvalidateRect(hWnd, nullptr, false);
			return 0;
		}
		case 0X43://поворот вокруг x против часовой
		{
			if (i != -1 && i > 2)
			{
				Model3D m = scene3D.getModel3D(i);
				m.Apply(RotationX(M_PI / 6), true);
				scene3D.Change3D(i, m);
			}
			InvalidateRect(hWnd, nullptr, false);
			return 0;
		}
		case 0X44://поворот вокруг x по часовой
		{
			if (i != -1 && i > 2)
			{
				Model3D m = scene3D.getModel3D(i);
				m.Apply(RotationX(-M_PI / 6), true);
				scene3D.Change3D(i, m);
			}
			InvalidateRect(hWnd, nullptr, false);
			return 0;
		}
		case 0X45://поворот вокруг у против часовой
		{
			if (i != -1 && i > 2)
			{
				Model3D m = scene3D.getModel3D(i);
				m.Apply(RotationY(M_PI / 6), true);
				scene3D.Change3D(i, m);
			}
			InvalidateRect(hWnd, nullptr, false);
			return 0;
		}
		case 0X46://поворот вокруг у по часовой
		{
			if (i != -1 && i > 2)
			{
				Model3D m = scene3D.getModel3D(i);
				m.Apply(RotationY(-M_PI / 6), true);
				scene3D.Change3D(i, m);
			}
			InvalidateRect(hWnd, nullptr, false);
			return 0;
		}


		case 0X47://поворот вокруг центра относительно x против часовой 
		{
			if (i != -1 && i > 2)
			{
				Triad middle = scene3D.getModel3D(i).Middle();
				Model3D m = scene3D.getModel3D(i);
				m.Apply(Translation(-middle.getX(), -middle.getY(), -middle.getZ()), false);
				m.Apply(RotationX(M_PI / 6), false);
				m.Apply(Translation(middle.getX(), middle.getY(), middle.getZ()), true);
				scene3D.Change3D(i, m);
			}
			InvalidateRect(hWnd, nullptr, false);
			return 0;
		}
		case 0X48://поворот вокруг центра относительно у против часовой 
		{
			if (i != -1 && i > 2)
			{
				Triad middle = scene3D.getModel3D(i).Middle();
				Model3D m = scene3D.getModel3D(i);
				m.Apply(Translation(-middle.getX(), -middle.getY(), -middle.getZ()), false);
				m.Apply(RotationY(M_PI / 6), false);
				m.Apply(Translation(middle.getX(), middle.getY(), middle.getZ()), true);
				scene3D.Change3D(i, m);
			}
			InvalidateRect(hWnd, nullptr, false);
			return 0;
		}
		case 0X49://поворот вокруг центра относительно z против часовой 
		{
			if (i != -1 && i > 2)
			{
				Triad middle = scene3D.getModel3D(i).Middle();
				Model3D m = scene3D.getModel3D(i);
				m.Apply(Translation(-middle.getX(), -middle.getY(), -middle.getZ()), false);
				m.Apply(RotationZ(M_PI / 6), false);
				m.Apply(Translation(middle.getX(), middle.getY(), middle.getZ()), true);
				scene3D.Change3D(i, m);
			}
			InvalidateRect(hWnd, nullptr, false);
			return 0;
		}




		case VK_OEM_PLUS://увеличение фигуры
		{
			if (i != -1 && i > 2)
			{
				Model3D m = scene3D.getModel3D(i);
				m.Apply(Scaling(1.5,1.5,1.5), true);
				scene3D.Change3D(i, m);
			}
			InvalidateRect(hWnd, nullptr, false);
			return 0;
		}
		case VK_OEM_MINUS://увеличение фигуры
		{
			if (i != -1 && i > 2)
			{
				Model3D m = scene3D.getModel3D(i);
				m.Apply(Scaling(0.8, 0.8, 0.8), true);
				scene3D.Change3D(i, m);
			}
			InvalidateRect(hWnd, nullptr, false);
			return 0;
		}




		case 0X31://отражение относительно плоскости xу
		{
			if (i != -1 && i > 2)
			{
				Model3D m = scene3D.getModel3D(i);
				m.Apply(MapingXY(), true);
				scene3D.Change3D(i, m);
			}
			InvalidateRect(hWnd, nullptr, false);
			return 0;
		}
		case 0X32://отражение относительно плоскости xz
		{
			if (i != -1 && i > 2)
			{
				Model3D m = scene3D.getModel3D(i);
				m.Apply(MapingZX(), true);
				scene3D.Change3D(i, m);
			}
			InvalidateRect(hWnd, nullptr, false);
			return 0;
		}
		case 0X33://отражение относительно плоскости уz
		{
			if (i != -1 && i > 2)
			{
				Model3D m = scene3D.getModel3D(i);
				m.Apply(MapingYZ(), true);
				scene3D.Change3D(i, m);
			}
			InvalidateRect(hWnd, nullptr, false);
			return 0;
		}




		case 0X34://отражение относительно x
		{
			if (i != -1 && i > 2)
			{
				Model3D m = scene3D.getModel3D(i);
				m.Apply(MapingX(), true);
				scene3D.Change3D(i, m);
			}
			InvalidateRect(hWnd, nullptr, false);
			return 0;
		}
		case 0X35://отражение относительно у
		{
			if (i != -1 && i > 2)
			{
				Model3D m = scene3D.getModel3D(i);
				m.Apply(MapingY(), true);
				scene3D.Change3D(i, m);
			}
			InvalidateRect(hWnd, nullptr, false);
			return 0;
		}
		case 0X36://отражение относительно z
		{
			if (i != -1 && i > 2)
			{
				Model3D m = scene3D.getModel3D(i);
				m.Apply(MapingZ(), true);
				scene3D.Change3D(i, m);
			}
			InvalidateRect(hWnd, nullptr, false);
			return 0;
		}


		case 0X37://отражение относительно центра
		{
			if (i != -1 && i > 2)
			{
				Model3D m = scene3D.getModel3D(i);
				m.Apply(MapingO(), true);
				scene3D.Change3D(i, m);
			}
			InvalidateRect(hWnd, nullptr, false);
			return 0;
		}



		case 0X38://отражение относительно плоскости пр через центр парал xy
		{
			if (i != -1 && i > 2)
			{
				Triad middle = scene3D.getModel3D(i).Middle();
				Model3D m = scene3D.getModel3D(i);
				m.Apply(Translation(-middle.getX(),-middle.getY(), -middle.getZ()), false);
				m.Apply(MapingXY(), false);
				m.Apply(Translation(middle.getX(), middle.getY(), middle.getZ()), true);
				scene3D.Change3D(i, m);
			}
			InvalidateRect(hWnd, nullptr, false);
			return 0;
		}

		case 0X39://отражение относительно плоскости пр через центр парал xz
		{
			if (i != -1 && i > 2)
			{
				Triad middle = scene3D.getModel3D(i).Middle();
				Model3D m = scene3D.getModel3D(i);
				m.Apply(Translation(-middle.getX(), -middle.getY(), -middle.getZ()), false);
				m.Apply(MapingZX(), false);
				m.Apply(Translation(middle.getX(), middle.getY(), middle.getZ()), true);
				scene3D.Change3D(i, m);
			}
			InvalidateRect(hWnd, nullptr, false);
			return 0;
		}

		case 0X30://отражение относительно плоскости пр через центр парал yz
		{
			if (i != -1 && i > 2)
			{
				Triad middle = scene3D.getModel3D(i).Middle();
				Model3D m = scene3D.getModel3D(i);
				m.Apply(Translation(-middle.getX(), -middle.getY(), -middle.getZ()), false);
				m.Apply(MapingYZ(), false);
				m.Apply(Translation(middle.getX(), middle.getY(), middle.getZ()), true);
				scene3D.Change3D(i, m);
			}
			InvalidateRect(hWnd, nullptr, false);
			return 0;
		}





		}
		return 0;
	}





	case WM_SIZE:
	{
		HDC dc = GetDC(hWnd);
		scene3D.SetResolution(dc);
		ReleaseDC(hWnd, dc);
		InvalidateRect(hWnd, nullptr, false);
		return 0;
	}
	
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	
	default:
	{
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	}

	return 0;
}







//LRESULT _stdcall WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)		// оконная процедура принимает и обрабатывает все сообщения, отправленные окну
//{
//	switch (msg)
//	{
//	case WM_PAINT:
//	{
//		HDC dc = GetDC(hWnd);
//
//		scene.Clear(dc);				// Вызов реализованного в классе Camera2D метода, отвечающего за очистку рабочей области окна hWnd
//		scene.Render(dc);		// Вызов реализованного в классе Scene2D метода, отвечающего за отрисовку графика синусоиды
//		ReleaseDC(hWnd, dc);
//		return DefWindowProc(hWnd, msg, wParam, lParam);
//		
//	}
//
//	case WM_KEYDOWN:
//	{
//		switch (wParam)
//		{
//		case VK_F1:
//		{
//			int nv = 8;
//			int ne = 8;
//
//			pair<int, int>* ed = new pair<int, int>[ne];
//			for (int i = 0; i < ne - 1; i++)
//			{
//				ed[i].first = i;
//				ed[i].second = i + 1;
//			}
//			ed[7].first = 7;
//			ed[7].second = 0;
//
//			pair<double, double>* v = new pair<double, double>[nv];
//			int k = 1;
//			for (int i = 0; i < nv - 1; i++)
//			{
//				if (i != 0 && i % 2 != 0)
//				{
//					v[i].first = v[i - 1].first;
//					v[i].second = v[i - 1].second - k;
//				}
//				else
//				{
//					if (i != 0 && i % 2 == 0)
//					{
//						v[i].first = v[i - 1].first + k;
//						v[i].second = v[i - 1].second;
//					}
//					else
//					{
//						v[i].first = 1;
//						v[i].second = -1;
//					}
//				}
//			}
//			v[7].first = 4;
//			v[7].second = -1;
//
//			scene.CreateModel(v, nv, ed, ne);
//			InvalidateRect(hWnd, nullptr, false);
//			break;
//		}
//
//		case VK_F2:
//		{
//			int nv = 8;
//			int ne = 8;
//
//			pair<int, int>* ed = new pair<int, int>[ne];
//			for (int i = 0; i < ne - 1; i++)
//			{
//				ed[i].first = i;
//				ed[i].second = i + 1;
//			}
//			ed[7].first = 7;
//			ed[7].second = 0;
//
//			pair<double, double>* v = new pair<double, double>[nv];
//			v[0].first = 3;
//			v[0].second = -1;
//			v[1].first = 1;
//			v[1].second = -3;
//			v[2].first = 1;
//			v[2].second = -5;
//			v[3].first = 2.5;
//			v[3].second = -5;
//			v[4].first = 3;
//			v[4].second = -4;
//			v[5].first = 3.5;
//			v[5].second = -5;
//			v[6].first = 5;
//			v[6].second = -5;
//			v[7].first = 5;
//			v[7].second = -3;
//
//			scene.CreateModel(v, nv, ed, ne);
//			InvalidateRect(hWnd, nullptr, false);
//			break;
//		}
//
//		case VK_TAB:
//		{
//			if (i == -1) i = 0;
//			else i = (i + 1) % scene.GetSize();
//			break;
//		}
//
//		case VK_LEFT://сдвиг влево
//		{
//			if (i != -1)
//			{
//				Model2D m = scene.GetModel(i);
//				m.Apply(Translation(-0.5, 0),true);	
//				scene.Change(i, m);
//			}
//			InvalidateRect(hWnd, nullptr, false);
//			break;
//		}
//
//		case VK_RIGHT://сдвиг впарво
//		{
//			if (i != -1)
//			{
//				Model2D m = scene.GetModel(i);
//				m.Apply(Translation(0.5, 0),true);
//				scene.Change(i, m);
//			}
//			InvalidateRect(hWnd, nullptr, false);
//			break;
//		}
//
//		case VK_UP://сдвиг вверх
//		{
//			if (i != -1)
//			{
//				Model2D m = scene.GetModel(i);
//				m.Apply(Translation(0, -0.5),true);
//				scene.Change(i, m);
//			}
//			InvalidateRect(hWnd, nullptr, false);
//			break;
//		}
//		case VK_DOWN://сдвиг вниз
//		{
//			if (i != -1)
//			{
//				Model2D m = scene.GetModel(i);
//				m.Apply(Translation(0, 0.5),true);
//				scene.Change(i, m);
//			}
//			InvalidateRect(hWnd, nullptr, false);
//			break;
//		}
//
//		case VK_OEM_PLUS://поворот вправо 
//		{
//			if (i != -1)
//			{
//				Model2D m = scene.GetModel(i);
//				pair<double, double> oxy = m.OXY();				
//				m.Apply(Translation(-oxy.first,-oxy.second),false);
//				m.Apply(Rotation(M_PI/6), false);
//				m.Apply(Translation(oxy.first, oxy.second), true);
//				scene.Change(i, m);
//			}
//			InvalidateRect(hWnd, nullptr, false);
//			break;
//		}
//
//		case VK_OEM_MINUS://поворот влево
//		{
//			if (i != -1)
//			{
//				Model2D m = scene.GetModel(i);
//				pair<double, double> oxy = m.OXY();
//				m.Apply(Translation(-oxy.first, -oxy.second), false);
//				m.Apply(Rotation(-M_PI / 6), false);
//				m.Apply(Translation(oxy.first, oxy.second), true);
//				scene.Change(i, m);
//			}
//			InvalidateRect(hWnd, nullptr, false);
//			break;
//		}
//
//		case VK_F4:
//		{
//			if (i != -1) 
//			{
//				Model2D m = scene.GetModel(i);
//				m.Apply(Rotation(M_PI / 6), true);
//				scene.Change(i, m);
//			}
//			InvalidateRect(hWnd, nullptr, false);
//			break;
//		}
//
//		case VK_F5:
//		{
//			if (i != -1)
//			{
//				Model2D m = scene.GetModel(i);
//				m.Apply(Rotation(-M_PI / 6), true);
//				scene.Change(i, m);
//			}
//			InvalidateRect(hWnd, nullptr, false);
//			break;
//		}
//
//		case 0X58: //x отражение относитльно центра по OX
//		{
//			if (i != -1) {
//				Model2D m = scene.GetModel(i);
//				pair<double, double> oxy = m.OXY();
//				m.Apply(Translation(0, -oxy.second), false);
//				m.Apply(MapingX(), false);
//				m.Apply(Translation(0, oxy.second), true);
//				scene.Change(i, m);
//			}
//			InvalidateRect(hWnd, nullptr, false);
//			break;
//		}
//
//		case 0x59://y отражение относитльно центра по OY
//		{
//			if (i != -1) {
//				Model2D m = scene.GetModel(i);
//				pair<double, double> oxy = m.OXY();
//				m.Apply(Translation(-oxy.first, 0), false);
//				m.Apply(MapingY(), false);
//				m.Apply(Translation(oxy.first, 0), true);
//				scene.Change(i, m);
//			}
//			InvalidateRect(hWnd, nullptr, false);
//			break;
//		}
//		case 0X52://h отражение относитльно OX
//		{
//			if (i != -1) {
//				Model2D m = scene.GetModel(i);
//				pair<double, double> oxy = m.OXY();
//				m.Apply(MapingX(), true);
//				scene.Change(i, m);
//			}
//			InvalidateRect(hWnd, nullptr, false);
//			break;
//
//		}
//		case 0x48://r отражение относитльно OY
//		{
//			if (i != -1) {
//				Model2D m = scene.GetModel(i);
//				pair<double, double> oxy = m.OXY();
//				m.Apply(MapingY(), true);
//				scene.Change(i, m);
//			}
//			InvalidateRect(hWnd, nullptr, false);
//			break;
//		}
//		case 0x4F://o отражение относитльно центра координат 
//		{
//			if (i != -1) {
//				Model2D m = scene.GetModel(i);
//				pair<double, double> oxy = m.OXY();
//				m.Apply(Maping0(), true);
//				scene.Change(i, m);
//			}
//			InvalidateRect(hWnd, nullptr, false);
//			break;
//		}
//
//		case 0X42://b увеличение
//		{
//			if (i != -1) {
//				Model2D m = scene.GetModel(i);
//				pair<double, double> oxy = m.OXY();
//				m.Apply(Translation(-oxy.first, -oxy.second), false);
//				m.Apply (Scaling(2,2), false);
//				m.Apply(Translation(oxy.first, oxy.second), true);
//				scene.Change(i, m);
//			}
//			InvalidateRect(hWnd, nullptr, false);
//			break;
//		}
//
//		case 0X53://s уменьшение
//		{
//			if (i != -1) {
//				Model2D m = scene.GetModel(i);
//				pair<double, double> oxy = m.OXY();
//				m.Apply(Translation(-oxy.first, -oxy.second), false);
//				m.Apply(Scaling(0.5, 0.5), false);
//				m.Apply(Translation(oxy.first, oxy.second), true);
//				scene.Change(i, m);
//			}
//			InvalidateRect(hWnd, nullptr, false);
//			break;
//		}
//
//		case VK_F3:
//		{
//			if (i != -1)
//			{
//				Model2D m = scene.GetModel(i);
//				pair<double, double> p = m.GetFirst();
//				m.Apply(Translation(-p.first, -p.second), true);
//				m.Apply(Scaling(0.5, 0.5), false);
//				m.Apply(Translation(p.first, p.second), true);
//				scene.Change(i, m);
//			}
//			InvalidateRect(hWnd, nullptr, false);
//			break;
//		}
//
//		/*case 0X50:
//		{
//
//		Model2D m = scene.GetModel(i);
//				m.Apply(Translation(1,0),false);
//				m.Apply(Rotation(-M_PI/4), false);
//				m.Apply(MapingX(), false);
//				m.Apply(Rotation(M_PI / 4), false);
//				m.Apply(Translation(-1, 0), true);
//				scene.Change(i, m);
//
//
//			if (i != -1) {
//				POINT P;
//				P.x = GET_X_LPARAM(lParam);
//				P.y = GET_Y_LPARAM(lParam);
//				ScreenToClient(hWnd, &P);
//				double x = scene.ScreenToWorldX(P.x);
//				double y = scene.ScreenToWorldY(P.y);
//
//				Model2D m = scene.GetModel(i);
//				m.Apply(Translation(-x, -y), false);
//				m.Apply(Rotation(-M_PI / 6), false);
//				m.Apply(Translation(x,y), true);
//				scene.Change(i, m);
//			}
//			InvalidateRect(hWnd, nullptr, false);
//		}*/
//
//		}
//		
//		return 0;
//	}
//
//	case WM_LBUTTONDOWN:
//	{
//	    i = scene.Inside(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));		
//		scene.StartDraging(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
//		return 0;
//	}
//
//	case WM_MOUSEMOVE:
//	{
//		if (scene.IsDraging())
//		{
//			scene.Draging(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
//			InvalidateRect(hWnd, nullptr, false);
//		}
//		return 0;
//	}
//
//	case WM_LBUTTONUP:
//	{
//		scene.StopDraging();
//		return 0;
//	}
//
//
//	case WM_MOUSEWHEEL:
//	{
//		int delta = GET_WHEEL_DELTA_WPARAM(wParam);
//		POINT P;
//		P.x = GET_X_LPARAM(lParam);
//		P.y = GET_Y_LPARAM(lParam);
//		ScreenToClient(hWnd, &P);
//
//		scene.Mashtab(delta, P.x, P.y);
//		InvalidateRect(hWnd, nullptr, false);
//		return 0;
//	}
//
//	case WM_SIZE:
//	{
//		HDC dc = GetDC(hWnd);
//		scene.SetResolution(dc);
//		ReleaseDC(hWnd, dc);
//		InvalidateRect(hWnd, nullptr, false);
//		return 0;
//	}
//
//	case WM_DESTROY:
//	{
//		PostQuitMessage(0);
//		return 0;
//	}
//
//	default:
//	{
//		return DefWindowProc(hWnd, msg, wParam, lParam);
//	}
//	}
//	return 0;
//}
