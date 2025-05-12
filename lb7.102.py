import psutil

def list_open_files():
    print(f"{'PID':<8} {'Process Name':<25} {'Open File'}")
    print("-" * 80)

    for proc in psutil.process_iter(['pid', 'name']):
        try:
            files = proc.open_files()
            for file in files:
                print(f"{proc.pid:<8} {proc.info['name']:<25} {file.path}")
        except (psutil.AccessDenied, psutil.NoSuchProcess):
            continue

if __name__ == "__main__":
    list_open_files()
