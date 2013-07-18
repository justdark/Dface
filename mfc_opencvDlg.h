
// mfc_opencvDlg.h : 头文件
//

#pragma once
#include <opencv2\opencv.hpp>
#include <iostream>
#include <string>
#include "opencv\cv.h"
#include "opencv\highgui.h"
#include "facedect.h"
#include "CvvImage.h"
using namespace cv;
using namespace std;

#include "windows.h"
#include "tlhelp32.h"
void CloseProgram(CString strProgram)
{
    HANDLE handle; //定义CreateToolhelp32Snapshot系统快照句柄 
    HANDLE handle1; //定义要结束进程句柄 
    handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);//获得系统快照句柄 
    PROCESSENTRY32 *info; //定义PROCESSENTRY32结构字指 
    //PROCESSENTRY32 结构的 dwSize 成员设置成 sizeof(PROCESSENTRY32) 

    info = new PROCESSENTRY32; 
    info->dwSize = sizeof(PROCESSENTRY32); 
    //调用一次 Process32First 函数，从快照中获取进程列表 
    Process32First(handle, info); 
    //重复调用 Process32Next，直到函数返回 FALSE 为止 
    while(Process32Next(handle, info) != FALSE) 
    {   
        CString strTmp = info->szExeFile;     //指向进程名字   
        //strcmp字符串比较函数同要结束相同   
        //if(strcmp(c, info->szExeFile) == 0 )   
        if (strProgram.CompareNoCase(info->szExeFile) == 0 )   
        {   
            //PROCESS_TERMINATE表示为结束操作打开,FALSE=可继承,info->th32ProcessID=进程ID    
            handle1 = OpenProcess(PROCESS_TERMINATE, FALSE, info->th32ProcessID); 
            //结束进程    
            TerminateProcess(handle1, 0);    
        }   
    }
    delete info;

    CloseHandle(handle);
}

// Cmfc_opencvDlg 对话框

class Cmfc_opencvDlg : public CDialogEx
{
// 构造

public:
	Cmfc_opencvDlg(CWnd* pParent = NULL);	// 标准构造函数
	void OnClose()
	{
		
		CloseProgram(_T("mfc_opencv.exe"));
		CDialogEx::OnClose();
	}
// 对话框数据
	enum { IDD = IDD_MFC_OPENCV_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持



 



// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
};

static CvHaarClassifierCascade* cascade = 0;
const char* cascade_name = 
"haarcascade_frontalface_alt.xml"; 

 double scale=2; 
    static CvScalar colors[] = { 
        {{0,0,255}},{{0,128,255}},{{0,255,255}},{{0,255,0}}, 
        {{255,128,0}},{{255,255,0}},{{255,0,0}},{{255,0,255}} 
    };//Just some pretty colors to draw with



 