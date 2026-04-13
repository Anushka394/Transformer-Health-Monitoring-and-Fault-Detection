import subprocess
import matplotlib.pyplot as plt
import os

proc = subprocess.Popen(
    ["../run.exe"],
    stdout=subprocess.PIPE,
    text=True
)

voltages = []
temps = []
loads = []
healths = []

plt.ion()

os.makedirs("../output", exist_ok=True)
log_file = "../output/logs.txt"

current_status = "NORMAL"
fault_message = ""

for line in proc.stdout:
    try:
        # Detect FAULT lines separately
        if "FAULT" in line:
            fault_message = line.strip()
            print(fault_message)
            continue

        data = list(map(float, line.split()))

        v, c, load, pf, oil_temp, wind_temp, oil_level, relay, health = data

        voltages.append(v)
        temps.append(oil_temp)
        loads.append(load)
        healths.append(health)

        #  HEALTH STATUS
        if health > 80:
            current_status = "HEALTHY"
            color = "green"
        elif health > 50:
            current_status = "WARNING"
            color = "orange"
        else:
            current_status = "CRITICAL"
            color = "red"

        plt.clf()

        # Main health line
        plt.plot(healths, color=color, linewidth=2, label="Health")

        # Other parameters
        plt.plot(temps, linestyle="--", label="Oil Temp")
        plt.plot(loads, linestyle="-.", label="Load %")

        #  Title with FAULT + STATUS
        title_text = f"Transformer Status: {current_status}"

        if fault_message != "":
            title_text += f" | {fault_message}"

        plt.title(title_text)

        plt.xlabel("Time")
        plt.ylabel("Values")

        plt.legend()
        plt.grid(True)

        plt.pause(0.1)

        # logging
        with open(log_file, "a") as f:
            f.write(line)

    except:
        print("Skipping:", line.strip())