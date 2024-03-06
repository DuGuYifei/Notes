# Java_IDEA

1. [IntelliJ IDEA](#intellij-idea)
   1. [test coverage](#test-coverage)
      1. [报错参数不对](#报错参数不对)
   2. [添加library](#添加library)
   3. [打包jar](#打包jar)
      1. [最后:报错](#最后报错)
         1. [运行jar如果出现 invalid or corrupt jarfile的报错](#运行jar如果出现-invalid-or-corrupt-jarfile的报错)
2. [Maven打包](#maven打包)
   1. [普通打包 找不到主类](#普通打包-找不到主类)
   2. [跳过test](#跳过test)


## IntelliJ IDEA

### test coverage
右键`Run 'test' with Coverage`即可

#### 报错参数不对
其实是因为中文路径或者空格的问题可能，点击 help -> Edit Custom VM Options -> 添加`-Djava.io.tmpdir=xxxx`

### 添加library
File->project structure->libraries->➕->jar文件就选java然后找到jar文件就行

### 打包jar
[Intellij IDEA如何打包jar文件？_xiaoxiaoqin117的博客-CSDN博客_idea如何打包jar](https://blog.csdn.net/xiaoxiaoqin117/article/details/123530053)
1. File-> Project structure->Artifacts -> JAR ->From modules with dependencis.
2. 此时会在你选择的Main Class 同一目录下生成META-INF 文件夹以及其中的.MF 文件
3. 点击Build -> Build Artfacts ->Action(Build),此时会在你的项目文件中产生一个out 文件夹，其中可以看到已经打包好的jar 文件。
4. 用cmd 运行jar 包：`java -jar +your jar file` 就可以执行相应的功能。

#### 最后:报错
##### 运行jar如果出现 invalid or corrupt jarfile的报错
请确保你的.MF 文件夹与main class 在同一目录下，再做尝试，重新build。 祝你好运！


## Maven打包

```xml
    <properties>
        <java.version>11</java.version>
        <spring-cloud.version>Hoxton.SR8</spring-cloud.version>
        <start-class>com.example.springbootlab.GatewayApplication</start-class>
    </properties>
    <build>
        <plugins>
            <plugin>
                <groupId>org.springframework.boot</groupId>
                <artifactId>spring-boot-maven-plugin</artifactId>
                <configuration>
                    <fork>true</fork>
                    <mainClass>${start-class}</mainClass>
                </configuration>
                <executions>
                    <execution>
                        <goals>
                            <goal>repackage</goal>
                        </goals>
                    </execution>
                </executions>
            </plugin>
        </plugins>
    </build>
```
使用package打包即可

[SpringBoot - making jar files - No auto configuration classes found in META-INF/spring.factories](https://stackoverflow.com/questions/38792031/springboot-making-jar-files-no-auto-configuration-classes-found-in-meta-inf)
[maven三种打包方式详解_lixiangchibang的博客-CSDN博客_mvn package打包](https://blog.csdn.net/lixiangchibang/article/details/123797831)

### 普通打包 找不到主类
添加Artifacts时选择"copy to output...."，并将`.MF`文件放到src/main/resource下。但是结果会产生大量jar包。

### 跳过test
不同方法：
1. IDEA 按下maven里的闪电标志(skip tests)
2. `mvn install -Dmaven.test.skip=true`
3. pom.xml
   ```
   <plugin>
        <groupId>org.apache.maven.plugins</groupId>
        <artifactId>maven-surefire-plugin</artifactId>
        <configuration>
            <skip>true</skip>
        </configuration>
    </plugin>
    ```

   