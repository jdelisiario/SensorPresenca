#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <EthernetServer.h>
#include <EthernetUdp.h>

//Define o pino que lerá o LED
#define LED 7
//Define o pino que lerá o Sensor
#define PIR 2

//Configura a shield Ethernet para a nossa rede
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //physical mac address
byte ip[] = { 192, 168, 0, 120 }; // ip in lan
byte gateway[] = { 192, 168, 0, 1 }; // internet access via router
byte subnet[] = { 255, 255, 255, 0 }; //subnet mask

//Escolhe a porta que será o servidor - Como a porta é a 80, o protocolo utilizado é TCP
EthernetServer server(80); //server port

//Variável que receberá as variações do sinal do sensor de presença
byte leitura;

void setup(){
  //Inicializa a shield com os dados pré-determinados
  Ethernet.begin(mac, ip, gateway, subnet);
  //Define a frequência para 9600
  Serial.begin(9600);

  //Define que o pino do LED será de saída
  pinMode(LED, OUTPUT);
  //Define que o pino do sensor será de entrada
  pinMode(PIR, INPUT);
}

void loop(){
  //Torna o servidor acessível
  EthernetClient client = server.available();

  //Faz o arduino ler o sensor
  leitura = digitalRead(PIR);
  
  //Escreve no LED a situação do sensor
  //Quando sensor 1 houve detecção de movimento, então acende o LED
  //Quando sensor 0 não houve detecção de movimento, então apaga o LED
  digitalWrite(LED, leitura);
   
  if(leitura){
    //Exibe a página quando há movimentação detectada pelo sensor
    client.println(F("HTTP/1.1 200 OK"));
    client.println(F("Content-Type: text/html"));
    client.println("Refresh: 1");
    client.println(F("\r\n"));
    client.println(F("<HTML>"));
    client.println(F("   <head>"));
    client.println(F("      <title>Sensoriamento da Fazenda Comp01</title>"));
    client.println(F("   </head>"));
    client.println(F("   <body>"));
    client.println(F("      <h3>Sensor de deteccao de presenca</h3>"));
    client.println(F("      <h2> Movimento detectado</h2> "));
    client.println(F("   </body>"));
    client.println(F("</html>"  ));
    
    delay(1);                     
    client.stop();  //stopping client                    
                    
  } else {
    //Exibe a página quando não há movimentação detectada pelo sensor
    client.println(F("HTTP/1.1 200 OK"));
    client.println(F("Content-Type: text/html"));
    client.println("Refresh: 1");
    client.println(F("\r\n"));
    client.println(F("<HTML>"));
    client.println(F("   <head>"));
    client.println(F("      <title>Sensoriamento da Fazenda Comp01</title>"));
    client.println(F("   </head>"));
    client.println(F("   <body>"));
    client.println(F("      <h3>Sensor de deteccao de presenca</h3>"));
    client.println(F("      <h2> Movimento nao detectado</h2> "));
    client.println(F("   </body>"));
    client.println(F("</html>"  ));
    
    delay(1);                     
    client.stop();  //stopping client                 

   }
}
 





