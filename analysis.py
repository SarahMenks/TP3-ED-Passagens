import subprocess
import time
import pandas as pd
import re

# Caminhos dos arquivos de entrada
input_files = [f"inputs/input_{i}.txt" for i in range(1, 12)]
output_data = []

# Comando base para execução com Valgrind
EXECUTAVEL = "bin/tp3.out"

for input_file in input_files:
    print(f"Executando: {input_file}")

    # Iniciar medição do tempo
    start_time = time.time()

    # Comando Valgrind para obter estatísticas de memória
    valgrind_cmd = [
        "valgrind", "--tool=massif", "--time-unit=B",
        "--log-file=valgrind_output.txt",
        EXECUTAVEL, input_file
    ]

    # Executar o processo
    subprocess.run(valgrind_cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

    # Calcular tempo de execução
    exec_time = time.time() - start_time

    # Extrair uso de memória do log do Valgrind
    mem_usage = 0
    with open("valgrind_output.txt", "r") as log_file:
        for line in log_file:
            match = re.search(r"mem_heap_B=(\d+)", line)
            if match:
                mem_usage = int(match.group(1))

    # Armazenar os resultados
    output_data.append([input_file, exec_time, mem_usage])

# Criar DataFrame com os resultados
df = pd.DataFrame(output_data, columns=["Arquivo", "Tempo (s)", "Memória (B)"])

# Exibir os resultados
print(df)

# Salvar em CSV (opcional)
df.to_csv("resultados_tp3.csv", index=False)
