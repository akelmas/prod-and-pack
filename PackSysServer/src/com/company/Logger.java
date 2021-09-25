package com.company;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.Scanner;

public class Logger {
    void saveEvent(int productId,int eventId,int currentState){
        //get current date and time
        LocalDateTime dateTime=LocalDateTime.now();
        DateTimeFormatter formatter=DateTimeFormatter.ofPattern("yyyyMMddhhmmss");
        String eventWord="NaN";


        switch (eventId){
            case 0:
                eventWord="PRECHECK";
                break;
            case 1:
                eventWord="INPROCESS";
                break;
            case 2:
                eventWord="PASSQUALTYCHECK";
                break;
            case 3:
                eventWord="TRASH";
                break;
        }

        String logLine=String.format("[%s] PID : [%6d] STATE: [%d] EVENT : [%s]\n",dateTime.format(formatter),productId,currentState,eventWord);

        File logFile=new File("log.txt");

        try {
            FileOutputStream fileOutputStream=new FileOutputStream(logFile,true);
            fileOutputStream.write(logLine.getBytes(StandardCharsets.UTF_8));
        } catch (IOException e) {
            e.printStackTrace();
        }


    }
}
