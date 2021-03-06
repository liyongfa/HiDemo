#pragma once

namespace DuiLib
{
#define PEN_SIZE 10


	class e::CurvesConfig;
	class CSubCurveUI : public CControlUI
	{
	public:
		CSubCurveUI(void);
		CSubCurveUI(int nWidth, int nHeight);
		virtual ~CSubCurveUI(void);
		LPCTSTR GetClass(void) const;
		LPVOID GetInterface(LPCTSTR pstrName);
		virtual void DoInit(void) override;
		virtual void DoPaint(HDC hDC, const RECT& rcPaint) override;
		virtual void DoEvent(TEventUI& event) override;
		void SetLineWidth(int nLineWidth);
	protected:
		bool SetSize(int nWidth, int nHeight);
		bool CreatePens(int nCount);
		void Update(void);
		void OnLButtonDown(POINT & point);
		void OnMouseMove(POINT & point);
		void OnLButtonUp(POINT & point);
		void Clear(void);
	protected:
		RECT	m_rcBitmap;
		RECT	m_rcCorners;
		HBITMAP m_hBitmap;
		e::CurvesConfig* m_pCurvesConfig;
		HPEN m_hPen[PEN_SIZE];

		int	m_nWidth;
		int	m_nHeight;
		int	m_nPointCount;
		int	m_nSelectPoint;
		int	m_nLeftMost;
		int	m_nRightMost;
		bool m_bCapture;

		int m_nLineWidth;
	};

	class CCurveUI : public CContainerUI//CVerticalLayoutUI
	{
	public:
		CCurveUI(void);
		virtual ~CCurveUI(void);
	public:
		LPCTSTR GetClass(void) const;
		LPVOID GetInterface(LPCTSTR pstrName);
		virtual void DoInit(void) override;
		virtual void DoPaint(HDC hDC, const RECT& rcPaint) override;
		virtual void DoEvent(TEventUI& event) override;
	};
}
