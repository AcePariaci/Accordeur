; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAccordageGuitareDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Accordage Guitare.h"

ClassCount=4
Class1=CAccordageGuitareApp
Class2=CAccordageGuitareDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CDlgDiagramme
Resource3=IDD_ACCORDAGEGUITARE_DIALOG
Resource4=IDD_DIALOG_FREQUENCE

[CLS:CAccordageGuitareApp]
Type=0
HeaderFile=Accordage Guitare.h
ImplementationFile=Accordage Guitare.cpp
Filter=N

[CLS:CAccordageGuitareDlg]
Type=0
HeaderFile=Accordage GuitareDlg.h
ImplementationFile=Accordage GuitareDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=ID_GO

[CLS:CAboutDlg]
Type=0
HeaderFile=Accordage GuitareDlg.h
ImplementationFile=Accordage GuitareDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_ACCORDAGEGUITARE_DIALOG]
Type=1
Class=CAccordageGuitareDlg
ControlCount=13
Control1=ID_GO,button,1342242817
Control2=ID_STOP,button,1342242816
Control3=IDC_COMBO_CARTESON,combobox,1344340226
Control4=IDC_COMBO_ACCORD,combobox,1344339970
Control5=IDC_SLIDER_NOTES,msctls_trackbar32,1342242821
Control6=IDC_STATIC_1,static,1342308865
Control7=IDC_STATIC_2,static,1342308865
Control8=IDC_STATIC_3,static,1342308865
Control9=IDC_STATIC_4,static,1342308865
Control10=IDC_STATIC_5,static,1342308865
Control11=IDC_STATIC_6,static,1342308865
Control12=IDC_STATIC_CARTE,static,1342308865
Control13=IDC_STATIC_ACCORD,static,1342308865

[DLG:IDD_DIALOG_FREQUENCE]
Type=1
Class=CDlgDiagramme
ControlCount=2
Control1=IDC_EDIT_FREQMOINS,edit,1350633600
Control2=IDC_EDIT_FREQPLUS,edit,1350633600

[CLS:CDlgDiagramme]
Type=0
HeaderFile=DlgDiagramme.h
ImplementationFile=DlgDiagramme.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT_FREQMOINS
VirtualFilter=dWC

