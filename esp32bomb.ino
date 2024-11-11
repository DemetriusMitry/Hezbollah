#include <WiFi.h>
#include <ThingESP.h>

ThingESP32 thing("User Name", "Project Title", "Project Credential");

const int armador = 22; // Pino do LED
const int detonador = 23;  // Pino 10
String countdownCommand = ""; // Comando de contagem regressiva

void setup() {
    Serial.begin(115200);
    pinMode(detonador, OUTPUT); // Configura o pino do LED como saída
    pinMode(armador, OUTPUT);  // Configura o pino 10 como saída
    digitalWrite(armador, LOW); // Garante que o LED comece desligado
    digitalWrite(detonador, LOW);   // Garante que o pino 10 comece desligado
    thing.SetWiFi("NOME-DO-WIFI", "SENHA-DO-WIFI");
    thing.initDevice();
}

String HandleResponse(String query) {
    if (query.startsWith("detone em ")) {
        countdownCommand = query.substring(10); // Extrai o número da contagem
        return "Iniciando contagem regressiva para " + countdownCommand + "";
    } else if (query == "armar bomba") {
        return "Digite a senha para armar a bomba:";
    } else if (query.startsWith("senha")) {
        String inputPassword = query.substring(5); // Extrai a senha fornecida
        if (inputPassword == " secreta") {
            digitalWrite(armador, HIGH); // Liga o pino 10
            return "Bomba Armada!";
        } else {
            return "Senha incorreta. Tente novamente.";
        }
    } else if (query == "detone") {
            digitalWrite(detonador, HIGH); // Aqui você pode adicionar a lógica da detonação
            return "Detonando.";
    } else {
            return "Não fez Cabum!!!";
        }
       return "Mensagem Enviada Com Sucesso!!!";
    }
void loop() {
    thing.Handle();

    if (countdownCommand.length() > 0) {
        int countdownValue = countdownCommand.toInt();
        for (int i = countdownValue; i >= 0; i--) {
            Serial.println(i);
            delay(1000); // Espera 1 segundo
        }
        digitalWrite(detonador, HIGH); // Acende o LED
        Serial.println("Explosão Iniciada!");
        countdownCommand = ""; // Reseta o comando após a execução
    }
}
