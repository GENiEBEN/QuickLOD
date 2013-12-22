#SingleInstance force  ;Prevents launching the wrapper multiple times by accident.
#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
; #Warn  ; Enable warnings to assist with detecting common errors.
SendMode Input  ; Recommended for new scripts due to its superior speed and reliability.
SetWorkingDir %A_ScriptDir%  ; Ensures a consistent starting directory.


;Run commands as Admin if we're not one.
if not A_IsAdmin
{
   Run *RunAs "%A_ScriptFullPath%"
}

;Are we trying to run this on ancient OS?
if A_OSVersion in WIN_NT4,WIN_95,WIN_98,WIN_ME  ; Note: No spaces around commas.
{
	MsgBox, "This OS is not supported."
	ExitApp
}

;Get LOD values
RegRead, amd_lod1, HKCU, SOFTWARE\GENiEBEN\QuickLOD, AMD_1
RegRead, amd_lod2, HKCU, SOFTWARE\GENiEBEN\QuickLOD, AMD_2
RegRead, amd_lod3, HKCU, SOFTWARE\GENiEBEN\QuickLOD, AMD_3
RegRead, amd_lod4, HKCU, SOFTWARE\GENiEBEN\QuickLOD, AMD_4
RegRead, amd_lod5, HKCU, SOFTWARE\GENiEBEN\QuickLOD, AMD_5

;Ctrl-Alt-0
~^!0::
	ExitApp
return

;Ctrl-Alt-1
~^!1::
	Run quicklod.exe -%amd_lod1%
return

;Ctrl-Alt-2
~^!2::
	Run quicklod.exe -%amd_lod2%
return

;Ctrl-Alt-3
~^!3::
	Run quicklod.exe -%amd_lod3%
return

;Ctrl-Alt-4
~^!4::
	Run quicklod.exe -%amd_lod4%
return

;Ctrl-Alt-5
~^!5::
	Run quicklod.exe -%amd_lod5%
return
