#include "stdafx.h"
#include "AppState.h"
#include "MessageNounConditionPane.h"
#include "MessageDoc.h"
#include "Text.h"
#include "Message.h"
#include "CObjectWrap.h"


MessageNounConditionPane::MessageNounConditionPane(CWnd* pParent /*=NULL*/)
    : CExtDialogFwdCmd(IDD, pParent), _hAccel(nullptr)
{
    // Load our accelerators
    // HINSTANCE hInst = AfxFindResourceHandle(MAKEINTRESOURCE(IDR_ACCELERATORPICCOMMANDS), RT_ACCELERATOR);
    // _hAccel = ::LoadAccelerators(hInst, MAKEINTRESOURCE(IDR_ACCELERATORPICCOMMANDS));
}

MessageNounConditionPane::~MessageNounConditionPane()
{
}

void MessageNounConditionPane::DoDataExchange(CDataExchange* pDX)
{
    __super::DoDataExchange(pDX);

    DDX_Control(pDX, IDC_LISTCONDITIONS, m_wndConditions);
    DDX_Control(pDX, IDC_LISTNOUNS, m_wndNouns);
    DDX_Control(pDX, IDC_STATIC1, m_wndLabel1);
    DDX_Control(pDX, IDC_STATIC2, m_wndLabel2);
    DDX_Control(pDX, IDC_BUTTONADDNOUN, m_wndButton1);
    DDX_Control(pDX, IDC_BUTTONADDCONDITION, m_wndButton2);
}


BEGIN_MESSAGE_MAP(MessageNounConditionPane, CExtDialogFwdCmd)
    ON_WM_DRAWITEM()
    ON_WM_CREATE()
    ON_WM_ERASEBKGND()
    ON_BN_CLICKED(IDC_BUTTONADDNOUN, &MessageNounConditionPane::OnBnClickedButtonaddnoun)
    ON_BN_CLICKED(IDC_BUTTONADDCONDITION, &MessageNounConditionPane::OnBnClickedButtonaddcondition)
END_MESSAGE_MAP()

BOOL MessageNounConditionPane::OnEraseBkgnd(CDC *pDC)
{
    return __super::OnEraseBkgnd(pDC);
}


// MessageNounConditionPane message handlers

//
// To properly handle commands we do two things here:
// 1) Process our own accelerators
//      - The main frame's accelerator table doesn't get used in dialogs in control bars,
//        so we need to do our own.  So, e.g. Ctrl-Z becomes ID_EDIT_UNDO
// 2) Fwd any commands we receive to our frame
//      if we don't handle them ourselves.
//      - they don't bubble up naturally in dialogs in control bars.
//      - we do this by inheriting from CExtDialogFwdCmd
//
BOOL MessageNounConditionPane::PreTranslateMessage(MSG* pMsg)
{
    BOOL fRet = FALSE;
    if (_hAccel && (pMsg->message >= WM_KEYFIRST && pMsg->message <= WM_KEYLAST))
    {
        fRet = ::TranslateAccelerator(GetSafeHwnd(), _hAccel, pMsg);
    }
    if (!fRet)
    {
        fRet = __super::PreTranslateMessage(pMsg);
    }
    return fRet;
}

BOOL MessageNounConditionPane::OnInitDialog()
{
    BOOL fRet = __super::OnInitDialog();

    // Set up anchoring for resize
    AddAnchor(IDC_LISTNOUNS, CPoint(0, 0), CPoint(100, 50));
    AddAnchor(IDC_LISTCONDITIONS, CPoint(0, 50), CPoint(100, 100));
    AddAnchor(IDC_STATIC2, CPoint(0, 50), CPoint(100, 50));
    AddAnchor(IDC_BUTTONADDCONDITION, CPoint(100, 50), CPoint(100, 50));
    AddAnchor(IDC_BUTTONADDNOUN, CPoint(100, 0), CPoint(100, 0));
    // Hide the sizing grip
    ShowSizeGrip(FALSE);

    return fRet;
}

void MessageNounConditionPane::UpdateNonView(CObject *pObject)
{
    // TODO: Provide more specific update mechanism
    MessageChangeHint hint = GetHint<MessageChangeHint>(pObject);
    if (IsFlagSet(hint, MessageChangeHint::Changed))
    {
        _Update();
    }
}

void MessageNounConditionPane::_Update()
{
    if (_pDoc)
    {
        m_wndNouns.SetSource(_pDoc->GetNounMessageSource());
        m_wndConditions.SetSource(_pDoc->GetConditionMessageSource());
    }
}

void MessageNounConditionPane::SetDocument(CDocument *pDoc)
{
    _pDoc = static_cast<CMessageDoc*>(pDoc);
    if (_pDoc)
    {
        _pDoc->AddNonViewClient(this);
        _Update();
    }
}

void MessageNounConditionPane::OnBnClickedButtonaddnoun()
{
    if (_pDoc)
    {
        MessageSource *source = _pDoc->GetNounMessageSource();
        if (source)
        {
            // TODO: doc needs to send out a notification? Except it's not undoes.
        }
    }
}

void MessageNounConditionPane::OnBnClickedButtonaddcondition()
{
    if (_pDoc)
    {
        MessageSource *source = _pDoc->GetConditionMessageSource();
        if (source)
        {

        }
    }

}
