# Com-dados-nodemcu
Trabalho: IoT
Restrições básicas:
• O trabalho poderá ser realizado em grupo de no máximo 3 alunos.
• O trabalho tem valor igual a 10 (dez) pontos, que corresponderão a 30% da nota final do curso.
• Não serão aceitos trabalhos copiados. A detecção de cópias entre grupos causará a ANULAÇÃO dos mesmos, equivalendo a nota 0,0 (ZERO).

Contexto:

A Internet das Coisas (IoT-Internet of Things) está aumentando a conexão entre pessoas e coisas em proporções jamais imaginadas. Os dispositivos conectados superam a população mundial em de 1.5 para 1. O ritmo de adoção da IoT pelo mercado está aumentando cada vez mais pelos seguintes motivos: expansão das soluções analíticas e da computação em nuvem; Aumento da conectividade entre máquinas e dispositivos pessoais inteligentes; Crescimento do número de aplicações que conectam cadeias de suprimentos, parceiros e clientes [Cisco, Web].

Um dos maiores eletrodomésticos que geram consumo de energia é o ar-condicionado. Deixar esses aparelhos ligados desnecessariamente é uma grande fonte de desperdício de recurso. Por essa razão deseja-se criar uma forma de controle e monitoramento de salas de aula, que permite o acionamento e o monitoramento pela rede.

Descrição:

Criar um dispositivo de monitoramento e acionamento de chaves(liga/desliga) com acesso remoto e controle por requisições HTTP e acesso por rede IP sobre Wireless/Ethernet. O ponto de controle poderá ser qualquer navegador web, de PC ou Smartphone, conectado à mesma rede Wifi, ou a uma rede remota devidamente roteada.

Em um microcontrolador (veja [NodeMCU]) disponibilizar um servidor Web HTTP, com páginas que disponibilizem por HTML, ou semelhante, os seguintes controles (sugestão: nodemcu):
• Sensoriamento do nível de luminosidade.
• Sensoriamento analógico de temperatura ambiente. Sugestão: LM35.
• Sensoriamento de presença.
• Acionamento de comandos de um eletrodoméstico (preferencialmente Ar-condicionado)
por infravermelho.
	◦ O sistema deverá aprender os comandos (pelo menos 5 comandos) de um controle remoto (preferencialmente, todos). E estar nas proximidades do aparelho de maneira a conseguir aciona-lo via infravermelho.
	◦ Os comandos devem ser disponibilizados por interface HTML/GET entre o microcontrolador e o gerente (celular/smartphone/computador) de controle e monitoramento, por páginas HTTP com comandos enviados via URL GET.
	◦ A comunicação entre o Gerente e o microcontrolador deverá ser feita por Wifi+IP via requisições HTTP. Os comandos de sensoriamento e acionamento devem ser encapsulados em requisições GET de um browser e recebidos e processados pelo MCU do projeto.
• O MCU deve funcionar tanto no modo AP quanto no modo cliente. Dependendo de um
acionamento de botão no hardware que habilita as duas funções. No modo cliente,
deve se conectar à uma rede Wifi definida no ambiente e com a devida segurança de
acesso. Para o modo AP, o controlador deve disponibilizar uma SSID wifi com
segurança WPA2.

Requisitos:

1) Os testes serão realizados a partir de um Browser Cliente (Firefox/Chrome/Safari) tanto na versão Desktop ou Mobile. Recomenda-se a realização de testes de validação da interface cliente antes da submissão final.
2) Deverá ser entregue um relatório simplificado (Report), com seções mínimas de:
	◦ Tempo de resposta do MCU a nível de rede, serviço HTTP e tempo de
acionamento de comandos (tempo entre o comando e sua completa realização).
	◦ Informações detalhadas sobre os hardwares utilizados, sensores, etc.(tabela de recursos utilizados) e efetivo custo final da solução.
	◦ Análise de trade-off entre a solução adota e os custos envolvidos para produção em larga escala.
3) Poderá ser utilizado um computador como o Raspberry Pi, Omega, LinkIt ou afim.
4) A entrega do código fonte deve ser feita (obrigatóriamente) em um repositório GIT (gitlab.com, bitbucket, bitbuck), com link disponível no relatório. Caso seu repositório seja privado, defina junto ao professor um acesso comum ao time de desenvolvimento para acesso ao código para avaliação. [GIT, web]
5) Deverá ser gravado um video demostrativo com disponibilização pela Internet, via
Youtube/Vimeo ou afins.

Entrega e Avaliação:

• A data limite para entrega e apresentação do trabalho é o dia 05/07/2017;
• A submissão do relatório do trabalho será feito EXCLUSIVAMENTE pelo sistema MOODLE, do IFES, não sendo aceita nenhuma outra forma de envio; Caso haja alguma indisponibilidade do sistema do IFES, um novo dia próximo será definido pelo professor para entrega.
• Os alunos deverão agendar com o professor uma data/local para apresentação do trabalho, respeitado a data limite (07/06) e as restrições de horário do professor e dos laboratórios. A data final para submissão do trabalho no Moodle é 05/07;
• No pacote submetido no Moodle, espera-se:
	◦ Arquivo em pacote tipo ZIP ou TAR.
	◦ Código fonte (disponibilização referência versionada será um diferencial)

Critérios de avaliação:
	◦ O funcionamento do trabalho conforme as especificações (50%), nota do grupo;
	◦ Report dentro das especificações (10%), nota do grupo;
	◦ O conhecimento dos alunos sobre o trabalho implementado, a ser avaliado em apresentação junto ao professor com avaliação oral individual de cada membro do grupo (40%); Nota individual.
	◦ Adicionais (na nota do trabalho):
		1) Entrega do código de forma versionado em Git: +1,0 pt. (OBS: A evolução do código deve ser versionada, e deve ser mantida os crédito de autores anteriores no caso de utilização de alguma biblioteca padrão).
		2) Entrega antecipada: Para a entrega do trabalho funcional e completo realizado com data antecipada, será data a seguinte bonificação:
			• Até dia 23/06: +1,5 pts
			• Até dia 28/06: +0,5 pt
	◦ OBS: Caso a nota total supere os 10pts, o valor excedente será utilizado na prova em que o aluno teve o pior desempenho, com a bonificação aplicada com o fator de 0,3 (30%) e somada a pior nota.

Referências:

1. [Cisco, Web] http://www.cisco.com/c/pt_br/solutions/internet-of-things/overview.html
2. [Hackster, Web] https://www.hackster.io/rayburne/esp8266-access-point-using-arduino-ide-
19f632
3. [GIT, web] http://rogerdudler.github.io/git-guide/index.pt_BR.html
4. [NodeMCU] https://www.allaboutcircuits.com/projects/how-to-make-an-interactive-tcp-server-nodemcu-on-the-esp8266/
