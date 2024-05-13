# Trabalho Estrutura de Dados

Tarefa 1: (consulta cidade)
objetivo: dado o codigo_ibge retorne as informações desta cidade

Tarefa 2 (vizinhos mais próximo de uma cidade dado o seu codigo_ibge)
objetivo:  Dado o código_ibge,  você deverá retornar o codigo_ibge das N cidades vizinhas mais próximas, onde N é um parâmetro do usuário.

Tarefa 3 (combinar tarefa 1 e 2).
objetivo: dado o nome de uma cidade retornar todas as informações das N cidades vizinhas mais próximas. 


### cumpridas

Tarefa 1: COMPLETA

Tarefa 2: INCOMPLETA

Tarefa 3: NÂO FEITA

## Como rodar o projeto

necessário ter os programas
- gcc
- wget
- tar
- make

1. clone o projeto
```bash
git clone https://github.com/WilkerSebastian/trabalho_ed_wilker.git
```
2. entre na pasta do projeto
```bash
cd trabalho_ed_wilker
```

3. execute o comando make dependencies para instalar a biblioteca jansson que foi utilizada no projeto
```bash
sudo make dependencies
```

4. exexcute o comando make run para compilar e executar o binario do projeto
```bash
make run
```