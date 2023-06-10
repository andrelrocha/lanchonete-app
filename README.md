# lanchonete-app { trabalho prog. algo }

Não alterem a branch main, sempre tenham atenção a dar git pull na branch desenvolvimento.

Somente o arquivo main.C é o código correto, o resto é rascunho que eu uso para não perder pensamento.


## Capacidade de manipulação (adição, remoção, edição e visualização) de um estoque de mantimentos. ✅
• Cada mantimento deve possuir nome, código, preço e quantidade. ✅
• É possível comprar ingredientes para o estoque apenas se a lanchonete tiver saldo suficiente para pagar o preço deles. 

```
falta alterar saldo para um arquivo próprio e questão do app só adicionar uma nova linha se não encontrar linha com o mesmo nome
AO INVÉS DE ALTERAR (if encontrarNome -> break printf("o mantimento já existe na base, altere-o corretamente quando da inicialização"))
```

## Capacidade de manipulação (adição, remoção, edição e visualização) de um cardápio de comidas.
• Cada comida possui um código, preço, nome e uma lista de mantimentos necessários para a cocção de cada uma.
• Uma comida só pode ser preparada se todos os seus ingredientes estiverem disponíveis no estoque.

## Capacidade de registrar um pedido feito por um cliente, contendo as comidas e suas respectivas quantidades.
• O sistema deve calcular o preço de venda das comidas, que será o lucro.
• O sistema deve registrar o custo total dos mantimentos utilizados em cada porção da comida pedida.

## Geração de relatórios que mostrem o lucro ou prejuízo da lanchonete, além das seguintes informações:
• Comida com a maior margem de lucro.
• Comida com a menor margem de lucro ou prejuízo.
• Se houver alguma comida impossível de ser feita devido à falta de algum mantimento específico, o sistema deve emitir um aviso.

1. Saldo inicial da lanchonete é de R$ 1000.
2. Possibilidade de depositar e sacar dinheiro do negócio.
3. Infos devem ser registradas em arquivos
