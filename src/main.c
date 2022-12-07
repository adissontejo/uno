#include <stdio.h>
#include <string.h>

#include "../include/players.h"
#include "../include/cards.h"

#define MAX_LINE 100
#define MAX_ACTION 10
#define MAX_ID_SIZE 10

void debug(char *message) {
  fprintf(stderr, "%s\n", message);
}

int main() {
  char temp[MAX_LINE];
  char my_id[MAX_ID_SIZE];

  setbuf(stdin, NULL);
  setbuf(stdout, NULL);
  setbuf(stderr, NULL);

  readPlayers();

  scanf("YOU %s\n", my_id);

  readCards();
  
  // Lê a carta aberta sobre a mesa. Ex: TABLE 8♣
  scanf("TABLE %s\n", temp);

  char id[MAX_ID_SIZE];
  char action[MAX_ACTION];
  char complement[MAX_LINE];

  int qtBuy = 0;

  /*
  O `while(1) faz o bot entra num laço infinito, mas não se preocupe. O simulador do jogo irá
  "matar" o seu programa quando o jogo terminar.
  O jogo termina em duas ocasiões:
    1) quando um bot não tiver mais carta (GANHOU!)
    2) quando não tiver mais carta na pilha para comprar.
  Nesse último caso, ganha quem tiver menos cartas na mão. Em caso de mais de um bot ter o menor
  número de cartas na mão, todos eles são considerados os ganhadores.
  */
  while(1) {
    while (1) {
      scanf("%s %[^\n]", action, complement);

      if (strcmp(action, "TURN") == 0 && strcmp(complement, my_id) == 0) {
        break;
      }

      qtBuy = 0;

      if (strcmp(action, "DISCARD") == 0) {
        if (complement[0] == 'V') {
          qtBuy = 2;
        } else if (complement[0] == 'C') {
          qtBuy = 4;
        }
      }
    }

    
    // agora é a vez do seu bot jogar
    
    /*
    Seu bot realiza uma ação no jogo enviando para a saída-padrão uma string no formato:
      <ação> <complemento1> [complemento2]

    Por exemplo, se o bot anterior soltar uma carta de compra (compre 2 ou compre 4), a
    <ação> que seu bot deve fazer é "BUY" e o <complemento1> será "2" ou "4", dependendo da
    quantidade de cartas que ele deve comprar.
    Ou seja, a string que seu bot deve enviar para a saída-padrão será:
    - "BUY 4", se o bot anterior soltou um Coringa (C), ou;
    - "BUY 2", se o bot anterior soltou um Valete (V).
    Depois do envio desta ação, o simulador irá enviar para o seu bot uma quantidade de cartas
    correspondente ao número solicitado. Então, prepare-se para ler da entrada padrão as cartas.
    Se a ação for "BUY 2", leia duas strings. Elas serão as cartas compradas e você deve
    guardá-las na sua mão. Se for "BUY 4", leia 4 strings.
    Depois da leitura, termina a vez do seu bot e o simulador passa a vez para um outro bot.

    Caso não tenha nenhuma ação de compra a ser realizada, seu bot deve jogar normalmente,
    que é descartar uma carta cujo valor ou naipe é o mesmo da carta da mesa. Ou seja, você
    deve saber qual a última carta descartada ou, se foi um Ás ou Coringa, qual o naipe
    solicitado.

    No exemplo abaixo, a <ação> é "DISCARD" e o <complemento1> é a carta a ser descartada:
      "DISCARD 2♣"

    O bot também pode descartar uma carta especial, independente do naipe da mesa, que pode
    ser um Ás (A = muda de naipe) ou um Coringa (C = além de fazer o próximo comprar 4,
    também muda o naipe). As demais cartas devem obrigatoriamente seguir o naipe da mesa.

    Ao descartar um Ás ou Coringa, você deve enviar um segundo complemento para sua ação com
    o naipe que você deseja. Por exemplo:
      "DISCARD C♣ ♥"
    Neste caso, seu bot soltou um coringa preto e pediu para o naipe mudar para ♥ (o próximo
    jogador precisar comprar 4 cartas e o seguinte levar em conta que o ♥ é o naipe da vez).
    Depois do descarte, a vez do seu bot termina.

    Se o bot não tiver carta com o naipe da mesa para descartar, ele deve comprar uma carta
    do baralho, enviando a ação "BUY" e o complemento "1", informando que ele irá comprar uma
    carta da pilha.
    Assim como as ações "BUY 2" e "BUY 4", após o envio desta ação, seu bot deve ler da
    entrada-padrão a carta puxada da pilha e guarde na sua mão.

    Vale ressaltar que nada impede do bot comprar quantas cartas quiser, mesmo tendo uma carta
    na mão com o valor ou naipe da mesa. Só não é possível comprar uma quantidade diferente de
    cartas quando ele deve obrigatoriamente comprar 2 (por causa de um Valete) ou 4 (por causa
    de um coringa).

    Depois da carta lida, não há opção de descarte. Agora, é a vez de um outro bot jogar.

    Além das ações de descartar (DISCARD) e comprar (BUY), o bot pode também enviar mensagens
    para serem apresentadas no jogo. Essas mensagens não são repassadas para os outros bot, mas
    aparecem no console. Para enviar uma mensagem, o bot deverá enviar para a saída-padrão o
    seguinte comando:
      SAY <text>

    O bot pode enviar quantas mensagens quiser, desde que seja *ANTES* das ações de descarte ou
    de compra. Alguns exemplos de mensagens são:
      "SAY Caramba! Eu já ia bater!"
      "SAY Tu tá lascado!!!"

    Resumindo, o bot pode realizar uma das seguintes ações:
    - "SAY <text>", onde <texto> é uma mensagem que irá aparecer durante a partida.
    - "DISCARD <card> [naipe]", onde <card> é a carta da mão a ser descartada.
      Se <card> for um Coringa (C) ou Ás (A), um naipe deve ser informado também.
    - "BUY <num>", onde <num> é a quantidade de cartas a serem compradas da pilha.

    Exemplos:
      DISCARD 4♥
      DISCARD A♣ ♥
      SAY Droga!
      BUY 2
      BUY 4
      BUY 1

    OBS: Todas as mensagens enviadas **DEVEM terminar com salto de linha ('\n')**, caso
         contrário, o simulador não saberá quando uma ação termina e quebrar o sincronização
         das mensagens.

    Qualquer ação enviada para o simulador que não seja condizente com o estado do jogo,
    haverá uma penalidade para o bot.
    - Se o bot descartar uma carta que não tem na mão ou se o naipe da carta não for o que
      se encontra sobre a mesa, a ação será ignorada. Ou seja, para o simulador, o bot
      continuará com a referida carta na mão.
    - Se o bot precisar comprar 2 ou 4 cartas e não enviar a ação "BUY" com o complemento
      correspondente, o bot sai do jogo e perde de vez a partida. 
    
    Outra penalidade é se o bot demorar mais de 3 segundos para responder uma ação. Isso
    significa que a leitura e escrita dos dados está fora de sincronia com o simulador
    (o bot esperando um dado do simulador e o simulador esperando um dado do bot).
    Nesse caso, o bot também será removido da partida.
    */

    // Nesse exemplo de ação, o bot tenta descartar a carta 4♥.
    // Se ele não tiver na mão, a ação é simplesmente ignorada.
    if (qtBuy != 0) {
      buyCards(qtBuy);

      continue;
    }

    char card[] = "A♥ ♥";
    printf("DISCARD %s\n", card);
  }

  return 0;
}