---
layout: post
title:  "Repositório II"
category: 'Apprendice'
introduction: David, me empresta 50 conto, que eu transfiro o dinheiro. Só pra eu não ter que ir lá no caixa rápido. Emprestei. Até hoje estou esperando essa transferência. Deve ter sido problema no banco.
description: 
image: '/assets/repositorio2/figura.jpg'
tags:
- composição
- login
- excessões
---

O objetivo dessa atividade é implementar uma agência bancária simplificada. Deve ser capaz de cadastrar cliente. Cada cliente pode ter várias contas. Uma conta não pode existir se não estiver viculada a um cliente.

Expanda a atividade nível 1 Conta Bancária e adicione os novos requisitos.

## Funcionalidades

## Exemplos

```python
#######################################
# Cadastrar um cliente com idCliente / ADMINISTRADOR
#######################################

### Ações Administrativas

- **[1.0 P]** Cadastrar um cliente com idCliente.
    - idClientes devem ser únicos no sistema.
    - Quando o cliente é cadastrado no sistema, automaticamente é aberta uma conta

```
addCliente _idCliente
  done: conta _idConta adicionada ao cliente
```

---
- **[1.0 P]** Abrir novas contas para clientes.
    - Cada conta deve receber do sistema um número único no sistema.
    - Quando o cliente é cadastrado no sistema, automaticamente é aberta uma conta
  para ele.
    - **[1.0 E]** Cada cliente pode ter até 2 contas ativas.

```
abrirConta _idCliente
  done: conta _idConta adicionada ao cliente
  fail: limite de contas atingido
```

---
- **[1.0 E]** Encerrar contas de clientes
    - Contas encerradas não podem mais realizar nenhuma operação. Elas não são apagadas. Apenas desabilitadas.
    - Contas só podem ser desabilitadas se tiverem com saldo zerado.

```
encerrarConta _idCliente _idConta
  done
  fail: conta _idConta ja esta encerrada
  fail: conta _idConta possui saldo positivo
```

---

### Ações de Clientes

- **[1.0 P]** Mostrar os clientes e suas contas ativas.
    - **[1.0 E]** Mostre ordenado por nome do cliente.

```
showAll
  _idCliente1 [ _idConta1 ... ]
  _idCliente2 [ _idConta1 _idConta2 ... ]
  ...
```

---
- **[1.0 P]** Fazer login e logout no sistema.
    - Um único cliente pode estar logado de cada vez.
- Login:

```
login _idCliente
  done
```

- Logout:

```
logout
  done
```

---
- **[1.0 P]** Mostrar dados do cliente, suas contas e saldos.
    - Cliente precisa estar logado.
    - Se não tiver implementado encerrar conta, não mostre o status(ativa/inativa).

```
show
  Cliente: _idCliente
  Conta: _idConta, Saldo: _saldo, Status: _status
  Conta: _idConta, Saldo: _saldo, Status: _status
  ...
  Saldo total: _total
```

---
- **[1.0 P]** Realizar operações de saldo, saque, depósito e extrato, tal como foi implementado no primeiro trabalho.
     - Cliente só pode fazer operações em suas próprias contas.
     - Cliente precisa estar logado.

```
saldo _idConta
  done: Conta _idConta saldo: _saldo
saque _idConta _valor
  done
deposito _idConta _valor
  done
extrato _idConta
  Conta _idConta
  desc: _descricao, value: _value, saldo: _saldoResidual
  desc: _descricao, value: _value, saldo: _saldoResidual
  ...
```

---
- **[1.0 P]** Realizar operações de transferência entre contas.
    - No extrato essa ação deve vir com descrição "transferência para/de $conta".
    - Verifique se há saldo para efetuar a transação.
    - Cliente precisa estar logado e possuir a conta de débito.

```
transf _idConta _idContaDestino _valor
  done
```

---
- **[1.0 P]** Faça um código de inicialização para que seu sistema já inicie com alguns clientes, contas e operações realizadas.

### Mensagens de erro comuns

- Faça as devidas verificações e emita o aviso caso alguma das operações inválida tente ser executada.

```
Adicionar outro cliente com mesmo id
  fail: cliente _idCliente ja existe
Obter um cliente que nao existe
  fail: cliente _idCliente nao existe

Adicionar outra conta com mesmo id
  fail: conta _idConta ja existe
Obter uma conta que nao existe ou não pertence ao cliente
  fail: conta _idConta nao existe
Realizar operação em conta encerrada
  fail: conta _idConta esta encerrada

Realizar uma operação que exige estar logado sem estar logado
  fail: ninguem logado
Realizar saque ou transferencia sem ter dinheiro suficiente
  fail: saldo insuficiente
```

### Lista de Comandos

```
# Admin
addCliente    _idCliente
abrirConta    _idCliente
encerrarConta _idCliente _idConta
showAll

# Login e logout
login    _idCliente
logout

# Exige login
show
saldo    _idConta
extrato  _idConta
saque    _idConta _valor
deposito _idConta _valor
transf   _idConta _idContaDestino _valor
```

## Pontuação

```
[ ][1.0 P] cadastrar cliente
[ ][1.0 P] abrir conta cliente
[ ][1.0 P] mostrar todos os clientes
[ ][1.0 P] cadastrar cliente
[ ][1.0 P] login
[ ][1.0 P] logout
[ ][1.0 P] mostrar contas de um cliente
[ ][1.0 P] saldo, saque, deposito, extrato

[ ][1.0 E] limitar contas ativas
[ ][1.0 E] encerrar contas
[ ][1.0 P] mostrar clientes ordenados
```

---
## Raio X

````java
class Agencia
- clientes: List<Cliente>
--
+ addCliente(cpf: String): boolean
+ abrirNovaConta(cpf: String): boolean
--
+ getClientes()

class Cliente
- idCliente: String
- contas: List<Conta>
--
+ addConta(conta: Conta): boolean
+ encerrarConta(numero: String): boolean
--
+ constructor(idCliente: String)
+ get idCliente()
+ getConta()

class Operacao
- descricao: String
- valor: float
- saldoParcial: float
--
+ constructor(desc, valor, saldo)
+ getDescricao()
+ getValor()
+ getSaldo()
+ setDescricao()
+ setValor()
+ setSaldo()

class Conta
- saldo: float
- numero: int
- extrato: List<Operacao>
- ativa: boolean
--
+ depositar(value: float): boolean
+ sacar(value: float): boolean
+ transferir(other: Conta, value: float): boolean
+ encerrar(): void
--
+ constructor(numero: int)
+ getSaldo()
+ getNumero()
+ getAtiva()
+ getExtrato()

````
