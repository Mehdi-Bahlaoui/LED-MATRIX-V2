import subprocess

platformio_project_dir = "C:/Users/Mehdi/Documents/PlatformIO/Projects/LED Matrix v2"
subprocess.run(["platformio", "run", "--target", "upload"], cwd=platformio_project_dir, check=True)