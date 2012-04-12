#ifndef INC_DIALOGFORMULASCINTILLA_H
#define INC_DIALOGFORMULASCINTILLA_H

#include "ScintillaWnd.h"
#include "WinMgr.h"
#include "SizerBar.h"
#include "CGrammar.h"


// CDlgFormulaScintilla dialog
#define	MENU_UPDATE_TIMER		1
#define	DEBUG_UPDATE_TIMER		2

#define	EDIT_NEW				0
#define	EDIT_RENAME				1
#define	EDIT_DELETE				2
//separator						3
#define	EDIT_UNDO				4
#define	EDIT_REDO				5
//separator						6
#define	EDIT_FIND				7
#define	EDIT_FIND_NEXT			8
#define	EDIT_FIND_PREV			9
//separator						10
#define	EDIT_CUT				11
#define	EDIT_COPY				12
#define	EDIT_PASTE				13
#define	EDIT_DELETE_TEXT		14
//separator						15
#define	EDIT_SELECTALL			16
//separator						17
#define	EDIT_FONT				18
#define	EDIT_SETTINGS			19
#define	EDIT_HANDLIST			20

#define DEBUG_FDEBUG_LOGGING	0
#define DEBUG_FDEBUG_MYTURN		1

#define SCE_C_DEFAULT 0
#define SCE_C_COMMENT 1
#define SCE_C_COMMENTLINE 2
#define SCE_C_COMMENTDOC 3
#define SCE_C_NUMBER 4
#define SCE_C_WORD 5
#define SCE_C_STRING 6
#define SCE_C_CHARACTER 7
#define SCE_C_UUID 8
#define SCE_C_PREPROCESSOR 9
#define SCE_C_OPERATOR 10
#define SCE_C_IDENTIFIER 11
#define SCE_C_STRINGEOL 12
#define SCE_C_VERBATIM 13
#define SCE_C_REGEX 14
#define SCE_C_COMMENTLINEDOC 15
#define SCE_C_WORD2 16
#define SCE_C_COMMENTDOCKEYWORD 17
#define SCE_C_COMMENTDOCKEYWORDERROR 18
#define SCE_C_GLOBALCLASS 19
#define MAX_STYLE_NUM 19

class CScintillaInfo
{
public:
	CScintillaInfo() { _pWnd = NULL; }
	CScintillaInfo(CScintillaWnd *pWnd, const char *name) { _pWnd = pWnd; _name = name; }
	CScintillaInfo(const CScintillaInfo &in) { operator=(in); }

	CScintillaInfo &operator=(const CScintillaInfo &in) { _pWnd = in._pWnd; _name = in._name; return *this; }

public:
	CScintillaWnd *_pWnd;
	CString _name;
};

class CDlgFormulaScintilla : public CDialog 
{
public:
	CDlgFormulaScintilla(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgFormulaScintilla();
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual BOOL DestroyWindow();
	void UpdateDebugAuto(void);

	enum { IDD = IDD_FORMULA_SCINTILLA };
	
	CScintillaWnd	m_EmptyScinCtrl;
	CArray<CScintillaInfo, CScintillaInfo &> m_ScinArray;
	CScintillaWnd	*m_pActiveScinCtrl;
	CScintillaWnd	*FindScintillaWindow(const char *name);

	CButton			m_ButtonAuto;
	bool			m_wrote_fdebug_header;
	bool			m_dirty;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void PostNcDestroy();
	afx_msg void OnBnClickedApply();
	afx_msg void OnBnClickedApplySave();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCalc();
	afx_msg void OnNew();
	afx_msg void OnRename();
	afx_msg void OnDelete();
	afx_msg void OnFont();
	afx_msg void OnHandList();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnWinMgr(WPARAM wp, LPARAM lp);
	afx_msg void OnTvnSelchangingFormulaTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSelchangedFormulaTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnExpandedFormulaTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTabSelectionChange(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnFunctionTabSelectionChange(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSymbolTreeTipInfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTreeContextMenu(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCancel();
	afx_msg void OnSearchUpdate();
	afx_msg void OnBnClickedLessPrecision();
	afx_msg void OnBnClickedMorePrecision();
	afx_msg void OnBnClickedEqualLeft();
	afx_msg void OnBnClickedEqualRight();
	afx_msg void OnBnClickedAuto();
	afx_msg void OnToggleBookmark();
	afx_msg void OnNextBookmark();
	afx_msg void OnPrevBookmark();
	afx_msg BOOL OnToolTipText(UINT nID, NMHDR* pNMHDR, LRESULT* pResult); 
	void CreateDebugTab(CString *cs);
	void WriteFDebugLog(bool write_header);
	void InitDebugArray(void);
	void ResizeDialogForControlBars(void);
	void LastChangeToFormula(CFormula *f);
	afx_msg void OnEditUndo();
	afx_msg void OnEditRedo();
	afx_msg void OnEditCopy();
	afx_msg void OnEditCut();
	afx_msg void OnEditPaste();
	afx_msg void OnEditDeleteText();
	afx_msg void OnEditSelectAll();
	afx_msg void OnFormulaDebugLogfdebug();
	afx_msg void OnFormulaDebugMyturn();
	afx_msg void OnHelp();
	afx_msg void OnHelpWiki();
	afx_msg void OnHelpForums();
	void SortUdfTree();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	void OnTimer(UINT nIDEvent);
	void SaveSettingsToRegistry();
	void SetStyleColors(CScintillaWnd *pWnd, bool enabled);

	BOOL CDlgFormulaScintilla::PreTranslateMessage(MSG* pMsg);
	CScintillaWnd *SetupScintilla(CScintillaWnd *pWnd, const char *title);
	void UpdateAllScintillaKeywords();
	void ConstructKeywords(CString &keys);
	void UpdateScintillaKeywords(CScintillaWnd *pWnd);
	void DeleteScintilla(CScintillaWnd *pWnd);

	// Support Functions for the Dialog
	void StopAutoButton();
	bool PromptToSave();
	void ResizeScintillaWindows();
	void SelectFunctionTab(CScintillaWnd *pCurScin);

	void PopulateSymbols();
	HTREEITEM AddSymbolTitle(const char *title, const char *description=NULL, HTREEITEM parentItem=NULL);
	HTREEITEM AddSymbolSubTitle(HTREEITEM parentItem, const char *title, const char *description=NULL);
	HTREEITEM AddSymbol(HTREEITEM parentItem, const char *symbol, const char *description);
	HTREEITEM hRawItem, hCatItem;

	void	  PopulateFormulaTree();
	void	  ConditionallyAddFunction(const CString &name, const CString &content, const CString &filter, HTREEITEM hParent);
	HTREEITEM FindUDFGroupItem(const char *groupName);
	HTREEITEM FindUDFStartingItem(const char *groupName);
	HTREEITEM MoveTreeItem(HTREEITEM hItem, HTREEITEM hNewParent, const char *name, bool bSelect);
	HTREEITEM FindFormulaWithWindow(const CScintillaWnd *pWnd, HTREEITEM hFirstItem);
	void	  GetGroupName(const char *functionName, CString &groupName);
	void	  RemoveSingleItemGroups();
	void	  GroupUDFs();
	void	  UngroupUDFs();
	HTREEITEM hUDFItem;

	void HandleEnables(bool All);

	// Find/Replace Support Functions and Variables
	afx_msg void OnFindReplaceDlg();
	afx_msg LONG OnFindReplace(WPARAM wParam, LPARAM lParam);
	afx_msg void OnFindNext();
	afx_msg void OnFindPrev();
			void CloseFindReplaceDialog();

			void DoFind(bool DirDown);

	CFindReplaceDialog *m_pFRDlg;
	CString			m_FindLastSearch;
	bool			m_FindWholeWord;
	bool			m_FindMatchCase;

	CMenu			m_Menu;
	CToolBar		m_toolBar;
	CStatusBar		m_wndStatusBar;
	CTreeCtrl		m_FormulaTree;
	CTreeCtrl		m_SymbolTree;
	CButton			m_ButtonCalc, m_FormulaCancel, m_FormulaApply, m_FormulaOK;
	CEdit			m_CalcResult;
	CEdit			m_SearchEdit;
	CWinMgr			m_winMgr;				// window manager
	CSizerBar		m_winMgrSizerBar;		// sizer bar
	CTabCtrl		m_TabControl;
	CTabCtrl		m_FunctionTab;

	HACCEL			m_hEditAccelTable;
	HACCEL			m_hDialogAccelTable;

	int				m_precision, m_equal;	// precision for debug tab
	bool			m_fdebuglog, m_fdebuglog_myturn;

	CString			m_current_edit;			// Name of formula currently in edit window
	CArray <SDebugTabInfo, SDebugTabInfo> debug_ar;		// holds debug tab information
	CFont			editfont;
	bool			in_startup;
	bool			ok_to_update_debug;

	// This is the copy of the formula class that is being worked on in the dialog
	CFormula		m_wrk_formula;

	CStringArray	m_standard_headings;
	bool			m_standard_expand[3];
	CStringArray	m_standard_functions[3];

	// This is used for formula parsing and evaluation
	CGrammar		gram;

	DECLARE_MESSAGE_MAP()

private:
	bool WriteProfileFont(LPCTSTR lpszKey, LPCTSTR lpszVal, CFont& font, CDC* pDC=NULL);
	bool GetProfileFont(LPCTSTR lpszKey, LPCTSTR lpszVal, CFont& font, CDC* pDC=NULL);
	CString ExtractCommentFromHandList(CString HandListAsString);
	void WarnAboutAutoplayerWhenApplyingFormulaAndTurnAutoplayerOff();
};

extern CDlgFormulaScintilla	*m_formulaScintillaDlg;


#endif //INC_DIALOGFORMULASCINTILLA_H