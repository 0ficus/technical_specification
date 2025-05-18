object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 441
  ClientWidth = 624
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object DBGrid1: TDBGrid
    Left = 8
    Top = 184
    Width = 593
    Height = 120
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -12
    TitleFont.Name = 'Segoe UI'
    TitleFont.Style = []
    OnDblClick = DBGrid1DblClick
  end
  object FDConnection1: TFDConnection
    Params.Strings = (
      'DriverID=FB'
      'Database=C:\UNIVERSITY.FDB'
      'Password=pswd'
      'User_Name=SYSDBA')
    Connected = True
    Left = 256
    Top = 64
  end
  object FDQuery1: TFDQuery
    Connection = FDConnection1
    Left = 384
    Top = 104
  end
  object DataSource1: TDataSource
    Left = 160
    Top = 89
  end
end
