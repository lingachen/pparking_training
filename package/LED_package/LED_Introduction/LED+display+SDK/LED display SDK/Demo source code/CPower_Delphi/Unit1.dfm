object Form1: TForm1
  Left = 423
  Top = 180
  Width = 723
  Height = 360
  Caption = 'C-Power Demo'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label4: TLabel
    Left = 144
    Top = 96
    Width = 28
    Height = 13
    Caption = 'Width'
  end
  object Label5: TLabel
    Left = 232
    Top = 96
    Width = 31
    Height = 13
    Caption = 'Height'
  end
  object Label9: TLabel
    Left = 403
    Top = 263
    Width = 3
    Height = 13
    Caption = ' '
  end
  object lbl11: TLabel
    Left = 368
    Top = 96
    Width = 95
    Height = 13
    Caption = 'Select send window'
  end
  object lbl1: TLabel
    Left = 113
    Top = 18
    Width = 46
    Height = 13
    Caption = 'COM Port'
  end
  object lbl2: TLabel
    Left = 304
    Top = 18
    Width = 43
    Height = 13
    Caption = 'Baudrate'
  end
  object lbl3: TLabel
    Left = 496
    Top = 18
    Width = 58
    Height = 13
    Caption = 'Controller ID'
  end
  object lbl4: TLabel
    Left = 112
    Top = 56
    Width = 41
    Height = 13
    Caption = 'IP Addr'
  end
  object lbl5: TLabel
    Left = 304
    Top = 56
    Width = 32
    Height = 13
    Caption = 'IP Port'
  end
  object lbl6: TLabel
    Left = 496
    Top = 56
    Width = 39
    Height = 13
    Caption = 'ID Code'
  end
  object edtSelPlay: TEdit
    Left = 504
    Top = 143
    Width = 105
    Height = 21
    TabOrder = 2
    Text = '1'
  end
  object btnSelPlay: TButton
    Left = 368
    Top = 141
    Width = 113
    Height = 25
    Caption = 'Play One Program'
    TabOrder = 3
    OnClick = btnSelPlayClick
  end
  object btnSendText: TButton
    Left = 16
    Top = 141
    Width = 113
    Height = 25
    Caption = 'Send Text'
    TabOrder = 4
    OnClick = btnSendTextClick
  end
  object edtText: TEdit
    Left = 144
    Top = 143
    Width = 169
    Height = 21
    TabOrder = 5
    Text = #27426#36814#20809#20020#27969#26126#30005#23376#65281
  end
  object btnSendPIcture: TButton
    Left = 16
    Top = 191
    Width = 113
    Height = 25
    Caption = 'Send Picture'
    TabOrder = 6
    OnClick = btnSendPIctureClick
  end
  object edtPicture: TEdit
    Left = 144
    Top = 191
    Width = 169
    Height = 21
    TabOrder = 7
    Text = 'test.bmp'
  end
  object btnSendStaticText: TButton
    Left = 16
    Top = 239
    Width = 113
    Height = 25
    Caption = 'Send Static Text'
    TabOrder = 8
    OnClick = btnSendStaticTextClick
  end
  object edtStaticText: TEdit
    Left = 144
    Top = 239
    Width = 169
    Height = 21
    TabOrder = 9
    Text = 'Welcome to Lumen!'
  end
  object btnSendClock: TButton
    Left = 16
    Top = 287
    Width = 113
    Height = 25
    Caption = 'Send Clock'
    TabOrder = 10
    OnClick = btnSendClockClick
  end
  object btnSetTime: TButton
    Left = 160
    Top = 287
    Width = 120
    Height = 24
    Caption = 'Set Time'
    TabOrder = 20
    OnClick = btnSetTimeClick
  end
  object edtWidth: TEdit
    Left = 176
    Top = 95
    Width = 41
    Height = 21
    TabOrder = 11
    Text = '64'
  end
  object edtHeight: TEdit
    Left = 272
    Top = 95
    Width = 41
    Height = 21
    TabOrder = 12
    Text = '32'
  end
  object btnSplitWnd: TButton
    Left = 16
    Top = 95
    Width = 113
    Height = 30
    Caption = 'Make two window'
    TabOrder = 13
    OnClick = btnSplitWndClick
  end
  object cmbWndNo: TComboBox
    Left = 504
    Top = 95
    Width = 105
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 17
    OnChange = cmbCardIDChange
    Items.Strings = (
      '0'
      '1')
  end
  object grp2: TGroupBox
    Left = 368
    Top = 183
    Width = 249
    Height = 138
    Caption = 'Make program/playbill and upload'
    Ctl3D = True
    ParentCtl3D = False
    TabOrder = 18
    object btnMakeProgram: TButton
      Tag = 1
      Left = 53
      Top = 24
      Width = 145
      Height = 25
      Caption = 'Make Program'
      TabOrder = 0
      OnClick = btnMakeProgramClick
    end
    object btnMakeplaybill: TButton
      Left = 53
      Top = 64
      Width = 145
      Height = 25
      Caption = 'Make Playbill'
      TabOrder = 1
      OnClick = btnMakeplaybillClick
    end
    object btnUpload: TButton
      Left = 53
      Top = 104
      Width = 145
      Height = 25
      Caption = 'Upload and restart App'
      TabOrder = 2
      OnClick = btnUploadClick
    end
  end
  object RadioButton1: TRadioButton
    Left = 15
    Top = 16
    Width = 81
    Height = 17
    Caption = 'RS232/485'
    TabOrder = 14
    OnClick = RadioButton1Click
  end
  object RadioButton2: TRadioButton
    Left = 15
    Top = 56
    Width = 89
    Height = 17
    Caption = 'NetWork'
    TabOrder = 15
    OnClick = RadioButton2Click
  end
  object cmbPort: TComboBox
    Left = 167
    Top = 16
    Width = 130
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 19
    OnChange = cmbPortChange
    Items.Strings = (
      'COM1'
      'COM2'
      'COM3'
      'COM4'
      'COM5'
      'COM6'
      'COM7'
      'COM8'
      'COM9'
      'COM10'
      'COM11'
      'COM12'
      'COM13'
      'COM14'
      'COM15'
      'COM16')
  end
  object cmbBaudrate: TComboBox
    Left = 355
    Top = 16
    Width = 130
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 0
    OnChange = cmbBaudrateChange
    Items.Strings = (
      '115200'
      '57600'
      '38400'
      '19200'
      '9600'
      '4800'
      '2400')
  end
  object edtIPPort: TEdit
    Tag = 1
    Left = 355
    Top = 53
    Width = 130
    Height = 21
    TabOrder = 16
    Text = '5200'
    OnChange = edtIPPortChange
  end
  object cmbCardID: TComboBox
    Left = 565
    Top = 16
    Width = 130
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 1
    OnChange = cmbCardIDChange
    Items.Strings = (
      '1'
      '2'
      '3'
      '4'
      '5'
      '6'
      '7'
      '8'
      '9'
      '10'
      '11'
      '12'
      '13'
      '14'
      '15'
      '16'
      '17'
      '18'
      '19'
      '20')
  end
end
