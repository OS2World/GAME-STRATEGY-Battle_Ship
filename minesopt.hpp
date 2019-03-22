// minesopt.h : header file
//

#ifndef __MINESOPT_H__
#define __MINESOPT_H__

#include "battle.h"
/////////////////////////////////////////////////////////////////////////////
// CMinesOptionDlg dialog

class CMinesOptionDlg : public CDialog
{
// Construction
public:
   CMinesOptionDlg(CBattleView* pParent = NULL); // standard constructor

// Dialog Data
   //{{AFX_DATA(CMinesOptionDlg)
   enum { IDD = IDD_MINESOPTION };
   int      m_nNumMines;
   BOOL  m_LayMines;
   //}}AFX_DATA

// Attributes
private:
   CBattleView*  m_pParent;
   
// Implementation
protected:
   virtual void DoDataExchange(CDataExchange* pDX);   // DDX/DDV support

   // Generated message map functions
   //{{AFX_MSG(CMinesOptionDlg)
   virtual BOOL OnInitDialog();
   virtual void OnOK();
   afx_msg void OnMinesChecked();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};
#endif

