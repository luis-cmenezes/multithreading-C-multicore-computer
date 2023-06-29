![GitHub last commit](https://img.shields.io/github/last-commit/luis-cmenezes/mutithreading-C-multicore-computer)
![GitHub repo size](https://img.shields.io/github/repo-size/luis-cmenezes/mutithreading-C-multicore-computer)
![GitHub top language](https://img.shields.io/github/languages/top/luis-cmenezes/mutithreading-C-multicore-computer)

# Multithreading C Programming for Multicore Computer

![](https://media.geeksforgeeks.org/wp-content/uploads/multithreading-python-21.png)

> O projeto, apresentado como Trabalho de Conclusão da disciplina Sistemas Operacionais, visa redigir um relatório técnico com objetivo de analisar o impacto da programação multithread voltada à
> engenharia, através de uma análise quantitativa do tempo de execução da multiplicação de matrizes com muitos elementos executando em 1, 2 e 4 threads, com e sem afinidade de processador.

### Planejamento do estudo de caso

O estudo de caso para relatório tem o seguinte planejamento:

- [x] Desenvolvimento dos códigos Single e Multi-Thread
- [x] Criação de um código de "carga de fundo" 
- [x] Experimento e obtenção dos tempos de execução
- [x] Estátistica dos resultados obtidos
- [x] Redação do relatório técnico

## 💻 Conclusões
Os resultados evidenciam o comportamento esperado para as condições propostas. Com o tempo de execução da aplicação diminuindo proporcionalmente à quantidade threads criadas, com a execução em single thread como referência, a execução em dual thread executou em metade o tempo, e em quad thread um quarto do tempo original, para o cenário sem afinidade de processador.

Para o cenário com afinidade de processador, observa-se que apesar de causar a impressão de seguir a mesma tendência que o cenário anterior, na execução em quad thread observa-se uma grande discrepância entre os tempos de execução com e sem afinidade de processador.

Tal comportamento anômalo pode ser atribuído a certas características intrínsecas dos sistemas operacionais de uso geral modernos. Especificamente, as otimizações de balanceamento de carga no escalonador de processos desempenham um papel significativo. Quando há a execução concorrente de uma carga de fundo e outros processos do sistema operacional, as threads da aplicação em questão provavelmente competem pelo tempo de processador se a afinidade for definida.

Por outro lado, quando a afinidade não é definida, é provável que a aplicação seja realocada várias vezes entre processadores durante sua execução, com o objetivo de equilibrar a carga em cada processador e minimizar a utilização de cada núcleo. Essa abordagem visa reduzir o tempo de execução, especialmente para aplicações com baixa prioridade de execução e característica de uso intensivo de CPU.

Em vista disso, a subdivisão de macrotarefas em subtarefas executadas por diferentes threads é uma boa solução para problemas análogos ao proposto neste trabalho, visto que melhor utiliza os recursos computacionais disponíveis e resulta em melhor desempenho da aplicação, sem causar ônus exagerado em contrapartida.


## 🤝 Colaboradores

Agradeço às seguintes pessoas que, junto à mim, desenvolveram este estudo:
* Professor Rivalino Matias Junior
* Discente [Alexandre Mendes Lanhoso](alexandre.lanhoso@ufu.br)
* Discente [Paulo Ricardo Bueno Branquinho](prbueno@ufu.br)
