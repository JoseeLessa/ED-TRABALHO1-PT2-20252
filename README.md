# ED-TRABALHO1-PT2-20252
#  Gerenciador de Campeonato em C

Este projeto é uma aplicação de **console em C**, criada para **gerenciar e exibir estatísticas de um campeonato de futebol**.  
O sistema é capaz de ler dados de times e resultados de partidas, processar essas informações e apresentar um **placar de classificação**, além de permitir **consultas detalhadas**.


---

##  funcionabilidades 
## PARTE 1
- **Carregamento de Dados:** Lê e interpreta automaticamente os arquivos de times e partidas ao iniciar.  
- **Cálculo de Estatísticas:** Processa os resultados de todas as partidas para calcular em tempo real a pontuação, saldo de gols e V/E/D de cada time.  
- **Interface Interativa:** Um menu de console simples e direto para acessar todas as funcionalidades.   
- **Tabela de Classificação:** Exibe uma tabela completa e formatada com o desempenho de todos os times no campeonato.
- **Opção 1: Consultar Time:** Busca o desempenho de um time usando um nome ou prefixo.
- **Opção 2: Consultar Partidas:** Busca partidas específicas por time (mandante, visitante ou ambos).

## PARTE 2

- **Implementaçãi de filas:** Agora as variáveis de banco de dados, antes implementados em vetores estáticos, foram implementadas em forma de Lista dinâmica simplesmente encadeada, sendo BDMatches e BDTeams a cabeça, com MNode e Node como nó.
- **Opção 5: Inserir Partida:** Agora é possível registrar novas partidas diretamente pelo sistema. Cada jogo recebe automaticamente um ID incremental, garantindo organização e integridade do banco de dados.
- **Opção 3: Atualizar Partida:** Permite modificar o placar de partidas já cadastradas. Ao alterar os gols, o sistema recalcula automaticamente todas as estatísticas dos times envolvidos, ajustando pontos, vitórias, empates, derrotas e saldo de gols.
- **Opção 4: Remover Partida:** Possibilita excluir um jogo do banco de dados. Ao remover a partida, o sistema reverte corretamente todos os pontos e estatísticas atribuídos aos times naquela partida.
- **Opção 6: Remover Partida:** A tabela de classificação agora é exibida de forma ordenada com base no desempenho das equipes, seguindo os critérios:

Pontos Ganhos (PG)

Número de Vitórias (V)

Saldo de Gols (S)

Essa ordenação possibilita uma visualização mais fiel da classificação real do campeonato.
- **Insertion Sort Aplicado:** O algoritmo Insertion Sort foi implementado para realizar a ordenação da tabela de classificação. Ele organiza os times de maneira eficiente para o volume de dados utilizado no projeto, garantindo simplicidade e boa performance para vetores de tamanho reduzido.
---

##  Arquitetura do Código

O projeto é estruturado de forma **modular**, separando a lógica principal, a interface e as funções utilitárias.

###  Arquivos Principais




## Como Compilar e Executar

### 1. Requisitos
- Compilador **gcc**  
- Utilitário **make**

### 2. Compilação
No terminal, execute:
```bash
make
```
Isso criará o arquivo executável **`campeonato_gronerjose`**.

### 3. Execução

#### Método A — Via Makefile
Compila (se necessário) e executa o programa automaticamente:
```bash
make run
```

#### Método B — Manualmente
Execute o binário diretamente:
```bash
./campeonato_gronerjose
```

---

## Arquivos de Dados

O programa espera encontrar os seguintes arquivos **no mesmo diretório do executável**:

- `times.csv`
- `partidas_vazio.csv`
- `partidas_parcial.csv`
- `partidas_completo.csv`

> Os nomes e caminhos desses arquivos estão definidos em `main.c`.  
> Caso deseje usar outro arquivo, escolhar entre 1, 2 e 3 durante a execução do aplicativo.
> O arquivo `times.csv` é obrigatório para a execução do código, não podendo assim ser alterado.

---

##  Evolução do Projeto (Próximos Passos)

- [ ] **Parâmetros de Linha de Comando:**  
  Modificar `main.c` para aceitar os nomes dos arquivos de times e partidas como argumentos de linha de comando:
  ```bash
  ./campeonato_gronerjose times.csv partidas.csv
  ```




---

**Autores:** *José Otávio e Pedro Groner*
