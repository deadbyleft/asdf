
// MFC_201014_02View.h: CMFC20101402View 클래스의 인터페이스
//

#pragma once


class CMFC20101402View : public CView
{
protected: // serialization에서만 만들어집니다.
	CMFC20101402View() noexcept;
	DECLARE_DYNCREATE(CMFC20101402View)

// 특성입니다.
public:
	CMFC20101402Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMFC20101402View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnVacationfire();
	void CalculateCoordinate(int angle, int power, int t,
		int* x, int* y);
	void DrawBackground(CDC* pDC);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPowerup();
	afx_msg void OnPowerdown();
	afx_msg void OnAngledown();
	afx_msg void OnAngleup();
};

#ifndef _DEBUG  // MFC_201014_02View.cpp의 디버그 버전
inline CMFC20101402Doc* CMFC20101402View::GetDocument() const
   { return reinterpret_cast<CMFC20101402Doc*>(m_pDocument); }
#endif

