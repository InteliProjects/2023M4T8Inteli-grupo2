# Inteli - Instituto de Tecnologia e Liderança

<p align="center">
<a href= "https://www.inteli.edu.br/"><img src="assets/inteli.png" alt="Inteli - Instituto de Tecnologia e Liderança" border="0" width=40% height=40%></a>
</p>

<br>

# Solução Orbit

## Orbit

## 👨‍🎓 Integrantes:
- <a href="https://www.linkedin.com/in/claramohammad/">Clara Coelho Mohammad</a>
- <a href="https://www.linkedin.com/in/gabriellysilvavitor/">Gabrielly Silva Vitor</a>
- <a href="https://www.linkedin.com/in/luan-ramos-de-mello-253b28268/">Luan Ramos de Melo</a>
- <a href="https://www.linkedin.com/in/marina-ladeira-867159269/">Marina Ladeira</a>
- <a href="https://www.linkedin.com/in/pedro-henrique-coutinho-cruz/">Pedro Cruz</a>
- <a href="https://www.linkedin.com/in/sophianobrega/">Sophia Nóbrega</a>

## 👩‍🏫 Professores:
### Orientador(a)
- <a href="https://www.linkedin.com/in/fabiana-martins-de-oliveira-8993b0b2/">Fabiana Martins de Oliveira</a>
### Instrutores
- <a href="https://www.linkedin.com/in/victorbarq/">Bruna Mayer</a>
- <a href="https://www.linkedin.com/in/flaviomarquesazevedo/">Flávio Marques Azevedo</a>
- <a href="https://www.linkedin.com/in/henrique-mohallem-paiva-6854b460/">Henrique Paiva</a>
- <a href="https://www.linkedin.com/in/rafael-jacomossi-6135b0a1//">Rafael Jacomossi</a>
- <a href="https://www.linkedin.com/in/vthayashi/">Victor Hayashi</a>

## 📜 Descrição

Este projeto utiliza o microcontrolador ESP32 conectado à internet, gerando uma comunicação eficiente e confiável. O principal ponto do sistema é a transmissão contínua de dados para o Broker MQTT, uma plataforma responsável por gerenciar o envio e recebimento de informações em tempo real, tornando possível acompanhar o desempenho de cada ativo. Além disso, o projeto integra a tecnologia Node.js, proporcionando um acesso fluido ao banco de dados dos ativos. Este banco de dados é uma mina de informações, catalogando detalhes cruciais como a data de validade e o tipo de cada ativo. Esta estrutura não só facilita uma visão abrangente sobre os ativos e sua performance dentro da organização, mas também potencializa a tomada de decisões estratégicas, otimizando as operações e elevando a eficiência empresarial.


Vídeo de demonstração do protótipo: <https://www.youtube.com/watch?v=4CM4yatpG2Y>

## 📁 Estrutura de pastas


A estrutura de diretórios do projeto é organizada da seguinte forma:
<br>|--> assets <br>
<br>|--> documents</br>
 <br>| documentacao.md</br>
 <br>| Manual de Instrução</br>
<br>| --> src</br>
 <br>| --> backend</br>
 <br>| --> firmware</br>
 <br>| --> frontend</br>
| README.MD
A organização dos diretórios do projeto é descrita a seguir:

- `assets`
  - Esta pasta é destinada aos recursos gráficos necessários, como imagens e ícones, utilizados nos materiais da documentação

- `documents`
  - `documentacao.md`: Contém a documentação do projeto em formato de texto, explicando seu funcionamento e instruções de uso.
  - `Manual de Instrução`: Fornece as informações detalhadas sobre a montagem do projeto

- `src`
  - `backend`: Aqui ficam os arquivos responsáveis pela lógica de processamento central do projeto, incluindo a manipulação de dados e a interação com o broker MQTT
  - `firmware`: Nesta pasta fica o código fonte utilizado no ESP32, responsável por fazer as medições e enviar para o canal MQTT
  - `frontend`: Contém os arquivos relacionados à parte da aplicação que interage com o usuário, abrangendo a apresentação visual e os elementos de interação.

- `README.MD`
  - Um arquivo introdutório que oferece uma visão geral do projeto, orientações básicas para sua utilização e outras informações relevantes para quem acessa o repositório pela primeira vez.



## 🔧 Instalação

## Parte de Hardware: Trabalhando com o ESP32

### 1. Arduino IDE
- Baixe e instale a Arduino IDE do [site oficial da Arduino](https://www.arduino.cc/en/software).

### 2. Instalar a Placa ESP32 na Arduino IDE
- Siga as instruções para adicionar suporte para a placa ESP32 na Arduino IDE.

### 3. Escrever e Carregar o Firmware
- Use a Arduino IDE para escrever/carregar o firmware no ESP32.

## Pré-Requisitos de Software

### 1. IDE para Desenvolvimento JavaScript
- Escolha uma IDE como Visual Studio Code, WebStorm, Atom, etc.

### 2. Node.js e npm
- Baixe e instale o Node.js e o npm do [site oficial do Node.js](https://nodejs.org/).

## Instalação do Projeto

### 1. Clonar o Repositório
- Use o comando `git clone https://github.com/2023M4T8Inteli/grupo2.git`.

## Instalar Dependências

### 1. Backend
- Navegue até `Grupo2/Src/backend` e execute `npm i`.

### 2. Frontend
- Navegue até `Grupo2/Src/frontend` e execute `npm i`.

## Executando o Projeto

### 1. Frontend
- Navegue até `src/frontend/src` e execute `npm start`.

### 2. Backend
- Em outro terminal, vá para `src/backend` e execute `node app.js`.

Link para o Manual de Instruções: <https://github.com/2023M4T8Inteli/grupo2/blob/main/document/Manual%20de%20Instru%C3%A7%C3%A3o%20-%20Orbit.pdf>


## 🗃 Histórico de lançamentos

* 1.0 - 29/10/2023  
    **_Scrum master:_** Sophia
    * Clara - Criação de personas e mapa de jornada do usuário;
    * Luan - Proposta de solução, matriz de riscos e Value Proposition Canvas; 
    * Gabrielly - Criação de User Stories e Storyboard;
    * Marina - Requisitos funcionais e proposta de solução;
    * Pedro - Política de privacidade e BOM;
    * Sophia - Análise SWOT, 5 forças de Porter e contexto da indústria.
 
    
* 2.0 - 12/11/2023  
    **_Scrum master:_** Clara
    * Clara - Desenho esquemático da solução e wireframe;
    * Luan - Montagem física do protótipo e documentação de testes; 
    * Gabrielly - Requisitos não funcionais;
    * Marina - Vídeo e documentação do protótipo inicial; 
    * Pedro - Montagem física do protótipo e desenvolvimento do backend; 
    * Sophia - Requisitos não funcionais.


* 3.0 - 24/11/2023  
    **_Scrum master:_** Marina
    * Clara - Melhorias wireframe e mockup;
    * Luan - Desenvolvimento backend e protótipo com display;
    * Gabrielly - Arquitetura da solução;
    * Marina - Casos de teste e vídeo do protótipo;
    * Pedro - Desenvolvimento backend e vídeo arquitetura da solução;
    * Sophia - Revisão documentação da versão anterior.
 
      
* 4.0 - 08/12/2023  
    **_Scrum master:_** Gabrielly
    * Clara - Manual de instruções; 
    * Luan - Criação interface web (frontend);
    * Gabrielly - Arquitetura do protótipo;
    * Marina - Manual de instruções;
    * Pedro - Desenvolvedor da interface web;
    * Sophia - Possibilidades de descarte do protótipo.
 
      
* 5.0 - 21/12/2023  
    **_Scrum master:_** Pedro e Luan
    * Clara - Conclusão e vídeo do protótipo e interface web finais;
    * Luan - Integração do backend e vídeo do protótipo e interface web finais;
    * Gabrielly - Testes de usabilidade e revisão geral;
    * Marina - Arquitetura refinada da solução e documentação testes de guerrilha;
    * Pedro - Integração do backend e vídeo do protótipo e interface web finais;
    * Sophia - Revisão documentação e manual de instruções.

## 📋 Licença/License
[Grupo 2](https://github.com/2023M4T8Inteli/grupo2) © 2023 [by Clara Mohammed, Gabrielly Vitor, Luan Ramos de Mello, Marina Ladeira, Pedro Cruz e Sophia Nóbrega](https://www.inteli.edu.br/) is licensed under [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/?ref=chooser-v1)
