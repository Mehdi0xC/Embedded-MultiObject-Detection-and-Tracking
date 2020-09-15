ssh pi@192.168.1.7 "cd ~/Desktop/embedded-object-detection; rm -f -r *"
scp -r  ~/Desktop/cloud/research/guitar/embedded-object-detection pi@192.168.1.7:~/Desktop/

ssh pi@192.168.1.7 "cd ~/Desktop/embedded-object-detection; bash remote_run.sh"
