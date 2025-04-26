# log系统

## 标准库
- **log**
  - Go 自带的，非常轻量。
  - 简单场景够用，但功能比较基础（比如没有日志分级、异步写入等）。

---

## 流行第三方库
- **zap** （Uber 出品）
  - 特点：**高性能**，**结构化日志**，支持非常细粒度的配置。
  - 适合高并发、大规模项目。
  - 有 **SugaredLogger**（稍微慢但更易用）和 **Logger**（极致性能）两种模式。
  - 👉 [https://github.com/uber-go/zap](https://github.com/uber-go/zap)

- **logrus**
  - 特点：**API友好**，**社区广泛使用**，支持各种 hook（比如发送日志到别的系统）。
  - 性能比 zap 稍差，但开发体验好。
  - 👉 [https://github.com/sirupsen/logrus](https://github.com/sirupsen/logrus)

- **zerolog**
  - 特点：**性能极高**，JSON日志输出，极小内存占用。
  - API 偏函数式风格，初学者可能觉得不太直观。
  - 👉 [https://github.com/rs/zerolog](https://github.com/rs/zerolog)

- **seelog** （虽然比较老了）
  - 特点：配置强大，可以用 xml 配置输出格式和目标。
  - 但现在已经很久没人维护了，不推荐新项目使用。

---

## 辅助类库
- **lumberjack**
  - 用于做日志文件的**滚动切割**（比如每天一个日志文件，或者按大小切分）。
  - 经常搭配 zap / logrus 使用。
  - 👉 [https://github.com/natefinch/lumberjack](https://github.com/natefinch/lumberjack)

---

## 常见组合
- **zap + lumberjack**：高性能生产环境标准配置。
- **logrus + lumberjack**：开发体验好，适合小中型项目。

---

## 选型建议
- 如果你追求**极致性能** ➔ **zap**。
- 如果想**快速上手、开发友好** ➔ **logrus**。
- 如果是**超小内存环境/IoT设备** ➔ **zerolog**。
- 如果只是简单脚本 ➔ **log（标准库）** 就够了。

---

就选：zap + lumberjack，也有标准化输出，json之类的，用于数据分析。

## zap + lumberjack 示例
```go
package log

import (
	"go.uber.org/zap"
	"go.uber.org/zap/zapcore"
	"gopkg.in/natefinch/lumberjack.v2"
	"os"
	"path/filepath"
	"time"
)

var Log *zap.Logger

// InitLogger 初始化日志配置
func InitLogger(logPath string, logLevel string) {
	// 创建日志目录
	if err := os.MkdirAll(filepath.Dir(logPath), 0766); err != nil { // 0766表示读、写、执行权限
		panic(err)
	}

	// 配置 lumberjack 进行日志分割
	hook := lumberjack.Logger{
		Filename:   logPath, // 日志文件路径
		MaxSize:    100,     // 每个日志文件最大尺寸(MB)
		MaxBackups: 30,      // 保留旧文件最大数量
		MaxAge:     7,       // 保留旧文件最大天数
		Compress:   true,    // 是否压缩
		LocalTime:  true,    // 使用本地时间
	}

	// 设置日志编码器配置
	encoderConfig := zapcore.EncoderConfig{
		TimeKey:        "time",
		LevelKey:       "level",
		NameKey:        "logger",
		CallerKey:      "caller",
		FunctionKey:    zapcore.OmitKey,
		MessageKey:     "msg",
		StacktraceKey:  "stacktrace",
		LineEnding:     zapcore.DefaultLineEnding,
		EncodeLevel:    zapcore.CapitalLevelEncoder,    // 大写编码器
		EncodeTime:     customTimeEncoder,              // 自定义时间格式
		EncodeDuration: zapcore.SecondsDurationEncoder, // 持续时间格式
		EncodeCaller:   zapcore.ShortCallerEncoder,     // 简短路径编码器
		EncodeName:     zapcore.FullNameEncoder,
	}

	// 设置日志级别
	var level zapcore.Level
	switch logLevel {
	case "debug":
		level = zap.DebugLevel
	case "info":
		level = zap.InfoLevel
	case "warn":
		level = zap.WarnLevel
	case "error":
		level = zap.ErrorLevel
	default:
		level = zap.InfoLevel
	}

	// 创建核心
	fileCore := zapcore.NewCore(
		zapcore.NewJSONEncoder(encoderConfig),               // JSON格式化
		zapcore.NewMultiWriteSyncer(zapcore.AddSync(&hook)), // 同时输出到文件
		level,
	)

	consoleCore := zapcore.NewCore(
		zapcore.NewConsoleEncoder(encoderConfig), // 控制台格式化
		zapcore.AddSync(os.Stdout),               // 同时输出到控制台
		zap.DebugLevel,                           // 控制台输出Debug级别及以上
	)

	core := zapcore.NewTee(fileCore, consoleCore) // 合并核心

	// 创建Logger
	Log = zap.New(
		core,
		zap.AddCaller(),                   // 添加调用者信息
		zap.AddCallerSkip(1),              // 跳过一层调用层级
		zap.AddStacktrace(zap.ErrorLevel), // Error级别及以上添加堆栈跟踪
	)
}

// 自定义时间编码器，按照特定格式输出
func customTimeEncoder(t time.Time, enc zapcore.PrimitiveArrayEncoder) {
	enc.AppendString(t.Format("2025-04-26 15:04:05.000"))
}

// 下面添加一些便捷方法

func Debug(msg string, fields ...zap.Field) {
	Log.Debug(msg, fields...)
}

func Info(msg string, fields ...zap.Field) {
	Log.Info(msg, fields...)
}

func Warn(msg string, fields ...zap.Field) {
	Log.Warn(msg, fields...)
}

func Error(msg string, fields ...zap.Field) {
	Log.Error(msg, fields...)
}

func Fatal(msg string, fields ...zap.Field) {
	Log.Fatal(msg, fields...)
}

// Close 关闭日志
func Close() {
	Log.Sync()
}
```