object YKHFForm: TYKHFForm
  Left = 0
  Top = 0
  Caption = 'YKHFForm'
  ClientHeight = 491
  ClientWidth = 780
  Color = clCream
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 16
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 489
    Height = 457
    Caption = #32508#21512#25805#20316
    TabOrder = 0
    object GroupBox4: TGroupBox
      AlignWithMargins = True
      Left = 5
      Top = 167
      Width = 479
      Height = 90
      Align = alTop
      Caption = #22351#26426#35831#21345
      TabOrder = 0
      ExplicitTop = 135
      object Button2: TButton
        Left = 128
        Top = 31
        Width = 169
        Height = 38
        Caption = #22351#26426#28165#21345
        TabOrder = 0
        OnClick = Button2Click
      end
    end
    object GroupBox2: TGroupBox
      AlignWithMargins = True
      Left = 5
      Top = 21
      Width = 479
      Height = 140
      Align = alTop
      Caption = #26377#21345#25442#25151
      TabOrder = 1
      object Label3: TLabel
        Left = 24
        Top = 32
        Width = 45
        Height = 16
        Caption = #21345#21495#65306
      end
      object Label4: TLabel
        Left = 248
        Top = 32
        Width = 45
        Height = 16
        Caption = #22995#21517#65306
      end
      object Label1: TLabel
        Left = 110
        Top = 69
        Width = 75
        Height = 16
        Caption = #25442#25151#27425#25968#65306
      end
      object Edit3: TEdit
        Left = 75
        Top = 29
        Width = 150
        Height = 24
        ReadOnly = True
        TabOrder = 0
      end
      object Edit4: TEdit
        Left = 299
        Top = 29
        Width = 150
        Height = 24
        ReadOnly = True
        TabOrder = 1
      end
      object Button3: TButton
        Left = 128
        Top = 101
        Width = 75
        Height = 25
        Caption = #35835'   '#21345
        TabOrder = 2
        OnClick = Button3Click
      end
      object Button4: TButton
        Left = 280
        Top = 101
        Width = 75
        Height = 25
        Caption = #25442'   '#25151
        Enabled = False
        TabOrder = 3
        OnClick = Button4Click
      end
      object Edit1: TEdit
        Left = 188
        Top = 66
        Width = 150
        Height = 24
        ReadOnly = True
        TabOrder = 4
      end
    end
    object GroupBox3: TGroupBox
      AlignWithMargins = True
      Left = 5
      Top = 263
      Width = 479
      Height = 90
      Align = alTop
      Caption = #21457#27979#35797#21345
      TabOrder = 2
      ExplicitTop = 231
      object Button1: TButton
        Left = 128
        Top = 31
        Width = 169
        Height = 38
        Caption = #21457#27979#35797#21345
        TabOrder = 0
        OnClick = Button1Click
      end
    end
    object Button5: TButton
      Left = 133
      Top = 367
      Width = 169
      Height = 38
      Caption = #36864'   '#20986
      TabOrder = 3
      OnClick = Button5Click
    end
  end
  object ADOWithDrawQuery: TADOQuery
    Connection = SDIAppForm.ADOConnection1
    Parameters = <>
    Left = 544
    Top = 96
  end
  object ADOQuery1: TADOQuery
    Connection = SDIAppForm.ADOConnection1
    Parameters = <>
    Left = 640
    Top = 320
  end
  object LaunchNewCardADOQ: TADOQuery
    Connection = SDIAppForm.ADOConnection1
    Parameters = <>
    Left = 648
    Top = 384
  end
end
