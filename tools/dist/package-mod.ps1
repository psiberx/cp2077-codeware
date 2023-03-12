param ($ReleaseBin, $ProjectName = "Codeware")

$StageDir = "build/package"
$DistDir = "build/dist"
$Version = & $($PSScriptRoot + "\steps\get-version.ps1")

& $($PSScriptRoot + "\steps\compose-redscripts.ps1") -StageDir ${StageDir} -ProjectName ${ProjectName} -Version ${Version}
& $($PSScriptRoot + "\steps\compose-plugin-red4ext.ps1") -StageDir ${StageDir} -ProjectName ${ProjectName} -ReleaseBin ${ReleaseBin}
& $($PSScriptRoot + "\steps\create-zip-from-stage.ps1") -StageDir ${StageDir} -ProjectName ${ProjectName} -DistDir ${DistDir} -Version ${Version}

Remove-Item -Recurse ${StageDir}
