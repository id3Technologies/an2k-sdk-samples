rem Build the sample with the jar from the sdk
javac -cp ".;../sdk/java/eu.id3.an2k.jar" An2KSample.java

rem Copy native library to current directory
copy ..\\sdk\\bin\\windows\\x64\\id3An2K.dll id3An2K.dll

rem Run the sample
java -cp ".;../sdk/java/eu.id3.an2k.jar" An2KSample