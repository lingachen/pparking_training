unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, IniFiles,  
  cpower, CommCtrl,ExtCtrls;

type
  TForm1 = class(TForm)
    cmbPort: TComboBox;
    cmbBaudrate: TComboBox;
    cmbCardID: TComboBox;
    edtSelPlay: TEdit;
    btnSelPlay: TButton;
    btnSendText: TButton;
    edtText: TEdit;
    btnSendPIcture: TButton;
    edtPicture: TEdit;
    btnSendStaticText: TButton;
    edtStaticText: TEdit;
    btnSendClock: TButton;
    btnSetTime: TButton;
    edtWidth: TEdit;
    edtHeight: TEdit;
    Label4: TLabel;
    Label5: TLabel;
    btnSplitWnd: TButton;
    RadioButton1: TRadioButton;
    RadioButton2: TRadioButton;
    edtIPPort: TEdit;
    Label9: TLabel;
    lbl11: TLabel;
    cmbWndNo: TComboBox;
    grp2: TGroupBox;
    btnMakeProgram: TButton;
    btnMakeplaybill: TButton;
    btnUpload: TButton;
    lbl1: TLabel;
    lbl2: TLabel;
    lbl3: TLabel;
    lbl4: TLabel;
    lbl5: TLabel;
    lbl6: TLabel;
    procedure FormCreate(Sender: TObject);
    procedure cmbPortChange(Sender: TObject);
    procedure btnSelPlayClick(Sender: TObject);
    procedure cmbBaudrateChange(Sender: TObject);
    procedure cmbCardIDChange(Sender: TObject);
    procedure btnSendTextClick(Sender: TObject);
    procedure btnSendPIctureClick(Sender: TObject);
    procedure btnSendStaticTextClick(Sender: TObject);
    procedure btnSendClockClick(Sender: TObject);
    procedure btnSetTimeClick(Sender: TObject);
    procedure btnSplitWndClick(Sender: TObject);
    procedure RadioButton1Click(Sender: TObject);
    procedure RadioButton2Click(Sender: TObject);
    procedure edtIPPortChange(Sender: TObject);
    procedure btnMakeProgramClick(Sender: TObject);
    procedure btnMakeplaybillClick(Sender: TObject);
    procedure btnUploadClick(Sender: TObject);

  private
    procedure ReadIni();
    procedure EnableCtrl();
    procedure InitComm();
    procedure GetSplitWnd( pWndRects:pInteger );

    function qd0str(const count,num:integer):String;
    function GetProgramFileName():AnsiString;
    function GetPlaybillFileName():AnsiString;
  public
    { Public declarations }
  end;








var
  Form1: TForm1;

  m_nPort: Byte; //串口端口号
  m_nBaudrate: Integer;     //波特率
  m_nTimeout: Integer;      //串口超时
  m_nCardID: Byte;          //当前显示屏ID

  m_nWidth: Integer ;     //0号窗口宽度
  m_nHeight:  Integer ;   //0号窗口高度
  ipAddrCtl:  HWND;
  idCodeCtl:  HWND;

  m_nCommType: Byte;
  m_dwIPAddr: Integer	;
  m_dwIDCode: Integer	;
  m_nIPPort: Integer;
const
  m_baudtbl:   array[0..6]   of   DWORD =(115200, 57600, 38400, 19200, 9600, 4800 , 2400 );

implementation

{$R *.dfm}

procedure TForm1.FormCreate(Sender: TObject);
var I: Integer;
ICC: TInitCommonControlsEx;
begin
  m_nPort := 0;
  m_nBaudrate := 115200;
  m_nTimeout := 600;
  m_nCardID := 1;
  m_nWidth := 64;
  m_nHeight := 32;

  m_nCommType := 0;
  m_dwIPAddr := MAKEIPADDRESS(192,168,1,100);
  m_dwIDCode := MAKEIPADDRESS(255,255,255,255);
  m_nIPPort:= 5200;

  //初始化IP控件类
  ICC.dwSize := SizeOf(TInitCommonControlsEx);
  ICC.dwICC := ICC_INTERNET_CLASSES;
  If not InitCommonControlsEx(ICC)
  then begin
      MessageBox(0, 'Failed', 'InitCommonControlsEx', MB_OK);
  end;

  ipAddrCtl:=CreateWindow(WC_IPADDRESS, nil, WS_CHILD or WS_VISIBLE, 167,53,130,23, Form1.Handle,0,hInstance,nil);
  idCodeCtl:=CreateWindow(WC_IPADDRESS, nil, WS_CHILD or WS_VISIBLE, 565,53,130,23, Form1.Handle,0,hInstance,nil);


  ///

  ReadIni();        //从配置文件hgp.ini读入设置参数

  edtWidth.Text := IntToStr(m_nWidth);
  edtHeight.Text := IntToStr(m_nHeight);

  SendMessage(ipAddrCtl,IPM_SETADDRESS,0,m_dwIPAddr);
  SendMessage(idCodeCtl,IPM_SETADDRESS,0,m_dwIDCode);
  edtIPPort.Text := IntToStr(m_nIPPort);

  cmbPort.ItemIndex := m_nPort;
  cmbBaudrate.ItemIndex := 0;
  for I := 0 to 6 do
    if m_baudtbl[I] = m_nBaudrate then
      cmbBaudrate.ItemIndex := I;

  cmbCardID.ItemIndex := m_nCardID - 1;
  cmbWndNo.ItemIndex := 0 ;

  if( m_nCommType = 0) then
   begin
    RadioButton1.Checked := TRUE ;
    RadioButton2.Checked := FALSE ;
   end
  else
   begin
    RadioButton1.Checked := FALSE ;
    RadioButton2.Checked := TRUE ;
   end ;

   EnableCtrl();

end;

procedure TForm1.ReadIni();
var
  Ini: TIniFile;
  strIp: String;
begin
  Ini := TIniFile.Create( ChangeFileExt( Application.ExeName, '.INI' ) );
  try
    m_nPort := Ini.ReadInteger( 'COMM', 'PORT', 1 );
    if m_nPort > 0 then
      m_nPort := m_nPort - 1;

    m_nBaudrate := Ini.ReadInteger( 'COMM', 'BAUDRATE', 115200);
    m_nTimeout  := Ini.ReadInteger( 'COMM', 'TIMEOUT', 600);
    m_nCardID   := Ini.ReadInteger( 'COMM', 'CARDID', 1);

    m_nCommType := Ini.ReadInteger( 'COMM', 'TYPE', 0);

    strIp  := Ini.ReadString( 'COMM', 'IPADDR', '-1062731411');
    m_dwIPADDR := StrToInt64(strIp);

    strIp  := Ini.ReadString( 'COMM', 'IDCODE', '-1');
    m_dwIDCode := StrToInt64(strIp);

    m_nIPPort   := Ini.ReadInteger( 'COMM', 'IPPORT', 5200);

  finally
    Ini.Free;
  end;
end;

procedure TForm1.EnableCtrl();
var
  bComm: Boolean;
begin
  if (m_nCommType = 0) then
    bComm := TRUE
  else
    bComm := FALSE;

  cmbPort.Enabled :=  bComm;
  cmbBaudrate.Enabled := bComm;
  //cmbCardID.Enabled := bComm;

  edtIPPort.Enabled := not bComm;
  EnableWindow(idCodeCtl , not bComm);
  EnableWindow(ipAddrCtl , not bComm);

end;

procedure TForm1.InitComm();
var
  name:AnsiString;
  Ini: TIniFile;
begin
  if( m_nCommType = 0 )  then
  begin
	 name := Format('COM%d', [m_nPort+1]);
   CP5200_RS232_InitEx(name, m_nBaudrate, m_nTimeout);
  end
  else
  begin
   SendMessage(idCodeCtl,IPM_GETADDRESS,0,Integer(@m_dwIDCode));
   SendMessage(ipAddrCtl,IPM_GETADDRESS,0,Integer(@m_dwIPADDR));
   CP5200_Net_Init( m_dwIpAddr, m_nIPPort, m_dwIDCode, m_nTimeout);

   Ini := TIniFile.Create( ChangeFileExt( Application.ExeName, '.INI' ) );
   try
    begin
    Ini.WriteString( 'COMM', 'IPADDR', IntToStr(m_dwIpAddr) );
    Ini.WriteString( 'COMM', 'IDCODE', IntToStr(m_dwIDCode) );
    end
   finally
    Ini.Free;
   end;
  end;

end;

procedure TForm1.GetSplitWnd( pWndRects:pInteger ) ;
begin
  m_nWidth := StrToInt(edtWidth.Text);
  m_nHeight := StrToInt(edtHeight.Text);

  PInteger(Integer(pWndRects)+ 0)^ := 0;
  PInteger(Integer(pWndRects)+ 4)^ := 0;
  PInteger(Integer(pWndRects)+ 8)^ :=  Integer(m_nWidth div 2);
  PInteger(Integer(pWndRects)+ 12)^ := m_nHeight;
  PInteger(Integer(pWndRects)+ 16)^ := Integer(m_nWidth div 2);
  PInteger(Integer(pWndRects)+ 20)^ := 0;
  PInteger(Integer(pWndRects)+ 24)^ := m_nWidth;
  PInteger(Integer(pWndRects)+ 28)^ := m_nHeight;
end;


procedure TForm1.cmbPortChange(Sender: TObject);
var
  Ini: TIniFile;
begin
  m_nPort := cmbPort.ItemIndex;

  Ini := TIniFile.Create( ChangeFileExt( Application.ExeName, '.INI' ) );
  try
    Ini.WriteString( 'COMM', 'PORT', IntToStr(m_nPort + 1) );
  finally
    Ini.Free;
  end;
end;


procedure TForm1.cmbBaudrateChange(Sender: TObject);
var
  Ini: TIniFile;
begin
  m_nBaudrate := m_baudtbl[cmbBaudrate.ItemIndex];
  Ini := TIniFile.Create( ChangeFileExt( Application.ExeName, '.INI' ) );
  try
    Ini.WriteString( 'COMM', 'BAUDRATE', IntToStr(m_nBaudrate) );
  finally
    Ini.Free;
  end;
end;

procedure TForm1.cmbCardIDChange(Sender: TObject);
var
  Ini: TIniFile;
begin
  m_nCardID := 1 + cmbCardID.ItemIndex;
  Ini := TIniFile.Create( ChangeFileExt( Application.ExeName, '.INI' ) );
  try
    Ini.WriteString( 'COMM', 'CARDID', IntToStr(m_nCardID) );
  finally
    Ini.Free;
  end;
end;

procedure TForm1.btnSplitWndClick(Sender: TObject);
var
  ret: Integer;
  nWndRect:   array[0..7]   of   Integer ;
begin
  GetSplitWnd( @nWndRect ) ;
  InitComm();
  if( m_nCommType = 0) then
    ret :=  CP5200_RS232_SplitScreen( m_nCardID,m_nWidth,m_nHeight,2,@nWndRect )
  else
    ret :=  CP5200_Net_SplitScreen( m_nCardID,m_nWidth,m_nHeight,2,@nWndRect );
  if (ret >= 0) then
    MessageBox(0, 'Successful', 'Msg', MB_OK)
  else
    MessageBox(0, 'Failed', 'Msg', MB_OK);
end;

procedure TForm1.btnSelPlayClick(Sender: TObject);
var
  ret: Integer;
  prg: Integer;
  str: array[1..255] of Word;
begin
  prg := StrToInt(edtSelPlay.Text);
  if(prg < 0) then
    prg:= 0;
  str[1] := prg;
  str[2] := 0;
  InitComm();
  if( m_nCommType = 0) then
    ret := CP5200_RS232_PlaySelectedPrg(m_nCardID, @str, 1, 0)
  else
    ret := CP5200_Net_PlaySelectedPrg(m_nCardID, @str, 1, 0);

  if (ret >= 0) then
    MessageBox(0, 'Successful', 'Msg', MB_OK)
  else
    MessageBox(0, 'Failed', 'Msg', MB_OK);

end;

procedure TForm1.btnSendTextClick(Sender: TObject);
var
  ret: Integer;
begin
  InitComm();
  if( m_nCommType = 0) then
    ret := CP5200_RS232_SendText(m_nCardID, cmbWndNo.ItemIndex, pchar(edtText.Text), RGB(255,0,0), 16, 3, 0, 3, 5)
  else
    ret := CP5200_Net_SendText(m_nCardID, cmbWndNo.ItemIndex, pchar(edtText.Text), RGB(255,0,0), 16, 3, 0, 3, 5);

  if (ret >= 0) then
    MessageBox(0, 'Successful', 'Msg', MB_OK)
  else
    MessageBox(0, 'Failed', 'Msg', MB_OK);

end;

procedure TForm1.btnSendPIctureClick(Sender: TObject);
var
  ret: Integer;
  nWndRect:   array[0..7]   of   Integer ;
begin
  InitComm();
  GetSplitWnd( @nWndRect);
  if( m_nCommType = 0) then
    ret := CP5200_RS232_SendPicture(m_nCardID, cmbWndNo.ItemIndex, 0, 0,
			nWndRect[cmbWndNo.ItemIndex*4+2] - nWndRect[cmbWndNo.ItemIndex*4+0],
			nWndRect[cmbWndNo.ItemIndex*4+3] - nWndRect[cmbWndNo.ItemIndex*4+1],
			pchar(edtPicture.Text), 1, 0, 3, 0)
  else
    ret := CP5200_Net_SendPicture(m_nCardID, cmbWndNo.ItemIndex, 0, 0,
      nWndRect[cmbWndNo.ItemIndex*4+2] - nWndRect[cmbWndNo.ItemIndex*4+0],
			nWndRect[cmbWndNo.ItemIndex*4+3] - nWndRect[cmbWndNo.ItemIndex*4+1],
			pchar(edtPicture.Text), 1, 0, 3, 0);

  if (ret >= 0) then
    MessageBox(0, 'Successful', 'Msg', MB_OK)
  else
    MessageBox(0, 'Failed', 'Msg', MB_OK);

end;



procedure TForm1.btnSendStaticTextClick(Sender: TObject);
var
  ret: Integer;
  nWndRect:   array[0..7]   of   Integer ;
begin
  InitComm();
  GetSplitWnd( @nWndRect);
  if( m_nCommType = 0) then
    ret := CP5200_RS232_SendStatic(m_nCardID, cmbWndNo.ItemIndex, pchar(edtstaticText.Text), RGB(255,0,0), 16,0,
      0,0,nWndRect[cmbWndNo.ItemIndex*4+2] - nWndRect[cmbWndNo.ItemIndex*4+0], 	nWndRect[cmbWndNo.ItemIndex*4+3] - nWndRect[cmbWndNo.ItemIndex*4+1]) 
  else
    ret := CP5200_Net_SendStatic(m_nCardID, cmbWndNo.ItemIndex, pchar(edtstaticText.Text), RGB(255,0,0), 16,0,
      0,0,nWndRect[cmbWndNo.ItemIndex*4+2] - nWndRect[cmbWndNo.ItemIndex*4+0], 	nWndRect[cmbWndNo.ItemIndex*4+3] - nWndRect[cmbWndNo.ItemIndex*4+1]);

  if (ret >= 0) then
    MessageBox(0, 'Successful', 'Msg', MB_OK)
  else
    MessageBox(0, 'Failed', 'Msg', MB_OK);

end;

procedure TForm1.btnSendClockClick(Sender: TObject);
var
  ret: Integer;
begin
  InitComm();
  if( m_nCommType = 0) then
    ret :=  CP5200_RS232_SendClock( m_nCardID,cmbWndNo.ItemIndex,3,0,7,7,1 ,255,255,255 ,'Date' )
  else
    ret :=  CP5200_Net_SendClock( m_nCardID,cmbWndNo.ItemIndex,3,0,7,7,1 ,255,255,255 ,'Date' );
  if (ret >= 0) then
    MessageBox(0, 'Successful', 'Msg', MB_OK)
  else
    MessageBox(0, 'Failed', 'Msg', MB_OK);
end;

procedure TForm1.btnSetTimeClick(Sender: TObject);
var
  ret: Integer;
  dateTime: TDateTime;
  sTime: TSystemTime;
  byTime:   array[0..6]   of   byte ;
begin
  dateTime:= Now;
  DateTimetoSystemTime(dateTime,sTime);
  byTime[0] := sTime.wSecond;
  byTime[1] := sTime.wMinute;
  byTime[2] := sTime.wHour;
  byTime[3] := sTime.wDayOfWeek;
  byTime[4] := sTime.wDay;
  byTime[5] := sTime.wMonth;
  byTime[6] := sTime.wYear-2000;

  InitComm();
  if( m_nCommType = 0) then
    ret :=  CP5200_RS232_SetTime( m_nCardID, @byTime )
  else
    ret :=  CP5200_Net_SetTime( m_nCardID, @byTime );
  if (ret = 1) then
    MessageBox(0, 'Successful', 'Msg', MB_OK)
  else
    MessageBox(0, 'Failed', 'Msg', MB_OK);

end;


procedure TForm1.RadioButton1Click(Sender: TObject);
var
  Ini: TIniFile;
begin
 m_nCommType := 0;
 EnableCtrl();
 Ini := TIniFile.Create( ChangeFileExt( Application.ExeName, '.INI' ) );
  try
    Ini.WriteString( 'COMM', 'TYPE', IntToStr(m_nCommType) );
  finally
    Ini.Free;
  end;
end;

procedure TForm1.RadioButton2Click(Sender: TObject);
var
  Ini: TIniFile;
begin
 m_nCommType := 1;
 EnableCtrl();
  Ini := TIniFile.Create( ChangeFileExt( Application.ExeName, '.INI' ) );
  try
    Ini.WriteString( 'COMM', 'TYPE', IntToStr(m_nCommType) );
  finally
    Ini.Free;
  end;
end;

procedure TForm1.edtIPPortChange(Sender: TObject);
var
  Ini: TIniFile;
begin
  m_nIPPort := StrtoInt( edtIpPort.Text ) ;
  Ini := TIniFile.Create( ChangeFileExt( Application.ExeName, '.INI' ) );
  try
    Ini.WriteString( 'COMM', 'IPPORT', IntToStr(m_nIPPort) );
  finally
    Ini.Free;
  end;
end;

function TForm1.qd0str(const count,num:integer):String;
Var 
 s1,s2:String; 
begin
 s1:=IntToStr(Num);
 s2:='00000000000000000000'; 
 if (Length(s1)>=count) then
  s2:=''
 else if(count>20) then
  SetLength(S2,20-Length(s1)) 
 else 
  SetLength(S2,count-Length(s1));

 Result:=S2+S1; 
end; 


function TForm1.GetProgramFileName():AnsiString;
var
  strName:AnsiString;
begin
  strName := qd0str( 4 , m_nCardID ) ;
  strName := strName + '0000.lpp' ;
  result:= strName;
end;

function TForm1.GetPlaybillFileName():AnsiString;
begin
  result:= 'playbill.lpp';
end;  

procedure TForm1.btnMakeProgramClick(Sender: TObject);
var
  hObj: PLongint;
  bRet: Boolean ;
  nItemCnt: Integer;
  nWndNo:Integer;
  nWndRect:   array[0..7]   of   Integer ;
begin
  bRet := False ;
  nItemCnt := 0;
  GetSplitWnd( @nWndRect);
  hObj := CP5200_Program_Create( m_nWidth, m_nHeight, $77 );
  if( hObj <> nil ) then
  begin
    if( CP5200_Program_SetProperty( hObj , $FFFF , 1 ) > 0 ) then
    begin
      //0号窗口放文字，
      nWndNo := CP5200_Program_AddPlayWindow( hObj , nWndRect[0], nWndRect[1], nWndRect[2]-nWndRect[0], nWndRect[3]-nWndRect[1] );
      if( nWndNo >= 0) then
      begin
        CP5200_Program_SetWindowProperty( hObj , nWndNo , $30 , 1 ); //设置窗口边框
        if ( CP5200_Program_AddText(hObj, nWndNo, pchar(edtText.Text), 16, $FF, $FFFF, 100, 3 ) >= 0 ) then
           nItemCnt:= nItemCnt+1 ;
      end;

      //1号窗口放图片
      nWndNo := CP5200_Program_AddPlayWindow( hObj , nWndRect[4], nWndRect[5], nWndRect[6]-nWndRect[4], nWndRect[7]-nWndRect[5] );
      if( nWndNo >= 0) then
      begin
        if ( CP5200_Program_AddPicture(hObj, nWndNo, pchar(edtPicture.Text), 2, $FFFF, 100, 3, 0 ) >= 0) then
           nItemCnt:= nItemCnt+1 ;
      end;

      if ( (nItemCnt > 0) and ( CP5200_Program_SaveToFile( hObj, GetProgramFileName() ) >= 0 ) ) then
					bRet := TRUE ;
    end;
    CP5200_Program_Destroy( hObj);
  end;

  if (bRet ) then
    MessageBox(0, 'Successful', 'Msg', MB_OK)
  else
    MessageBox(0, 'Failed', 'Msg', MB_OK);
end;


procedure TForm1.btnMakeplaybillClick(Sender: TObject);
var
  hObj: PLongint;
  bRet: Boolean ;
begin
  bRet := False ;
  hObj := CP5200_Playbill_Create( m_nWidth, m_nHeight, $77 );
  if( hObj <> nil ) then
  begin
    	if ( CP5200_Playbill_AddFile( hObj, GetProgramFileName()) >= 0) then
      begin
        if ( CP5200_Playbill_SaveToFile( hObj, GetPlaybillFileName()) = 0) then
				   bRet := TRUE;
      end;
		  CP5200_Playbill_Destroy(hObj);
  end;

  if (bRet ) then
    MessageBox(0, 'Successful', 'Msg', MB_OK)
  else
    MessageBox(0, 'Failed', 'Msg', MB_OK);
end;

procedure TForm1.btnUploadClick(Sender: TObject);
var
  nUploadCnt: Integer;
begin
  nUploadCnt := 0 ;
  InitComm();
  if( m_nCommType = 0) then
    begin
      if ( 0 = CP5200_RS232_UploadFile( m_nCardID, GetProgramFileName(), GetProgramFileName()) )  then
		   	nUploadCnt := nUploadCnt + 1;

		  if ( 0 = CP5200_RS232_UploadFile( m_nCardID, GetPlaybillFileName(), GetPlaybillFileName()) ) then
		  	nUploadCnt := nUploadCnt + 1;

		  if ( nUploadCnt > 0)  then
		  	CP5200_Net_RestartApp( m_nCardID );
    end
  else
    begin
      if ( 0 = CP5200_Net_UploadFile( m_nCardID, GetProgramFileName(), GetProgramFileName()) )  then
		   	nUploadCnt := nUploadCnt + 1;

      if ( 0 = CP5200_Net_UploadFile( m_nCardID, GetPlaybillFileName(), GetPlaybillFileName()) ) then
		  	nUploadCnt := nUploadCnt + 1;

		  if ( nUploadCnt > 0)  then
		  	CP5200_Net_RestartApp( m_nCardID);
    end;

    ShowMessage(Format( 'Upload 2 files , %d successful , %d failed !' , [nUploadCnt , 2 - nUploadCnt] ));
end;

end.

