using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace CPower_CSharp
{
    public class LafDll
    {
        private const string m_strPath = "F:\\desktop_file\\Cpower_Sample\\CPower_CSharp\\CPower_CSharp\\CPower_CSharp\\CP5200\\LafDll.dll";

        //[DllImport(m_strPath, CharSet = CharSet.Auto)]
        //public static extern int CP5200_RS232_SplitScreen(int nCardID, int nScrWidth, int nScrHeight, int nWndCnt, params int[] pWndRects);
    }
}