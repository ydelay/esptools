
import os
import subprocess

def before_upload(source, target, env):
    env.AutodetectUploadPort()
    upload_port = env.subst("$UPLOAD_PORT")
    subprocess.check_call(["esptool.py", "--port", upload_port, "erase_flash"])