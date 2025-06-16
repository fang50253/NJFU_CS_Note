// #include "pch.h"
// #include "framework.h"
// #include "YourApp.h"
// #include "YourAppDlg.h"
// #include "afxdialogex.h"
#include <map>
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

class CYourAppDlg : public CDialogEx
{
public:
    CYourAppDlg(CWnd* pParent = nullptr);
    std::map<std::string, std::string> studentInfo;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    DECLARE_MESSAGE_MAP()

public:
    afx_msg void OnBnClickedAdd();
    afx_msg void OnBnClickedSearch();
};

BEGIN_MESSAGE_MAP(CYourAppDlg, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_ADD, &CYourAppDlg::OnBnClickedAdd)
    ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CYourAppDlg::OnBnClickedSearch)
END_MESSAGE_MAP()

CYourAppDlg::CYourAppDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_YOURAPP_DIALOG, pParent)
{}

void CYourAppDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

void CYourAppDlg::OnBnClickedAdd()
{
    CString strId, strName;
    GetDlgItemText(IDC_EDIT_ID, strId);
    GetDlgItemText(IDC_EDIT_NAME, strName);

    if (strId.IsEmpty() || strName.IsEmpty())
    {
        MessageBox(_T("学号或姓名不能为空！"), _T("错误"), MB_ICONERROR);
        return;
    }

    studentInfo[std::string(CT2A(strId))] = std::string(CT2A(strName));
    MessageBox(_T("学生信息添加成功！"), _T("成功"), MB_ICONINFORMATION);
}

void CYourAppDlg::OnBnClickedSearch()
{
    CString strSearchId;
    GetDlgItemText(IDC_EDIT_SEARCH_ID, strSearchId);

    if (strSearchId.IsEmpty())
    {
        MessageBox(_T("请输入要查询的学号！"), _T("错误"), MB_ICONERROR);
        return;
    }

    auto it = studentInfo.find(std::string(CT2A(strSearchId)));
    if (it != studentInfo.end())
    {
        CString result;
        result.Format(_T("姓名：%s"), CA2T(it->second.c_str()));
        SetDlgItemText(IDC_STATIC_RESULT, result);
    }
    else
    {
        SetDlgItemText(IDC_STATIC_RESULT, _T("未找到该学号的学生信息！"));
    }
}