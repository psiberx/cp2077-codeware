param ($GameDir, $ReleaseBin, $ProjectName = "Codeware")

$StageDir = "build/package"
$Version = & $($PSScriptRoot + "\steps\get-version.ps1")

& $($PSScriptRoot + "\steps\compose-redscripts.ps1") -StageDir ${StageDir} -ProjectName ${ProjectName} -Version ${Version}
& $($PSScriptRoot + "\steps\compose-plugin-red4ext.ps1") -StageDir ${StageDir} -ProjectName ${ProjectName} -ReleaseBin ${ReleaseBin}
& $($PSScriptRoot + "\steps\install-from-stage.ps1") -StageDir ${StageDir} -GameDir ${GameDir}

Remove-Item -Recurse ${StageDir}
