# Projeto_3_lp1
Projeto de um mini ventilador teleguiado para refrescar a mente de um programador estressado usando OpenCV, Arduino e C++/C

A ideia original consistia em utilizar o algorítimo de detecção de faces da biblioteca OpenCV com o intuito de identificar a posição relativa do usuário e com isso movimentar um sistema com dois motores, um para o eixo horizontal e outro para o eixo vertical que ajustariam o ventilador. Por conta de problemas técnicos, um dos motores queimou e fomos impossibilitados de continuar com o projeto para dois eixos, então no projeto final, apenas um dos eixos foi levado em conta.

Para poder detectar a face do usuário presente, foi utilizado o método de treinamento  do Haar Cascade(CascadeClassifier::load) para carregar os modelos em XML de pré-treinamento do programa, presentes no diretório local da biblioteca OpenCV. Em seguida, dentro de um while, criamos um retângulo em volta de cada face detectada através de um vector de retângulos, ajustando o retângulo de acordo com o tamanho da face em relação à distância da webcam, um para cada face detectada.

Para transformar os dados da posição do retângulo da face em dados de ângulos, dividiu-se o retângulo obtido a partir do Webcam Feed em nove partes de comprimento igual, enumeradas da mais à esquerda até a mais à direita, e foi verificado por operadores ternários em sequência em qual das nove partes o ponto localizado no centro do retângulo da face detectada está localizado. 

Após isso, como cada uma das nove partes representa um ângulo que é enviado para o microcontrolador, foi necessário criar uma lógica para impedir o flood do buffer enquanto o motor ainda funcionava para solucionar os bugs gerados por isso. Com este objetivo, foi utilizada a biblioteca ctime e uma lógica que permite o envio de dados para o microcontrolador apenas após a permanência por 1.5 segundos(um valor arbitrário) do centro do retângulo da face detectada na mesma parte, resolvendo o problema.

E por fim, através da biblioteca SerialPort os dados dos ângulos em formato de string foram utilizados para fazer o servo motor(eixo x) se mover. Para tal, as informações das strings foram convertidas para valores inteiros. Por fim, foi utilizado um botão de enable auxiliar no controle e calibração do servo.

O link abaixo leva a um vídeo que mostra o codigo e a estrutura montada em funcionamento:
https://drive.google.com/file/d/1hq2FR_1ShWW31F17uoKjIBnaZOjayKGb/view?usp=sharing

INTEGRANTES:

Miguel Elias Silva Rodrigues, 20190018853.
