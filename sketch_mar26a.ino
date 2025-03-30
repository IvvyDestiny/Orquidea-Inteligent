/*
  Projeto: Sistema de Monitoramento de Umidade para Orquídeas
  Autor: Ivan (com suporte de Microsoft Copilot)
  Data: Março de 2025
  Descrição:
    Este código controla LEDs com base nos sinais de um sensor de umidade,
    indicando os níveis de umidade do substrato de uma orquídea em um vaso fechado.

  Funcionalidades:
    - Vermelho: Solo muito seco
    - Amarelo: Solo levemente seco
    - Azul: Umidade moderada
    - Verde: Umidade ideal
    - Branco: Solo muito úmido

  Componentes Necessários:
    - Sensor de Umidade MH séries
    - LEDs (Vermelho, Amarelo, Azul, Verde, Branco)
    - Resistor de 220Ω (1 por LED)
    - Arduino Nano
    - Regulador LM7805
    - Bateria 9V
    - Jumpers e Protoboard

  Direitos:
    Este código foi gerado com suporte de Microsoft Copilot. Ele é fornecido como parte de um guia de aprendizado,
    e o autor (Ivan) tem total liberdade para utilizar, modificar e adaptar o código conforme necessário.

  Notas:
    - Certifique-se de ajustar os limites de umidade conforme necessário para a sua planta e condições específicas.
    - Recomenda-se monitorar regularmente o sistema para garantir o funcionamento adequado.
    - Em caso de dúvida ou problemas, entre em contato ou revise o circuito com cuidado.

  Ligações:
  Conexões do Circuito
1. Alimentação (Bateria 9V e LM7805)
- Bateria 9V:- Positivo (+): Conecte ao pino IN do regulador LM7805.
- Negativo (-): Conecte ao GND do regulador LM7805.

- Regulador LM7805:- IN: Recebe o positivo da bateria de 9V.
- GND: Conecte ao negativo da bateria e ao GND geral do circuito.
- OUT: Fornece 5V estabilizados para o Arduino Nano no pino VIN.

2. Sensor de Umidade (MH séries)
- VCC: Conecte ao pino 5V do Arduino Nano.
- GND: Conecte ao GND do Arduino Nano.
- Saída Analógica (A0): Conecte ao pino A0 do Arduino Nano.

3. LEDs (Vermelho, Amarelo, Azul, Verde, Branco)
- Conecte o ânodo (pino positivo) de cada LED ao resistor de 220Ω e depois aos pinos digitais do Arduino Nano:- LED Vermelho: Pino D2.
- LED Amarelo: Pino D3.
- LED Azul: Pino D4.
- LED Verde: Pino D5.
- LED Branco: Pino D6.
- O cátodo (pino negativo) de cada LED deve ser conectado ao GND do Arduino Nano.

4. Arduino Nano
- VIN: Recebe 5V do regulador LM7805.
- GND: Conecte ao GND geral do circuito.
- A0: Conectado ao sensor de umidade.
- Pinos Digitais (D2 a D6): Conectados aos LEDs.

    ESQUEMA DE LIGAÇÃO
    _____________________________________________________________________________________
    |  Bateria 9V (+) ____> IN (LM7805) ____> OUT (5V)______________> VIN (5V) (Arduino)|
    |                         |                               |              |          |
    |                        GND        Sensor Umidade: VCC___|              |          |
    |Bateria 9V (-) ----------|<------  Sensor Umidade GND:                  |          |
    |                                   Sensor Umidade(out):|================|          |
    |                                                                        |          |
    |       LEDs:                                                            |          |
    | Vermelho:   Anodo ---> D2 (Arduino)|---------------------------------- |          |
    |             Catodo---> ---> Resistor ---> GND                          |          |
    | Amarelo:    Anodo ---> D3 (Arduino)|-----------------------------------|          |
    |             Catodo---> ---> Resistor ---> GND                          |          |
    | Azul:       Anodo ---> D4 (Arduino)|-----------------------------------|          |
    |             Catodo---> ---> Resistor ---> GND                          |          |
    | Verde:      Anodo ---> D5 (Arduino)|-----------------------------------|          |
    |             Catodo---> ---> Resistor ---> GND                          |          |
    | Branco:     Anodo ---> D6 (Arduino)|-----------------------------------|          |
    |             Catodo---> ---> Resistor ---> GND                                     |
    |                                                                                   |
    |                                                                                   |
    |                                                                                   |
    |___________________________________________________________________________________|
                 (Arduino)
                OUT ---> A0 (Arduino)


*/

const int sensorPin = A0;         // Pino do sensor de umidade
const int leds[] = {2, 3, 4, 5, 6}; // Pinos dos LEDs: vermelho, amarelo, azul, verde, branco
const int thresholds[] = {300, 500, 700, 900}; // Limites de umidade para os LEDs

void setup() {
  for (int i = 0; i < 5; i++) {
    pinMode(leds[i], OUTPUT); // Configura os pinos dos LEDs como saída
  }
  Serial.begin(9600); // Inicia comunicação serial para monitorar a umidade
}

void loop() {
  int moisture = analogRead(sensorPin); // Lê a umidade do solo
  Serial.print("Umidade do solo: ");
  Serial.println(moisture);

  // Determina qual LED acender com base nos limites
  for (int i = 0; i < 5; i++) {
    if (i == 4 || moisture < thresholds[i]) {
      digitalWrite(leds[i], HIGH); // Acende o LED correspondente
    } else {
      digitalWrite(leds[i], LOW);  // Apaga os LEDs fora do limite
    }
  }

  delay(2000); // Aguarda 2 segundos antes de atualizar
}
