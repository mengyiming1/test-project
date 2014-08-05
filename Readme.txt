Sensor Data Transform Test Project

[Development tool] 
    QtCreator 5.3.0

[Compile environment]
    Qt 5.3
    Windows Desktop Static, MinGW 32bit

[Surce File]
    SensorProjectClient\
        SensorProjectClient.pro   Client application Qt project
        main.cpp                  Client application main source
        sensordata.h              Sensor data abstract base class head
        sensordata.cpp            Sensor data abstract base class source
        xrfsensordata.h           XRF Sensor Data class head
        xrfsensordata.cpp         XRF Sensor Data class source
        emssensordata.h           EMS Sensor Data class head
        emssensordata.cpp         EMS Sensor Data class head
        libssensordata.h          LIBS Sensor Data class source
        libssensordata.cpp        LIBS Sensor Data class source
        sensorclient.h            Sensor Data transfor client head
        sensorclient.cpp          Sensor Data transfor client source
    SensorProcessServer\
        SensorProcessServer.pro   Server application Qt project
        main.cpp                  Server application main source
        testsensorserver.h        Sensor Data transfor server head
        testsensorserver.cpp      Sensor Data transfor server source
        sensordataparser.h        Recieved sensor data processing class head
        sensordataparser.cpp      Recieved sensor data processing class source

[Release]
    Release\client\
         SensorProjectClient.exe  Executable sensor data process client
         xrftestdata.txt          XRF sample test data
         emstestdata.txt          EMS sample test data
         libstestdata.txt         LIBS sample test data
    Release\server\
         SensorProcessServer.exe  Executable sensor data process server application

[Execute]
1. Start server application.
   Double click SensorProcessServer.exe from File Explorer 
   Or follow the following steps
     >Start Windows Command Prompt
     >cd directory  which stores SensorProcessServer.exe
     >.\SensorProcessServer
2. Start client application.
   Double click SensorProcessServer.exe from File Explorer
   Or follow the following steps
     >Start Windows Command Prompt
     >cd directory  which stores SensorProjectClient.exe
     >.SensorProjectClient [server host name]
      * if no host name is given, program will use "127.0.0.1" by default
*Port number 1024 is used
*Client keeps looping in sending sensor data. Press CTL+c to stop the client program
*Server keeps looping in listening from any client. Press CTL+c to stop the server program
   