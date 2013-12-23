!include "x64.nsh" 

; Installer settings
SetCompressor /SOLID lzma
SetDatablockOptimize on
VIProductVersion "1.00.000.0"
VIAddVersionKey "ProductName" "QuickLOD"
VIAddVersionKey "Comments" "This setup will install QuickLOD and its dependencies."
VIAddVersionKey "CompanyName" "GENiEBEN"
VIAddVersionKey "FileVersion" "1.00.000"

XPStyle on

; The name of the installer
Name "Install QuickLOD v1.00.000"
BrandingText "(c) 2013 GENiEBEN"

; The file to write
OutFile "Install QuickLOD.exe"

; The default installation directory
InstallDir $PROGRAMFILES\GENiEBEN\QuickLOD

; Registry key to check for directory (so if you install again, it will 
; overwrite the old one automatically)
InstallDirRegKey HKCU "Software\GENiEBEN\QuickLOD" "InstallLocation"

; Request application privileges for Windows Vista
RequestExecutionLevel admin

;--------------------------------

; Pages

Page components
Page directory
Page instfiles

UninstPage uninstConfirm
UninstPage instfiles

;--------------------------------

; The stuff to install
Section "Main Files (required)"

	SectionIn RO

	; Set output path to the installation directory.-
	SetOutPath $INSTDIR

	; Put file there
	File "bin\release\*.exe"
	File "bin\release\*.dll"
	CreateDirectory "$INSTDIR\platforms"
	SetOutPath "$INSTDIR\platforms"
	File "bin\release\platforms\*.dll"
	SetOutPath $INSTDIR
	
	;Write application settings into registry
	WriteRegStr HKCU "SOFTWARE\GENiEBEN\QuickLOD" "InstallLocation" "$INSTDIR"
	WriteRegStr HKCU "SOFTWARE\GENiEBEN\QuickLOD" "AMD" "0"

	; Write the uninstall keys for Windows
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\QuickLOD" "DisplayName" "QuickLOD"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\QuickLOD" "DisplayVersion" "1.00.000"  
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\QuickLOD" "DisplayIcon" "$INSTDIR\quicklod.exe"   
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\QuickLOD" "UninstallString" "$INSTDIR\uninstall.exe"  

	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\QuickLOD" "URLInfoAbout" "https://github.com/GENiEBEN/quick-lod"   
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\QuickLOD" "URLUpdateInfo" "https://github.com/GENiEBEN/quick-lod"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\QuickLOD" "Publisher" "GENiEBEN"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\QuickLOD" "HelpLink" "https://github.com/GENiEBEN/quick-lod"  
	WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\QuickLOD" "NoModify" 1
	WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\QuickLOD" "NoRepair" 1
	WriteUninstaller "uninstall.exe"
  
SectionEnd

; Optional section (can be disabled by the user)
Section "Shortcuts"
	CreateDirectory "$SMPROGRAMS\GENiEBEN\QuickLOD"
	CreateShortCut "$SMPROGRAMS\GENiEBEN\QuickLOD\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0
	CreateShortCut "$SMPROGRAMS\GENiEBEN\QuickLOD\QuickLOD.lnk" "$INSTDIR\quicklod.exe" "" "$INSTDIR\quicklod.exe" 0
	CreateShortCut "$DESKTOP\QuickLOD.lnk" "$INSTDIR\quicklod.exe" "" "$INSTDIR\quicklod.exe" 0
SectionEnd


; These are the programs that are needed to run properly
SubSection "Prerequisites"
	Section "Visual C++ 2010"
		CreateDirectory "$INSTDIR\redis"
		SetOutPath "$INSTDIR\redis"
		File "bin\release\redis\vcredist_2010_x64.exe"
		File "bin\release\redis\vcredist_2010_x86.exe"
		ExecWait "$INSTDIR\redis\vcredist_2010_x86.exe /q"
		${if} ${RunningX64}
		ExecWait "$INSTDIR\redis\vcredist_2010_x64.exe /q"
		${endif}
		RMDir /r "$INSTDIR\redis"
	SectionEnd
SubSectionEnd
;--------------------------------

; Uninstaller

Section "Uninstall"
  
  ; Remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\QuickLOD"
  DeleteRegKey HKLM "SOFTWARE\GENiEBEN\QuickLOD"

  ; Remove files and uninstaller
  Delete "$INSTDIR\*.*"
  Delete "$DESKTOP\QuickLOD.lnk"

  ; Remove directories used
  RMDir /r "$SMPROGRAMS\GENiEBEN\QuickLOD"
  RMDir /r "$INSTDIR"

SectionEnd
