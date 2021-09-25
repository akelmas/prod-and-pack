package com.company;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.charset.StandardCharsets;
import java.util.*;

public class TcpServer {
    private static final int EVENT_PRODUCT_IN=0;
    private static final int EVENT_PRODUCT_IN_PROCESS=1;
    private static final int EVENT_PRODUCT_OUT=2;
    private static final int EVENT_PRODUCT_TRASH=3;

    ServerSocket serverSocket;
    Socket socket;

    Queue<Integer> productQueue=new PriorityQueue<>();

    void sendMessageToPMak(){
        try {
            Socket clientSocket=new Socket("0.0.0.0",5001);
            OutputStream outputStream=clientSocket.getOutputStream();
            outputStream.write("CLIENT MESSAGE".getBytes(StandardCharsets.UTF_8));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }


    public TcpServer(){
        Thread t = new Thread(()->{
            while (true){
                if(!productQueue.isEmpty()){
                    productQueue.remove();
                }
                sendMessageToPMak();

                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }

        });
        t.start();
        try {
            serverSocket=new ServerSocket(1903);
            socket=serverSocket.accept();
            //TODO handle when clients disconnect
            System.out.println("Connected.");
            InputStream inputStream=socket.getInputStream();
            OutputStream outputStream=socket.getOutputStream();
            Logger logger=new Logger();

            while (true)
            {
                if(inputStream.available()>0){
                    int len;
                    byte[] ACK={0x06};
                    byte[] receivedBytes=new byte[128];
                    len=inputStream.read(receivedBytes);
                    if(len>-1)
                    System.out.println("Received: "+Arrays.toString(Arrays.copyOf(receivedBytes,len)));

                    int productId;
                    int eventId;
                    int currentState;
                    byte optionalParam;

                    productId=ByteBuffer.wrap(Arrays.copyOfRange(receivedBytes,0,4)).order(ByteOrder.LITTLE_ENDIAN).getInt();
                    eventId=ByteBuffer.wrap(Arrays.copyOfRange(receivedBytes,4,8)).order(ByteOrder.LITTLE_ENDIAN).getInt();
                    currentState=ByteBuffer.wrap(Arrays.copyOfRange(receivedBytes,8,12)).order(ByteOrder.LITTLE_ENDIAN).getInt();
                    optionalParam=ByteBuffer.wrap(Arrays.copyOfRange(receivedBytes,12,13)).order(ByteOrder.LITTLE_ENDIAN).get();

                    logger.saveEvent(productId,eventId,currentState);

                    if(eventId==EVENT_PRODUCT_OUT)
                    {
                        productQueue.add(productId);
                        System.out.println(Arrays.toString(productQueue.toArray()));
                    }

                    System.out.printf("PID :%10d  EVENT: %10d %10d %10d\n",productId,eventId,currentState,optionalParam);

                    outputStream.write(ACK);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }




}
