# FTM1

위 자료는 2019 졸업프로젝트 진행 중 아두이노 코드들이며 서버통신과 센서, 모듈제어에 중심을 두고 있습니다.

아두이노 : Arduino Nano

와이파이 모듈 : ESP01
모터드라이버, 인체감지센서 사용 ( 모델명과 무관 )
온도센서 : tmp36

- door0618.ino
  - 사용 라이브러리
    - "WifiEsp.h" , "SoftwareSerial.h"
  
  - 아두이노 pin
    - sensor : 인체감지센서 OUT pin과 연결
    - motorA1, motorA2 : 모터드라이버 A1, A2 pin과 연결
    - Rx, Tx : Serial1에 정의된 2, 3 번 핀으로 ESP01의 TX, RX 핀과 연결
  
  - WiFiEspClient client
    - ESP01 모듈을 사용하기위한 객체 생성
    
  - int connectServer(String s)
    - String s 의 변수로 들어오는 값을 GET 함수로 서버에 HTTP 통신을 통해 송신
    - client.connect("서버 ip", "포트 번호") 서버와 연결하는 함수 사용
    - 서버의 응답을 확인하여 개방여부 파악 후 return
  
  - void openDoor(int m1, int m2, int n)
    - m1, m2 : 모터드라이버의 A1, A2 핀
    - n : delay시간을 조정하기위해 사용한 변수 ( 수정 후 사용X )
    
  - void closeDoor(int m1, int m2, int n)
    - m1, m2 : 모터드라이버의 A1, A2 핀
    - n : delay시간을 조정하기위해 사용한 변수 ( 수정 후 사용X )
  
  - void holdo(int m1, int m2, int t)
    - m1, m2 : 모터드라이버의 A1, A2 핀
    - t : delay 함수롤 사용하여 t 시간동안 모터 정지

- dot_Matrix_nXn.ino
  - 4X4와 8X8 모두 shield가 없어 직접 pin Number에 따른 LED점등 확인으로 모양을 지정함
  
- fire_push0531.ino
  - 사용 라이브러리
    - "WiFiEsp.h", "SoftwareSerial.h"
    
  - WiFi 모듈을 사용한 서버와 연결은 door0618.ino와 동일한 코드를 사용
  
  - Analog pin을 온도센서 ( tmp36 )의 OUTPUT PIN과 연결
  
  - 온도에 따른 Analog pin의 전압크기 변화를 다시 섭씨온도로 변화시킨 후 지정 온도 이상 감지 시 서버에 쿼리문 전달
  
