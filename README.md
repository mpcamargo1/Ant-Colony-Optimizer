# Ant-Colony-Optimizer aplicado ao problema berlin52.tsp
O algoritmo da otimização da colônia de formigas (ACO, do inglês ant colony optimization algorithm), introduzido por Marco Dorigo em sua tese de PhD é uma heurística baseada em probabilidade, criada para solução de problemas computacionais que envolvem procura de caminhos em grafos. Este algoritmo foi inspirado na observação do comportamento das formigas ao saírem de sua colônia para encontrar comida.<p>
No mundo real, as formigas andam sem rumo (pelo menos inicialmente) até que, encontrada comida, elas retornam à colônia deixando um rastro de feromônio. Se outras formigas encontram um desses rastros, elas tendem a não seguir mais caminhos aleatórios. Em vez disso, seguem a trilha encontrada, retornando e inclusive enfatizando se acharam alimento.
Com o transcorrer do tempo, entretanto, as trilhas de feromônio começam a evaporar, reduzindo, assim, sua força atrativa. Quanto mais formigas passarem por um caminho predeterminado, mais tempo será necessário para o feromônio da trilha evaporar. Analogamente, elas marcharão mais rapidamente por sobre um caminho curto, o que implica aumento da densidade de feromônio depositado antes que ele comece a evaporar. A evaporação do feromônio também possui a vantagem de evitar a convergência para uma solução local ótima: se a evaporação não procedesse, todas as trilhas escolhidas pelas primeiras formigas tornar-se-iam excessivamente atrativas para as outras e, neste caso, a exploração do espaço da solução delimitar-se-ia consideravelmente.
Todavia, quando uma formiga encontra um bom (curto) caminho entre a colônia e a fonte de alimento, outras formigas tenderão a seguir este caminho, gerando assim feedback positivo, o que eventualmente torna um determinado caminho mais interessante. A idéia do algoritmo da colônia de formigas é imitar este comportamento através de "formigas virtuais" que caminham por um grafo que por sua vez representa o problema a ser resolvido.
- Fonte: Wikipedia
<div>
  <p align="center">
    <img width=618 src=https://www.news.ucsb.edu/sites/default/files/styles/article_horizontal/public/images/2018/ants-uc-santa-barbara.jpg?itok=EcZof6Ii>
    <img src=https://assets.bwbx.io/images/users/iqjWHBFdfxIU/i13hjObZKkNM/v0/-999x-999.gif>
  </p>
</div>

# Observações
- Compilar com gcc : 'gcc aco.c lib.c mtwister.c -o output -lm'
- lib.c contem os dados das cidades a serem visitadas (berlin52.tsp)
- Imprimir caminho realizado (path.txt) -> Plotar com GNUplot : 'plot "plot.txt" every :::0::1 with lp pt 7'

