# TCP in PHP

目标：使用poll函数实现多个客户端连接

## 1. 服务端

### stream_select 和 socket_select
* `stream_select`:
  * 通用流操作：当你需要处理文件、网络连接或者任何通过 PHP 的流封装层（streams）打开的资源时。这包括使用 fopen(), fsockopen(), stream_socket_client() 等函数创建的流。
  * 高层抽象：适用于不需要直接控制套接字选项或底层网络行为的高层应用。例如，你可能只需要读取来自文件或通过 HTTP 进行数据传输的数据。
  * 跨协议应用：如果你的应用涉及多种类型的流，如同时处理文件IO和网络IO，使用 stream_select() 可以统一处理这些不同类型的流。
  * 简便性和兼容性：对于使用标准库和函数轻松创建和管理的流资源，stream_select() 提供了一个简单而强大的接口。
* `socket_select`:
  * 底层网络编程：当你使用 PHP 的套接字扩展直接创建套接字（通过 socket_create() 等函数）并进行原始网络通信时。
  * 精细控制：如果你需要对套接字进行详细的配置和控制，如设置套接字的行为、超时、非阻塞模式等，使用 socket_select() 更合适。
  * 性能敏感型应用：对于需要高性能网络通信的应用，直接使用套接字函数可以提供更低层次的系统调用，可能带来性能优势。
  * 特定协议处理：如果你的应用需要处理特定的网络协议或需要直接操作网络

```php
<?php
// 设置无超时
set_time_limit(0);

// 设置IP地址和端口号
$address = '127.0.0.1';
$port = 2048;

// 创建一个 TCP/IP socket
$sock = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
if ($sock === false) {
    echo "socket_create() failed: reason: " . socket_strerror(socket_last_error()) . "\n";
}

// 绑定到socket地址和端口
if (socket_bind($sock, $address, $port) === false) {
    echo "socket_bind() failed: reason: " . socket_strerror(socket_last_error($sock)) . "\n";
}

// 监听端口
if (socket_listen($sock, 5) === false) {
    echo "socket_listen() failed: reason: " . socket_strerror(socket_last_error($sock)) . "\n";
}

// 客户端套接字数组
$clients = array($sock);

echo "Server is running on $address:$port\n";

// 无限循环，等待连接和消息
while (true) {
    $read = $clients;
    $write = $except = null;

    // 阻塞等待socket变化
    if (socket_select($read, $write, $except, null) === false) {
        echo "socket_select() failed: reason: " . socket_strerror(socket_last_error()) . "\n";
        break;
    }

    // 处理每个套接字
    foreach ($read as $read_sock) {
        // 检查是否是新连接
        if ($read_sock == $sock) {
            // 接受新的连接
            if (($newsock = socket_accept($sock)) === false) {
                echo "socket_accept() failed: reason: " . socket_strerror(socket_last_error($sock)) . "\n";
                continue;
            }
            // 添加到客户端数组
            $clients[] = $newsock;
            echo "New client connected: " . socket_getpeername($newsock, $addr, $port) . "\n";
        } else {
            // 读取客户端数据
            $data = @socket_read($read_sock, 1024, PHP_BINARY_READ);
            if ($data === false) {
                // 客户端断开连接
                $key = array_search($read_sock, $clients);
                unset($clients[$key]);
                socket_close($read_sock);
                echo "Client disconnected.\n";
            } elseif ($data != '') {
                // 打印数据
                echo "Received message: $data\n";
                // 回复客户端
                $msg = "收到了";
                socket_write($read_sock, $msg, strlen($msg));
            }
        }
    }
}

// 关闭服务器套接字
socket_close($sock);
?>
```