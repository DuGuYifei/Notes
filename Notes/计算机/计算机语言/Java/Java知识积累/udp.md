# udp

## 使用注意

`ObjectOutputStream`在底层输出流时会在开头放额外字节，所以我才每次都重新创建，如果能找到方法彻底成为流式，自己收集大小，就不用每次重新创建。

## 案例
### Sender
```java
        @Bean
        public DatagramPacket metricsDatagramPacket() throws UnknownHostException {
                InetAddress inetAddress = InetAddress.getByName("localhost");
                return new DatagramPacket(new byte[0], 0, inetAddress, 3001);
        }

        /**
         * Create a metrics datagram socket bean.
         *
         * @return A DatagramSocket bean.
         * @throws SocketException If the socket is not created.
         */
        @Bean
        public DatagramSocket metricsDatagramSocket() throws SocketException {
                return new DatagramSocket();
        }
```

```java
package lsea.service;

import org.springframework.stereotype.Service;

import java.io.ByteArrayOutputStream;
import java.io.ObjectOutputStream;
import java.net.DatagramPacket;
import java.net.DatagramSocket;

/**
 * This service is responsible for handling udp service for the metrics
 * which are used for the monitoring the sso project by client.
 */
/* Requirement 6 */
@Service
public class MetricsUdpService {

    /**
     * The metrics service of the application.
     */
    private final MetricsService metricsService;

    /**
     * The metrics datagram socket of the application.
     */
    private final DatagramSocket metricsDatagramSocket;

    /**
     * The metrics datagram packet of the application.
     */
    private final DatagramPacket metricsDatagramPacket;

    /**
     * The constructor of the MetricsUdpService class.
     * 
     * @param metricsService        the metrics service of the application
     * @param metricsDatagramSocket the metrics datagram socket of the client app
     * @param metricsDatagramPacket the metrics datagram packet used to send the
     *                              metrics to the client
     */
    public MetricsUdpService(MetricsService metricsService, DatagramSocket metricsDatagramSocket,
            DatagramPacket metricsDatagramPacket) {
        this.metricsService = metricsService;
        this.metricsDatagramSocket = metricsDatagramSocket;
        this.metricsDatagramPacket = metricsDatagramPacket;
        sendMetrics();
    }

    /**
     * Start a new thread to always send the packet to the client.
     */
    /* Requirement 6.UDP */
    public void sendMetrics() {
        new Thread(() -> {

            byte[] data;
            try {
                while (true) {
                    ByteArrayOutputStream bos = new ByteArrayOutputStream();
                    ObjectOutputStream out = new ObjectOutputStream(bos);
                    metricsService.updateMetricsIndex();
                    out.writeObject(metricsService.getMetricsIndex());
                    data = bos.toByteArray();
                    out.flush();
                    metricsDatagramPacket.setData(data);
                    metricsDatagramSocket.send(metricsDatagramPacket);
                    bos.close();
                    out.close();
                }
            } catch (Exception e) {
                e.printStackTrace();
                metricsDatagramSocket.close();
            }
        }).start();
    }

}

```

### Receiver
```java
package client.metrics;

import lsea.utils.MetricsIndex;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.ObjectInput;
import java.io.ObjectInputStream;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;

/**
 * This class is used to receive the metrics of the server by udp transference.
 */
/* Requirement 6 */
public class MetricsUdpReceiver {

    /**
     * The metrics index of the SSO server.
     */
    private MetricsIndex metricsIndex;

    /**
     * The metrics datagram socket to receive packet from server.
     */
    private final DatagramSocket metricsDatagramSocket;

    /**
     * The metrics datagram packet to fill the data from server.
     */
    private final DatagramPacket metricsDatagramPacket;

    /**
     * The constructor of the class.
     *
     * @param port The port of the udp client receiver.
     */
    public MetricsUdpReceiver(int port) {
        try {
            this.metricsDatagramSocket = new DatagramSocket(port);
        } catch (SocketException e) {
            throw new RuntimeException(e);
        }
        this.metricsDatagramPacket = new DatagramPacket(new byte[1024], 1024);
        this.metricsIndex = new MetricsIndex();
        receiveMetrics();
    }

    /**
     * The getter of the metrics index.
     *
     * @return The metrics index of the SSO server.
     */
    public MetricsIndex getMetricsIndex() {
        return metricsIndex;
    }

    /**
     * Start a new thread to always receive the packet from the server.
     */
    /* Requirement 6.UDP */
    public void receiveMetrics() {
        new Thread(() -> {
            byte[] myObj;
            while (true) {
                try {
                    metricsDatagramSocket.receive(metricsDatagramPacket);
                    myObj = new byte[metricsDatagramPacket.getLength()];
                    System.arraycopy(metricsDatagramPacket.getData(), 0, myObj, 0, metricsDatagramPacket.getLength());
                    ByteArrayInputStream bis = new ByteArrayInputStream(myObj);
                    ObjectInput in = new ObjectInputStream(bis);
                    metricsIndex = (MetricsIndex) in.readObject();
                    in.close();
                    bis.close();
                    metricsDatagramPacket.setLength(1024);
                } catch (ClassNotFoundException | IOException e) {
                    e.printStackTrace();
                    break;
                }
            }
            metricsDatagramSocket.close();
        }).start();
    }

}
```