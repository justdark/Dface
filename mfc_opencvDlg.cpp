
// mfc_opencvDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "mfc_opencv.h"
#include "mfc_opencvDlg.h"
#include "afxdialogex.h"
#include <opencv2\opencv.hpp>
#include <iostream>
#include <string>
#include "opencv\cv.h"
#include "opencv\highgui.h"
#include <shlwapi.h>
#pragma comment(lib,"Shlwapi.lib")
#include "CvvImage.h"
using namespace cv;
using namespace std;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}



void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cmfc_opencvDlg 对话框





Cmfc_opencvDlg::Cmfc_opencvDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cmfc_opencvDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cmfc_opencvDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Cmfc_opencvDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &Cmfc_opencvDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Cmfc_opencvDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &Cmfc_opencvDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &Cmfc_opencvDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &Cmfc_opencvDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// Cmfc_opencvDlg 消息处理程序

BOOL Cmfc_opencvDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Cmfc_opencvDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Cmfc_opencvDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Cmfc_opencvDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
static CvMemStorage* storage = 0; 
char * cs2ca(CString str)
{
	char *ptr;
	#ifdef _UNICODE
	LONG len;
	len = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
	ptr = new char [len+1];
	memset(ptr,0,len + 1);
	WideCharToMultiByte(CP_ACP, 0, str, -1, ptr, len + 1, NULL, NULL);
	#else
	ptr = new char [str.GetAllocLength()+1];
	sprintf(ptr,_T("%s"),str);
	#endif
	return ptr;
}
void DrawPicToHDC(Cmfc_opencvDlg* q,IplImage *image, UINT ID)
	 {
		CDC *pDC = q->GetDlgItem(ID)->GetDC();
		HDC hDC=  pDC->GetSafeHdc();
		CRect rect;
		q->GetDlgItem(ID)->GetClientRect(&rect);
		CvvImage cimg;       //只有CvvImage类的图像才有下面的DrawToHDC函数
		cimg.CopyOf(image,3);
		cimg.DrawToHDC(hDC,&rect);
		q->ReleaseDC(pDC);
		cimg.Destroy();
		}
CvSize dst_cvsize=(cvSize(100,100));   //目标图像尺寸

IplImage* save_file=cvCreateImage( dst_cvsize, IPL_DEPTH_8U, 3);
#include <fstream>
#include <sstream>
string num2str(int i)
{
        stringstream ss;
        ss<<i;
        return ss.str();
}
CString get_words(int index)
{


	CString strText;
	CStringA str;
	strText.Format(_T("C:\\Users\\Darkscope\\Desktop\\face\\%d.ini"),index);
	CFile fFile(strText,CFile::modeRead);  
	fFile.Read(str.GetBufferSetLength(fFile.GetLength()),fFile.GetLength());
	fFile.Close();  
	str.ReleaseBuffer();  
	return CString(str);
}
int get_index()
{
	ifstream in;
	in.open("C:\\Users\\Darkscope\\Desktop\\face\\access.ini");
	int k=0;
	in>>k;
	in.close();
	return k;
}
#define NUM_EIGENFACES 10
#define HEIGHT		 100
#define WIDTH			100
#define PCA_MEAN    "mean"
#define PCA_EIGEN_VECTOR    "eigen_vector" 
void pca_make_eigen()
{	/*
	  to prepare the need for svd recognize
	*/
	int index=get_index();
	Mat SampleSet(index, 100*100, CV_32FC1);  
	CString cs;
	for (int s=0; s<index; ++s)  
    {   cs.Format(_T("C:\\Users\\Darkscope\\Desktop\\face\\%d.jpg"),s);
		IplImage *img = cvLoadImage(cs2ca(cs));  
        IplImage *img_g = cvCreateImage(cvSize(img->width,img->height),IPL_DEPTH_8U, 1);  
        cvCvtColor(img, img_g, CV_BGR2GRAY);//Change it to gray level  
        Mat frame(img_g);  
        for (int row=0; row<img->height; ++row)  
        {  
            for (int col=0; col<img->width; ++col)  
            {  
                float f = (float)(frame.at<uchar>(row, col));  
                SampleSet.at<float>(s, (row*(img->width) + col) ) = f;  
            }  
        }  
        cvReleaseImage(&img);  
        cvReleaseImage(&img_g);  
    }  
	PCA *pca = new PCA(SampleSet, Mat(), CV_PCA_DATA_AS_ROW);
	
	int c_index=0;    
    float sum=0, sum0=0, ratio;    
    for (int d=0; d<pca->eigenvalues.rows; ++d)    
    {    
        sum += pca->eigenvalues.at<float>(d,0);    
    }    
    for (int d=0; d<pca->eigenvalues.rows; ++d)    
    {    
        sum0 += pca->eigenvalues.at<float>(d,0);    
        ratio = sum0/sum;    
        if(ratio > 0.9){  //0.9 is the threshold  
            c_index = d;    
            break;    
        }    
    }    
    Mat eigenvetors_d;    
    eigenvetors_d.create((c_index+1), WIDTH*HEIGHT, CV_32FC1);//eigen values of decreased dimension    
    for (int i=0; i<(c_index+1); ++i)    
    {    
        pca->eigenvectors.row(i).copyTo(eigenvetors_d.row(i));    
    }    
    //cout << "eigenvectors" <<endl << eigenvetors_d << endl;    
    FileStorage fs_w("C:\\Users\\Darkscope\\Desktop\\face\\config.xml", FileStorage::WRITE);//write mean and eigenvalues into xml file    
    fs_w << PCA_MEAN << pca->mean;    
    fs_w << PCA_EIGEN_VECTOR << eigenvetors_d;    
    fs_w.release();    
	delete pca;  
   
}
bool flag=0;
int index;
PCA *pca_encoding;
Mat SampleSet;
CString cs;
Mat encoded;

void prepare()
{
    index=get_index();
	pca_encoding = new PCA();  //Read config  
    SampleSet=Mat(index, 100*100, CV_32FC1);  
	for (int s=0; s<index; ++s)  
    {   cs.Format(_T("C:\\Users\\Darkscope\\Desktop\\face\\%d.jpg"),s);
		IplImage *img = cvLoadImage(cs2ca(cs));  
        IplImage *img_g = cvCreateImage(cvSize(img->width,img->height),IPL_DEPTH_8U, 1);  
        cvCvtColor(img, img_g, CV_BGR2GRAY);//Change it to gray level  
        Mat frame(img_g);  
        for (int row=0; row<img->height; ++row)  
        {  
            for (int col=0; col<img->width; ++col)  
            {  
                float f = (float)(frame.at<uchar>(row, col));  
                SampleSet.at<float>(s, (row*(img->width) + col) ) = f;  
            }  
        }  
        cvReleaseImage(&img);  
        cvReleaseImage(&img_g);  
    }  
    FileStorage fs_r("C:\\Users\\Darkscope\\Desktop\\face\\config.xml", FileStorage::READ);    
    fs_r[PCA_MEAN] >> pca_encoding->mean;    
    fs_r[PCA_EIGEN_VECTOR] >> pca_encoding->eigenvectors;    
    fs_r.release();    
	encoded=Mat(index, pca_encoding->eigenvectors.rows, CV_32FC1);  
    for (int s=0; s<index; ++s)  
    {  
        Mat in = SampleSet.row(s);  
        Mat out = encoded.row(s);  
        //pca->project(in, out);  
        pca_encoding->project(in, out);  
        
    }  
}
int  pca_detect(IplImage *img_test)
{
	
	if (!flag)
	{
		prepare();
		flag=1;
	}

	IplImage *img_test_g = cvCreateImage(cvSize(img_test->width,img_test->height),IPL_DEPTH_8U, 1);  
	cvCvtColor(img_test, img_test_g, CV_BGR2GRAY);
	Mat mat_img(img_test_g);//input  
    Mat mat_test(1, HEIGHT*WIDTH, CV_32FC1);  
	for (int row=0; row<HEIGHT; ++row)  
    {  
        for (int col=0; col<WIDTH; ++col)  
        {  
            float f = (float)(mat_img.at<uchar>(row, col));  
            mat_test.at<float>(0, (row*(WIDTH) + col) ) = f;  
        }  
    }  
    Mat encoded_test(1, pca_encoding->eigenvectors.rows, CV_32FC1);  
    pca_encoding->project(mat_test, encoded_test);  
   // cvReleaseImage(&img_test);  
    cvReleaseImage(&img_test_g);

	float min_sum = CV_MAX_ALLOC_SIZE;  
    int min_index;  
    for (int s=0; s<index; ++s)  
    {  
        float sum=0;  
        for (int e=0; e<pca_encoding->eigenvectors.rows; ++e)  
        {  
            float fs = encoded.at<float>(s,e);  
            float fi = encoded_test.at<float>(0,e);  
            sum += ((fs-fi)*(fs-fi));  
        }  
        if(sum < min_sum){  
            min_sum = sum;  
            min_index = s;  
        }  
       
    }  
	/*
	 reuturn the index of the most similar face for the given img.
	*/
 
	return min_index;
}
void save_face(Cmfc_opencvDlg* D,IplImage* img, CvRect *face, double scale)
{
	assert(img!=NULL);
	assert(face!=NULL);
	IplImage* pimg=cvCreateImage(cvSize(img->width,img->height),img->depth,img->nChannels);
	cvCopy(img,pimg);

	cvSetImageROI(
			pimg,
			cvRect(
				face->x *scale,            /* x = start from leftmost */
				face->y *scale,
				face->width *scale,
				face->height *scale
			)
		);
	IplImage *dst = 0;
		//save as 704 * 576 image
   //目标图像指针

		dst = cvCreateImage( dst_cvsize, pimg->depth, pimg->nChannels); //构造目标图象
		cvResize(pimg, dst, CV_INTER_LINEAR); //缩放源图像到目标图像
		cvCopy(dst,save_file);

		cvReleaseImage(&pimg);
		DrawPicToHDC(D,dst,IDC_FACE);
				cvReleaseImage(&dst);

}



 void detect_and_draw(Cmfc_opencvDlg* D,IplImage* img ) 
{ 
   
	//Image Preparation 
	// 
	IplImage* gray = cvCreateImage(cvSize(img->width,img->height),8,1); 
	IplImage* small_img=cvCreateImage(
		cvSize(cvRound(img->width/scale),cvRound(img->height/scale))
		,8
		,1); 

	cvCvtColor(img,gray, CV_BGR2GRAY); 
	cvResize(gray, small_img, CV_INTER_LINEAR);

	cvEqualizeHist(small_img,small_img); //直方图均衡

	//Detect objects if any 
	// 
	cvClearMemStorage(storage); 
	double t = (double)cvGetTickCount(); 
	CvSeq* objects = cvHaarDetectObjects(small_img, 
														 cascade, 
														 storage, 
														 1.1, 
														 2, 
														 0/*CV_HAAR_DO_CANNY_PRUNING*/, 
														 cvSize(30,30));

	t = (double)cvGetTickCount() - t; 
	//Loop through found objects and draw boxes around them 
	for(int i=0;i<(objects? objects->total:0);++i) 
	{ 
		CvRect* r=(CvRect*)cvGetSeqElem(objects,i); 
		save_face(D,img,r,scale);
		cvRectangle(img, cvPoint(r->x*scale,r->y*scale), cvPoint((r->x+r->width)*scale,(r->y+r->height)*scale), colors[i%8]); 
		
	} 
	for( int i = 0; i < (objects? objects->total : 0); i++ ) 
	{ 
		CvRect* r = (CvRect*)cvGetSeqElem( objects, i ); 
		CvPoint center; 
		int radius; 
		center.x = cvRound((r->x + r->width*0.5)*scale); 
		center.y = cvRound((r->y + r->height*0.5)*scale); 
		radius = cvRound((r->width + r->height)*0.25*scale); 
		cvCircle( img, center, radius, colors[i%8], 3, 8, 0 ); 
	}
	cvReleaseImage(&gray);
	cvReleaseImage(&small_img);
}
 void control_mouse(Cmfc_opencvDlg* D)
 {
	 	CButton* pBtn = (CButton*)D->GetDlgItem(IDC_CHECK1);
		int state = pBtn->GetCheck();
		if (state==0)
			return;
	 	int t=pca_detect(save_file);
		POINT pp;
		GetCursorPos(&pp);
		switch (t)
		{
		case 1:SetCursorPos(pp.x-15, pp.y);
	           break;
		case 2:SetCursorPos(pp.x+15, pp.y);
	           break;
		case 3:SetCursorPos(pp.x, pp.y-15);
	           break;
		case 5:SetCursorPos(pp.x, pp.y-15);
	           break;
		case 4:SetCursorPos(pp.x, pp.y+15);
	           break;
		}
 }
UINT  ThreadProc1(LPVOID lpParam)
{

	Cmfc_opencvDlg* D=(Cmfc_opencvDlg*) lpParam;

	CvCapture* capture;
	cascade = (CvHaarClassifierCascade*)cvLoad( cascade_name, 0, 0, 0 ); 
	storage = cvCreateMemStorage(0); 
	cvClearMemStorage(storage); 

	capture = cvCreateCameraCapture( 0 );

	assert( capture != NULL );

	IplImage* frame;
	while(1) {

		frame = cvQueryFrame( capture );
		if( !frame ) break;
		IplImage* img_rgb =frame;
		detect_and_draw(D,img_rgb);
		control_mouse(D);
		//IplImage* img_gry = cvCreateImage( cvSize( img_rgb->width,img_rgb->height ), img_rgb->depth, 1);
		//cvCvtColor(img_rgb, img_gry ,CV_BGR2GRAY);
		//IplImage* img_cny = doCanny( img_gry, 35, 100, 3 );
		//IplImage* img_inv = inverse(img_cny);
		//cvShowImage( "FaceDetect", img_rgb );
		DrawPicToHDC(D,img_rgb,IDC_IMG);
	}
	cvReleaseCapture( &capture );
	return 0;
}
CWinThread* asd=0;
void Cmfc_opencvDlg::OnBnClickedButton1()
{
	asd=AfxBeginThread((AFX_THREADPROC)ThreadProc1,this);
	asd->m_bAutoDelete=true;
	// TODO: 在此添加控件通知处理程序代码
}

#include <iostream>
#include <fstream>
void Cmfc_opencvDlg::OnBnClickedButton2()
{
	
	int k=get_index();
	ofstream ou;
	ou.open("C:\\Users\\Darkscope\\Desktop\\face\\access.ini");
	ou<<k+1;
	ou.close();

	CString *s=new CString();
	s->Format(_T("%d"),k);
	CString *name=new CString();
	GetDlgItemText(IDC_EDIT_TEST,*name);
	CString b(".jpg");
	CString f=*s+b;
	CString p("C:\\Users\\Darkscope\\Desktop\\face\\");
	f=p+f;
	if (PathFileExists(f))
	{
		MessageBox(_T("该文件已经存在"));
		return;
	}
	cvSaveImage(cs2ca(f),save_file);
	b=".ini";
	f=*s+b;
	f=p+f;
	ofstream out;
	out.open(f,ios::trunc);
	out<<cs2ca(*name)<<endl;
	out.close();
	//CloseProgram(_T("mfc_opencv.exe"));
	//KillProcessFromName("mfc_opencv.exe")
	//exit(0);  
	//kill the process
	// TODO: 在此添加控件通知处理程序代码

}


void Cmfc_opencvDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void Cmfc_opencvDlg::OnBnClickedButton3()
{
	CloseProgram(_T("mfc_opencv.exe"));
	// TODO: 在此添加控件通知处理程序代码
}


void Cmfc_opencvDlg::OnBnClickedButton4()
{
	pca_make_eigen();
	// TODO: 在此添加控件通知处理程序代码
}



void Cmfc_opencvDlg::OnBnClickedButton5()
{
	CString a;
	int t=pca_detect(save_file);
	a.Format(_T("%d"),t);


	CString aa=get_words(t);
	MessageBox(aa,_T("解析结果"));
	// TODO: 在此添加控件通知处理程序代码
}
