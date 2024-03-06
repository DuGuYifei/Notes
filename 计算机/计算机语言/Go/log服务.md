# log服务

## 轻量级log
```
log "github.com/cihub/seelog"


	testConfig := `
		<seelog minlevel="info">
		    <outputs>

		        <console formatid="console" />

		        <rollingfile formatid="file" type="date" filename="logs/app.log" datepattern="2006-01-02-15" maxrolls="5" />
		    </outputs>
		    <formats>
		        <format id="console" format="%Date %Time [%LEVEL] %Msg%n"/>
				<format id="file" format="%Date %Time [%LEVEL] %Msg%n"/>
		    </formats>
		</seelog>`

	defer log.Flush()
	logger, err := log.LoggerFromConfigAsBytes([]byte(testConfig))
	if err != nil {
		fmt.Println(err.Error())
		panic(err.Error())
	}
	log.ReplaceLogger(logger)

	log.Debug("Check heartbeat at time: ", t)
```

## 官方log

1. 它给所以注意在fileLog创建了一个Write函数，使它有了write这个接口相当于有了写入文件的能力
2. 于是`stlog.New(fileLog(destination), "go", stlog.LstdFlags)`中第一个参数就使得它变成了写入文件的函数，不然应该可以是`OpenFile`的返回值作为第一个参数
   1. 所以注意在`fileLog.Write`函数里，有OpenFile.

```Go
package log

import (
	"io"
	stlog "log"
	"net/http"
	"os"
)

var log *stlog.Logger

type fileLog string

func (fl fileLog) Write(data []byte) (int, error) {
	f, err := os.OpenFile(string(fl), os.O_CREATE|os.O_WRONLY|os.O_APPEND, 0600)
	if err != nil {
		return 0, err
	}
	defer f.Close()
	return f.Write(data)
}

func Run(destination string) {
	log = stlog.New(fileLog(destination), "go", stlog.LstdFlags)
}

func Write(message string) {
	log.Printf("%v\n", message)
}

func RegisterHandlers() {
	http.HandleFunc("/log", func(w http.ResponseWriter, r *http.Request) {
		switch r.Method {
		case http.MethodPost:
			msg, err := io.ReadAll(r.Body)
			if err != nil || len(msg) == 0 {
				w.WriteHeader(http.StatusBadRequest)
				return
			}
			Write(string(msg))
		default:
			w.WriteHeader(http.StatusMethodNotAllowed)
		}
	})
}
```