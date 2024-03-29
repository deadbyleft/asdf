﻿
// MFC_201014_02Doc.h: CMFC20101402Doc 클래스의 인터페이스
//


#pragma once


class CMFC20101402Doc : public CDocument
{
protected:
	int Angle = 70;
	int Power = 80;

public:
	int GetAngle() { return Angle; }
	int GetPower() { return Power; }

	int AddPower() { return Power++; }
	int MinPower() { return Power--; }

	int AddAngle() { return Angle++; }
	int MinAngle() { return Angle--; }
protected: // serialization에서만 만들어집니다.
	CMFC20101402Doc() noexcept;
	DECLARE_DYNCREATE(CMFC20101402Doc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void OnPowerup();
	virtual void OnPowerDown();
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CMFC20101402Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
