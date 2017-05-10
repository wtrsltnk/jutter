set "PATH=%JAVA_HOME%\bin;%ANDROID_HOME%\build-tools\23.0.3;%PATH%"

del bin\SDLActivity-release-signed.apk

copy bin\SDLActivity-release-unsigned.apk bin\SDLActivity-release-signed.apk
del bin\PassPerfect.apk

jarsigner -verbose -sigalg SHA1withRSA -digestalg SHA1 -keystore pass-perfect-release-key.keystore bin\SDLActivity-release-signed.apk pprelease

zipalign -p 4 bin\SDLActivity-release-signed.apk bin\PassPerfect.apk

pause