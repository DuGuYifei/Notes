# validation
简介
--

1.  old: [protoc-gen-validate (PGV)](https://github.com/bufbuild/protoc-gen-validate)
2.  new: [**protovalidate**](https://github.com/bufbuild/protovalidate)

案例
--

1.  proto文件
2.  dependency和build的plugins
3.  其他注意事项

### proto文件

其中在intelliJ中使用validate.proto时候，可能cel模式用不了，需要在settings里面添加proto路径，即直接加`**protovalidate**`该jar包即可。

```text-x-ruby
syntax = 'proto3';

import "proto/commons.proto";
import "buf/validate/validate.proto";

option java_multiple_files = true;
option java_package = "com.pokemoney.redisservice.interfaces.proto";
option java_outer_classname = "RedisServiceProto";

message RedisKeyValueGetRequestDto {
  string key = 1 [(buf.validate.field).string.min_len = 1];
  string prefix = 3 [(buf.validate.field).string.max_len = 64];
}

message RedisKeyValueDto {
  string key = 1 [(buf.validate.field).string.min_len = 1];
  string value = 2 [(buf.validate.field).string.min_len = 1];
  int64 timeout = 3 [(buf.validate.field).cel = {
    id: "redis.timeout",
    message: "Value timeout must be between 1 and 2592000 seconds (30 days).",
    expression: "this >= 1 && this <= 2592000"
  }];
  string prefix = 4 [(buf.validate.field).string.max_len = 64];
}

message RedisHashKeyValueGetRequestDto {
  string key = 1 [(buf.validate.field).string.min_len = 1];
  string prefix = 3 [(buf.validate.field).string.max_len = 64];
}

message RedisHashKeyValueDto {
  string key = 1 [(buf.validate.field).string.min_len = 1];
  map <string, string> value = 2 [(buf.validate.field).map.min_pairs = 1];
  int64 timeout = 3 [(buf.validate.field).cel = {
    id: "redis.timeout",
    message: "Value timeout must be between 1 and 2592000 seconds (30 days).",
    expression: "this >= 1 && this <= 2592000"
  }];
  string prefix = 4 [(buf.validate.field).string.max_len = 64];
}

message RedisDelRequestDto {
  string key = 1 [(buf.validate.field).string.min_len = 1];
  string prefix = 2 [(buf.validate.field).string.max_len = 64];
}

service RedisService {
  rpc Del(RedisDelRequestDto) returns (response) {}
  rpc Set(RedisKeyValueDto) returns (response) {}
  rpc Get(RedisKeyValueGetRequestDto) returns (response) {}
  rpc HSet(RedisHashKeyValueDto) returns (response) {}
  rpc HGet(RedisHashKeyValueGetRequestDto) returns (response) {}
}
```

### denpendency和build的plugins

```text-x-ruby
		<dependency>
            <groupId>build.buf</groupId>
            <artifactId>protovalidate</artifactId>
            <version>0.1.7</version>
        </dependency>
```

```text-x-ruby
<plugins>
            <plugin>
                <groupId>org.apache.maven.plugins</groupId>
                <artifactId>maven-dependency-plugin</artifactId>
                <executions>
                    <execution>
                        <phase>generate-sources</phase>
                        <goals>
                            <goal>unpack</goal>
                        </goals>
                        <configuration>
                            <artifactItems>
                                <artifactItem>
                                    <groupId>com.pokemoney.commons</groupId>
                                    <artifactId>commons</artifactId>
                                    <version>0.0.1-SNAPSHOT</version>
                                    <type>jar</type>
                                    <includes>**/*.proto</includes>
                                    <outputDirectory>${project.build.directory}/protoc-dependencies/commons</outputDirectory>
                                </artifactItem>
                            </artifactItems>
                        </configuration>
                    </execution>
                </executions>
            </plugin>
            <plugin>
                <groupId>org.apache.maven.plugins</groupId>
                <artifactId>maven-jar-plugin</artifactId>
                <version>3.3.0</version>
            </plugin>
            <plugin>
                <groupId>org.xolstice.maven.plugins</groupId>
                <artifactId>protobuf-maven-plugin</artifactId>
                <version>0.6.1</version>
                <configuration>
                    <protocArtifact>com.google.protobuf:protoc:${protobuf.version}:exe:${os.detected.classifier}</protocArtifact>
                    <pluginId>grpc-java</pluginId>
                    <pluginArtifact>io.grpc:protoc-gen-grpc-java:${grpc.version}:exe:${os.detected.classifier}</pluginArtifact>
                    <protocPlugins>
                        <protocPlugin>
                            <id>dubbo</id>
                            <groupId>org.apache.dubbo</groupId>
                            <artifactId>dubbo-compiler</artifactId>
                            <version>${dubbo.version}</version>
                            <mainClass>org.apache.dubbo.gen.tri.Dubbo3TripleGenerator</mainClass>
                        </protocPlugin>
                    </protocPlugins>
                </configuration>
                <executions>
                    <execution>
                        <goals>
                            <goal>compile</goal>
                        </goals>
                    </execution>
                </executions>
            </plugin>
        </plugins>
```

### 其他注意事项

1.  如上例，当我想要import一个其他包的proto文件可以靠dependency，但我我需要将这个jar包给加到build里unpack来帮忙打包。