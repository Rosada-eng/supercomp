# Pré-analise

**Examinando o código:**

    O código tenta reduzir o tamanho do laço até que seja pequeno o suficiente para processá-lo.

    Enquanto não é pequeno suficiente, a função é chamada recursivamente com valores menores.

    A primeira chamada fará outras chamadas recursivas até que o tamanho do laço seja pequeno o suficiente. Só então, processará os dados e aí, sim, chamará o segundo pi_r recursivamente que, por sua vez, fará uma série de chamadas até que o tamanho do laço seja pequeno o suficiente.

    Essa abordagem é uma espécie de "divisão e conquista".

    Porém, seriam necessários vários passos até que TODO o processo seja feito.

**As oportunidades de paralelismo aparecem em**:

* [ ] Chamada recursiva das funções pi_r (Não precisam ser executadas sequencialmente, visto que não há dependência)
* [ ] Na execução do laço for

**Número MIN_BLK:**

- Ele afeta o algoritmo. Quanto menor esse número, mais recursões são necessárias até que o laço seja executado.
- Vamos testar como ele influencia, em questão de desempenho.
  - A questão de desempenho dependerá do que é mais custoso: Laços for ou recorrências.
    - Reduzindo para 1024 * 512, houve uma melhoria no desempenho.
    - Reduzindo para 1024 * 256, o desempenho passou a piorar, em relação a 1024 * 512
    - Aumentando para 1024 * 1024 * 512, o desempenho melhorou bastante
    - Passando para 1024 * 1024 * 1024, o desempenho piorou.

# **Tempo de Execução**

Em série: 

```
2147483648 steps pi = 3.14159265358977 in 26.6545347000065 secs
```

omp parallel for

```
for 2147483648 steps pi = 3.14159265358979 in 5.7167652999924 secs
```

omp parallel for task (simples)

```
for 2147483648 steps pi = 3.14159265358979 in 3.07578479999211 secs
task_count = 30
```
