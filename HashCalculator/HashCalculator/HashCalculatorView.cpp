
// HashCalculatorView.cpp: CHashCalculatorView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "HashCalculator.h"
#endif

#include "HashCalculatorDoc.h"
#include "HashCalculatorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHashCalculatorView

IMPLEMENT_DYNCREATE(CHashCalculatorView, CView)

BEGIN_MESSAGE_MAP(CHashCalculatorView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_DROPFILES()
	ON_WM_CREATE()
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CHashCalculatorView 생성/소멸

CHashCalculatorView::CHashCalculatorView() noexcept
	: m_nLineTab(30)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CHashCalculatorView::~CHashCalculatorView()
{
}

BOOL CHashCalculatorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CHashCalculatorView 그리기

void CHashCalculatorView::OnDraw(CDC* /*pDC*/)
{
	CHashCalculatorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CHashCalculatorView 인쇄

BOOL CHashCalculatorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CHashCalculatorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CHashCalculatorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CHashCalculatorView 진단

#ifdef _DEBUG
void CHashCalculatorView::AssertValid() const
{
	CView::AssertValid();
}

void CHashCalculatorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHashCalculatorDoc* CHashCalculatorView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHashCalculatorDoc)));
	return (CHashCalculatorDoc*)m_pDocument;
}
#endif //_DEBUG


// CHashCalculatorView 메시지 처리기


void CHashCalculatorView::OnDropFiles(HDROP hDropInfo)
{
	// CApp에서 작업하기 위해 주소를 담습니다.
	theApp.m_pDropInfo = &hDropInfo;

	theApp.HashGenerateFunction();

	CView::OnDropFiles(hDropInfo);
}


int CHashCalculatorView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// View Window에 파일을 드랍할 수 있게 설정하는 함수입니다.
	// 한 번만 호출하면 드랍이 가능한 상태가 계속됩니다.
	DragAcceptFiles();

	return 0;
}


void CHashCalculatorView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CView::OnPaint()을(를) 호출하지 마십시오.

	POSITION pos;

	pos = m_CstrList.GetHeadPosition();

	for (int i = 0; i < m_CstrList.GetCount(); ++i)
	{
		dc.TextOutW(30, m_nLineTab, (CString)m_CstrList.GetNext(pos));
		//m_nLineTab += 50;
		m_nLineTab += 30;
	}

	m_nLineTab = 30;
}
