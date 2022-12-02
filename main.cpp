#include <iostream>
#include <stdlib.h>

using namespace std;

// ALUNOS 
// Gabriel Da Silveira Vanolli
// Henrique Tabalipa Alves Da S
// Thiago Henrique Dalsochio

int main() {
  setlocale(LC_CTYPE, "");

  /*
  LEGENDA DAS VARIAVEIS:

  colunas = numero de colunas informadas pelo usuario;
  c = variavel do loop FOR para caminhar pelas colunas do campo minado;
  cc = variavel do loop FOR para caminhar pelas colunas vizinhas a bomba
  adicionada; 
  cb = variavel usada DENTRO do loop FOR para gerar aleatóriamente a
  coluna onde ficará a bomba; 
  colunaVizinha = variavel usada DENTRO do loop FOR para dizer qual coluna vizinha da bomba está sendo tratada;
  linhas = numero de linhas informadas pelo usuario;
  l = variavel do loop FOR para caminhar pelas linhas do campo minado;
  ll = variavel do loop FOR para caminhar pelas linhas vizinhas a bomba adicionada; 
  lb = variavel usada DENTRO do loop FOR para gerar aleatóriamente a linha onde ficará a bomba;
  linhaVizinha = variavel usada DENTRO do loop FOR para dizer qual linha vizinha da bomba está sendo tratada;
  bombas = quantidade de bombas informadas pelo usuario;
  b = variavel do loop FOR para caminhar pelo numero de bombas informadas;
  escolhaL = linha informada pelo usuario
  escolhaC = coluna informada pelo usuario
  campos = numeros de campos totais no jogo (é feita uma conta de linhas * colunas)
  camposRevelados = numero de campos revelados por uma jogada do usuario
  jogadas = numero de jogadas unicas (jogadas válidas sem pisar em uma bomba)
  
  fim = indica fim do jogo
  bomba = indica se uma bomba explodiu

  */
  int colunas, c, cc, cb, colunaVizinha, linhas, l, ll, lb, linhaVizinha,
      bombas, b, escolhaL, escolhaC, campos,
                       camposRevelados = 0, jogadas = 0;
  bool fim = false, bomba = false;


  // Solicita ao usuário o número de linhas para gerar o campo minado
  cout << "Informe o número de LINHAS: ";
  cin >> linhas;

  // Verifica se o usuário informou pelo menos 2 linhas.
  if (linhas < 2) {
    linhas = 2;
  }
  
  // Solicita ao usuário o número de colunas para gerar o campo minado
  cout << "Informe o número de COLUNAS: ";
  cin >> colunas;

  // Verifica se o usuário informou pelo menos 2 colunas.
  if (colunas < 2) {
    colunas = 2;
  }

  // Faz o calculo do número total de campos no jogo.
  campos = linhas * colunas;

  // Solicita ao usuário o número de bombas para adicionar ao campo minado
  cout << "Informe o número de BOMBAS: ";
  cin >> bombas;

  // Verifica se o número de bombas é maior que o número de campos no jogo,
  // se for maior, deixa pelo menos 1 campo livre para ser escolhido.
  if (bombas >= campos) {
    bombas = campos - 1;
  }

  // Após receber as quantidades e verifica-las, as matrizes são criadas.
  // campoMinado é a matriz do jogo completo, onde estão os numeros e as bombas.
  int campoMinado[linhas][colunas];
  // campoMinadoB é a matriz de tela, que será mostrada ao usuário
  int campoMinadoB[linhas][colunas];

  // Matriz campoMinado é preenchido por zeros para poder receber as bombas.
  for (l = 0; l < linhas; l++) {
    for (c = 0; c < colunas; c++) {
      campoMinado[l][c] = 0;
    }
  }

  // variavel randomica que reseta o numero baseado tempo
  srand(time(NULL));

  // loop FOR para gerar as bombas no campoMinado
  for (b = 0; b < bombas; /* no primeiro if*/) {
    
    // decide qual linha e qual coluna ficará a bomba
    // o numero randomica % linha significa que a função rand()
    // não pode ser maior que o número de linhas/colunas
    lb = rand() % linhas;
    cb = rand() % colunas;

    // se a posição aleatória não tiver uma bomba ainda (bombas são numero 9)...
    if (campoMinado[lb][cb] != 9) {
      // ...então adiciona +1 na variavel b para dizer que uma nova bomba foi adicionada
      b++;

      // adiciona a bomba na posicao aleatorio (bombas são numero 9)
      campoMinado[lb][cb] = 9;

      // loop para verificar os vizinhos da bomba
      /*
         EXPLICANDO O LOOP:
          O loop imagina uma mini matriz de 3x3 em que na posição central está a bomba.
          Usando operação matemática simples de menos com menos é igual a mais,
          fizemos um FOR que começa da posicao 1x1 e vai até a 3x3.

          Para chegar na linha/coluna vizinha, usa-se a 
          posição da bomba - o valor atual do loop
            
            EXEMPLO: 

            ** linha bomba LB = 5
            *variavel loop LL = 1

            linhaVizinha a esquerda: 5 - 1 = 4
            linhaVizinha do meio (onde a bomba está): 5 - 0 = 5
            linhaVizinha a direita: 5 - -1 = 6

            * coluna bomba CB = 6
            *variavel loop CC = 1

            colunaVizinha a esquerda: 6 - 1 = 4
            colunaVizinha do meio (onde a bomba está): 6 - 0 = 6
            colunaVizinha a direita: 6 - -1 = 6
        
      */
      for (ll = 1; ll >= -1; ll--) {
        linhaVizinha = lb - ll;

        // verifica se a linhaVizinha não é fora do mapa do campo
        if (linhaVizinha >= 0 && linhaVizinha < linhas) {
          for (cc = 1; cc >= -1; cc--) {
            colunaVizinha = cb - cc;

            // verifica se a colunaVizinha não é fora do mapa do campo
            if (colunaVizinha >= 0 && colunaVizinha < colunas) {

              // se o vizinho ao redor da bomba NÃO for outra bomba, então adicione +1
              if (campoMinado[linhaVizinha][colunaVizinha] < 9) {
                campoMinado[linhaVizinha][colunaVizinha] =
                    campoMinado[linhaVizinha][colunaVizinha] + 1;
              }
            }
          }
        }
      }
    }
  }

  
  // MATRIZ DO MAPA QUE SERÁ MOSTRADO NA TELA PARA O USUARIO

  // Gera a matriz vazio com -1 
  // (-1 para simbolizar campo disponivel para selecao)
  // ** escolhemos -1 (ao inves de 0) para melhor entendimento dentro do codigo
  // para evitar confusão com a primeira matriz criada la em cima
  for (l = 0; l < linhas; l++) {
    for (c = 0; c < colunas; c++) {
      campoMinadoB[l][c] = -1;
    }
  }

  // JOGO COMEÇA... ENQUANTO A VARIAVEL fim FOR FALSA, O LOOP RODARÁ
  while (fim == false) {
    // campos - bombas signfica campos válidos que o usuário pode escolher sem perder;
    // campos revelados significa a quantidade de campos que já foram revelados através
    // das jogadas do usuário;
    // caso os camposValidos e os camposRevelados forem iguais, o usuário ganhou!
    if (campos - bombas == camposRevelados) {
      fim = true;
      break;
    }

    // SE O USUÁRIO AINDA NÃO GANHOU O JOGO, O CAMPO É DESENHADO NA TELA
    // **ABAIXO LOOPS DE ESTICA DO JOGO

    system("cls|clear");
    // loop para desenhar o numero das colunas no topo da grade
    cout << "       ";
    for (c = 0; c < colunas; c++) {

      // note que é acrescentado +1 no numero da coluna para fazer sentido ao usuario
      // qual coluna ele está escolhendo... sem esse +1 seria mostrado a coluna 0.
      if (c < 8) {
        cout << c + 1 << "   ";
      } else if (c < 98) {
        cout << c + 1 << "  ";
      } else {
        cout << c + 1 << " ";
      }
    }
    cout << endl;

    // loop para desenhar os riscos embaixo dos numeros de colunas da grade
    cout << "    ";
    for (c = 0; c < colunas; c++) {
      cout << "____";
    }
    cout << "___";
    cout << endl;

    // loop que desenha os contornos lateriais da grade
    cout << "   |";
    for (l = 0; l < linhas; l++) {
      cout << "    ";
    }
    cout << "   |" << endl;

    // loop que desenha as linhas do jogo e apresenta os campos
    for (l = 0; l < linhas; l++) {

      // primeiro desenha o numero de linhas e abre a parede da grade
      // note que é acrescentado +1 no numero da linha para fazer sentido ao usuario
      // qual linha ele está escolhendo... sem esse +1 seria mostrado a linha 0.
      if (l < 9) {
        cout << l + 1 << "  |   ";
      } else if (l < 99) {
        cout << l + 1 << " |   ";
      } else {
        cout << l + 1 << "|   ";
      }

      // segundo escreve os campos
      // asterisco (*) significa disponivel
      for (c = 0; c < colunas; c++) {
        if (campoMinadoB[l][c] == -1) {
          cout << "*"
               << "   ";
        } else {
          cout << campoMinadoB[l][c] << "   ";
        }
      }

      // terceiro fecha a parede da grade
      cout << "|" << endl;
    }

    // loop que desenha os contornos lateriais da grade
    cout << "   |";
    for (c = 0; c < colunas; c++) {
      cout << "____";
    }
    cout << "___|";

    // MENSAGEM INFORMATIVAS PARA O USUARIO
    cout << endl << endl << endl << "Ainda restam >> " << (campos - bombas) - camposRevelados
         << " << campos válidos." << endl
         << endl
         << "(Existem " << bombas << " bombas escondidas.)" << endl
         << endl
         << endl;

    // SOLICITA A LINHA QUE O USUARIO DESEJA REVELAR
    cout << "Informe uma linha:" << endl;
    cin >> escolhaL;

    // SOLICITA A COLUNA QUE O USUARIO DESEJA REVELAR
    cout << "Informe uma coluna:" << endl;
    cin >> escolhaC;

    // o usuario escolhe uma linha/coluna em formato humano (de 1 em diante)
    // então é subtraido -1 para que o script possa acessar as casas corretas da matriz
    // exemplo: a linha/coluna 1 do usuario é a posicao 0 do array
    escolhaL = escolhaL - 1;
    escolhaC = escolhaC - 1;

    // verifica se a posicao escolhida do usuario não é uma bomba
    // note que ele busca na matriz 'campoMinado'
    if (campoMinado[escolhaL][escolhaC] == 9) {
      // se for bomba, o fim e bomba se torna verdadeiro e o loop quebrado
      fim = true;
      bomba = true;
      break;
    }

    // verificar se o usuario não escolheu a linha/coluna anteriormente
    // para evitar que o contador de jogadas seja somado 1
    // ou seja, se a posição informada for igual a -1 na matriz 'campoMinadoB'
    // então é a primeira vez que a escolhe e os contadores campoRevelados e jogadas rodam
    if (campoMinadoB[escolhaL][escolhaC] == -1) {
      camposRevelados += 1;
      jogadas += 1;
    }

    // copia o valor da posicao do 'campoMinado' na matriz
    // 'campoMinadoB' para ser mostrado em tela
    campoMinadoB[escolhaL][escolhaC] = campoMinado[escolhaL][escolhaC];

    // a fim de acelerar o jogo, criamos o loop abaixo para revelar os vizinhos 
    // do campo informado pelo usuario. se os campos vizinhos não forem uma bomba,
    // então eles serão copiados para a matriz 'campoMinadoB' e mostrado na tela 

    // ** a logica desse loop é a mesma do loop de vizinhos da bomba, porem aqui
    // só revela posicões que NÃO SÃO BOMBAS (identificadas na matriz campoMinado como 9)
    for (ll = 1; ll >= -1; ll--) {
      linhaVizinha = escolhaL - ll;
      if (linhaVizinha >= 0 && linhaVizinha < linhas) {
        for (cc = 1; cc >= -1; cc--) {
          colunaVizinha = escolhaC - cc;
          if (colunaVizinha >= 0 && colunaVizinha < colunas) {
            if (campoMinado[linhaVizinha][colunaVizinha] < 9) {
                // se esse vizinho ainda não foi revelado então...
              if (campoMinadoB[linhaVizinha][colunaVizinha] == -1) {
                // soma 1 no contador camposRevelados
                camposRevelados += 1;
                // e revela o campo na tela do usuario
                campoMinadoB[linhaVizinha][colunaVizinha] =
                    campoMinado[linhaVizinha][colunaVizinha];
              }
            }
          }
        }
      }
    }
  }

  system("cls|clear");
  // CASO O JOGO TENHA TERMINADO, O CAMPO É DESENHADO NOVAMENTE NA TELA
  // JUNTO COM AS MENSAGENS FINAIS

  // loop que desenha os numeros de colunas da grade
  cout << "       ";
  for (c = 0; c < colunas; c++) {
    if (c < 8) {
      cout << c + 1 << "   ";
    } else if (c < 98) {
      cout << c + 1 << "  ";
    } else {
      cout << c + 1 << " ";
    }
  }
  cout << endl;

  // loop para desenhar os riscos embaixo dos numeros de colunas da grade
  cout << "    ";
  for (c = 0; c < colunas; c++) {
    cout << "____";
  }
  cout << "___";
  cout << endl;

  // loop que desenha os contornos lateriais da grade
  cout << "   |";
  for (l = 0; l < linhas; l++) {
    cout << "    ";
  }
  cout << "   |" << endl;

  // loop que desenha as linhas do jogo e apresenta os campos
  // mesma logica usada dentro do loop while, a diferença aqui é que 
  // as bombas são mostradas como X
  for (l = 0; l < linhas; l++) {
    if (l < 9) {
      cout << l + 1 << "  |   ";
    } else if (l < 99) {
      cout << l + 1 << " |   ";
    } else {
      cout << l + 1 << "|   ";
    }

    for (c = 0; c < colunas; c++) {
      // se for bomba
      if (campoMinado[l][c] == 9) {
        // desenha X na tela
        cout << "X"
             << "   ";
      } else {
        cout << campoMinado[l][c] << "   ";
      }
    }
    cout << "|" << endl;
  }

  // loop que desenha os contornos lateriais da grade
  cout << "   |";
  for (c = 0; c < colunas; c++) {
    cout << "____";
  }
  cout << "___|";
  cout << endl << endl;

  // ESPAÇO DE ESCRITA DAS MENSAGENS FINAIS

  // se bomba for verdadeiro (ou seja, o usuario explodiu alguma)...
  if (bomba) {
    /// ...então informa a perda
    cout << endl << "     VOCÊ PERDEU!" << endl << endl;
  } else {
    /// ...se não informa a vitória e o número de bombas que o usuario desarmou.
    cout << endl
         << "     PARABÉNS! Você desarmou as " << bombas << " bombas." << endl;
  }

  // mensagem informativa com o numero de jogadas unicas (validas) feitas pelo usuario
  // e o numero de camposRevelados pelo usuario.

  // ** nota-se: os camposRevelados somam a jogada e os campos vizinhos da jogada que não forem bomba.
  cout << "     Foram feitas " << jogadas << " jogadas, revelando "
       << camposRevelados << " campos." << endl
       << endl;
  
  return 0;
}