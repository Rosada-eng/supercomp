# Quizz de Revisão (PI)

1. Defina um problema difícil computacionalmente.

   Um problema difícil computacionalmente é um problema que requer uma grande quantidade de recursos computacionais (tempo e espaço) para ser resolvido de forma eficiente. Existem muitos exemplos de problemas difíceis computacionalmente, mas um dos mais conhecidos é o problema do "caixeiro viajante" (Traveling Salesman Problem).

   O problema do caixeiro viajante é um problema de otimização combinatória que envolve encontrar o menor caminho possível que um caixeiro viajante deve percorrer para visitar um conjunto de cidades exatamente uma vez e retornar à cidade de origem. Embora pareça simples, a quantidade de combinações possíveis aumenta exponencialmente à medida que o número de cidades aumenta, o que torna o problema extremamente difícil de resolver em tempo hábil.

   Outros exemplos de problemas difíceis computacionalmente incluem a fatoração de grandes números inteiros (que é a base da criptografia de chave pública), a solução de sistemas de equações diferenciais parciais complexas e a criação de modelos precisos de previsão do tempo. Esses problemas exigem muito poder de processamento e são muito difíceis de serem resolvidos de forma eficiente com a tecnologia atual.
2. Qual o papel das heurísticas na abordagem de obter soluções para problemas computacionalmente difíceis?

   Elas fornecem técnicas para encontrar soluções razoáveis de forma rápida e eficiente, mesmo que elas não sejam necessariamente as melhores soluções possíveis. Seja por que a melhor solução não é possível de ser encontrada ou por que demandaria muito tempo de processamento para calculá-la.

   Em resumo, as heurísticas são ferramentas valiosas para encontrar soluções aproximadas para problemas computacionalmente difíceis, permitindo que as pessoas encontrem soluções eficazes em tempo hábil, mesmo que elas não sejam exatamente as melhores soluções possíveis.
3. A heurística gulosa tem alguma garantia de otimalidade?

   Não.
4. Qual o papel que a aleatoriedade exerce em problemas de combinação discretos?

   A aleatoriedade pode ser usada em problemas de combinação discretos como uma forma de explorar o espaço de busca de forma mais eficiente e encontrar soluções melhores.
5. A heurística de busca local apresenta vantagens em relação à heurística gulosa?

   A heurística de busca local pode ser especialmente útil em situações em que a escolha da melhor opção em cada etapa pode levar a uma solução geralmente pior, como é o caso em problemas com muitos ótimos locais ou em que a solução depende de escolhas anteriores.

   Outra vantagem da heurística de busca local é que ela pode ser mais eficiente em termos de tempo de execução do que a heurística gulosa em muitos casos.

   No entanto, é importante notar que a heurística de busca local pode ficar presa em mínimos locais ou em platôs, onde não há melhorias possíveis. Além disso, a escolha da solução inicial pode afetar significativamente o desempenho da heurística de busca local. Portanto, é importante considerar diferentes técnicas de busca local e testá-las em diferentes conjuntos de dados para encontrar a técnica mais adequada para cada problema.
6. No Valgrind, qual o papel do indicador IR?
7. Se um problema é 30% sequencial, qual o speedup máximo que ele pode ter ao paralelizarmos?

   speedup máximo = 1 / (1 - p + (p / n))

   = 1.18
8. 
9. Quais vantagens e desvantagens da passagem de parâmetros por referência?
10. Na aula sobre valgrind, nós vimos formas diferentes de somar os números de uma matriz. Qual a razão para a diferença de performance?
11. Como se dá a heurística por algoritmos genéticos? Qual o papel da mutação?
12. Na busca exaustiva, a profundidade de busca afeta consideravelmente o resultado obtido. Explique com suas palavras a importância de se buscar conhecer uma profundidade razoável de busca?
