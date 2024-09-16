
// HashCalculatorView.h: CHashCalculatorView 클래스의 인터페이스
//

#pragma once


class CHashCalculatorView : public CView
{
protected: // serialization에서만 만들어집니다.
	CHashCalculatorView() noexcept;
	DECLARE_DYNCREATE(CHashCalculatorView)

// 특성입니다.
public:
	CHashCalculatorDoc* GetDocument() const;

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
	virtual ~CHashCalculatorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CStringList m_CstrList;
	afx_msg void OnPaint();
	int m_nLineTab;
};

#ifndef _DEBUG  // HashCalculatorView.cpp의 디버그 버전
inline CHashCalculatorDoc* CHashCalculatorView::GetDocument() const
   { return reinterpret_cast<CHashCalculatorDoc*>(m_pDocument); }
#endif

