
// MFC_201014_02View.cpp: CMFC20101402View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFC_201014_02.h"
#endif

#include "MFC_201014_02Doc.h"
#include "MFC_201014_02View.h"

#include <mmsystem.h>
#pragma comment(lib, "winmm")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFC20101402View

IMPLEMENT_DYNCREATE(CMFC20101402View, CView)

BEGIN_MESSAGE_MAP(CMFC20101402View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_VacationFire, &CMFC20101402View::OnVacationfire)
	ON_WM_MBUTTONDOWN()
	ON_COMMAND(ID_PowerUp, &CMFC20101402View::OnPowerup)
	ON_COMMAND(ID_PowerDown, &CMFC20101402View::OnPowerdown)
	ON_COMMAND(ID_AngleDown, &CMFC20101402View::OnAngledown)
	ON_COMMAND(ID_AngleUp, &CMFC20101402View::OnAngleup)
END_MESSAGE_MAP()

// CMFC20101402View 생성/소멸

CMFC20101402View::CMFC20101402View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMFC20101402View::~CMFC20101402View()
{
}

BOOL CMFC20101402View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMFC20101402View 그리기

void CMFC20101402View::OnDraw(CDC* pDC)
{
	CMFC20101402Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	DrawBackground(pDC);
}


// CMFC20101402View 인쇄

BOOL CMFC20101402View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFC20101402View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFC20101402View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMFC20101402View 진단

#ifdef _DEBUG
void CMFC20101402View::AssertValid() const
{
	CView::AssertValid();
}

void CMFC20101402View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFC20101402Doc* CMFC20101402View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFC20101402Doc)));
	return (CMFC20101402Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFC20101402View 메시지 처리기

#define GROUND 50




void CMFC20101402View::OnVacationfire()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	MessageBox(L"당신의 휴가, \n대포동 미사일로 대체되었다.");

	int x = 0, y = 0;
	static bool Playing = false;
	CMFC20101402Doc* pDoc = GetDocument();

	int a = pDoc->GetAngle();
	int p = pDoc->GetPower();

	if (!Playing)
	{
		//PlaySound(TEXT("military.wav"), NULL, SND_LOOP | SND_ASYNC);
		Playing = true;
	}
		

	CRect rect;
	GetClientRect(&rect);

	CClientDC dc(this);
	

	for (int t = 0; t < 100; t++)
	{
		CalculateCoordinate(a, p, t, &x, &y);
		y = rect.bottom - y - GROUND;
		if (y > rect.bottom - GROUND)
			break;

		dc.Ellipse(x - 30, y - 30, x + 30, y + 30);

		Sleep(30);
		DrawBackground(&dc);
	}

}

void CMFC20101402View::CalculateCoordinate
	(int angle, int power, int t, int* x, int* y)
{
	const double g = 9.8;
	const double pi = 3.141592;

	double theta = angle * pi / 180.;
	double v0 = (double)power;

	*x = (int)(v0 * t * cos(theta));
	*y = (int)(v0 * t * sin(theta) - g * t * t / 2.);
}

void CMFC20101402View::DrawBackground(CDC* pDC)
{
	CRect rect;
	
	GetClientRect(&rect);
	CClientDC dc(this);

	CMFC20101402Doc* pDoc = GetDocument();

	CString str;

	dc.FillSolidRect(rect, RGB(0, 80, 0));

	str.Format(L"Angle = %d, Power = %d", pDoc->GetAngle(), pDoc->GetPower());
	pDC->TextOutW(10, 10, str);

	pDC->MoveTo(rect.left, rect.bottom - GROUND);
	pDC->LineTo(rect.right, rect.bottom - GROUND);
	
	
}

void CMFC20101402View::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

}


void CMFC20101402View::OnPowerup()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFC20101402Doc* pDoc = GetDocument();
	CClientDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	
	pDoc->AddPower();

	DrawBackground(&dc);
}


void CMFC20101402View::OnPowerdown()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFC20101402Doc* pDoc = GetDocument();
	CClientDC dc(this);
	CRect rect;
	GetClientRect(&rect);

	if (pDoc->GetPower() > 0)
		pDoc->MinPower();

	DrawBackground(&dc);
}


void CMFC20101402View::OnAngledown()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFC20101402Doc* pDoc = GetDocument();
	CClientDC dc(this);
	CRect rect;
	GetClientRect(&rect);

	if (pDoc->GetAngle() > 1)
		pDoc->MinAngle();

	DrawBackground(&dc);
}


void CMFC20101402View::OnAngleup()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFC20101402Doc* pDoc = GetDocument();
	CClientDC dc(this);
	CRect rect;
	GetClientRect(&rect);

	if (pDoc->GetAngle() < 90)
		pDoc->AddAngle();

	DrawBackground(&dc);
}
