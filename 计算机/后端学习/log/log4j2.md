# log4j2

## spring 
### pom.xml
    
```xml
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-web</artifactId>
    <exclusions>
        <exclusion>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-logging</artifactId>
        </exclusion>
    </exclusions>
</dependency>
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-log4j2</artifactId>
</dependency>
```

### application.properties

```properties
logging.config=classpath:log4j2.xml
```

### log4j2.xml

```xml
<?xml version="1.0" encoding="UTF-8"?>
<Configuration status="WARN">
    <Properties>
        <Property name="LOG_HOME">logs</Property>
    </Properties>
    <Appenders>
        <Console name="Console" target="SYSTEM_OUT">
            <PatternLayout pattern="%d{yyyy-MM-dd HH:mm:ss.SSS} [%t] %-5level %logger{36} - %msg%n"/>
        </Console>
        <RollingRandomAccessFile name="RollingRandomAccessFile" fileName="${LOG_HOME}/log.log"
                                 filePattern="${LOG_HOME}/log-%d{yyyy-MM-dd}-%i.log">
            <PatternLayout pattern="%d{yyyy-MM-dd HH:mm:ss.SSS} [%t] %-5level %logger{36} - %msg%n"/>
            <Policies>
                <TimeBasedTriggeringPolicy interval="1" modulate="true"/>
                <SizeBasedTriggeringPolicy size="10MB"/>
            </Policies>
            <DefaultRolloverStrategy max="10"/>
        </RollingRandomAccessFile>
    </Appenders>
    <Loggers>
        <Root level="info">
            <AppenderRef ref="Console"/>
            <AppenderRef ref="RollingRandomAccessFile"/>
        </Root>
    </Loggers>
</Configuration>
```

```xml
<?xml version="1.0" encoding="UTF-8"?>
<Configuration>
    <!--<Configuration status="WARN" monitorInterval="30"> -->
    <properties>
        <property name="LOG_HOME">../user-service/logs</property>
    </properties>
    <Appenders>
        <!--*******************Console Log**********************-->
        <Console name="consoleAppender" target="SYSTEM_OUT">
            <PatternLayout
                    pattern="%style{%d{ISO8601}}{bright,green} %highlight{%-5level} [%style{%t}{bright,blue}] %style{%C{}}{bright,yellow}: %msg%n%style{%throwable}{red}"
                    disableAnsi="false" noConsoleNoAnsi="false"
            />
        </Console>

        <!--*********************File Log***********************-->
        <!--all-level. file pattern: %i means the number of log file, %d{yyyy-MM-dd} means the date of log file-->
        <RollingRandomAccessFile name="allFileAppender"
                     fileName="${LOG_HOME}/all.log"
                     filePattern="${LOG_HOME}/$${date:yyyy-MM}/all-%d{yyyy-MM-dd}-%i.log.gz">
            <!--Setup pattern of log-->
            <PatternLayout>
                <!--date，level，class, method, thread, message, \n-->
                <pattern>%d %p %C{} [%t] %m%n</pattern>
            </PatternLayout>
            <Policies>
                <!-- set up log file split parameters -->
                <!--<OnStartupTriggeringPolicy/>-->
                <!--set up log file size, if the size is over the limit, the log file will be rolled-->
                <SizeBasedTriggeringPolicy size="10 MB"/>
                <!--set up log file roll time, depend on filePattern-->
                <TimeBasedTriggeringPolicy/>
            </Policies>
            <!--set up log file number limit, if not set, the default value is 7, if the number is over the limit, the log file will be covered; depend on %i in filePattern-->
            <DefaultRolloverStrategy max="10"/>
        </RollingRandomAccessFile>

        <!--debug-->
        <RollingRandomAccessFile name="debugFileAppender"
                     fileName="${LOG_HOME}/debug.log"
                     filePattern="${LOG_HOME}/$${date:yyyy-MM}/debug-%d{yyyy-MM-dd}-%i.log.gz">
            <Filters>
                <!--filter off warn and higher level log-->
                <ThresholdFilter level="info" onMatch="DENY" onMismatch="NEUTRAL"/>
            </Filters>
            <PatternLayout>
                <pattern>%d %p %C{} [%t] %m%n</pattern>
            </PatternLayout>
            <Policies>
                <!--<OnStartupTriggeringPolicy/>-->
                <SizeBasedTriggeringPolicy size="10 MB"/>
                <TimeBasedTriggeringPolicy/>
            </Policies>
            <DefaultRolloverStrategy max="10"/>
        </RollingRandomAccessFile>

        <!--info-->
        <RollingRandomAccessFile name="infoFileAppender"
                     fileName="${LOG_HOME}/info.log"
                     filePattern="${LOG_HOME}/$${date:yyyy-MM}/info-%d{yyyy-MM-dd}-%i.log.gz">
            <Filters>
                <ThresholdFilter level="warn" onMatch="DENY" onMismatch="NEUTRAL"/>
            </Filters>
            <PatternLayout>
                <pattern>%d %p %C{} [%t] %m%n</pattern>
            </PatternLayout>
            <Policies>
                <!--<OnStartupTriggeringPolicy/>-->
                <SizeBasedTriggeringPolicy size="10 MB"/>
                <!--set up log file roll time, depend on filePattern, interval is day, modulate is true means the log file will be rolled at the beginning of the day-->
                <TimeBasedTriggeringPolicy interval="1" modulate="true" />
            </Policies>
            <DefaultRolloverStrategy max="10"/>
        </RollingRandomAccessFile>

        <!--warn级别日志-->
        <RollingRandomAccessFile name="warnFileAppender"
                     fileName="${LOG_HOME}/warn.log"
                     filePattern="${LOG_HOME}/$${date:yyyy-MM}/warn-%d{yyyy-MM-dd}-%i.log.gz">
            <Filters>
                <ThresholdFilter level="error" onMatch="DENY" onMismatch="NEUTRAL"/>
            </Filters>
            <PatternLayout>
                <pattern>%d %p %C{} [%t] %m%n</pattern>
            </PatternLayout>
            <Policies>
                <!--<OnStartupTriggeringPolicy/>-->
                <SizeBasedTriggeringPolicy size="10 MB"/>
                <TimeBasedTriggeringPolicy/>
            </Policies>
            <DefaultRolloverStrategy max="10"/>
        </RollingRandomAccessFile>

        <!--error-->
        <RollingRandomAccessFile name="errorFileAppender"
                     fileName="${LOG_HOME}/error.log"
                     filePattern="${LOG_HOME}/$${date:yyyy-MM}/error-%d{yyyy-MM-dd}-%i.log.gz">
            <PatternLayout>
                <pattern>%d %p %C{} [%t] %m%n</pattern>
            </PatternLayout>
            <Policies>
                <!--<OnStartupTriggeringPolicy/>-->
                <SizeBasedTriggeringPolicy size="10 MB"/>
                <TimeBasedTriggeringPolicy/>
            </Policies>
            <DefaultRolloverStrategy max="10"/>
        </RollingRandomAccessFile>

        <!--json format error-level log-->
        <RollingRandomAccessFile name="errorJsonAppender"
                     fileName="${LOG_HOME}/error-json.log"
                     filePattern="${LOG_HOME}/error-json-%d{yyyy-MM-dd}-%i.log.gz">
            <JSONLayout compact="true" eventEol="true" locationInfo="true"/>
            <Policies>
                <SizeBasedTriggeringPolicy size="10 MB"/>
                <TimeBasedTriggeringPolicy interval="1" modulate="true"/>
            </Policies>
            <DefaultRolloverStrategy max="10"/>
        </RollingRandomAccessFile>
    </Appenders>

    <Loggers>
        <!-- root -->
        <Root level="debug">
            <AppenderRef ref="allFileAppender" level="all"/>
            <AppenderRef ref="consoleAppender" level="debug"/>
            <AppenderRef ref="debugFileAppender" level="debug"/>
            <AppenderRef ref="infoFileAppender" level="info"/>
            <AppenderRef ref="warnFileAppender" level="warn"/>
            <AppenderRef ref="errorFileAppender" level="error"/>
            <AppenderRef ref="errorJsonAppender" level="error"/>
        </Root>

        <!-- spring -->
        <Logger name="org.springframework" level="debug"/>
        <!-- druid datasource -->
        <Logger name="druid.sql.Statement" level="warn"/>
        <!-- mybatis -->
        <Logger name="com.mybatis" level="warn"/>
        <Logger name="org.hibernate" level="warn"/>
        <Logger name="com.zaxxer.hikari" level="info"/>
        <Logger name="org.quartz" level="info"/>
        <Logger name="com.andya.demo" level="debug"/>
    </Loggers>

</Configuration>
```

### 代码

```java
private static final Logger logger = LoggerFactory.getLogger(HelloController.class);

logger.off("off");
logger.fatal("fatal");
logger.info("info");
logger.debug("debug");
logger.error("error");
logger.warn("warn");
logger.trace("trace");
```