object KYQFrm: TKYQFrm
  Left = 183
  Top = 100
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #21345#20313#39069#26126#32454#26597#35810
  ClientHeight = 578
  ClientWidth = 811
  Color = clCream
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 16
  object cxGroupBox1: TcxGroupBox
    AlignWithMargins = True
    Left = 3
    Top = 3
    Align = alTop
    Alignment = alCenterCenter
    Style.LookAndFeel.NativeStyle = True
    StyleDisabled.LookAndFeel.NativeStyle = True
    StyleFocused.LookAndFeel.NativeStyle = True
    StyleHot.LookAndFeel.NativeStyle = True
    TabOrder = 0
    Height = 46
    Width = 805
    object cxLabel15: TcxLabel
      Left = 12
      Top = 14
      Caption = #21345'   '#21495':'
      ParentColor = False
      Style.Color = clCream
    end
    object KHTextEdit: TcxTextEdit
      Left = 71
      Top = 13
      Properties.MaxLength = 9
      TabOrder = 1
      OnKeyPress = BHTextEditKeyPress
      Width = 121
    end
    object BHTextEdit: TcxTextEdit
      Left = 272
      Top = 13
      Properties.MaxLength = 10
      TabOrder = 2
      OnKeyPress = BHTextEditKeyPress
      Width = 121
    end
    object cxLabel17: TcxLabel
      Left = 212
      Top = 14
      Caption = #32534'   '#21495':'
      ParentColor = False
      Style.Color = clCream
    end
    object cxLabel16: TcxLabel
      Left = 411
      Top = 14
      Caption = #22995'  '#21517':'
      ParentColor = False
      Style.Color = clCream
    end
    object cxLabel1: TcxLabel
      Left = 605
      Top = 14
      Caption = #37096'   '#38376':'
      ParentColor = False
      Style.Color = clCream
    end
    object BMComboBox: TcxComboBox
      Left = 664
      Top = 13
      TabOrder = 6
      OnKeyPress = BMComboBoxKeyPress
      Width = 121
    end
    object XMTextEdit: TcxTextEdit
      Left = 464
      Top = 13
      Properties.MaxLength = 10
      TabOrder = 7
      Width = 121
    end
  end
  object cxGroupBox2: TcxGroupBox
    AlignWithMargins = True
    Left = 3
    Top = 55
    Align = alClient
    Alignment = alCenterCenter
    Style.LookAndFeel.NativeStyle = True
    StyleDisabled.LookAndFeel.NativeStyle = True
    StyleFocused.LookAndFeel.NativeStyle = True
    StyleHot.LookAndFeel.NativeStyle = True
    TabOrder = 1
    Height = 520
    Width = 805
    object cxGroupBox3: TcxGroupBox
      AlignWithMargins = True
      Left = 2
      Top = 2
      Margins.Left = 0
      Margins.Top = 0
      Margins.Right = 0
      Margins.Bottom = 2
      Align = alClient
      Alignment = alCenterCenter
      TabOrder = 0
      Height = 403
      Width = 801
      object DataGrid: TcxGrid
        AlignWithMargins = True
        Left = 5
        Top = 5
        Width = 791
        Height = 393
        Align = alClient
        TabOrder = 0
        object DataGridDBTV: TcxGridDBTableView
          NavigatorButtons.ConfirmDelete = False
          DataController.Summary.DefaultGroupSummaryItems = <>
          DataController.Summary.FooterSummaryItems = <>
          DataController.Summary.SummaryGroups = <>
          OptionsCustomize.ColumnFiltering = False
          OptionsCustomize.ColumnSorting = False
          OptionsData.CancelOnExit = False
          OptionsData.Deleting = False
          OptionsData.DeletingConfirmation = False
          OptionsData.Editing = False
          OptionsData.Inserting = False
          OptionsSelection.CellSelect = False
          OptionsView.CellAutoHeight = True
          OptionsView.ColumnAutoWidth = True
          OptionsView.GroupByBox = False
          Styles.StyleSheet = GridTableViewStyleSheetDevExpress
        end
        object DataGridLL: TcxGridLevel
          GridView = DataGridDBTV
        end
      end
    end
    object cxGroupBox4: TcxGroupBox
      AlignWithMargins = True
      Left = 2
      Top = 409
      Margins.Left = 0
      Margins.Top = 2
      Margins.Right = 0
      Margins.Bottom = 2
      Align = alBottom
      Alignment = alCenterCenter
      TabOrder = 1
      Height = 35
      Width = 801
      object KYExportProgressBar: TcxProgressBar
        Left = 2
        Top = 2
        Align = alClient
        Properties.ShowTextStyle = cxtsText
        Style.LookAndFeel.NativeStyle = True
        StyleDisabled.LookAndFeel.NativeStyle = True
        StyleFocused.Color = clLime
        StyleFocused.LookAndFeel.NativeStyle = True
        StyleHot.LookAndFeel.NativeStyle = True
        TabOrder = 0
        Width = 797
      end
    end
    object cxGroupBox5: TcxGroupBox
      AlignWithMargins = True
      Left = 2
      Top = 483
      Margins.Left = 0
      Margins.Top = 2
      Margins.Right = 0
      Margins.Bottom = 0
      Align = alBottom
      Alignment = alCenterCenter
      TabOrder = 2
      Height = 35
      Width = 801
      object Panel2: TPanel
        Left = 22
        Top = 2
        Width = 777
        Height = 31
        Align = alRight
        BevelOuter = bvNone
        Color = clWhite
        ParentBackground = False
        TabOrder = 0
        object Label2: TLabel
          Left = 177
          Top = 7
          Width = 75
          Height = 16
          Caption = #21345#20313#24635#39069#65306
        end
        object Label1: TLabel
          Left = 0
          Top = 6
          Width = 75
          Height = 16
          Caption = #21345#29255#24635#25968#65306
        end
        object KYExportBTN: TcxButton
          Left = 524
          Top = 3
          Width = 75
          Height = 25
          Caption = #23548'   '#20986
          Enabled = False
          LookAndFeel.NativeStyle = True
          TabOrder = 0
          OnClick = KYExportBTNClick
        end
        object KYExitBTN: TcxButton
          Left = 692
          Top = 3
          Width = 75
          Height = 25
          Caption = #36864'   '#20986
          LookAndFeel.NativeStyle = True
          TabOrder = 1
          OnClick = KYExitBTNClick
        end
        object PreviewBTN: TcxButton
          Left = 608
          Top = 3
          Width = 75
          Height = 25
          Caption = #25171#21360#39044#35272
          Enabled = False
          LookAndFeel.NativeStyle = True
          TabOrder = 2
          OnClick = PreviewBTNClick
        end
        object ReadCardInfoBTN: TcxButton
          Left = 356
          Top = 3
          Width = 75
          Height = 25
          Caption = #35835'  '#21345
          LookAndFeel.NativeStyle = True
          TabOrder = 3
          OnClick = ReadCardInfoBTNClick
        end
        object QueryBTN: TcxButton
          Left = 440
          Top = 3
          Width = 75
          Height = 25
          Caption = #26597'   '#35810
          LookAndFeel.NativeStyle = True
          TabOrder = 4
          OnClick = QueryBTNClick
        end
        object AllKYTextEdit: TcxTextEdit
          Left = 248
          Top = 3
          TabOrder = 5
          OnKeyPress = AllKSTextEditKeyPress
          Width = 100
        end
        object AllKSTextEdit: TcxTextEdit
          Left = 72
          Top = 3
          TabOrder = 6
          OnKeyPress = AllKSTextEditKeyPress
          Width = 100
        end
      end
    end
    object cxGroupBox6: TcxGroupBox
      Left = 2
      Top = 446
      Align = alBottom
      Alignment = alCenterCenter
      TabOrder = 3
      Height = 35
      Width = 801
      object Panel1: TPanel
        Left = 2
        Top = 2
        Width = 797
        Height = 31
        Align = alClient
        BevelOuter = bvNone
        Caption = #23548#20986#25968#25454#38656#35201'XLS'#36719#20214#25903#25345#65292#35831#30830#35748#31995#32479#20013#23433#35013'XLS'#36719#20214#65292#21542#21017#26080#27861#23436#25104#23548#20986'!'
        Color = 8421631
        ParentBackground = False
        TabOrder = 0
      end
    end
  end
  object cxStyleRepository1: TcxStyleRepository
    Left = 80
    Top = 344
    PixelsPerInch = 96
    object cxStyle1: TcxStyle
      AssignedValues = [svColor]
      Color = 15451300
    end
    object cxStyle2: TcxStyle
      AssignedValues = [svColor, svFont, svTextColor]
      Color = 16247513
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      TextColor = clBlack
    end
    object cxStyle3: TcxStyle
      AssignedValues = [svColor, svTextColor]
      Color = 16247513
      TextColor = clBlack
    end
    object cxStyle4: TcxStyle
      AssignedValues = [svColor, svTextColor]
      Color = 16247513
      TextColor = clBlack
    end
    object cxStyle5: TcxStyle
      AssignedValues = [svColor, svTextColor]
      Color = 14811135
      TextColor = clBlack
    end
    object cxStyle6: TcxStyle
      AssignedValues = [svColor, svFont, svTextColor]
      Color = 14811135
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      TextColor = clNavy
    end
    object cxStyle7: TcxStyle
      AssignedValues = [svColor]
      Color = 14872561
    end
    object cxStyle8: TcxStyle
      AssignedValues = [svColor, svTextColor]
      Color = 4707838
      TextColor = clBlack
    end
    object cxStyle9: TcxStyle
      AssignedValues = [svColor, svFont, svTextColor]
      Color = 12937777
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      TextColor = clWhite
    end
    object cxStyle10: TcxStyle
      AssignedValues = [svColor]
      Color = 15451300
    end
    object cxStyle11: TcxStyle
      AssignedValues = [svColor, svTextColor]
      Color = 4707838
      TextColor = clBlack
    end
    object cxStyle12: TcxStyle
      AssignedValues = [svColor]
      Color = 15451300
    end
    object cxStyle13: TcxStyle
      AssignedValues = [svColor, svFont, svTextColor]
      Color = 14811135
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      TextColor = clNavy
    end
    object cxStyle14: TcxStyle
      AssignedValues = [svColor, svTextColor]
      Color = 12937777
      TextColor = clWhite
    end
    object GridTableViewStyleSheetDevExpress: TcxGridTableViewStyleSheet
      Caption = 'DevExpress'
      Styles.Background = cxStyle1
      Styles.Content = cxStyle2
      Styles.ContentEven = cxStyle3
      Styles.ContentOdd = cxStyle4
      Styles.FilterBox = cxStyle5
      Styles.Inactive = cxStyle10
      Styles.IncSearch = cxStyle11
      Styles.Selection = cxStyle14
      Styles.Footer = cxStyle6
      Styles.Group = cxStyle7
      Styles.GroupByBox = cxStyle8
      Styles.Header = cxStyle9
      Styles.Indicator = cxStyle12
      Styles.Preview = cxStyle13
      BuiltIn = True
    end
  end
  object KYADOQuery: TADOQuery
    AutoCalcFields = False
    Connection = SDIAppForm.ADOConnection1
    CommandTimeout = 100
    Parameters = <>
    Left = 80
    Top = 288
  end
  object KYDataSource: TDataSource
    DataSet = KYADOQuery
    Left = 80
    Top = 232
  end
  object SaveDialog: TSaveDialog
    FileName = #37325#21629#21517
    Filter = 'xls'
    Left = 192
    Top = 408
  end
  object ADOQInThread: TADOQuery
    Connection = SDIAppForm.ADOConnection1
    Parameters = <>
    Left = 80
    Top = 408
  end
  object frxKYReport: TfrxReport
    Version = '4.9.32'
    DotMatrixReport = False
    IniFile = '\Software\Fast Reports'
    PreviewOptions.Buttons = [pbPrint, pbLoad, pbSave, pbExport, pbZoom, pbFind, pbOutline, pbPageSetup, pbTools, pbEdit, pbNavigator, pbExportQuick]
    PreviewOptions.Zoom = 1.000000000000000000
    PrintOptions.Printer = 'Default'
    PrintOptions.PrintOnSheet = 0
    ReportOptions.CreateDate = 40866.701952210600000000
    ReportOptions.LastChange = 40901.612759687500000000
    ScriptLanguage = 'PascalScript'
    ScriptText.Strings = (
      ''
      'begin'
      ''
      'end.')
    Left = 544
    Top = 224
    Datasets = <>
    Variables = <>
    Style = <>
    object Data: TfrxDataPage
      Height = 1000.000000000000000000
      Width = 1000.000000000000000000
    end
    object Page1: TfrxReportPage
      Orientation = poLandscape
      PaperWidth = 257.000000000000000000
      PaperHeight = 182.000000000000000000
      PaperSize = 256
      LeftMargin = 10.000000000000000000
      RightMargin = 10.000000000000000000
      TopMargin = 10.000000000000000000
      BottomMargin = 10.000000000000000000
      object ReportTitle1: TfrxReportTitle
        Height = 99.267765350000000000
        Top = 18.897650000000000000
        Width = 895.748610000000000000
        object Memo2: TfrxMemoView
          Left = 360.834880000000000000
          Width = 173.858380000000000000
          Height = 34.015770000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -27
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Memo.UTF8W = (
            #21345#20313#39069#26126#32454#25253#34920)
          ParentFont = False
        end
        object Memo3: TfrxMemoView
          Top = 34.015770000000000000
          Width = 76.346456692913400000
          Height = 20.787401570000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -16
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
          HAlign = haCenter
          Memo.UTF8W = (
            #21345#21495)
          ParentFont = False
        end
        object Memo4: TfrxMemoView
          Left = 0.456710000000000000
          Top = 55.472480000000000000
          Width = 75.590600000000000000
          Height = 20.787401570000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -16
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
          HAlign = haCenter
          Memo.UTF8W = (
            #22995#21517)
          ParentFont = False
        end
        object KHMemo: TfrxMemoView
          Left = 76.590600000000000000
          Top = 34.015770000000000000
          Width = 188.976377950000000000
          Height = 20.787401570000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -16
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
          ParentFont = False
        end
        object Memo7: TfrxMemoView
          Left = 265.181200000000000000
          Top = 34.015770000000000000
          Width = 75.590600000000000000
          Height = 20.787401570000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -16
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
          HAlign = haCenter
          Memo.UTF8W = (
            #32534#21495)
          ParentFont = False
        end
        object Memo8: TfrxMemoView
          Left = 264.842610000000000000
          Top = 55.472480000000000000
          Width = 76.346456690000000000
          Height = 20.787401570000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -16
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
          HAlign = haCenter
          Memo.UTF8W = (
            #37096#38376)
          ParentFont = False
        end
        object BHMemo: TfrxMemoView
          Left = 341.464750000000000000
          Top = 34.015770000000000000
          Width = 188.976377950000000000
          Height = 20.787401570000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -16
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
          ParentFont = False
        end
        object BMMemo: TfrxMemoView
          Left = 341.433210000000000000
          Top = 55.472480000000000000
          Width = 188.976377950000000000
          Height = 20.787401570000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -16
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
          ParentFont = False
        end
        object XMMemo: TfrxMemoView
          Left = 76.511750000000000000
          Top = 54.913420000000000000
          Width = 188.976377950000000000
          Height = 21.165354330000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -16
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
          ParentFont = False
        end
        object Memo23: TfrxMemoView
          Left = 529.976810000000000000
          Top = 34.015770000000000000
          Width = 75.590600000000000000
          Height = 20.787401570000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -16
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
          Memo.UTF8W = (
            #29983#25104#26085#26399)
          ParentFont = False
        end
        object Memo24: TfrxMemoView
          Left = 529.976810000000000000
          Top = 55.472480000000000000
          Width = 75.590600000000000000
          Height = 20.787401570000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
          HAlign = haCenter
          Memo.UTF8W = (
            #25253#34920#25805#20316#21592)
          ParentFont = False
        end
        object SCRQMemo: TfrxMemoView
          Left = 605.567410000000000000
          Top = 34.015770000000000000
          Width = 289.511811020000000000
          Height = 20.787401570000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -16
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
          ParentFont = False
        end
        object CZYMemo: TfrxMemoView
          Left = 605.567410000000000000
          Top = 55.472480000000000000
          Width = 289.511811020000000000
          Height = 20.787401570000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -16
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
          ParentFont = False
        end
        object Memo28: TfrxMemoView
          Top = 76.590600000000000000
          Width = 894.992125980000000000
          Height = 22.677165350000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -19
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
          HAlign = haCenter
          Memo.UTF8W = (
            #21345#20313#39069#35814#32454#24773#20917)
          ParentFont = False
        end
      end
      object MasterData1: TfrxMasterData
        Height = 20.787401570000000000
        Top = 222.992270000000000000
        Width = 895.748610000000000000
        DataSet = frxDBDataset1
        DataSetName = 'frxDBDataset1'
        RowCount = 0
        object KH: TfrxMemoView
          Width = 94.488188980000000000
          Height = 20.787401570000000000
          ShowHint = False
          DataSet = frxDBDataset1
          DataSetName = 'frxDBDataset1'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -16
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
          HAlign = haCenter
          ParentFont = False
        end
        object BH: TfrxMemoView
          Left = 94.590600000000000000
          Width = 94.488188980000000000
          Height = 20.787401570000000000
          ShowHint = False
          DataSet = frxDBDataset1
          DataSetName = 'frxDBDataset1'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -16
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
          HAlign = haCenter
          ParentFont = False
        end
        object XM: TfrxMemoView
          Left = 189.181200000000000000
          Width = 83.149606300000000000
          Height = 20.787401570000000000
          ShowHint = False
          DataSet = frxDBDataset1
          DataSetName = 'frxDBDataset1'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -16
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
          HAlign = haCenter
          ParentFont = False
        end
        object SFYE: TfrxMemoView
          Left = 271.771800000000000000
          Width = 75.590551180000000000
          Height = 20.787401570000000000
          ShowHint = False
          DataSet = frxDBDataset1
          DataSetName = 'frxDBDataset1'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -16
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
          HAlign = haCenter
          ParentFont = False
        end
        object XB: TfrxMemoView
          Left = 347.362400000000000000
          Width = 37.795275590000000000
          Height = 20.787401570000000000
          ShowHint = False
          DataSet = frxDBDataset1
          DataSetName = 'frxDBDataset1'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -16
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
          HAlign = haCenter
          ParentFont = False
        end
        object BM: TfrxMemoView
          Left = 384.953000000000000000
          Width = 113.385826770000000000
          Height = 20.787401570000000000
          ShowHint = False
          DataSet = frxDBDataset1
          DataSetName = 'frxDBDataset1'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -16
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
          HAlign = haCenter
          ParentFont = False
        end
        object BZ: TfrxMemoView
          Left = 498.134200000000000000
          Width = 94.488188980000000000
          Height = 20.787401570000000000
          ShowHint = False
          DataSet = frxDBDataset1
          DataSetName = 'frxDBDataset1'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -16
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
          HAlign = haCenter
          ParentFont = False
        end
        object ZB: TfrxMemoView
          Left = 592.165740000000000000
          Width = 52.913385830000000000
          Height = 20.787401570000000000
          ShowHint = False
          DataSet = frxDBDataset1
          DataSetName = 'frxDBDataset1'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -16
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
          HAlign = haCenter
          ParentFont = False
        end
        object ZW: TfrxMemoView
          Left = 645.197280000000000000
          Width = 56.692913390000000000
          Height = 20.787401570000000000
          ShowHint = False
          DataSet = frxDBDataset1
          DataSetName = 'frxDBDataset1'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
          HAlign = haCenter
          ParentFont = False
        end
        object ZT: TfrxMemoView
          Left = 702.228820000000000000
          Width = 37.795275590000000000
          Height = 20.787401570000000000
          ShowHint = False
          DataSet = frxDBDataset1
          DataSetName = 'frxDBDataset1'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -16
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
          HAlign = haCenter
          ParentFont = False
        end
        object RQ: TfrxMemoView
          Left = 739.921770000000000000
          Width = 154.960629920000000000
          Height = 20.787401570000000000
          ShowHint = False
          DataSet = frxDBDataset1
          DataSetName = 'frxDBDataset1'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
          HAlign = haCenter
          ParentFont = False
        end
      end
      object PageFooter1: TfrxPageFooter
        Height = 22.677180000000000000
        Top = 306.141930000000000000
        Width = 895.748610000000000000
        object Memo1: TfrxMemoView
          Left = 819.158010000000000000
          Top = 2.779530000000000000
          Width = 75.590600000000000000
          Height = 18.897650000000000000
          ShowHint = False
          HAlign = haRight
          Memo.UTF8W = (
            '[Page#]')
        end
      end
      object PageHeader1: TfrxPageHeader
        Height = 20.787401570000000000
        Top = 139.842610000000000000
        Width = 895.748610000000000000
        object Memo29: TfrxMemoView
          Width = 94.488188980000000000
          Height = 20.787401570000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -16
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
          HAlign = haCenter
          Memo.UTF8W = (
            #21345#21495)
          ParentFont = False
        end
        object Memo30: TfrxMemoView
          Left = 94.590600000000000000
          Width = 94.488188980000000000
          Height = 20.787401570000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -16
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
          HAlign = haCenter
          Memo.UTF8W = (
            #32534#21495)
          ParentFont = False
        end
        object Memo31: TfrxMemoView
          Left = 189.181200000000000000
          Width = 83.149606299212600000
          Height = 20.787401570000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -16
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
          HAlign = haCenter
          Memo.UTF8W = (
            #22995#21517)
          ParentFont = False
        end
        object Memo32: TfrxMemoView
          Left = 271.771800000000000000
          Width = 75.590551181102400000
          Height = 20.787401570000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -16
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
          HAlign = haCenter
          Memo.UTF8W = (
            #21345#20313#39069)
          ParentFont = False
        end
        object Memo33: TfrxMemoView
          Left = 347.362400000000000000
          Width = 37.795275590000000000
          Height = 20.787401570000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -16
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
          HAlign = haCenter
          Memo.UTF8W = (
            #24615#21035)
          ParentFont = False
        end
        object Memo34: TfrxMemoView
          Left = 384.953000000000000000
          Width = 113.385826771654000000
          Height = 20.787401570000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -16
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
          HAlign = haCenter
          Memo.UTF8W = (
            #37096#38376)
          ParentFont = False
        end
        object Memo36: TfrxMemoView
          Left = 498.134200000000000000
          Width = 94.488188980000000000
          Height = 20.787401570000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -16
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
          HAlign = haCenter
          Memo.UTF8W = (
            #29677#21035)
          ParentFont = False
        end
        object Memo37: TfrxMemoView
          Left = 592.165740000000000000
          Width = 52.913385830000000000
          Height = 20.787401570000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -16
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
          HAlign = haCenter
          Memo.UTF8W = (
            #32452#21035)
          ParentFont = False
        end
        object Memo38: TfrxMemoView
          Left = 645.197280000000000000
          Width = 56.692913390000000000
          Height = 20.787401570000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -16
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
          HAlign = haCenter
          Memo.UTF8W = (
            #32844#21153)
          ParentFont = False
        end
        object Memo39: TfrxMemoView
          Left = 702.228820000000000000
          Width = 37.795275590000000000
          Height = 20.787401570000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -16
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
          HAlign = haCenter
          Memo.UTF8W = (
            #29366#24577)
          ParentFont = False
        end
        object Memo40: TfrxMemoView
          Left = 739.921770000000000000
          Width = 154.960629920000000000
          Height = 20.787401570000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -16
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
          HAlign = haCenter
          Memo.UTF8W = (
            #26368#21518#28040#36153#26085#26399)
          ParentFont = False
        end
      end
    end
  end
  object frxDBDataset1: TfrxDBDataset
    UserName = 'frxDBDataset1'
    CloseDataSource = False
    DataSource = KYDataSource
    BCDToCurrency = False
    Left = 544
    Top = 312
  end
end
