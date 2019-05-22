# Manipulação Básica de Arquivos
## Descrição Geral do Trabalho
Neste trabalho deverá ser feito um programa para gerenciar uma base persistente de pares chave, valor. Diversas aplicações atuais se baseiam em bases deste tipo. A base de dados manterá uma quantidade potencialmente muito grande destes pares.

Cada unidade de armazenamento na base será chamada de um registro. Cada registro terá, portanto, dois campos: uma `chave`, que será uma cadeia de, no máximo, 20 caracteres; e um `conteúdo`, que será também uma cadeia de caracteres, mas de tamanho máximo 50. Nesta aplicação, poderá haver mais de um registro com o mesmo valor de chave. As sequências de caracteres somente conterão caracteres minúsculos, sem acento, e numerais.

O objetivo do trabalho será realizar uma implementação bastante eficiente de um programa que faça consultas, insira e remova registros da base.

## Formato de Entrada e Saída
O programa deverá ter, como parâmetro, o nome de um arquivo. Este arquivo terá um registro por linha.
Os valores dos campos serão separados por uma vírgula. Este arquivo conterá o estado inicial da base de dados.
A seguir, o programa deverá ler uma sequência de operações sobre a base de dados. As operações e seus formatos estão descritos abaixo:

- **insere registro**: esta operação conterá duas linhas. A primeira linha conterá um valor de chave.
segunda linha conterá o valor do campo conteúdo.
Esta operação insere o registro na base e não gera saída.

- **consulta registros por chave**: esta operação conterá duas linhas. A primeira linha conterá a letra
’c’. A segunda conterá um valor de chave.
Esta operação retornará todos os registros que contenham o valor de chave digitado, um por linha. Em cada linha deve aparecer inicialmente o valor da chave, seguido por um espaço, seguido pelo valor do
conteúdo.

- **remove registro**: esta operação conterá duas linhas. A primeira linha conterá a letra ’r’. A segunda
conterá um valor de chave.
Esta operação removerá todos os registros da base que contenham este valor de chave. Esta operação não gera saída.

- **término da sequência de comandos**: a sequência de comandos será terminada por uma linha com
a letra ’e’.

*Importante*: o programa não deve gerar nenhum caractere a mais na saída, além dos indicados acima. Em particular, o programa não deve conter menus.


Não deve haver espaço entre linhas na saída. A saída deve apresentar os caracteres em letras minúsculas.