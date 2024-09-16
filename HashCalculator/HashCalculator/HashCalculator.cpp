
// HashCalculator.cpp: 응용 프로그램에 대한 클래스 동작을 정의합니다.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "HashCalculator.h"
#include "MainFrm.h"

#include "HashCalculatorDoc.h"
#include "HashCalculatorView.h"

#include <wincrypt.h>
#pragma comment (lib, "crypt32.lib")

#define BUFFERSIZE 4096
#define SHA1LENGTH 20

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHashCalculatorApp

BEGIN_MESSAGE_MAP(CHashCalculatorApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CHashCalculatorApp::OnAppAbout)
	// 표준 파일을 기초로 하는 문서 명령입니다.
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// 표준 인쇄 설정 명령입니다.
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()


// CHashCalculatorApp 생성

CHashCalculatorApp::CHashCalculatorApp() noexcept
	: m_nSha1Length(SHA1LENGTH)
	, m_nBufferSize(BUFFERSIZE)
{
	// 다시 시작 관리자 지원
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// 응용 프로그램을 공용 언어 런타임 지원을 사용하여 빌드한 경우(/clr):
	//     1) 이 추가 설정은 다시 시작 관리자 지원이 제대로 작동하는 데 필요합니다.
	//     2) 프로젝트에서 빌드하려면 System.Windows.Forms에 대한 참조를 추가해야 합니다.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: 아래 응용 프로그램 ID 문자열을 고유 ID 문자열로 바꾸십시오(권장).
	// 문자열에 대한 서식: CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("HashCalculator.AppID.NoVersion"));

	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}

// 유일한 CHashCalculatorApp 개체입니다.

CHashCalculatorApp theApp;


// CHashCalculatorApp 초기화

BOOL CHashCalculatorApp::InitInstance()
{
	// 응용 프로그램 매니페스트가 ComCtl32.dll 버전 6 이상을 사용하여 비주얼 스타일을
	// 사용하도록 지정하는 경우, Windows XP 상에서 반드시 InitCommonControlsEx()가 필요합니다. 
	// InitCommonControlsEx()를 사용하지 않으면 창을 만들 수 없습니다.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 응용 프로그램에서 사용할 모든 공용 컨트롤 클래스를 포함하도록
	// 이 항목을 설정하십시오.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	// OLE 라이브러리를 초기화합니다.
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// RichEdit 컨트롤을 사용하려면 AfxInitRichEdit2()가 있어야 합니다.
	// AfxInitRichEdit2();

	// 표준 초기화
	// 이들 기능을 사용하지 않고 최종 실행 파일의 크기를 줄이려면
	// 아래에서 필요 없는 특정 초기화
	// 루틴을 제거해야 합니다.
	// 해당 설정이 저장된 레지스트리 키를 변경하십시오.
	// TODO: 이 문자열을 회사 또는 조직의 이름과 같은
	// 적절한 내용으로 수정해야 합니다.
	SetRegistryKey(_T("로컬 응용 프로그램 마법사에서 생성된 응용 프로그램"));
	LoadStdProfileSettings(4);  // MRU를 포함하여 표준 INI 파일 옵션을 로드합니다.


	// 응용 프로그램의 문서 템플릿을 등록합니다.  문서 템플릿은
	//  문서, 프레임 창 및 뷰 사이의 연결 역할을 합니다.
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CHashCalculatorDoc),
		RUNTIME_CLASS(CMainFrame),       // 주 SDI 프레임 창입니다.
		RUNTIME_CLASS(CHashCalculatorView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// 표준 셸 명령, DDE, 파일 열기에 대한 명령줄을 구문 분석합니다.
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);




	// 명령줄에 지정된 명령을 디스패치합니다.
	// 응용 프로그램이 /RegServer, /Register, /Unregserver 또는 /Unregister로 시작된 경우 FALSE를 반환합니다.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// 창 하나만 초기화되었으므로 이를 표시하고 업데이트합니다.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

int CHashCalculatorApp::ExitInstance()
{
	//TODO: 추가한 추가 리소스를 처리합니다.
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}

// CHashCalculatorApp 메시지 처리기


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() noexcept;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// 대화 상자를 실행하기 위한 응용 프로그램 명령입니다.
void CHashCalculatorApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CHashCalculatorApp 메시지 처리기





int CHashCalculatorApp::HashGenerateFunction()
{
	// DragQueryFile 함수를 사용해 드랍한 Files의 정보를 얻어오고 갯수를 nFilesCount에 저장합니다.
	int nFilesCount = DragQueryFile(*m_pDropInfo, 0xFFFFFFFF, NULL, 0);
	wchar_t temppath[MAX_PATH];

	CHashCalculatorView *pView = (CHashCalculatorView*)((CFrameWnd*)m_pMainWnd)->GetActiveView();

	unsigned long ulStatus = 0;
	HCRYPTPROV hProv = 0;
	HCRYPTHASH hHash = 0;
	void *pFile = nullptr;
	unsigned char arrFileData[BUFFERSIZE] = { 0 };
	unsigned char arrHashData[SHA1LENGTH] = { 0 };
	unsigned long cbRead = 0;
	unsigned long cbHash = 0;
	LPCWSTR filelocation = nullptr;


	for (int i = 0; i < nFilesCount; ++i)
	{
		// m_pDropInfo가 가리키는 파일중에 i번째 파일의 절대경로를 temppath로 가져옵니다.
		DragQueryFile(*m_pDropInfo, i, temppath, MAX_PATH);
		// temppath는 배열의 이름이므로 filelocation에 담을 수 있습니다.
		filelocation = temppath;

		// 옵션 설정
		pFile = CreateFileW(filelocation, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
		CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT);
		// 압축 알고리즘을 선택합니다.
		// NULL은 key값과 flag 값입니다.
		CryptCreateHash(hProv, CALG_SHA1, NULL, NULL, &hHash);

		// pFile이 가리키는 파일의 내용을 arrFileData에 BUFFERSIZE만큼 입력합니다.
		while (false != ReadFile(pFile, arrFileData, BUFFERSIZE, &cbRead, NULL) )
		{
			// 가져올 값이 남아있지 않으면
			if (0 == cbRead)
				break;

			else
				// 입력된 버퍼를 기반으로 해시를 생성합니다.
				CryptHashData(hHash, arrFileData, cbRead, NULL);
		}

		cbHash = SHA1LENGTH;
		// Hash값을 만들어서 arrFileHash에 저장합니다.
		CryptGetHashParam(hHash, HP_HASHVAL, arrHashData, &cbHash, NULL);

		pView->m_CstrList.AddTail(filelocation);

		CString strHashData;
		CString strTmp;

		for (int i = 0; i < SHA1LENGTH; ++i)
		{
			strTmp.Format(_T("%02X"), arrHashData[i]);
			strHashData += strTmp;
		}
		
		pView->m_CstrList.AddTail(strHashData);

	}

	// hHash를 닫습니다. hHash를 hProv보다 먼저 닫는 이 순서를 꼭 지켜야합니다.
	CryptDestroyHash(hHash);

	// hProv를 닫습니다.
	CryptReleaseContext(hProv, NULL);

	// pFile은 nullptr로 초기화하면 OS의 Hash Table에서 지워지지 않으므로
	// 반드시 CloseHandle 함수를 사용해서 초기화해야 합니다.
	CloseHandle(pFile);

	pView->RedrawWindow();

	return 0;
}
