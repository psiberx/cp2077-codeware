param ($StageDir, $ReleaseBin, $ProjectName)

$DataDir = "${StageDir}/red4ext/plugins/${ProjectName}"

New-Item -ItemType directory -Force -Path ${DataDir} | Out-Null
Copy-Item -Path "data/*" -Destination ${DataDir}
