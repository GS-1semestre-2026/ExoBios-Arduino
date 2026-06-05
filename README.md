# EXOBIOS - Sistema Inteligente de Controle para Estufas

## Integrantes do Grupo

* Amanda Silva da Mata
* Beatriz Mantovani da Cruz
* Felipi Bandeira de Godoy
* Gustavo Ducatti Bugelli
* Laura Sampaio Neves

---

# Descrição do Projeto

O EXOBIOS é um sistema inteligente de monitoramento e controle ambiental para estufas agrícolas desenvolvido com Arduino, pensado para operar em ambientes hostis como bases na Lua ou em Marte.

O projeto simula uma estufa automatizada capaz de monitorar temperatura, umidade do ar e luminosidade, ajustando automaticamente as condições ideais para diferentes culturas agrícolas selecionadas pelo usuário.

A proposta busca representar como sistemas embarcados e automação podem auxiliar na produção de alimentos em missões espaciais de longa duração, onde o cultivo precisa ocorrer em ambientes controlados, com pouca intervenção humana e alta eficiência no uso de recursos.

---

# Objetivo da Solução

Desenvolver uma estufa inteligente capaz de monitorar e controlar automaticamente as condições ambientais necessárias para o cultivo de alimentos em ambientes extremos, como a Lua e Marte.

O sistema tem como objetivos:

* Monitorar temperatura do ambiente;

* Monitorar umidade do ar;

* Monitorar luminosidade;

* Permitir a seleção de diferentes culturas agrícolas;

* Ajustar automaticamente os parâmetros ideais para cada planta;

* Emitir alertas quando as condições estiverem fora da faixa adequada;

* Demonstrar aplicações de automação e sistemas embarcados na agricultura espacial.

--- 

<img width="1067" height="740" alt="image" src="https://github.com/user-attachments/assets/13ddbd10-2e68-401a-8776-2df1dc1aaed5" />

---

# Plantas Disponíveis

O sistema possui suporte para as seguintes culturas:

1. Alface
2. Tomate
3. Cenoura
4. Ervilha
5. Batata-doce
6. Grão-de-bico
7. Ora-pro-nóbis

Cada planta possui requisitos próprios de temperatura, umidade e luminosidade, tornando o sistema mais flexível e adaptável a diferentes cenários de cultivo.

---

# Componentes Utilizados

## Hardware

| Componente            | Quantidade |
| --------------------- | ---------- |
| Arduino Uno           | 1          |
| Display LCD 16x2 I2C  | 1          |
| Sensor DHT22          | 1          |
| Sensor LDR            | 1          |
| Teclado Matricial 4x4 | 1          |
| Buzzer                | 1          |
| LED Vermelho          | 1          |
| LED Azul              | 1          |
| LED Verde             | 1          |
| LED Branco            | 1          |
| Protoboard            | 1          |
| Jumpers               | Diversos   |

## Bibliotecas

* Wire.h
* LiquidCrystal_I2C.h
* DHT.h
* Keypad.h

---

# Explicação do Funcionamento

## Inicialização

Ao iniciar o sistema, é exibida uma tela de carregamento no display LCD.

Após alguns segundos, o menu de seleção de culturas é apresentado ao usuário.

---

## Seleção da Cultura

A navegação é realizada por meio do teclado matricial.

### Controles

| Tecla | Função                     |
| ----- | -------------------------- |
| A     | Próxima planta             |
| B     | Planta anterior            |
| #     | Confirmar seleção          |
| D     | Retornar ao menu principal |

Após a confirmação, o sistema carrega automaticamente os parâmetros ideais da planta escolhida.

---

## Monitoramento Ambiental

Após a seleção da cultura, o sistema passa a monitorar continuamente:

### Temperatura

Obtida através do sensor DHT22.

O sistema verifica se a temperatura está:

* Abaixo do mínimo ideal;
* Dentro da faixa ideal;
* Acima do máximo ideal.

### Umidade do Ar

Obtida através do sensor DHT22.

O sistema verifica se a umidade está:

* Abaixo do ideal;
* Dentro da faixa adequada;
* Acima do ideal.

### Luminosidade

Obtida através do sensor LDR.

O sistema verifica se a luminosidade está:

* Baixa;
* Adequada;
* Excessiva.

---

# Sistema de Alertas

## LED Vermelho

Indica necessidade de aquecimento.

Ativado quando:

Temperatura < Temperatura mínima da planta.

---

## LED Azul

Indica necessidade de resfriamento.

Ativado quando:

Temperatura > Temperatura máxima da planta.

---

## LED Verde

Indica necessidade de correção da umidade.

Ativado quando:

* Umidade abaixo do mínimo;
* Umidade acima do máximo.

---

## LED de Iluminação

Indica necessidade de correção da luminosidade.

Ativado quando:

* Luminosidade abaixo do mínimo;
* Luminosidade acima do máximo.

---

## Buzzer

O buzzer é acionado sempre que qualquer parâmetro estiver fora da faixa ideal.

Isso permite alertar rapidamente o operador da estufa sobre possíveis problemas ambientais.

---

# Display LCD

O display apresenta informações em tempo real.

### Linha 1

Nome da planta selecionada.

Exemplo:

ALFACE

### Linha 2

Estado atual do sistema.

Exemplos:

| Código      | Significado                               |
| ----------- | ----------------------------------------- |
| AQ          | Aquecendo                                 |
| RF          | Resfriando                                |
| UM-         | Umidade abaixo do ideal                   |
| UM+         | Umidade acima do ideal                    |
| LUZ+        | Luminosidade abaixo do ideal              |
| LUZ-        | Luminosidade acima do ideal               |
| AMBIENTE OK | Todos os parâmetros dentro da faixa ideal |

O LCD pode exibir múltiplas condições simultaneamente quando mais de um parâmetro estiver fora da faixa adequada.

---

# Monitor Serial

O sistema também envia informações detalhadas para o Serial Monitor.

Exemplo:

Planta: TOMATE | Temp: 32.1 | Umidade: 55.0 | Luz: 950 | Status: RF UM-

Essas informações auxiliam na análise do comportamento da estufa e facilitam testes e depuração do sistema.

---

# Parâmetros das Culturas

| Cultura       | Temperatura | Umidade   | Luminosidade |
| ------------- | ----------- | --------- | ------------ |
| Alface        | 18°C - 24°C | 60% - 80% | 400 - 800    |
| Tomate        | 20°C - 30°C | 60% - 75% | 600 - 1000   |
| Cenoura       | 16°C - 24°C | 55% - 70% | 500 - 900    |
| Ervilha       | 13°C - 22°C | 60% - 80% | 400 - 850    |
| Batata-doce   | 21°C - 30°C | 50% - 70% | 600 - 1000   |
| Grão-de-bico  | 18°C - 30°C | 40% - 60% | 650 - 1000   |
| Ora-pro-nóbis | 20°C - 35°C | 30% - 60% | 700 - 1023   |

---

# Estrutura do Circuito

## Sensor DHT22

| DHT22 | Arduino |
| ----- | ------- |
| VCC   | 5V      |
| SDA   | D2      |
| GND   | GND     |

## Display LCD I2C

| LCD | Arduino |
| --- | ------- |
| VCC | 5V      |
| GND | GND     |
| SDA | A4      |
| SCL | A5      |

## Sensor LDR

| LDR | Arduino |
| --- | ------- |
| VCC | 5V      |
| GND | GND     |
| AO  | A1      |

## Buzzer

| Buzzer   | Arduino |
| -------- | ------- |
| Positivo | A2      |
| Negativo | GND     |

## LEDs

| LED        | Pino |
| ---------- | ---- |
| Vermelho   | D10  |
| Azul       | D8   |
| Verde      | D9   |
| Iluminação | D11  |

## Teclado Matricial

| Keypad | Arduino |
| ------ | ------- |
| R1     | D3      |
| R2     | D4      |
| R3     | D5      |
| R4     | D6      |
| C1     | D7      |
| C2     | D12     |
| C3     | D13     |
| C4     | A0      |

---

# Instruções de Execução

## Wokwi

1. Abrir o projeto no Wokwi.
2. Verificar se as bibliotecas estão instaladas:

   * LiquidCrystal I2C
   * DHT Sensor Library
   * Keypad
3. Executar a simulação.
4. Selecionar uma cultura utilizando o teclado matricial.
5. Alterar os valores dos sensores para observar as respostas do sistema.
6. Acompanhar os resultados pelo LCD, LEDs, buzzer e Serial Monitor.

---

# Link da Simulação

[LINK DO PROJETO](https://wokwi.com/projects/465581583251762177)

---

# Possíveis Melhorias Futuras

* Sensor de umidade do solo;
* Controle automático de irrigação por bomba d'água;
* Controle automático de ventilação;
* Integração com IoT;
* Aplicativo mobile;
* Armazenamento em nuvem;
* Histórico de dados ambientais;
* Inteligência Artificial para previsão de condições ideais.

---

# Tecnologias Utilizadas

* Arduino Uno
* Linguagem C++
* Wokwi Simulator
* Sensores ambientais
* Sistemas embarcados

---

# Conclusão

O EXOBIOS demonstra a aplicação de conceitos de automação, sensoriamento e monitoramento inteligente voltados para a agricultura.

Através da combinação de sensores, atuadores e programação embarcada, o sistema é capaz de simular uma estufa inteligente adaptável a diferentes culturas, promovendo maior controle ambiental, redução de riscos e auxílio na tomada de decisões para o cultivo agrícola.
