::' Magic header (this is a batch file with embedded vbs)

::
rem^ &@echo off
rem^ &call :'sub
rem^ &exit /b

:'sub
rem^ &cls
rem^ &cscript //nologo //e:vbscript "%~f0"
rem^ &exit /b

 '
 ' Copyright (C) 2012
 '     Dale Weiler
 '
 ' Permission is hereby granted, free of charge, to any person obtaining a copy of
 ' this software and associated documentation files (the "Software"), to deal in
 ' the Software without restriction, including without limitation the rights to
 ' use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 ' of the Software, and to permit persons to whom the Software is furnished to do
 ' so, subject to the following conditions:
 '
 ' The above copyright notice and this permission notice shall be included in all
 ' copies or substantial portions of the Software.
 '
 ' THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 ' IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 ' FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 ' AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 ' LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 ' OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 ' SOFTWARE.
 '

BuildDirectory = ".build"

' some mirrors:
' http://thammuz.tchpc.tcd.ie/mirror/
' http://ftp.ntua.gr/mirror/
' http://ftp.jaist.ac.jp/pub/sourceforge/m/project/mi/mingw/
' http://202.55.147.10/sourceforge/m/project/mi/mingw/
DownloadDirectoryMirror     = "http://ftp.jaist.ac.jp/pub/sourceforge/m/project/mi/mingw/"

'bump when needed
DownloadDirectory_gcc       = DownloadDirectoryMirror + "MinGW/Base/gcc/Version4/gcc-4.7.0-1/gcc-core-4.7.0-1-mingw32-bin.tar.lzma"
DownloadDirectory_binutils  = DownloadDirectoryMirror + "MinGW/Base/binutils/binutils-2.22/binutils-2.22-1-mingw32-bin.tar.lzma"
DownloadDirectory_make      = DownloadDirectoryMirror + "MSYS/Base/make/make-3.81-3/make-3.81-3-msys-1.0.13-bin.tar.lzma"
DownloadDirectory_coreutils = DownloadDirectoryMirror + "MSYS/Base/coreutils/coreutils-5.97-3/coreutils-5.97-3-msys-1.0.13-bin.tar.lzma"
DownloadDirectory_sed       = DownloadDirectoryMirror + "MSYS/Base/sed/sed-4.2.1-2/sed-4.2.1-2-msys-1.0.13-bin.tar.lzma"
DownloadDirectory_msyscore  = DownloadDirectoryMirror + "MSYS/Base/msys-core/msys-1.0.17-1/msysCORE-1.0.17-1-msys-1.0.17-bin.tar.lzma"
DownloadDirectory_iconv     = DownloadDirectoryMirror + "MSYS/Base/libiconv/libiconv-1.14-1/libiconv-1.14-1-msys-1.0.17-bin.tar.lzma"
DownloadDirectory_iconvdll  = DownloadDirectoryMirror + "MSYS/Base/libiconv/libiconv-1.14-1/libiconv-1.14-1-msys-1.0.17-dll-2.tar.lzma"
DownloadDirectory_gettext   = DownloadDirectoryMirror + "MSYS/Base/gettext/gettext-0.18.1.1-1/gettext-0.18.1.1-1-msys-1.0.17-bin.tar.lzma"
DownloadDirectory_libintl   = DownloadDirectoryMirror + "MSYS/Base/gettext/gettext-0.18.1.1-1/libintl-0.18.1.1-1-msys-1.0.17-dll-8.tar.lzma"
DownloadDirectory_bash      = DownloadDirectoryMirror + "MSYS/Base/bash/bash-3.1.17-4/bash-3.1.17-4-msys-1.0.16-bin.tar.lzma"
DownloadDirectory_libregex  = DownloadDirectoryMirror + "MSYS/Base/regex/regex-1.20090805-2/libregex-1.20090805-2-msys-1.0.13-dll-1.tar.lzma"
DownloadDirectory_libtermcap= DownloadDirectoryMirror + "MSYS/Base/termcap/termcap-0.20050421_1-2/libtermcap-0.20050421_1-2-msys-1.0.13-dll-0.tar.lzma"
DownloadDirectory_libgmp    = DownloadDirectoryMirror + "MinGW/Base/gmp/gmp-5.0.1-1/libgmp-5.0.1-1-mingw32-dll-10.tar.lzma"
DownloadDirectory_libmpc    = DownloadDirectoryMirror + "MinGW/Base/mpc/mpc-0.8.1-1/libmpc-0.8.1-1-mingw32-dll-2.tar.lzma"
DownloadDirectory_libmpfr   = DownloadDirectoryMirror + "MinGW/Base/mpfr/mpfr-2.4.1-1/libmpfr-2.4.1-1-mingw32-dll-1.tar.lzma"
DownloadDirectory_findutils = DownloadDirectoryMirror + "MSYS/Base/findutils/findutils-4.4.2-2/findutils-4.4.2-2-msys-1.0.13-bin.tar.lzma"
DownloadDirectory_grep      = DownloadDirectoryMirror + "MSYS/Base/grep/grep-2.5.4-2/grep-2.5.4-2-msys-1.0.13-bin.tar.lzma"
DownloadDirectory_file      = DownloadDirectoryMirror + "MSYS/Base/file/file-5.04-1/file-5.04-1-msys-1.0.13-bin.tar.lzma"
DownloadDirectory_libmagic  = DownloadDirectoryMirror + "MSYS/Base/file/file-5.04-1/libmagic-5.04-1-msys-1.0.13-dll-1.tar.lzma"
DownloadDirectory_zlib      = DownloadDirectoryMirror + "MSYS/Extension/zlib/zlib-1.2.7-1/zlib-1.2.7-1-msys-1.0.17-dll.tar.lzma"
' compression / extraction utilities
DownloadDirectory_zip       = "http://stahlforce.com/dev/unzip.exe"                                                                            ' must be exe
DownloadDirectory_lzma      = "http://mirror.transact.net.au/sourceforge/s/project/se/sevenzip/7-Zip/9.20/7za920.zip"                          ' must be in zip format
DownloadDirectory_tar       = "http://geoffair.net/unix/zips/tare07.zip"                                                                       ' must be in zip format

' some objects
Set FileSystemObject = CreateObject("Scripting.FileSystemObject")
Set DownloaderObject = CreateObject("WinHttp.WinHttpRequest.5.1")
Set CorePromptObject = CreateObject("WScript.Shell")

Sub DownloadFile(Url, File)
	' specify
	WScript.Echo "Downloading " + RIGHT(Url, Len(Url) - (InStrRev(Url, "/")))
	
	'validate the file doesn't already exist, if it does exit
	' simply remove the file
	If FileSystemObject.FileExists(File) Then
		FileSystemObject.Delete(File)
	End If
	
	' disable redirects
	DownloaderObject.Option(WinHttpRequestOption_EnableRedirects) = False
	
	' send the HTTP request
	DownloaderObject.Open "GET", Url, False
	DownloaderObject.Send
	
	' save binary
	Set WriteStream = CreateObject("ADODB.Stream")
	WriteStream.Type = 1 ' binary
	WriteStream.Open
	WriteStream.Write DownloaderObject.ResponseBody
	WriteStream.SaveToFile File, 2
	WriteStream.Close
	Set WriteStream = Nothing
End Sub

Sub ChangeDirectoryBuild()
	' changes the current directory to the build directory
	' some sanity check TODO here
	CorePromptObject.CurrentDirectory = ".\" + BuildDirectory
End Sub

Sub ExecuteExternalProcess(File)
	Call CorePromptObject.Run (File, 0)
End Sub


' extract utilities
Sub ExtractLZMA(File)
	WScript.Echo "Extracting  " + File
	Call ExecuteExternalProcess("7za e " + File)
End Sub

Sub ExtractTAR(File)
	WScript.Echo "Extracting  " + File
	Call ExecuteExternalProcess("tar xf " + File)
End Sub

Sub ExtractZIP(File)
	WScript.Echo "Extracting  " + File
	Call ExecuteExternalProcess("unzip " + File)
End Sub

Sub DeleteByExtension(Directory, Extensions)
	Dim objFolder, objSubFolder, objFile
	Dim strExt

	Set Folder = FileSystemObject.GetFolder(Directory)
	For Each File In Folder.Files
		For Each Ext In SPLIT(UCASE(Extensions),",")
			If RIGHT(UCASE(File.Path),LEN(Ext)+1) = "." & Ext Then
				WScript.Echo "Deleting    " & RIGHT(File.Path, Len(File.Path) - (InStrRev(File.Path, "\")))
				File.Delete
				Exit For
			End If
		Next
		WScript.Sleep(500)
	Next	
End Sub

Sub ObtainBuildEnviroment()
	' obtains a build enviroment for ccaprice (for windows)
	If FileSystemObject.FolderExists(".\" + BuildDirectory) Then
		FileSystemObject.DeleteFolder(".\" + BuildDirectory)
	End If
	WScript.Sleep(2000) ' give it time to referesh inode
	
	BuildFolder = FileSystemObject.CreateFolder(BuildDirectory)
	
	WScript.Echo "No build enviroment present"
	Wscript.Echo "Downloading build enviroment ... (this could take awhile)"
	WScript.Echo "Running Makefile.bat will not invoke this download again"
	WScript.Echo ""
	
	' make sure we're in the build directory
	Call ChangeDirectoryBuild()
	Call DownloadFile(DownloadDirectory_zip,       "unzip.exe")
	Call DownloadFile(DownloadDirectory_tar,       "tar.zip")
	Call DownloadFile(DownloadDirectory_lzma,      "lzma.zip")
	Call DownloadFile(DownloadDirectory_gcc,       "gcc.tar.lzma")
	Call DownloadFile(DownloadDirectory_binutils,  "binutils.tar.lzma")
	Call DownloadFile(DownloadDirectory_make,      "make.tar.lzma")
	Call DownloadFile(DownloadDirectory_coreutils, "coreutils.tar.lzma")
	Call DownloadFile(DownloadDirectory_sed,       "sed.tar.lzma")
	Call DownloadFile(DownloadDirectory_msyscore,  "msyscore.tar.lzma")
	Call DownloadFile(DownloadDirectory_iconv,     "iconv.tar.lzma")
	Call DownloadFile(DownloadDirectory_iconvdll,  "iconvdll.tar.lzma")
	Call DownloadFile(DownloadDirectory_gettext,   "gettext.tar.lzma")
	Call DownloadFile(DownloadDirectory_libintl,   "libintl.tar.lzma")
	Call DownloadFile(DownloadDirectory_bash,      "bash.tar.lzma")
	Call DownloadFile(DownloadDirectory_libregex,  "libregex.tar.lzma")
	Call DownloadFile(DownloadDirectory_libtermcap,"libtermcap.tar.lzma")
	Call DownloadFile(DownloadDirectory_libgmp,    "libgmp.tar.lzma")
	Call DownloadFile(DownloadDirectory_libmpc,    "libmpc.tar.lzma")
	Call DownloadFile(DownloadDirectory_libmpfr,   "libmpfr.tar.lzma")
	Call DownloadFile(DownloadDirectory_findutils, "findutils.tar.lzma")
	Call DownloadFile(DownloadDirectory_file,      "file.tar.lzma")
	Call DownloadFile(DownloadDirectory_grep,      "grep.tar.lzma")
	Call DownloadFile(DownloadDirectory_libmagic,  "libmagic.tar.lzma")
	Call DownloadFile(DownloadDirectory_zlib,      "zlib.tar.lzma")
	
	Call ExtractZIP("lzma.zip")
	Call ExtractZIP("tar.zip")
	WScript.Sleep(1000)
	
	Call ExtractLZMA("make.tar.lzma")
	Call ExtractLZMA("coreutils.tar.lzma")
	Call ExtractLZMA("sed.tar.lzma")
	Call ExtractLZMA("msyscore.tar.lzma")
	Call ExtractLZMA("gcc.tar.lzma")
	Call ExtractLZMA("binutils.tar.lzma")
	Call ExtractLZMA("iconv.tar.lzma")
	Call ExtractLZMA("iconvdll.tar.lzma")
	Call ExtractLZMA("gettext.tar.lzma")
	Call ExtractLZMA("libintl.tar.lzma")
	Call ExtractLZMA("bash.tar.lzma")
	Call ExtractLZMA("libregex.tar.lzma")
	Call ExtractLZMA("libtermcap.tar.lzma")
	Call ExtractLZMA("libgmp.tar.lzma")
	Call ExtractLZMA("libmpc.tar.lzma")
	Call ExtractLZMA("libmpfr.tar.lzma")
	Call ExtractLZMA("findutils.tar.lzma")
	Call ExtractLZMA("file.tar.lzma")
	Call ExtractLZMA("grep.tar.lzma")
	Call ExtractLZMA("libmagic.tar.lzma")
	Call ExtractLZMA("zlib.tar.lzma")
	WScript.Sleep(1000)
	
	Call ExtractTAR("make.tar")
	Call ExtractTAR("coreutils.tar")
	Call ExtractTAR("sed.tar")
	Call ExtractTAR("gcc.tar")
	Call ExtractTAR("binutils.tar")
	Call ExtractTAR("msyscore.tar")
	Call ExtractTAR("iconv.tar")
	Call ExtractTAR("iconvdll.tar")
	Call ExtractTAR("gettext.tar")
	Call ExtractTAR("libintl.tar")
	Call ExtractTAR("bash.tar")
	Call ExtractTAR("libregex.tar")
	Call ExtractTAR("libtermcap.tar")
	Call ExtractTAR("libgmp.tar")
	Call ExtractTAR("libmpc.tar")
	Call ExtractTAR("libmpfr.tar")
	Call ExtractTAR("findutils.tar")
	Call ExtractTAR("file.tar")
	Call ExtractTAR("grep.tar")
	Call ExtractTAR("libmagic.tar")
	Call ExtractTAR("zlib.tar")
	
	' create a bash rc file for path and clear command
	' also used to prevent downloads of the build enviroment 
	' thus removing the .bashrc file will redownload the enviroment
	Set WriteBashRC = FileSystemObject.OpenTextFile("env", 2, True)
		WriteBashRC.WriteLine("function clear {")
		WriteBashRC.WriteLine("    local CLEAR=$'\e[H\e[2J'")
		WriteBashRC.WriteLine("    echo -en " & chr(34) & "$CLEAR" & chr(34))
		WriteBashRC.WriteLine("    eval " & chr(34) & "function clear { echo -en '$CLEAR'; }" & chr(34))
		WriteBashRC.WriteLine("}")
		WriteBashRC.WriteLine("export PATH=.build\\bin")
		WriteBashRC.WriteLine("clear")
	WriteBashRC.Close()
	
	' cleanup the downloads
	Call DeleteByExtension(".", "tar,zip,exe,lzma")
End Sub

Sub ValidateBuildEnviroment()
	Call ChangeDirectoryBuild()
	
	If Not FileSystemObject.FileExists("env") Then
		' build enviroment isn't complete, delete everthing and retry
		Set Handle = FileSystemObject.GetFolder(".")
		' delete all files
		For Each FileObject in Handle.Files
			FileSystemObject.DeleteFile(FileObject.Name)
		Next
		
		' delete all folders
		For Each FolderObject in Handle.SubFolders
			FileSystemObject.DeleteFolder(FolderObject.Name)
		Next
			
		' delete build
		CorePromptObject.CurrentDirectory = "..\"
		FileSystemObject.DeleteFolder(".\" + BuildDirectory)
		
		' retry
		Call CheckBuildEnviroment()
	End If
End Sub
 
Sub CheckBuildEnviroment()
	If Not FileSystemObject.FolderExists(BuildDirectory) Then
		' no build enviroment present, so download and prepare
		' a build enviroment.
		Call ObtainBuildEnviroment()
	Else
		' validate that the build enviroment is complete
		' if not it deletes everything and sets up a new
		' build enviroment
		Call ValidateBuildEnviroment()
	End If
End Sub

CheckBuildEnviroment

'Everything from here is executed when this is opened
'we need to clear screen and execute the enviroment
'checker (all of this is a hack we send keys)
CorePromptObject.SendKeys "CLS + {ENTER}"
CorePromptObject.SendKeys ".build\bin\bash.exe --rcfile .build\env + {ENTER}"
	