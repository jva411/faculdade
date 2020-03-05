find -name "*.java" > JAVA_SOURCES.temp
javac @JAVA_SOURCES.temp
find -name "*.class" > JAVA_SOURCES.temp
jar cvfe tecnicas.jar tecnicas.Main @JAVA_SOURCES.temp
rm JAVA_SOURCES.temp
find -name "*.class" -delete